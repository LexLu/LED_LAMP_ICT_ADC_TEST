/* 
 * File:   interrupts.h
 * Author: Lex Lu
 *
 * Created on August 26, 2016, 1:03 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum _tag_IRQ_Priorities{  
    IRQ_DS = 0,
    IRQ_P1,
    IRQ_P2,
    IRQ_P3,
    IRQ_P4,
    IRQ_P5,
    IRQ_P6,        
    IRQ_HI            
} IRQ_Priority;




#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

