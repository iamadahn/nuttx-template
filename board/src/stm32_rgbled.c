/****************************************************************************
 * board/src/stm32_rgbled.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/timers/pwm.h>
#include <nuttx/leds/rgbled.h>
#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "stm32_pwm.h"
#include "weact-stm32f103.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

#define HAVE_RGBLED 1

#ifndef CONFIG_PWM
#  undef HAVE_RGBLED
#endif

#ifndef CONFIG_STM32_TIM1
#  undef HAVE_RGBLED
#endif

#ifndef CONFIG_STM32_TIM2
#  undef HAVE_RGBLED
#endif

#ifndef CONFIG_STM32_TIM4
#  undef HAVE_RGBLED
#endif

#ifndef CONFIG_STM32_TIM1_PWM
#  undef HAVE_RGBLED
#endif

#ifndef CONFIG_STM32_TIM2_PWM
#  undef HAVE_RGBLED
#endif

#ifndef CONFIG_STM32_TIM4_PWM
#  undef HAVE_RGBLED
#endif

#if CONFIG_STM32_TIM1_CHANNEL != RGBLED_RPWMCHANNEL
#  undef HAVE_PWM
#endif

#if CONFIG_STM32_TIM2_CHANNEL != RGBLED_GPWMCHANNEL
#  undef HAVE_PWM
#endif

#if CONFIG_STM32_TIM4_CHANNEL != RGBLED_BPWMCHANNEL
#  undef HAVE_PWM
#endif

#ifdef HAVE_RGBLED

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_rgbled_setup
 *
 * Description:
 *   Initial for support of a connected RGB LED using PWM.
 *
 ****************************************************************************/

int stm32_rgbled_setup(void)
{
  static bool initialized = false;
  struct pwm_lowerhalf_s    *ledr;
  struct pwm_lowerhalf_s    *ledg;
  struct pwm_lowerhalf_s    *ledb;
  struct pwm_info_s info;
  int ret;

  /* Have we already initialized? */

  if (!initialized)
    {
      /* Call stm32_pwminitialize() to get an instance of the PWM interface */

      ledr = stm32_pwminitialize(RGBLED_RPWMTIMER);
      if (!ledr)
        {
          lederr("ERROR: Failed to get the STM32 PWM lower half to LEDR\n");
          return -ENODEV;
        }

      /* Define frequency and duty cycle */

      info.frequency = 100;
      info.duty = 0;

      /* Initialize LED R */

      ledr->ops->setup(ledr);
      ledr->ops->start(ledr, &info);

      /* Call stm32_pwminitialize() to get an instance of the PWM interface */

      ledg = stm32_pwminitialize(RGBLED_GPWMTIMER);
      if (!ledg)
        {
          lederr("ERROR: Failed to get the STM32 PWM lower half to LEDG\n");
          return -ENODEV;
        }

      /* Initialize LED G */

      ledg->ops->setup(ledg);
      ledg->ops->start(ledg, &info);

      /* Call stm32_pwminitialize() to get an instance of the PWM interface */

      ledb = stm32_pwminitialize(RGBLED_BPWMTIMER);
      if (!ledb)
        {
          lederr("ERROR: Failed to get the STM32 PWM lower half to LEDB\n");
          return -ENODEV;
        }

      /* Initialize LED B */

      ledb->ops->setup(ledb);
      ledb->ops->start(ledb, &info);

      /* Register the RGB LED diver at "/dev/rgbled0" */

      ret = rgbled_register("/dev/rgbled0", ledr, ledg, ledb);
      if (ret < 0)
        {
          lederr("ERROR: rgbled_register failed: %d\n", ret);
          return ret;
        }

      /* Now we are initialized */

      initialized = true;
    }

  return OK;
}

#else
#  error "HAVE_RGBLED is undefined"
#endif /* HAVE_RGBLED */
