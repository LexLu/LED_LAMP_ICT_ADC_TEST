/* 
 * File:   adc.h
 * Author: Lex Lu
 *
 * Created on September 3, 2016, 9:24 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "General.h"

#define AD1BufferSizePerChannel    8
#define AD1ChannelNumber   4

#ifdef  FCY
#define TCY ( 1000000000 / FCY )  
#define ADCS_VAL    4                     // TAD = TCY * ( ADCS <7:0> + 1 ), TAD( 10bit mode ) >= 76 ns
#endif    
    
#define AD1BufferSize ( AD1ChannelNumber * AD1BufferSizePerChannel )

#if ( 1 == AD1BufferSizePerChannel )  
#define DMABL_VAL   0
#elif ( 2 == AD1BufferSizePerChannel )  
#define DMABL_VAL   1
#elif ( 4 == AD1BufferSizePerChannel )  
#define DMABL_VAL   2
#elif ( 8 == AD1BufferSizePerChannel )  
#define DMABL_VAL   3
#elif ( 16 == AD1BufferSizePerChannel )  
#define DMABL_VAL   4
#elif ( 32 == AD1BufferSizePerChannel )  
#define DMABL_VAL   5
#elif ( 64 == AD1BufferSizePerChannel )  
#define DMABL_VAL   6
#elif ( 128 == AD1BufferSizePerChannel )  
#define DMABL_VAL   7
#endif

typedef struct _tag_adcSymbols{
    unsigned AD1_Ok:    1;
    unsigned AD1_Rdy:   1;
}AD_Flags;   

extern AD_Flags AD_FLGs;
extern uint16_t uiAD1Result[ AD1ChannelNumber ];
extern uint16_t uiAD1Buffer[ AD1BufferSize ] __attribute__ ( ( eds, space ( dma ) ) ) ;

void DMA0_AD1_Init( void );
void AverageData( void );

extern void AD_Init( void );

extern void AD1ChannelEnable( uint8_t ucAD1Channel );
extern void AD1Go( void );


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

