################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/src/i2c_func_decl.c \
../Hardware/src/ov2640_regs.c \
../Hardware/src/spi_func_decl.c 

OBJS += \
./Hardware/src/i2c_func_decl.o \
./Hardware/src/ov2640_regs.o \
./Hardware/src/spi_func_decl.o 

C_DEPS += \
./Hardware/src/i2c_func_decl.d \
./Hardware/src/ov2640_regs.d \
./Hardware/src/spi_func_decl.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/src/%.o Hardware/src/%.su Hardware/src/%.cyclo: ../Hardware/src/%.c Hardware/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"/home/ampellicht/STM32CubeIDE/workspace_1.16.1/Capture Image V2/Hardware/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Hardware-2f-src

clean-Hardware-2f-src:
	-$(RM) ./Hardware/src/i2c_func_decl.cyclo ./Hardware/src/i2c_func_decl.d ./Hardware/src/i2c_func_decl.o ./Hardware/src/i2c_func_decl.su ./Hardware/src/ov2640_regs.cyclo ./Hardware/src/ov2640_regs.d ./Hardware/src/ov2640_regs.o ./Hardware/src/ov2640_regs.su ./Hardware/src/spi_func_decl.cyclo ./Hardware/src/spi_func_decl.d ./Hardware/src/spi_func_decl.o ./Hardware/src/spi_func_decl.su

.PHONY: clean-Hardware-2f-src

