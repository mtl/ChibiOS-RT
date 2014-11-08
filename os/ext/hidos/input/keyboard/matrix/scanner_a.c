/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/

#include <avr/pgmspace.h>
#include <util/delay.h>

#include "nil.h"
#include "hal.h"
#include "pal.h"

#include "input/keyboard/matrix/scanner_a.h"

/* Static function prototypes: */
static void get_pin( ioportid_t *, uint_fast8_t *, IOBus [], uint8_t, bool );
static void init( FwIKMatrixScanner* );
static void print( FwIKMatrixScanner* );
static void select_row( FwIKMatrixScanner*, uint8_t );
static uint8_t scan( FwIKMatrixScanner* );
static void scan_row( FwIKMatrixScanner*, uint8_t, uint8_t[] );
static void unselect_row( FwIKMatrixScanner*, uint8_t );

/**
 * @brief   The thread function for a Scanner A thread.
 * @details This function is declared noreturn and its signature has a void
 *          return type.
 *
 * @param[in] arg       unused (type void *)
 */
THD_FUNCTION( fwIKMatrixScannerAF, arg ) {
}






/**
 * @brief Get information about a matrix row or column pin.
 *
 * @param[out] portid the pin's I/O port
 * @param[out] offset the bit position of the pin on the I/O port
 * @param[in] pins the array of matrix pin definitions
 * @param[in] number the row or column number
 * @param[in] use_pgm whether or not to read from PROGMEM
 */
static void get_pin(
    ioportid_t * portid, uint_fast8_t * offset,
    IOBus pins[], uint8_t number, bool use_pgm
) {
  if ( use_pgm ) {

    IOBus * pin = &pins[ number ];

    /* Copy portid from PROGMEM: */
    ioportid_t * pgm_portid = &pin->portid;
    ioportid_t * pid = portid;
    for ( int i = 0; i < sizeof( ioportid_t ); i++ ) {
      *pid++ = pgm_read_byte( pgm_portid + i );
    }

    *offset = pgm_read_byte( &pin->offset );

  } else {
    *portid = pins[ number ].portid;
    *offset = pins[ number ].offset;
  }
}

/**
 * @brief Initialize the scanner.
 *
 * @param[in] self the keyboard matrix scanner
 */
static void init( FwIKMatrixScanner * self ) {

  // To use PORTF, disable JTAG by writing JTD bit twice within four cycles:
  /*MCUCR |= (1<<JTD);*/
  /*MCUCR |= (1<<JTD);*/
    
  /* Initialize rows: */
  FwIKMatrix * matrix = self->matrix;
  uint8_t num_rows = matrix->num_rows;
  for ( uint8_t row = 0; row < num_rows; row++ ) {
    unselect_row( self, row );
  }

  /* Initialize columns: */
  IOBus (*col_pins)[] = matrix->col_pins;
  uint8_t num_cols = matrix->num_cols;
  uint_fast8_t offset;
  ioportid_t portid;
  bool use_pgm = matrix->progmem;
  for ( uint8_t col = 0; col < num_cols; col++ ) {

    get_pin( &portid, &offset, *col_pins, col, use_pgm );
    palSetPadMode( portid, offset, PAL_MODE_INPUT_PULLUP );
  }

/*
  // initialize matrix state: all keys off
  for ( uint8_t i=0; i < MATRIX_ROWS; i++ ) {
    matrix[ i ] = (matrix_row_t) 0;
    matrix_debouncing[ i ] = (matrix_row_t) 0;
  }
*/

}

/**
 * @brief Print the current matrix state.
 *
 * @param[in] self the keyboard matrix scanner
 */
static void print( FwIKMatrixScanner * self ) {
}

/**
 * @brief   Select a row to be scanned.
 * @details Output low (DDR:1, PORT:0) to select.
 *
 * @param[in] self the keyboard matrix scanner
 * @param[in] row the number of the row to select
 *
 * @notapi
 */
static void select_row( FwIKMatrixScanner * self, uint8_t row ) {

  FwIKMatrix * matrix = self->matrix;
  uint_fast8_t offset;
  ioportid_t portid;

  get_pin( &portid, &offset, *matrix->row_pins, row, matrix->progmem );
  palSetPadMode( portid, offset, PAL_MODE_OUTPUT_PUSHPULL );
  palWritePad( portid, offset, PAL_LOW );
}

/**
 * @brief Scan the matrix.
 *
 * @param[in] self the keyboard matrix scanner
 */
static uint8_t scan( FwIKMatrixScanner * self ) {
  return 0;
}

/**
 * @brief Get a row of matrix column data.
 *
 * @param[in] self the keyboard matrix scanner
 * @param[in] row the number of the row to scan
 * @param[out] columns the column data
 *
 * @note Column 0 is the LSb of @p columns[0].
 * @note Column 8 is the LSb of @p columns[1].  Etc.
 *
 * @return the row of data
 */
static void scan_row( FwIKMatrixScanner * self, uint8_t row, uint8_t columns[] ) {

  FwIKMatrix * matrix = self->matrix;
  uint_fast8_t offset;
  ioportid_t portid;
  bool use_pgm = matrix->progmem;

  select_row( self, row );
  _delay_us( 30 );  // without this wait read unstable value.

  uint8_t col_bit = 0;
  uint8_t col_byte = 0;
  uint8_t col_byte_offset = 0;

  IOBus (*col_pins)[] = matrix->col_pins;
  uint8_t num_cols = matrix->num_cols;
  for ( uint8_t col = 0; col < num_cols; col++ ) {

    if ( col_bit++ < 8 ) {
      col_byte <<= 1;
    } else {
      columns[ col_byte_offset++ ] = col_byte;
      col_bit = 1;
      col_byte = 0;
    }

    get_pin( &portid, &offset, *col_pins, col, use_pgm );
    col_byte |= palReadPad( portid, offset );
  }

  unselect_row( self, row );
}

/**
 * @brief Get the scanner interface.
 *
 * @param[out] self the matrix scanner
 * @param[in] matrix the key matrix
 */
void scanner_a( FwIKMatrixScanner * self, FwIKMatrix * matrix ) {

  self->matrix = matrix;
  /*self->print = &print;*/
  /*self->scan = &scan;*/

  init( self );
}

/**
 * @brief   Unselect a row (to initialize or after scanning).
 * @details Hi-Z input (DDR:0, PORT:0) to unselect.
 *
 * @param[in] self the keyboard matrix scanner
 * @param[in] row the number of the row to unselect
 *
 * @notapi
 */
static void unselect_row( FwIKMatrixScanner * self, uint8_t row ) {

  FwIKMatrix * matrix = self->matrix;
  uint_fast8_t offset;
  ioportid_t portid;

  get_pin( &portid, &offset, *matrix->row_pins, row, matrix->progmem );
  palSetPadMode( portid, offset, PAL_MODE_INPUT );
}

/* vi: set et sts=2 sw=2 ts=2: */
