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

/* Keyboard state array elements: */
#define KBD_MATRIX_STATE_REPORTED 0
#define KBD_MATRIX_STATE_LATEST 1
#define KBD_MATRIX_STATE_BOUNCING 2

/**
 * @brief   Keyboard matrix structure.
 */
typedef struct kbd_matrix {
  /**
   * @brief Number of rows in the matrix.
   */
  uint8_t                   num_rows;
  /**
   * @brief Number of columns in the matrix.
   */
  uint8_t                   num_cols;
  /**
   * @brief Whether the rows and columns are stored in PROGMEM.
   */
  bool progmem;
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
   * @brief Array of matrix state data.
   */
  uint8_t                   (*state[3])[];
  /* End of the mandatory fields.*/
} KBDMatrix;

#endif
/* vi: set et sts=2 sw=2 ts=2: */
