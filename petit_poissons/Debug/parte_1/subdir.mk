################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../parte_1/poissons_1.c 

OBJS += \
./parte_1/poissons_1.o 

C_DEPS += \
./parte_1/poissons_1.d 


# Each subdirectory must supply rules for building sources it contributes
parte_1/%.o: ../parte_1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


