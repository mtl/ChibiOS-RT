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

/***************************************************************************/
// Static prototypes:

/**
 * @brief   Matrix scanner interface.
 */
typedef struct {
  /**
   * @brief Get a row of matrix data.
   */
  matrix_row_t (*get_row)( uint8_t row );
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

/**
 * @brief   Keyboard matrix interface configuration structure.
 */
typedef struct {
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
  IOBus *                   row_pins;
  /**
   * @brief Array of column pin descriptors.
   * @note  @p IOBus.mask must have only one bit set.
   */
  IOBus *                   col_pins;
  /**
   * @brief Matrix scanner interface.
   */
  KBDMatrixScanner *        scanner;
  /* End of the mandatory fields.*/
} KBDMatrixConfig;

#endif
/* vi: set et sts=2 sw=2 ts=2: */
