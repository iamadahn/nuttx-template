# nuttx-template
NuttX Rtos template with out-of-tree board and app, NuttX Kernel and NuttX Apps being added as submodules.

For this template ```board``` folder contains ported stm32f103-minimum board to WeAct Studio STM32F103C8T6 Bluepill.
The only major difference between them as that onboard LED is connected to PB2 instead of PC13.

However, it's important that you have to define that your board has leds, buttons and/or irq buttons.
An example how to do that is provided in ```board/Kconfig``` file:
```
config ARCH_BOARD_WEACT_STM32F103
	bool "WeAct Studio STM32F103 Board"
	depends on ARCH_CHIP_STM32F103CB
	select ARCH_HAVE_LEDS
	select ARCH_HAVE_BUTTONS
	select ARCH_HAVE_IRQBUTTONS
```
Without that, you won't be able to use listed peripherals, since NuttX doesn't know anything about your board.

Custom app getting registered as application because in ```board/configs/nsh/defconfig``` file ```CONFIG_CUSTOM_APP=y``` is defined. 

To build the template run ./configure.sh and ./build.sh, build artifacts will be located in ```nuttx``` folder.

