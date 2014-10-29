/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/

#include <util/delay.h>

#include "ch.h"
#include "hal.h"
#include "pal.h"

#include "keyboard/input/matrix/scanner_a.h"

/* Static function prototypes: */
static void init( KBDMatrixConfig* );
static void print( void );
static void select_row( uint8_t, KBDMatrixConfig* );
static uint8_t scan( void );
static void scan_row( uint8_t, uint8_t[], KBDMatrixConfig* );
static void unselect_row( uint8_t, KBDMatrixConfig* );

/**
 * @brief Scanner A interface structure.
 */
static KBDMatrixScanner scanner = {
  .init  = &init,
  .print  = &print,
  .scan  = &scan,
  .scan_row = &scan_row
};

/**
 * @brief Initialize the scanner.
 */
static void init( KBDMatrixConfig * config ) {

  // To use PORTF, disable JTAG by writing JTD bit twice within four cycles:
  /*MCUCR |= (1<<JTD);*/
  /*MCUCR |= (1<<JTD);*/
    
  /* Initialize rows: */
  for ( uint8_t i = 0; i < config->num_rows; i++ ) {
    unselect_row( i, config );
  }

  /* Initialize columns: */
  IOBus (*col_pins)[] = config->col_pins;
  for ( uint8_t i = 0; i < config->num_cols; i++ ) {
    palSetPadMode(
      (*col_pins)[ i ].portid,
      (*col_pins)[ i ].offset,
      PAL_MODE_INPUT_PULLUP
    );
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
 */
static void print( void ) {
}

/**
 * @brief   Select a row to be scanned.
 * @details Output low (DDR:1, PORT:0) to select.
 *
 * @param[in] row the number of the row to select
 * @param[in] config the matrix configuration
 *
 * @notapi
 */
static void select_row( uint8_t row, KBDMatrixConfig * config ) {

  /* Get port ID and pin offset: */
  IOBus *row_def = &(*config->row_pins)[ row ];
  ioportid_t portid = row_def->portid;
  uint_fast8_t offset = row_def->offset;

  palSetPadMode( portid, offset, PAL_MODE_OUTPUT_PUSHPULL );
  palWritePad( portid, offset, PAL_LOW );
}

/**
 * @brief Scan the matrix.
 */
static uint8_t scan( void ) {
  return 0;
}

/**
 * @brief Get a row of matrix column data.
 *
 * @param[in] row the number of the row to scan
 * @param[out] columns the column data
 *
 * @note Column 0 is the LSB of @p columns[0].
 * @note Column 8 is the LSB of @p columns[1].  Etc.
 *
 * @return the row of data
 */
static void scan_row( uint8_t row, uint8_t columns[], KBDMatrixConfig * config ) {

  select_row( row, config );
  _delay_us( 30 );  // without this wait read unstable value.

  uint8_t col_bit = 0;
  uint8_t col_byte = 0;
  uint8_t col_byte_offset = 0;

  IOBus (*col_pins)[] = config->col_pins;
  for ( uint8_t col = 0; col < config->num_cols; col++ ) {

    if ( col_bit++ < 8 ) {
      col_byte << 1;
    } else {
      columns[ col_byte_offset++ ] = col_byte;
      col_bit = 1;
      col_byte = 0;
    }

    IOBus *col_def = &(*col_pins)[ col ];
    col_byte |= palReadPad( col_def->portid, col_def->offset );
  }

  unselect_row( row, config );
}

/**
 * @brief Get the scanner interface.
 *
 * @return the scanner interface structure
 */
KBDMatrixScanner * scanner_a() {
  return &scanner;
}

/**
 * @brief   Unselect a row (to initialize or after scanning).
 * @details Hi-Z input (DDR:0, PORT:0) to unselect.
 *
 * @param[in] row the number of the row to unselect
 * @param[in] config the matrix configuration
 *
 * @notapi
 */
static void unselect_row( uint8_t row, KBDMatrixConfig * config ) {

  IOBus *row_def = &(*config->row_pins)[ row ];
  palSetPadMode( row_def->portid, row_def->offset, PAL_MODE_INPUT );
}

/* vi: set et sts=2 sw=2 ts=2: */
