# ##############################################################################
# board/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

set(SRCS stm32_boot.c stm32_bringup.c stm32_spi.c)

if(CONFIG_BOARDCTL)
  list(APPEND SRCS stm32_appinit.c)
  if(CONFIG_BOARDCTL_RESET)
    list(APPEND SRCS stm32_reset.c)
  endif()
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS stm32_buttons.c)
endif()

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS stm32_autoleds.c)
else()
  list(APPEND SRCS stm32_userleds.c)
endif()

if(CONFIG_ADC)
  list(APPEND SRCS stm32_adc.c)
endif()

if(CONFIG_DEV_GPIO)
  list(APPEND SRCS stm32_gpio.c)
endif()

if(CONFIG_PWM)
  list(APPEND SRCS stm32_pwm.c)
endif()

if(CONFIG_SENSORS_HYT271)
  list(APPEND SRCS stm32_hyt271.c)
endif()

if(CONFIG_SENSORS_DS18B20)
  list(APPEND SRCS stm32_ds18b20.c)
endif()

if(CONFIG_RGBLED)
  list(APPEND SRCS stm32_rgbled.c)
endif()

if(CONFIG_MMCSD)
  list(APPEND SRCS stm32_mmcsd.c)
endif()

if(CONFIG_MTD_W25)
  list(APPEND SRCS stm32_w25.c)
endif()

if(CONFIG_MTD_AT24XX)
  if(CONFIG_STM32_I2C1)
    list(APPEND SRCS stm32_at24.c)
  endif()
endif()

if(CONFIG_CAN_MCP2515)
  list(APPEND SRCS stm32_mcp2515.c)
endif()

if(CONFIG_LCD_MAX7219)
  list(APPEND SRCS stm32_max7219.c)
endif()

if(CONFIG_INPUT_NUNCHUCK)
  list(APPEND SRCS stm32_nunchuck.c)
endif()

if(CONFIG_LCD_SSD1306_I2C)
  list(APPEND SRCS stm32_lcd_ssd1306.c)
endif()

if(CONFIG_LCD_ST7567)
  list(APPEND SRCS stm32_lcd_st7567.c)
endif()

if(CONFIG_LCD_PCD8544)
  list(APPEND SRCS stm32_pcd8544.c)
endif()

if(CONFIG_USBDEV)
  list(APPEND SRCS stm32_usbdev.c)
endif()

if(CONFIG_USBMSC)
  list(APPEND SRCS stm32_usbmsc.c)
endif()

target_sources(board PRIVATE ${SRCS})

set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/ld.script")
