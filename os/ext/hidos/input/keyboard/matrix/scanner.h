/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/
#if !defined(__FW_IK_SCANNER__)
#define __FW_IK_SCANNER__

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

/*-------------------------------------------------------------------------*/

/**
 * @brief   Static working area allocation for keyboard matrix scanner.
 * @details This macro is used to allocate a static thread working area
 *          for a keyboard matrix scanner.
 *
 * @param[in] scanner   the scanner "class"
 * @param[in] id        the thread identifier
 */
#define FW_IK_MATRIX_SCANNER( scanner, id ) \
  THD_WORKING_AREA( id ## WA, scanner ## WASize )


/**
 * @brief   User threads table entry for keyboard matrix scanner
 * @details This macro is used to emit an entry for the user threads table
 *          to represent a keyboard matrix scanner thread.
 *
 * @param[in] scanner   the scanner "class"
 * @param[in] id        the thread identifier
 * @param[in] name      the thread name (string)
 * @param[in] config    the scanner configuration
 */
#define FW_IK_MATRIX_SCANNER_THD( scanner, id, name, config ) \
  THD_TABLE_ENTRY( id ## WA, name, scanner ## F, config )

/*-------------------------------------------------------------------------*/


/***************************************************************************/
// Static prototypes:

typedef struct fw_ik_matrix FwIKMatrix;

/**
 * @brief   Matrix scanner interface.
 */
typedef struct fw_ik_matrix_scanner {

  /**
   * @brief Keyboard matrix configuration.
   */
  FwIKMatrix * matrix;

} FwIKMatrixScanner;

#endif
/* vi: set et sts=2 sw=2 ts=2: */
