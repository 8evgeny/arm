# STM32Cube-F3-meson

# needed defines for the HAL Driver
c_args += '-DUSE_HAL_DRIVER'
c_args += '-DUSE_LEGACY'

# internal incdirs and srcsfiles
stm32cube_incdirs = []
stm32cube_srcs    = []

stm32cube_incdirs += include_directories('Drivers/CMSIS/Device/ST/STM32F3xx/Include')
stm32cube_incdirs += include_directories('Drivers/STM32F3xx_HAL_Driver/Inc')
stm32cube_incdirs += include_directories('Drivers/CMSIS/Include')
stm32cube_incdirs += include_directories('Drivers')

# sources
stm32cube_srcs += ['Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/system_stm32f3xx.c']

stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_adc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_adc_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cec.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_comp.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_crc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_crc_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dac.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dac_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_hrtim.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2s.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2s_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_irda.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_iwdg.c']
# stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_msp_template.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_nand.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_nor.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_opamp.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_opamp_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pccard.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pcd.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pcd_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rtc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rtc_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_sdadc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_smartcard.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_smartcard_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_smbus.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_sram.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c']
# stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_timebase_rtc_alarm_template.c']
# stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_timebase_rtc_wakeup_template.c']
# stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_timebase_tim_template.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tsc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_usart.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_wwdg.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_adc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_comp.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_crc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_dac.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_dma.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_exti.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_fmc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_gpio.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_hrtim.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_i2c.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_opamp.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_pwr.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_rcc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_rtc.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_spi.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_tim.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_usart.c']
stm32cube_srcs += ['Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_ll_utils.c']

#=============================================================================#

stm32cube_srcs = files(stm32cube_srcs)

# use the variables stm32cube_srcs and stm32cube_incdirs for the executable
