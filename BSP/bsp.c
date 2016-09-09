/* 
 * File:   bsp.c
 * Author: TOPTEC
 *
 * Created on September 3, 2016, 11:23 AM
 */
#include "../H//General.h"
#include "../H/bsp.h"
#include "../H/adc.h"
#include "../H/io.h"
/*
 * 
 */

void Init(){
    OSC_Init();
    AD_Init();
    IO_Init();
}

void OSC_Init(){   
    PLLFBD = 0x003F;
    CLKDIV = 0x0001;
    CLKDIVbits.PLLPRE  = 0x01;
    CLKDIVbits.PLLPOST = 0x00;
    
    __builtin_write_OSCCONH( 0b01 );
    __builtin_write_OSCCONL( 0x01 );
 
    OSCTUN = 0x0000;
     
     // Wait for Clock switch to occur
    while ( OSCCONbits.OSWEN ) { };
    
    //  Check Current Oscillator 
    while ( OSCCONbits.NOSC != OSCCONbits.COSC ) { };
    
    // Wait for PLL to lock
    while ( !OSCCONbits.LOCK ) { };
    
    //  Enable Watch Dog Timer
    RCONbits.SWDTEN = SET;      
}