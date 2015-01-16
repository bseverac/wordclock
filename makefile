CFLAGS=-W -Wall -ansi -pedantic

pc: pc_cc build common pc_main
ino: ino_cc build common ino_main convert_elf

pc_cc:
	$(eval CC=g++)

ino_cc:
	$(eval CC=avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=22)

convert_elf:
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega328p -o build/main_ino.elf build/main_ino.o  build/letter_matrix.o build/board_ino.o build/matrice_ino.o build/master.o -lm
	avr-objcopy -O ihex -R .eeprom build/main_ino.elf ino.hex
	avrdude -v -p m328p -P /dev/ttyACM0 -b115200 -c arduino -U flash:w:ino.hex


pc_main: build/main_i386.o build/board_i386.o build/matrice_i386.o
	$(CC) $^ build/time.o build/letter_matrix.o build/master.o -o main_i386

ino_main: build/main_ino.o build/letter_matrix.o build/board_ino.o build/matrice_ino.o build/master.o

common: build/time.o build/letter_matrix.o build/master.o

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

build/time.o: models/time.cpp
	$(CC) -o $@ -c $^

build/letter_matrix.o: models/letter_matrix.cpp
	$(CC) -o $@ -c $^

build/board_i386.o: hardware/board_i386.cpp
	$(CC) -o $@ -c $^

build/matrice_i386.o: hardware/matrice_i386.cpp
	$(CC) -o $@ -c $^

build/board_ino.o: hardware/board_ino.cpp
	$(CC) -o $@ -c $^

build/matrice_ino.o: hardware/matrice_ino.cpp
	$(CC) -o $@ -c $^

clean_w:
	rd /S build
clean:
	rm -rf build/*.o

clean_all: clean
	rm -rf main_i386

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = test

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra

build/time_test.o: test/models/time_test.cpp
	$(CC)  $(CPPFLAGS) -o $@ -c $^

build/letter_matrix_test.o: test/models/letter_matrix_test.cpp
	$(CC)  $(CPPFLAGS) -o $@ -c $^

unittest: build/time_test.o build/time.o build/time_test.o build/letter_matrix_test.o build/letter_matrix.o build/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
build/gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o build/gtest-all.o

build/gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o build/gtest_main.o

gtest.a : build/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

build/gtest_main.a : build/gtest-all.o build/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
