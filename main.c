/* 
 * File:   main.c
 * Author: Lex Lu
 *
 * Created on September 3, 2016, 9:20 AM
 */
#include "H/General.h"
#include "H/io.h"
#include "H/adc.h"
#include "H/bsp.h"
/*
 * 
 */
int main(int argc, char** argv) {
    Init();
    
    for(;;){
        if( AD_FLGs.AD1_Rdy ){
            AD1ChannelEnable( 0 );
            AD1ChannelEnable( 1 );
            AD1ChannelEnable( 2 );
            AD1ChannelEnable( 3 );
            AD1Go();
        }
    }
    
    return (EXIT_SUCCESS);
}

