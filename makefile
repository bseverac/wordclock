CFLAGS=-W -Wall -ansi -pedantic
CFILES = $(wildcard hardware/lib-ino/*.c)
CPPFILES = $(wildcard hardware/*.cpp) $(wildcard models/*.cpp) $(wildcard app/*.cpp) main.cpp
OBJECTS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)
BUILD_OBJECTS = $(addprefix build/,$(OBJECTS))
ino: ino_cc build ino_main convert_elf

ino_cc:
	$(eval CC=avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=22)

convert_elf:
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega328p -o build/main_ino.elf $(BUILD_OBJECTS) -lm
	avr-objcopy -O ihex -R .eeprom build/main_ino.elf ino.hex
	avrdude -v -p m328p -P /dev/cu.usbserial-A104K9ZJ -b57600 -c arduino -U flash:w:ino.hex

ino_main: $(OBJECTS)

build:
	mkdir build
	mkdir build/hardware
	mkdir build/hardware/lib-ino
	mkdir build/models
	mkdir build/app

%.o: %.cpp
	$(CC) -o build/$@ -c $^

%.o: %.c
	$(CC) -o build/$@ -c $^

clean_w:
	rd /S build

clean:
	rm -Rf build

clean_all: clean
	rm -rf main_i386

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = test

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include -arch i386

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra

build/models/time_view.o: models/time_view.cpp
	$(CC)  $(CPPFLAGS) -o $@ -c $^

build/models/time.o: models/time.cpp
	$(CC)  $(CPPFLAGS) -o $@ -c $^

build/models/letter_matrix.o: models/letter_matrix.cpp
	$(CC)  $(CPPFLAGS) -o $@ -c $^

build/models/time_test.o: test/models/time_test.cpp
	$(CC)  $(CPPFLAGS) -o $@ -c $^

build/models/letter_matrix_test.o: test/models/letter_matrix_test.cpp
	$(CC)  $(CPPFLAGS) -o $@ -c $^

unittest: build/models/time_view.o build/models/time_test.o build/models/time.o build/models/time_test.o build/models/letter_matrix_test.o build/models/letter_matrix.o build/gtest_main.a
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
