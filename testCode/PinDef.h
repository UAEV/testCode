/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PINDEF_H
#define	PINDEF_H


//RS485(2) Receive Pin - FTDI
#define RX2_Tris    TRISBbits.TRISB7        //RX2 IO
#define RX2_Lat     LATBbits.LATB7          //RX2 Output
#define RX2_Port    PORTBbits.RB7           //RX2 Input
#define RX2_Pin_Map     RPINR18bits.U1RXR   //Used to set UART2 Recieve to corresponding pin
#define RP7   RPOR11bits.RP7R               //Setting RP7 Peripherial Pin output Function
#define RX2_PIN_SET     7                   //Used to set UART2 Recieve to RP7

//RS485(2) Transmit Pin - FTDI
#define TX2_Tris    TRISBbits.TRISB8        //TX2 IO
#define TX2_Lat     LATCBits.LATB8          //TX2 Output
#define TX2_Port    PORTBbits.RB8           //TX2 Input
#define RP8    RPOR4bits.RP8R               //Setting RP8 Peripherial Pin output Function
#define TX2_OUTPUT      7                   //RPn tied to UART2 Transmit (Use this to set RP8 to Uart2 TX)  

#endif	/* XC_HEADER_TEMPLATE_H */

