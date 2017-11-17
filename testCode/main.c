/*
 * File:   main.c
 * Author: TylerMatthews
 *
 * Created on November 16, 2017, 5:49 PM
 */

/*
 Tosc = 1/Fosc
Fcy = Fosc/4
MIPS = Fcy/1000000
Tcy = 1/Fcy
Tcy = 4*Tosc
 */

#include <stdio.h>
#include <stdlib.h>

#include <xc.h>

#define FCY 12000000
#define BRATE 9600
#define _XTAL_FREQ 48000000

#pragma config FWDTEN = OFF
#pragma config POSCMD = HS
#pragma config FNOSC = PRIPLL
#pragma config ICS = PGD2

void uart_init();
void oscSetup();
void T1_Setup();
void UARTSend (char data);

int booleans = 0;
volatile int counter = 0;

void main(void) {
    char temp = 0b00000000;
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 1;
    oscSetup();
    T1_Setup();
    uart_init();
    
    
    
    while (1){
        printf("test");
        if (counter == 100){
            UARTSend(temp);
            temp = temp + 1;
            counter = 0;
            
            if (temp == 10){
                temp = 0;
            }
           
            if(booleans == 1){
                booleans = 0;
            }else{
                booleans = 1;
            }
            
           LATBbits.LATB9 = booleans;
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
/*  
    OSCCONbits.NOSC = 0b011;
    OSCCONbits.IOLOCK = 0;
    OSCCONbits.CLKLOCK = 0;
  */  
    
    
    PLLFBDbits.PLLDIV = 32; //M = 32
    CLKDIVbits.PLLPOST = 1; // N2 = 4
    CLKDIVbits.PLLPRE = 0; //N1 = 2

    // Clock switching to incorporate PLL
    __builtin_write_OSCCONH(0x03);  // Initiate Clock Switch to Primary
             // Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(0x01);  // Start clock switching
    while (OSCCONbits.COSC != 0b011); // Wait for Clock switch to occur
    // Wait for PLL to lock
    while(OSCCONbits.LOCK!=1);
}

void UARTSend (char data){

    while(!U1STAbits.TRMT);  // hold the program till TX buffer is free
    U1TXREG = data; //Load the transmitter buffer with the received value
}

void T1_Setup(void){
   
    T1CON = 0;
    T1CONbits.TSIDL = 0;
    T1CONbits.TCS = 0;
    //T1CONbits.TSYNC = 1;
    T1CONbits.TCKPS = 0b11; // Prescaler set 1:256
    
    IEC0bits.T1IE = 1;
    PR1 = 1875;
    T1CONbits.TON = 1;
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void){
    
    counter = counter +1 ;
    IFS0bits.T1IF = 0;
}