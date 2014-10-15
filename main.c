/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

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
#include "test.h"
#include "LEDDriver.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  bool testPad = false;
  while (TRUE) {

    palSetPad(GPIOD, GPIOD_LED4);
    chThdSleepMilliseconds(100);
    palClearPad(GPIOD, GPIOD_LED4);

    palSetPad(GPIOD, GPIOD_LED3);
    chThdSleepMilliseconds(100);
    palClearPad(GPIOD, GPIOD_LED3);

    palSetPad(GPIOD, GPIOD_LED5);
    chThdSleepMilliseconds(100);
    palClearPad(GPIOD, GPIOD_LED5);

    palSetPad(GPIOD, GPIOD_LED6);
    chThdSleepMilliseconds(100);
    palClearPad(GPIOD, GPIOD_LED6);

  }
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
  uint8_t *o_fb;

  /*
   * Initialize LedDriver - 150 leds in chain, GPIOA pin 1
   */
  ledDriverInit(30, GPIOA, 0b00000010, &o_fb);
  testPatternFB(o_fb);

  /*
   * Activates the serial driver 1 using the driver default configuration.
   * PA9(TX) and PA10(RX) are routed to USART1.
   */
  sdStart(&SD1, NULL);
  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));
  palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched.
   */
  while (TRUE) {
    if (palReadPad(GPIOA, GPIOA_BUTTON))
      testPatternFB(o_fb);
    chThdSleepMilliseconds(500);
  }
}
