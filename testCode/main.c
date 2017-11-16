/*
 * File:   main.c
 * Author: TylerMatthews
 *
 * Created on November 16, 2017, 5:49 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <xc.h>

#define FCY 48000000
#define BRATE 9600
#define _XTAL_FREQ 48000000

void uart_init();
void oscSetup();
void T1_Setup();

int counter = 0;
void main(void) {
    char temp = 0b00000000;
    
    uart_init();
    oscSetup();
    
    
    while (1){
        if (counter == 4){
            UARTSend(temp);
            temp = temp + 1;
            counter = 0;
          
            if (temp == 10){
                temp = 0;
            }
        }
    }
}

void uart_init(){
 
    int temp = ((FCY/BRATE)/16) - 1;
    U1BRG = temp;
    
    // U1MODE Register settings
    U2MODEbits.UARTEN = 1; //Enable UART1
    U2MODEbits.USIDL = 0; //Continue during idle
    U2MODEbits.IREN = 0; //IrDA encoder/decoder disable
    U2MODEbits.RTSMD = 0; //U1RTS in flow control mode
    U2MODEbits.UEN = 0b00; //U1TX and U1RX are enabled and used. UxCTS and UxRTS/BCLK pins controlled by port latches
    U2MODEbits.WAKE = 0; //No wake-up enabled
    U2MODEbits.LPBACK = 0;
    U2MODEbits.ABAUD = 0;
    U2MODEbits.URXINV = 0;
    U2MODEbits.BRGH = 0; //16x baud clock
    U2MODEbits.PDSEL = 0b00; //8bit data - no parity
    U2MODEbits.STSEL = 0;
    
    U2STAbits.URXISEL = 0b00;   //Interrupt when a character is transferred to the Transmit Shift register (this implies there is at least one character open in the transmit buffer)
    U2STAbits.UTXINV = 0;       //0 = UxTX Idle state is ?1?
    U2STAbits.UTXBRK = 0;
    U2STAbits.UTXEN = 1;    //Transmit enable bit
    U2STAbits.URXISEL = 0b00;
    U2STAbits.ADDEN = 0; //Address detect bit
    U2STAbits.OERR = 0;  //Overrun Error Status Bit
    
}
void oscSetup(){   
    //Setting Up External Oscillator
    OSCCONbits.COSC = 0b011;
    OSCCONbits.NOSC = 0b011;
    OSCCONbits.IOLOCK = 0;
    OSCCONbits.CLKLOCK = 1;
    
    
    CLKDIVbits.PLLPRE = 0; //N1 = 2
    CLKDIVbits.PLLPOST = 01; // N2 = 2
    PLLFBDbits.PLLDIV = 0x20; //M = 32

}

void UARTSend (char data){
     while(!U1STAbits.TRMT);  // hold the program till TX buffer is free
    U1TXREG = data; //Load the transmitter buffer with the received value
}

void T1_Setup(void){
    T1CONbits.TON = 1;
    T1CONbits.TSIDL = 0;
    T1CONbits.TCS = 1;
    //T1CONbits.TSYNC = 1;
    T1CONbits.TCKPS = 0b11; // Prescaler set 1:256
    
    PR1 = 0xB71B;
}

void __attribute__((interrupt, auto_psv)) T1Interrupt(void){
    
    counter = counter +1 ;
    
}