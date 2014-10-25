/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/

#include "matrix/scanner_a.h"

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
matrix_row_t scanner_a_get_row( uint8_t row ) {
}

/**
 * @brief Initialize the scanner.
 */
void scanner_a_init( KBDMatrixConfig* ) {
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
}

/* vi: set et sts=2 sw=2 ts=2: */
