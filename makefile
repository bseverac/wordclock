CFLAGS=-W -Wall -ansi -pedantic

pc: pc_cc build common pc_main
test: pc_cc build common pc_test
ino: ino_cc build common ino_main convert_elf

pc_cc:
	$(eval CC=gcc)

ino_cc:
	$(eval CC=avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=22)

convert_elf:
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega328p -o build/main_ino.elf build/main_ino.o  build/clock.o build/board_ino.o build/matrice_ino.o build/master.o -lm
	avr-objcopy -O ihex -R .eeprom build/main_ino.elf ino.hex
	avrdude -v -p m328p -P /dev/ttyACM0 -b115200 -c arduino -U flash:w:ino.hex


pc_main: build/main_i386.o build/board_i386.o build/matrice_i386.o
	$(CC) $^ build/clock.o build/master.o -o main_i386

pc_test: build/test_i386.o build/board_i386.o build/matrice_i386.o
	$(CC) $^ build/clock.o build/master.o -o test_i386

ino_main: build/main_ino.o build/clock.o build/board_ino.o build/matrice_ino.o build/master.o

common: build/clock.o build/master.o

build:
	mkdir build

build/test_i386.o: test_i386.cpp
	$(CC) -o $@ -c $^

build/main_i386.o: main_i386.cpp
	$(CC) -o $@ -c $^

build/main_ino.o: main_ino.cpp
	$(CC) -o $@ -c $^

build/master.o: app/master.cpp
	$(CC) -o $@ -c $^

build/clock.o: models/clock.cpp
	$(CC) -o $@ -c $^

build/board_i386.o: hardware/board_i386.cpp
	$(CC) -o $@ -c $^

build/matrice_i386.o: hardware/matrice_i386.cpp
	$(CC) -o $@ -c $^

build/board_ino.o: hardware/board_ino.cpp
	$(CC) -o $@ -c $^

build/matrice_ino.o: hardware/matrice_ino.cpp
	$(CC) -o $@ -c $^

clean:
	rm -rf build/*.o

clean_all: clean
	rm -rf main_i386
