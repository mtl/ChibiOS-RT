/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/

#include "matrix/scanner_a.h"
#include "pal.h"

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
void scanner_a_init( KBDMatrixConfig * config ) {

  /* Initialize columns.*/
  IOBus * col_pins = config->col_pins;
  for ( int i; i < config->num_cols; i++ ) {
    palSetPadMode(
      col_pins[ i ].portid,
      col_pins[ i ].offset,
      PAL_MODE_INPUT_PULLUP
    );
  }

  /*palSetPadMode( GPIOD, 4, PAL_MODE_OUTPUT_PUSHPULL, );*/
  /*palSetPad( GPIOD, 4 );*/
  /*palClearPad( GPIOD, 4 );*/



    // Input with pull-up(DDR:0, PORT:1)
//    DDRA  &= ~0b00100000;
//    PORTA |=  0b00100000;
//    DDRC  &= ~0b00001111;
//    PORTC |=  0b00001111;
//    DDRD  &= ~0b10011000;
//    PORTD |=  0b10011000;
//    DDRE  &= ~0b11000011;
//    PORTE |=  0b11000011;
//    DDRF  &= ~0b01111111;
//    PORTF |=  0b01111111;
}



    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
    
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for ( uint8_t i=0; i < MATRIX_ROWS; i++ ) {
        matrix[ i ] = (matrix_row_t) 0;
        matrix_debouncing[ i ] = (matrix_row_t) 0;
    }

    // Initialize LED control logic:
    led_init();

    // Initialize the OLED display:
#ifdef DISPLAY_ENABLE
    display_init();
#endif


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
