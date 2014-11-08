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

/**
 * @brief   Static working area allocation for keyboard matrix scanner.
 * @details This macro is used to allocate a static thread working area
 *          for a keyboard matrix scanner.
 *
 * @param[in] scanner   the scanner "class"
 * @param[in] id        the thread identifier
 */
#define HID_IK_MATRIX_SCANNER( scanner, id ) \
  THD_WORKING_AREA( id ## WA, scanner ## WASize )


/**
 * @brief   User threads table entry for keyboard matrix scanner
 * @details This macro is used to emit an entry for the user threads table
 *          to represent a keyboard matrix scanner thread.
 *
 * @param[in] scanner   the scanner "class"
 * @param[in] id        the thread identifier
 * @param[in] name      the thread name (string)
 * @param[in] arg       the thread function argument
 */
#define HID_IK_MATRIX_SCANNER_THD( scanner, id, name, arg ) \
  THD_TABLE_ENTRY( id ## WA, name, scanner ## F, arg )


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
