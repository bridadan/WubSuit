################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/startup_gcc/newlib_stubs.c 

S_SRCS += \
../CMSIS/startup_gcc/startup_a2fxxxm3.s 

OBJS += \
./CMSIS/startup_gcc/newlib_stubs.o \
./CMSIS/startup_gcc/startup_a2fxxxm3.o 

C_DEPS += \
./CMSIS/startup_gcc/newlib_stubs.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/startup_gcc/%.o: ../CMSIS/startup_gcc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\CMSIS -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers\CoreUARTapb -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers\mss_gpio -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers\mss_pdma -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers\mss_timer -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\drivers\mss_uart -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\hal -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\hal\CortexM3 -IN:\EECS373\wubsuit_base\SoftConsole\wubsuit_base_MSS_MSS_CM3_0\wubsuit_base_MSS_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O1 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/startup_gcc/%.o: ../CMSIS/startup_gcc/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Assembler'
	arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -specs=bare.specs  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


