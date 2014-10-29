/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/

#include "ch.h"
#include "hal.h"
#include "pal.h"

#include "keyboard/input/matrix/scanner_a.h"

/* Static function prototypes: */
static void select_row( uint8_t, KBDMatrixConfig * );
static void unselect_row( uint8_t, KBDMatrixConfig * );

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
 *
 * @return the scanner interface structure
 */
KBDMatrixScanner * scanner_a() {
  return &scanner;
}

/**
 * @brief Get a row of matrix data.
 *
 * @return the row of data
 */
uint8_t * scanner_a_get_row( uint8_t row ) {
  return NULL;
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
