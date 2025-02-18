/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

//#if NOT_TARGET(STM32F1)
  //#error "Oops! Select an STM32F1 board in 'Tools > Board.'"
//#endif

#include "env_validate.h"

#define BOARD_INFO_NAME      "AC_TRI_F1"
#define DEFAULT_MACHINE_NAME "STM32F103RET6"

#define BOARD_NO_NATIVE_USB

#define DISABLE_DEBUG

// Avoid conflict with TIMER_SERVO when using the STM32 HAL
#define TEMP_TIMER                          5

//
// EEPROM
//
#define FLASH_EEPROM_EMULATION
#define MARLIN_EEPROM_SIZE                  0x1000  // 4KB

#if 0
#if ENABLED(FLASH_EEPROM_EMULATION)
  // SoC Flash (framework-arduinoststm32-maple/STM32F1/libraries/EEPROM/EEPROM.h)
  #define EEPROM_START_ADDRESS (0x8000000UL + (512 * 1024) - 2 * EEPROM_PAGE_SIZE)
  #define EEPROM_PAGE_SIZE     (0x800U)           // 2KB, but will use 2x more (4KB)
  #define MARLIN_EEPROM_SIZE    EEPROM_PAGE_SIZE
#else
  #define MARLIN_EEPROM_SIZE                0x800U  // On SD, Limit to 2KB, require this amount of RAM
#endif
#endif

//
// Limit Switches
//
#if 0
#define X_STOP_PIN                          PA7
#define Y_STOP_PIN                          PC5
#define ZL_STOP_PIN                         PB2
#define ZR_STOP_PIN                         PC6
#define Z_STOP_PIN                          ZL_STOP_PIN
#endif

#define X_MIN_PIN                           PA7
#define X_MAX_PIN                           PC6
#define Y_MIN_PIN                           PC5
#define Y_MAX_PIN                           -1
#define Z_MIN_PIN                           PB2
#define Z_MAX_PIN                           -1

//
// Steppers
//
#define X_ENABLE_PIN                        PC3
#define X_STEP_PIN                          PC2
#define X_DIR_PIN                           PB9

#define Y_ENABLE_PIN                        PC13
#define Y_STEP_PIN                          PB8
#define Y_DIR_PIN                           PB7

#define Z_ENABLE_PIN                        PC14
#define Z_STEP_PIN                          PB6
#define Z_DIR_PIN                           PB5

#define E0_ENABLE_PIN                       PA15
#define E0_STEP_PIN                         PB4
#define E0_DIR_PIN                          PB3

#define Z2_ENABLE_PIN                       PC15
#define Z2_STEP_PIN                         PC0
#define Z2_DIR_PIN                          PC1

//
// Temperature Sensors
//
#define TEMP_0_PIN                          PC4   // T0
#define TEMP_1_PIN                          -1    // T1 PA6 used for power loss
#define TEMP_BED_PIN                        PB0   // TB

//
// Heaters
//
#define HEATER_0_PIN                        PA1  // H0
#define HEATER_1_PIN                        PA8  // H1
#define HEATER_BED_PIN                      PA4  // HB

//
// Fans
//
#define FAN_PIN                             PA0  // FAN
#define FAN0_PIN                            FAN_PIN  // FAN
#define FAN1_PIN                            PA14 // Connected to +24V
#define FAN2_PIN                            -1   // PB1, auto fan for E0
#define CONTROLLER_FAN_PIN                  FAN1_PIN
#define E0_AUTO_FAN_PIN                     PB1

//
// Misc
//
#define LED_CONTROL_PIN                     PA13
#define BEEPER_PIN                          PB15    // used for beeps using on board beeper
//#define LED_PIN                             PA8
//#define POWER_LOSS_PIN                      PA6     // logic level detection
#define FIL_RUNOUT_PIN                      PA5
#define CASE_LIGHT_PIN                      LED_CONTROL_PIN
#define POWER_MONITOR_VOLTAGE_PIN           PA6     // analog level detection
#define MAIN_VOLTAGE_MEASURE_PIN            PA6
#define AUTO_LEVEL_TX_PIN                   PB13
#define AUTO_LEVEL_RX_PIN                   PB12
#define PROBE_TARE_PIN                      AUTO_LEVEL_TX_PIN
#define Z_MIN_PROBE_PIN                     AUTO_LEVEL_RX_PIN
#define NEOPIXEL_PIN                        PB14    // neopixel LED driving pin
#define PROBE_ACTIVATION_SWITCH_PIN         PB2

//
// SD Card
//
#ifndef ONBOARD_SDIO
  #define ONBOARD_SDIO
#endif 

#define SD_DETECT_PIN                         PC7

#ifdef ONBOARD_SDIO
//
// SPI
//
  #define SPI_DEVICE                          -1
  #define SCK_PIN                             -1
  #define MISO_PIN                            -1
  #define MOSI_PIN                            -1
  #define SS_PIN                              -1

//
// SDIO
//
  #define SDIO_READ_RETRIES                   16
  #define SDIO_D0_PIN                         PC8
  #define SDIO_D1_PIN                         PC9
  #define SDIO_D2_PIN                         PC10
  #define SDIO_D3_PIN                         PC11
  #define SDIO_CK_PIN                         PC12
  #define SDIO_CMD_PIN                        PD2

#else

  #undef  SDSS
  #define SOFTWARE_SPI
  #define SS_PIN                   PC11
  #define SDSS                     PC11 // SDIO_D3_PIN
  #define SCK_PIN                  PC12 // SDIO_CK_PIN
  #define MISO_PIN                 PC8  // SDIO_D0_PIN
  #define MOSI_PIN                 PD2  // SDIO_CMD_PIN

#endif

#if HAS_TMC_UART
  /**
   * TMC2209 stepper drivers
   * Hardware serial communication ports.
   */
  #define X_HARDWARE_SERIAL  MSerial2
  #define Y_HARDWARE_SERIAL  MSerial2
  #define Z_HARDWARE_SERIAL  MSerial2
  #define Z2_HARDWARE_SERIAL  MSerial2
  //#define E1_HARDWARE_SERIAL MSerial2

  #define E0_SERIAL_TX_PIN                  PA11
  #define E0_SERIAL_RX_PIN                  PA12
  
  #define E1_SERIAL_TX_PIN                  -1
  #define E1_SERIAL_RX_PIN                  -1

  // Default TMC slave addresses
  #ifndef X_SLAVE_ADDRESS
    #define X_SLAVE_ADDRESS  3
  #endif
  #ifndef Y_SLAVE_ADDRESS
    #define Y_SLAVE_ADDRESS  2
  #endif
  #ifndef Z_SLAVE_ADDRESS
    #define Z_SLAVE_ADDRESS  1
  #endif
  #ifndef Z2_SLAVE_ADDRESS
    #define Z2_SLAVE_ADDRESS  0
  #endif
  #ifndef E0_SLAVE_ADDRESS
    #define E0_SLAVE_ADDRESS 0
  #endif

// Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                    115200
  #define TMC_E0_BAUD_RATE                  19200
#endif
