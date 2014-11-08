/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/
#if !defined(__FW_IK_MATRIX_SCANNER_A__)
#define __FW_IK_MATRIX_SCANNER_A__

#include <stdint.h>
#include "input/keyboard/matrix/scanner.h"

/**
 * @brief   The working area size for a scanner A thread.
 */
#define fwIKMatrixScannerAWASize 128

/***************************************************************************/
// Prototypes:

void fwIKMatrixScannerAF( void * );
void scanner_a( FwIKMatrixScanner *, FwIKMatrix * );

#endif
/* vi: set et sts=2 sw=2 ts=2: */
