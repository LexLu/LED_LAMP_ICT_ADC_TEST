/* 
 * File:   io.c
 * Author: TOPTEC
 *
 * Created on September 3, 2016, 10:52 AM
 */

#include "../H/io.h"

/*
 * 
 */
void IO_Init(){
    TRISB = 0xFFFF;
    AD1PCFGL = 0x0000;
    AD1PCFGH = 0x0000; 
}

