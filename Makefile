#################
#               #
#   Variables   #
#               #
#################

# Emplacement des librairies STM32CubeF4

STM32Cube = ../STM32Cube_FW_F4_V1.3.0/


#Compilateur C
CC = arm-none-eabi-gcc

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
INCLUDE = -I$(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Include/ -I./headers/ $(shell find $(STM32Cube)Drivers/ -path "*" -printf "-I%h/\n"|sort -u) $(shell find ./headers/ -path "*" -printf "-I%h/\n"|sort -u)#-I$(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Include/ -I$(STM32Cube)Drivers/CMSIS/Include/ #-I$(STM32Cube)Drivers/STM32F4xx_HAL_Driver/Inc/ -I./headers/ -I$(STM32Cube)Drivers/BSP/STM32F4-Discovery/ -I$(STM32Cube)Drivers/BSP/STM32F4-Discovery/ -I$(STM32Cube)Drivers/BSP/Components/cs43l22/ -I$(STM32Cube)Drivers/BSP/Components/lis3dsh $(shell find $(STM32Cube)Drivers/ -path "*" -printf "-I%h/\n"|sort -u)

#Linker
LINKER = $(STM32Cube)Projects/STM32F4-Discovery/Templates/TrueSTUDIO/STM32F4-Discovery/STM32F407VG_FLASH.ld

#Options pour l'édition de liens
#	-Wl,--gc-sections – enable garbage collection of unused input sections
LDFLAGS = $(TARGET) $(OTHER_OPTIONS) -T$(LINKER) -Wl,--gc-sections

#Lister ci-dessous les répertoires contenant les fichiers sources à compiler (1 variable par répertoire) ET LES AJOUTER A LA VARIABLE SRC !!!!
DIR = ./src/
DIR2 = $(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/

#Fichiers sources à compiler
SRC = $(shell find ./src/ -name *.c) $(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s

#Librairies
LIBS = -lHAL_Driver -lCMSIS -lBSP

#Répertoire contenant les librairies compilées
DIRLIB = ./lib/

#Fichiers objets générés à partir des fichiers sources
OBJ = $(SRC:.c=.o)
OBJ_ASS = $(SRC:.s=.o)

#Fichier exécutable généré
EXEC = ./bin/main.elf

#Convertit le fichier binaire .out au format hexadecimal d'Intel
CONVERT = arm-none-eabi-objcopy -Oihex ./bin/main.elf ./bin/main.hex

#Télécharge notre fichier hexadécimal dans le STM32
#Note: Le chemin d'accès au script peut varier selon les distributions GNU/Linux, vérifiez le contenu du package d'opencd de votre distribution pour trouver le chemin valide.
#Pour ceux du club, choisir entre stm32f4discovery.cfg et stm32f429discovery.cfg
#OLD : FLASH = openocd -f /usr/local/share/openocd/scripts/board/stm32f4discovery.cfg
FLASH = openocd -f /usr/local/share/openocd/scripts/board/stm32f4discovery.cfg  -c "init" -c "reset init" -c "flash write_image erase ./bin/main.hex" -c "reset" -c "shutdown"

#openocd -f board/stm32f4discovery.cfg  -c "init" -c "reset init" -c "flash write_image erase ./build/stm32f4_sample.hex" -c "reset" -c "shutdown"

CONNECT_HW = xterm -e "openocd -f /usr/local/share/openocd/scripts/board/stm32f4discovery.cfg" &
START_GDB = arm-none-eabi-gdb ./bin/main.elf --eval-command="target remote localhost:3333" --eval-command="monitor reset halt" --eval-command="load" --eval-command="b main" --eval-command="c"



#################
#				#
#	Règles		#
#				#
#################


all :	lib build oclean done

build :	compile link convert

#	$^ 	La liste des dépendances
compile :	oclean $(OBJ) $(OBJ_ASS) o2bin

%.o :	%.c
	@ $(CC) $(CFLAGS) -c -o $@ $^

%.o :	%.s
	@ $(CC) $(CFLAGS) -c -o $@ $^
	@ mv $@ ./bin/

o2bin :
	@ mv *.o ./bin/
	
done :
	@echo 'done ! (if no error)'

link :	compile
	@ $(CC) $(LDFLAGS) ./bin/*.o -L$(DIRLIB) $(LIBS) -o $(EXEC)
	@ rm -f *.o

convert :	compile link
	@ $(CONVERT)

flash :
	$(FLASH)

debug :
	$(CONNECT_HW)
	$(START_GDB)

debug1 :
	$(CONNECT_HW)

debug2 :
	$(START_GDB)

%.o :	%.c
	@ $(CC) $(CFLAGS) -c $^

lib:
	make -C ./lib

clean :	oclean bclean

oclean :
	@ rm -f *.o
	@ rm -f ./bin/*.o

lclean :
	rm -f ./lib/*.a
	rm -f ./lib/bin/*.o

bclean :
	rm -f ./bin/main*
