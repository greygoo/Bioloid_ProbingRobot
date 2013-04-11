PROJECT=BioloidProbing

CC=avr-gcc
OBJCOPY=avr-objcopy

MMCU=atmega2561

SOURCES=$(PROJECT).c drive.c status.c sensors.c claw.c objects.c
OBJS=$(SOURCES:.c=.o)


CFLAGS=-Wall -g -std=gnu99 -Os -DF_CPU=16000000UL -mmcu=$(MMCU) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LDFLAGS=-Wall -g -std=gnu99 -lm -Os -DF_CPU=16000000UL -mmcu=$(MMCU) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
ROBOTIS_INCLUDE_DIR=../embeded_c_cm510_v1.01/include
ROBOTIS_LIBRARY_DIR=../embeded_c_cm510_v1.01/lib


all: $(PROJECT).hex $(PROJECT).bin


$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -R .eeprom -O binary $(PROJECT).elf $(PROJECT).bin

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -O ihex -Wl,-Map="BioloidCControl.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group $< $(PROJECT).hex

$(PROJECT).elf: $(OBJS)
	$(CC) $(LDFLAGS) -L$(ROBOTIS_LIBRARY_DIR) $^ -lserial -ldynamixel -o $@


%.o: %.c
	$(CC) $(CFLAGS) -I$(ROBOTIS_INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(PROJECT).bin
	rm -f $(PROJECT).hex
	rm -f $(PROJECT).elf
	rm -f $(OBJS)
