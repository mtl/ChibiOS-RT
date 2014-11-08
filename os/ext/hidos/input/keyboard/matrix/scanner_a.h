/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/
#if !defined(__KBD_MATRIX_SCANNER_A__)
#define __KBD_MATRIX_SCANNER_A__

#include <stdint.h>
#include "input/keyboard/matrix/scanner.h"

/**
 * @brief   The working area size for a scanner A thread.
 */
#define hidIKMatrixScannerAWASize 128

/***************************************************************************/
// Prototypes:

void hidIKMatrixScannerAF( void * );
void scanner_a( KBDMatrixScanner *, KBDMatrix * );

#endif
/* vi: set et sts=2 sw=2 ts=2: */
