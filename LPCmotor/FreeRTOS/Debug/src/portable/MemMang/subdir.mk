################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/portable/MemMang/heap_3.c 

OBJS += \
./src/portable/MemMang/heap_3.o 

C_DEPS += \
./src/portable/MemMang/heap_3.d 


# Each subdirectory must supply rules for building sources it contributes
src/portable/MemMang/%.o: ../src/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC15XX__ -D__NEWLIB__ -I"C:\Users\Usin\Desktop\Projects\FishSauce\LPCmotor\FreeRTOS\inc" -I"C:\Users\Usin\Desktop\Projects\FishSauce\LPCmotor\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\Usin\Desktop\Projects\FishSauce\LPCmotor\lpc_chip_15xx\inc" -I"C:\Users\Usin\Desktop\Projects\FishSauce\LPCmotor\FreeRTOS\src\include" -I"C:\Users\Usin\Desktop\Projects\FishSauce\LPCmotor\FreeRTOS\src\portable\GCC\ARM_CM3" -I"C:\Users\Usin\Desktop\Projects\FishSauce\LPCmotor\FreeRTOS\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


