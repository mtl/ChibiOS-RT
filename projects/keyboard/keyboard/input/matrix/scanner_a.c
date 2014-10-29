/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/

#include "ch.h"
#include "hal.h"
#include "pal.h"

#include "keyboard/input/matrix/scanner_a.h"

/**
 * @brief Scanner A interface structure.
 */
static KBDMatrixScanner scanner = {
  .get_row = &scanner_a_get_row,
  .init  = &scanner_a_init,
  .print  = &scanner_a_print,
  .scan  = &scanner_a_scan
};

/**
 * @brief Get the scanner interface.
 */
KBDMatrixScanner * scanner_a( void ) {
  return &scanner;
}

/**
 * @brief Get a row of matrix data.
 */
uint8_t * scanner_a_get_row( uint8_t row ) {
  return NULL;
}

static void unselect_row( uint8_t row, KBDMatrixConfig * config ) {

  /* Get port ID and pin offset: */
  IOBus *row_def = &(*config->row_pins)[ row ];
  ioportid_t portid = row_def->portid;
  uint_fast8_t offset = row_def->offset;

  /* Hi-Z input: */
  palSetPadMode( portid, offset, PAL_MODE_INPUT );
  palClearPad( portid, offset );
}

static void select_row( uint8_t row, KBDMatrixConfig * config ) {

  /* Get port ID and pin offset: */
  IOBus *row_def = &(*config->row_pins)[ row ];
  ioportid_t portid = row_def->portid;
  uint_fast8_t offset = row_def->offset;

  /* Output low to select the row: */
  palSetPadMode( portid, offset, PAL_MODE_OUTPUT_PUSHPULL );
  palClearPad( portid, offset );
}

/**
 * @brief Initialize the scanner.
 */
void scanner_a_init( KBDMatrixConfig * config ) {

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
void scanner_a_print( void ) {
}

/**
 * @brief Scan the matrix.
 */
uint8_t scanner_a_scan( void ) {
  return 0;
}

/* vi: set et sts=2 sw=2 ts=2: */
