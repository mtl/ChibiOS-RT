/*
    ChibiOS - Copyright (C) 2006-2014 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "pal.h"
#include "test.h"

#include "pal_lld.h"

#include "keyboard/input/matrix/matrix.h"
#include "keyboard/input/matrix/scanner_a.h"

#define KBD_MATRIX_NUM_ROWS    5
#define KBD_MATRIX_NUM_COLS    19

/**
 * @brief Keyboard matrix configuration.
 */
KBDMatrixConfig * matrix_config = &(KBDMatrixConfig){
  .num_rows = KBD_MATRIX_NUM_ROWS,
  .num_cols = KBD_MATRIX_NUM_COLS,
  .row_pins = &(IOBus[]){
    { .portid = IOPORT1, .mask = 0b00000001, .offset = 0 }, /* Row 0 */
    { .portid = IOPORT1, .mask = 0b00000010, .offset = 1 }, /* Row 1 */
    { .portid = IOPORT1, .mask = 0b00000100, .offset = 2 }, /* Row 2 */
    { .portid = IOPORT1, .mask = 0b00001000, .offset = 3 }, /* Row 3 */
    { .portid = IOPORT1, .mask = 0b00010000, .offset = 4 }  /* Row 4 */
  },
  .col_pins = &(IOBus[]){
    { .portid = IOPORT3, .mask = 0b00001000, .offset = 3 }, /* Col  0 */
    { .portid = IOPORT3, .mask = 0b00000100, .offset = 2 }, /* Col  1 */
    { .portid = IOPORT3, .mask = 0b00000010, .offset = 1 }, /* Col  2 */
    { .portid = IOPORT3, .mask = 0b00000001, .offset = 0 }, /* Col  3 */
    { .portid = IOPORT6, .mask = 0b01000000, .offset = 6 }, /* Col  4 */
    { .portid = IOPORT6, .mask = 0b00100000, .offset = 5 }, /* Col  5 */
    { .portid = IOPORT6, .mask = 0b00010000, .offset = 4 }, /* Col  6 */
    { .portid = IOPORT6, .mask = 0b00001000, .offset = 3 }, /* Col  7 */
    { .portid = IOPORT6, .mask = 0b00000100, .offset = 2 }, /* Col  8 */
    { .portid = IOPORT6, .mask = 0b00000010, .offset = 1 }, /* Col  9 */
    { .portid = IOPORT5, .mask = 0b00000010, .offset = 1 }, /* Col 10 */
    { .portid = IOPORT5, .mask = 0b00000001, .offset = 0 }, /* Col 11 */
    { .portid = IOPORT4, .mask = 0b10000000, .offset = 7 }, /* Col 12 */
    { .portid = IOPORT5, .mask = 0b10000000, .offset = 7 }, /* Col 13 */
    { .portid = IOPORT6, .mask = 0b00000001, .offset = 0 }, /* Col 14 */
    { .portid = IOPORT1, .mask = 0b00100000, .offset = 5 }, /* Col 15 */
    { .portid = IOPORT4, .mask = 0b00010000, .offset = 4 }, /* Col 16 */
    { .portid = IOPORT4, .mask = 0b00001000, .offset = 3 }, /* Col 17 */
    { .portid = IOPORT5, .mask = 0b01000000, .offset = 6 }  /* Col 18 */
  }
};

static WORKING_AREA(waThread1, 32);
static msg_t Thread1(void *arg) {

  while (TRUE) {
    palTogglePad(IOPORT2, PORTD_LED1);
    chThdSleepMilliseconds(1000);
  }
  return 0;
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();


  matrix_config->scanner = scanner_a();
  matrix_config->scanner->init( matrix_config );












  palClearPad(IOPORT2, PORTD_LED1);

  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  sdStart(&SD2, NULL);

  /*
   * Starts the LED blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  TestThread(&SD2);
  while(TRUE) {
    chThdSleepMilliseconds(1000);
  }
}
/* vi: set et sts=2 sw=2 ts=2: */
