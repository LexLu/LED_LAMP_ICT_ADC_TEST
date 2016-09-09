/* 
 * File:   General.h
 * Author: Lex Lu
 *
 * Created on September 3, 2016, 9:26 AM
 */

#ifndef GENERAL_H
#define	GENERAL_H

#ifdef	__cplusplus
extern "C" {
#endif
#include    <xc.h>
#include    <stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
    
#define FOSC    80000000UL
#define FCY     ( FOSC / 2 )
    
#define CLR false
#define SET true

#ifdef	__cplusplus
}
#endif

#endif	/* GENERAL_H */

