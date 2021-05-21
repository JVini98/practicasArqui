################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../parte_2/poissons_2.c 

OBJS += \
./parte_2/poissons_2.o 

C_DEPS += \
./parte_2/poissons_2.d 


# Each subdirectory must supply rules for building sources it contributes
parte_2/%.o: ../parte_2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


