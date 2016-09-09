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
    AD_Init();
    IO_Init();
}