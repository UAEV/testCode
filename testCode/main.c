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
#include <xc.h>
#include <p33FJ128GP804.h>
#include <PPS.h>
#include "PinDef.h"

#define FCY 24000000
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
    char temp = 1;
    RX2_Tris = 0;
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 1;
    oscSetup();
    T1_Setup();
    uart_init();
    
    
    
    while (1){
        if (counter == 50){
            //printf("test");

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
//UxBRG=[Fcy/(16*Baud Rate)]-1.
void uart_init(){

    RPOR3bits.RP7R = 0x03;    // Make Pin RP8 U1TX
    U1MODEbits.STSEL = 0; // 1-stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 0; // Low Speed mode
    U1BRG = 155; // BAUD Rate Setting
    U1STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 0; // Disenable UART Tx interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART Tx
}


void UARTSend (char data){
    U1TXREG = 54;
    while(!U1STAbits.TRMT);
  //  IFS1bits.U2TXIF = 0;
}

void oscSetup(){   
    //Setting Up External Oscillator
/*  
    OSCCONbits.NOSC = 0b011;
    OSCCONbits.IOLOCK = 0;
    OSCCONbits.CLKLOCK = 0;
  */  
    
    
    PLLFBDbits.PLLDIV = 0b11110; //M = 32
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