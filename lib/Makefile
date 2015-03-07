#################
#				#
#	Variables	#
#				#
#################

# Emplacement des librairies STM32CubeF4

STM32Cube = ../../STM32Cube_FW_F4_V1.3.0/


#Compilateur C
CC = arm-none-eabi-gcc

#Programme qui crée les les librairies (libLIBRARY.a)à partir des fichiers compilés (SOURCE.o)
AR=arm-none-eabi-ar

#Options de compilations
# 	-Os – optimize for size
CFLAGS =  -Wall $(TARGET) $(INCLUDE) $(OTHER_OPTIONS) -Os -g

#Précise le processeur cible
TARGET = -mcpu=cortex-m4 -D$(DEVICE)

#Précise le processeur cible (utilisé dans le .h par exemple stm32f407xx.h)
DEVICE =STM32F407xx

#   -mlittle-endian – compile code for little endian target
#   -mthumb – generate core that executes in Thumb states
#  	-mthumb-interwork – generate code that supports calling between the ARM and Thumb instruction sets
# 	-DSTM32F401xE – define target processor (used in device header files)
OTHER_OPTIONS = -mlittle-endian -mthumb #-mthumb-interwork

#Indique au compilateur dans quels répertoires chercher les headers appelés avec la directive de préprocesseur "#include <header.h>"
INCLUDE = $(BASIC_INCLUDES) $(shell find $(STM32Cube)Drivers/ -path "*" -printf "-I%h/\n"|sort -u)#-I../STM32Cube_FW_F4_V1.3.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include/ -I../STM32Cube_FW_F4_V1.3.0/Drivers/CMSIS/Include/ #-I../STM32Cube_FW_F4_V1.3.0/Drivers/STM32F4xx_HAL_Driver/Inc/ -I./headers/ -I../STM32Cube_FW_F4_V1.3.0/Drivers/BSP/STM32F4-Discovery/ -I../STM32Cube_FW_F4_V1.3.0/Drivers/BSP/STM32F4-Discovery/ -I../STM32Cube_FW_F4_V1.3.0/Drivers/BSP/Components/cs43l22/ -I$(STM32Cube)Drivers/BSP/Components/lis3dsh $(shell find ../STM32Cube_FW_F4_V1.3.0/Drivers/ -path "*" -printf "-I%h/\n"|sort -u)

#Répertoires pour les headers requis (core_cm4.h, stm32f4xx.h, stm32f4xx_hal_conf.h, ...)
BASIC_INCLUDES = -I$(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Include/ -I$(STM32Cube)Projects/STM32F4-Discovery/Templates/Inc/ -I$(STM32Cube)Drivers/CMSIS/Include/

#Fichiers sources des librairies à compiler
SRC_HAL_Driver = $(shell find $(STM32Cube)Drivers/STM32F4xx_HAL_Driver/ -name *.c)
SRC_BSP = $(shell find $(STM32Cube)Drivers/BSP/ -name *.c)
SRC_CMSIS = $(shell find $(STM32Cube)Drivers/STM32F4xx_HAL_Driver/ -name *.c)

#Fichiers objets générés à partir des fichiers sources
OBJ_HAL_Driver = $(SRC_HAL_Driver:.c=.o)
OBJ_BSP = $(SRC_BSP:.c=.o)
OBJ_CMSIS = $(SRC_CMSIS:.c=.o)

#################
#				#
#	Règles		#
#				#
#################

all :	libHAL_Driver.a libCMSIS.a libBSP.a

win2unix_paths :
	./win2unix_paths.sh

%.o :	%.c
	$(CC) $(CFLAGS) -c -o $@ $^ -L. -lHAL_Driver
	mv $@ ./bin

compile :
	$(CC) $(CFLAGS) -c -o compiled_file.o $(F)

libHAL_Driver.a : $(OBJ_HAL_Driver)
	$(AR) -r $@ ./bin/*.o
	ranlib ./libHAL_Driver.a

libBSP.a : $(OBJ_BSP)
	$(AR) -r $@ ./bin/*.o
	echo si la tache échoue tenter : 'make win2unix_paths'

libCMSIS.a : $(OBJ_CMSIS)
	$(AR) -r $@ ./bin/*.o
	ranlib ./libHAL_Driver.a

clean :	lclean bclean

lclean :
	rm -f *.a

bclean :
	rm -f ./bin/*
