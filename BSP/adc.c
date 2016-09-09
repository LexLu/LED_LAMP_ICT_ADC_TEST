/* 
 * File:   adc.c
 * Author: Lex Lu
 *
 * Created on September 3, 2016, 9:22 AM
 */
#include    "../H/adc.h"
#include    "../H/dma.h"
#include    "../H/interrupt.h"
/*
 * 
 */
AD_Flags    AD_FLGs;
uint8_t     ucADCnt;
uint16_t    uiAD1Result[ AD1ChannelNumber ];
uint16_t    uiAD1Buffer[ AD1BufferSize ] __attribute__ ( ( eds, space ( dma ) ) ) ;

void    AD_Init(){
    AD_FLGs.AD1_Ok  = CLR;
    AD_FLGs.AD1_Rdy = SET;
    ucADCnt = 0;
    
    AD1CON1bits.AD12B   = 0;    //  10-bit, 4-channel ADC operation
    AD1CON1bits.ADSIDL  = 0;    //  Continue module operation in Idle mode
    AD1CON1bits.ASAM    = 1;    //  Sampling begins immediately after last conversion. SAMP bit is auto-set.
    AD1CON1bits.FORM    = 0;    //  Integer ( D OUT = 0000 00DD DDDD DDDD )
    AD1CON1bits.SSRC    = 7;    //  Internal counter ends sampling and starts conversion (auto-convert)
    
    AD1CON2bits.VCFG    = 0;    //  Converter Voltage Reference configured as: Vref+ -> Avdd, Vref- -> Avss
    AD1CON2bits.ALTS    = 0;    //  Always uses channel input selects for Sample A
    AD1CON2bits.BUFM    = 0;    //  Always starts filling buffer from the beginning
    AD1CON2bits.CHPS    = 0;    //  Converts CH0
    //AD1CON1bits.SIMSAM  = 0;    //  Simultaneous Sample Select bit (only applicable when CHPS<1:0> = 01 or 1x)
    AD1CON2bits.CSCNA   = 1;    //  Scan Inputs for CH0+ during Sample MUX A
    AD1CON2bits.SMPI    = 15;   //  ncrements the DMA address after completion of every 16th sample/conversion operation
    
    AD1CON3bits.ADRC    = 0;        //  Clock derived from system clock
    AD1CON3bits.ADCS    = ADCS_VAL; //  ADC Conversion Clock : TAD = TCY * ( ADCS<7:0> + 1 )
    AD1CON3bits.SAMC    = 2;        //  Auto-Sample Time bits : TAD * SAMC<4:0>
    
    AD1CON4bits.DMABL   = DMABL_VAL;    //  Selects Number of DMA Buffer Locations per Analog Input
    
    AD1CON1bits.ADDMABM = 0;    //  DMA buffers are written in Scatter/Gather mode.
    
    DMA0_AD1_Init();
}

void DMA0_AD1_Init(){
    DMA0CONbits.AMODE   = 2;    //  Configure DMA for Peripheral indirect mode
    DMA0CONbits.MODE    = 0;    //  Configure DMA for Continuous, Ping-Pong modes disabled

    DMA0CNT = AD1BufferSize - 1 ;
    
    DMA0PAD = ( uint16_t ) & ADC1BUF0;        //  Point DMA to ADC1BUF0
    
    DMA0REQ = DMA_IRQ_ADC1;   //  Select ADC1 as DMA Request source
    DMA0STA = __builtin_dmaoffset ( & uiAD1Buffer );

    IPC1bits.DMA0IP = IRQ_P4;
    IFS0bits.DMA0IF = 0;    //  Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = SET;  //  Set the DMA interrupt enable bit        
}

void AD1ChannelEnable( uint8_t ucAD1Channel ){
    uint16_t    uiChannelMask = 0x0001;
        
    if ( 15 < ucAD1Channel ){
        uiChannelMask <<= ( ucAD1Channel - 16 );
        AD1CSSH |= uiChannelMask;
    } else {
        uiChannelMask <<= ucAD1Channel;
        AD1CSSL |= uiChannelMask;
    }
    
    ucADCnt++;
}

void AD1Go(){
    while( !AD_FLGs.AD1_Rdy )
        ClrWdt();
    AD1CON2bits.SMPI = ucADCnt - 1;
    AD1CON1bits.ADON = SET;
    
    DMA0CNT = ucADCnt * AD1BufferSizePerChannel - 1;
    DMA0CONbits.CHEN = SET;
    AD_FLGs.AD1_Rdy  = CLR;   
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _DMA0Interrupt ( void ){
    IFS0bits.DMA0IF  = CLR;
    AD1CON1bits.ADON = CLR;
    AverageData();
}

void AverageData(){
    uint8_t i, j;
    
    for( i = 0; i < ucADCnt; i++ ){
        uiAD1Result[i] = 0x0000;
        
        for( j = 0; j < AD1BufferSizePerChannel; j++){
            uiAD1Result[i] += uiAD1Buffer[( i * AD1BufferSizePerChannel ) + j ];
            uiAD1Buffer[ ( i * AD1BufferSizePerChannel ) + j ] = 0x0000;
        }
        
        uiAD1Result[ i ] >>= DMABL_VAL;
    }
    
    ucADCnt = 0;
    AD_FLGs.AD1_Ok   = SET;
    AD_FLGs.AD1_Rdy  = SET;
}