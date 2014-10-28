/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/
#if !defined(__KBD_MATRIX_SCANNER_A__)
#define __KBD_MATRIX_SCANNER_A__

#include <stdint.h>
#include "keyboard/input/matrix/scanner.h"

/***************************************************************************/
// Prototypes:

KBDMatrixScanner * scanner_a( void );
uint8_t * scanner_a_get_row( uint8_t row );
void scanner_a_init( KBDMatrixConfig* );
void scanner_a_print( void );
uint8_t scanner_a_scan( void );

#endif
/* vi: set et sts=2 sw=2 ts=2: */
