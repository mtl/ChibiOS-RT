/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/

#include "input/keyboard/matrix/matrix.h"

uint16_t fwkm_get_data_size( FwIKMatrix * matrix ) {

  return (
    3 * matrix->num_rows * (
      matrix->num_cols / 8 +
      ( matrix->num_cols % 8 ? 1 : 0 )
    )
  );
}

void fwkm_init( FwIKMatrix * matrix ) {
}




/* vi: set et sts=2 sw=2 ts=2: */
