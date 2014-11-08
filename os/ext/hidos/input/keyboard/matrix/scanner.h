/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/
#if !defined(__KBD_SCANNER__)
#define __KBD_SCANNER__

//#include <stdint.h>
#include <stdbool.h>
//#include <avr/io.h>
//#include <util/delay.h>
//#include "debug.h"
//#include "led-local.h"
//#include "print.h"
//#include "matrix.h"
//#include "util.h"
//#include "pal.h"
#include "input/keyboard/matrix/matrix.h"

/***************************************************************************/
// Static prototypes:

typedef struct kbd_matrix KBDMatrix;

/**
 * @brief   Matrix scanner interface.
 */
typedef struct kbd_matrix_scanner {
  /**
   * @brief Keyboard matrix configuration.
   */
  KBDMatrix * matrix;
  /**
   * @brief Print the current matrix state.
   */
  void (*print)( struct kbd_matrix_scanner * );
  /**
   * @brief Scan the matrix.
   */
  uint8_t (*scan)( struct kbd_matrix_scanner * );
} KBDMatrixScanner;

#endif
/* vi: set et sts=2 sw=2 ts=2: */
