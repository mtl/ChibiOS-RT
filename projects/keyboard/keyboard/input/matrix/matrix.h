/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/
#if !defined(__KBD_MATRIX__)
#define __KBD_MATRIX__

//#include <stdint.h>
//#include <stdbool.h>
//#include <avr/io.h>
//#include <util/delay.h>
//#include "debug.h"
//#include "led-local.h"
//#include "print.h"
//#include "matrix.h"
//#include "util.h"
#include "pal.h"
#include "keyboard/input/matrix/scanner.h"

/***************************************************************************/
// Static prototypes:

typedef struct kbd_matrix_scanner KBDMatrixScanner;

/**
 * @brief   Keyboard matrix interface configuration structure.
 */
typedef struct kbd_matrix_config {
  /**
   * @brief Number of rows in the matrix.
   */
  uint8_t                   num_rows;
  /**
   * @brief Number of columns in the matrix.
   */
  uint8_t                   num_cols;
  /**
   * @brief Array of row pin descriptors.
   * @note  @p IOBus.mask must have only one bit set.
   */
  IOBus                     (*row_pins)[];
  /**
   * @brief Array of column pin descriptors.
   * @note  @p IOBus.mask must have only one bit set.
   */
  IOBus                     (*col_pins)[];
  /**
   * @brief Matrix scanner interface.
   */
  KBDMatrixScanner *        scanner;
  /* End of the mandatory fields.*/
} KBDMatrixConfig;

#endif
/* vi: set et sts=2 sw=2 ts=2: */
