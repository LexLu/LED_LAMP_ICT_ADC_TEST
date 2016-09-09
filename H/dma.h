/* 
 * File:   dma.h
 * Author: Lex Lu
 *
 * Created on August 26, 2016, 12:42 PM
 */

#ifndef DMA_H
#define	DMA_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DMA_IRQ_INT0    0b0000000
#define DMA_IRQ_IC1     0b0000001
#define DMA_IRQ_OC1     0b0000010
#define DMA_IRQ_IC2     0b0000101
#define DMA_IRQ_OC2     0b0000110
#define DMA_IRQ_TMR2    0b0000111
#define DMA_IRQ_TMR3    0b0001000
#define DMA_IRQ_SPI1    0b0001010
#define DMA_IRQ_U1RX    0b0001011
#define DMA_IRQ_U1TX    0b0001100
#define DMA_IRQ_ADC1    0b0001101
#define DMA_IRQ_ADC2    0b0010101
#define DMA_IRQ_U2RX    0b0011110
#define DMA_IRQ_U2TX    0b0011111
#define DMA_IRQ_SPI2    0b0100001
#define DMA_IRQ_ECAN1RX 0b0100010
#define DMA_IRQ_ECAN2RX 0b0110111
#define DMA_IRQ_DCI     0b0111100
#define DMA_IRQ_ECAN1TX 0b1000110
#define DMA_IRQ_ECAN2TX 0b1000111    




#ifdef	__cplusplus
}
#endif

#endif	/* DMA_H */

