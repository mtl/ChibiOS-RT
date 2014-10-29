/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/
#if !defined(__KBD_SCANNER__)
#define __KBD_SCANNER__

//#include <stdint.h>
//#include <stdbool.h>
//#include <avr/io.h>
//#include <util/delay.h>
//#include "debug.h"
//#include "led-local.h"
//#include "print.h"
//#include "matrix.h"
//#include "util.h"
//#include "pal.h"
#include "keyboard/input/matrix/matrix.h"

/***************************************************************************/
// Static prototypes:

typedef struct kbd_matrix_config KBDMatrixConfig;

/**
 * @brief   Matrix scanner interface.
 */
typedef struct kbd_matrix_scanner {
  /**
   * @brief Scan a row of matrix data.
   */
  void (*scan_row)( uint8_t, uint8_t[] );
  /**
   * @brief Initialize the scanner.
   */
  void (*init)( KBDMatrixConfig* );
  /**
   * @brief Print the current matrix state.
   */
  void (*print)( void );
  /**
   * @brief Scan the matrix.
   */
  uint8_t (*scan)( void );
} KBDMatrixScanner;

#endif
/* vi: set et sts=2 sw=2 ts=2: */
