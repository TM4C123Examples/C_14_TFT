INCLUDE_DIRS:= device/include cmsis/include ../include ../retarget/gcc/include 
SOURCE_DIRS:=  device/source ../source ../retarget/gcc/source

#the C files to compile
CFILES:= system_TM4C123.c main.c retarget_tm4c.c serial_stdio.c tft_driver.c tft_hal_tm4c.c
#the assembly files assemble
ASM_FILES:= startup_ARMCM4.S
#the target microcontroller
TCHIP:=TM4C123GH6PM
#The compiler to use
CC=arm-none-eabi-gcc
#LINKER OPTIONS
#The linker script for the microcontroller 
LD_SCRIPTS:= gcc_arm.ld
#the directories for linker files 
LIB_DIRS:= device/
#the libraries to link 
LIB_NAMES:=
#the lirabrary file name
LIB_FILE_NAMES:= $(patsubst %,lib%.a,$(LIB_NAMES))
#linker flags 
LFLAGS:= $(patsubst %,-L%,$(LIB_DIRS)) $(patsubst %,-l%,$(LIB_NAMES)) -T$(LD_SCRIPTS) 
#PREPROCESSOR OPTIONS
#Define macro for all files
DEFINES:= USE_STDPERIPH_DRIVER
DEFINE_FLAGS:=$(patsubst %,-D%,$(DEFINES))
INCLUDE_FLAGS:=$(patsubst %,-I%,$(INCLUDE_DIRS)) 
CFLAGS= -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -Wall -g -ffunction-sections -fdata-sections 
CPPFLAGS= $(INCLUDE_FLAGS) $(DEFINE_FLAGS) -D$(TCHIP) 
vpath %.h $(INCLUDE_DIRS)
vpath %.c $(SOURCE_DIRS)
vpath %.S device/source
vpath %.o objects
vpath %.a $(LIB_DIRS)

COBJECTS:= $(patsubst %.c,%.o,$(CFILES)) 
ASMOBJECTS:= $(patsubst %.S,%.o,$(ASM_FILES))

all: salida.elf 
objects:
	mkdir objects
salida.elf: objects $(COBJECTS) $(ASMOBJECTS) $(LIB_FILE_NAMES)
	$(CC) -Wl,--gc-sections -specs=nano.specs $(CFLAGS) objects/*.o $(LFLAGS) -o $@ ;
	arm-none-eabi-size $@ ;
$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o objects/$@;
$(ASMOBJECTS): %.o: %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o objects/$@;
.PHONY:clean rebuild burn
clean:
	rm -f  *.elf ;
	rm -fr objects ;
rebuild: clean all
burn: salida.elf
	/usr/bin/openocd -fboard/ek-tm4c123gxl.cfg -c"init" -c"reset" -c"sleep 300" -c"reset halt" -c"sleep 300" -c"flash write_image erase salida.elf 0x00 elf" -c"reset" -c"shutdown";
debug: salida.elf
	/usr/bin/openocd -fboard/ek-tm4c123gxl.cfg &> /dev/null & 
	sleep 1 ;
	! echo "reset" | telnet localhost 4444 &> /dev/null ;
	! echo "reset halt" | telnet localhost 4444 &> /dev/null ;
	sleep 0.5 ;
	arm-none-eabi-gdb --tui --eval-command="target remote localhost:3333" salida.elf ;
	! echo "reset" | telnet localhost 4444 &> /dev/null;
	sleep 0.5 ;
	! echo "shutdown" | telnet localhost 4444 &> /dev/null;
	sleep 0.1 ;
