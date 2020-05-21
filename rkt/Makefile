CXX      := arm-linux-gnueabihf-g++
CXXFLAGS := -fPIC -std=c++11 -O3
LDFLAGS  := \
	--sysroot=/tmp/raspberrypi_root/raspberrypi-tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot \
	-L/opt/vc/lib/ \
	-L/tmp/raspberrypi_root/stage/lib \
	-L/tmp/raspberrypi_root/raspberrypi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/lib \
	-Wl,-rpath-link,/tmp/raspberrypi_root/stage/lib \
	-Wl,-rpath-link,/tmp/raspberrypi_root/raspberrypi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/lib \
	-lSDL2 \
	-lbrcmGLESv2 \
	-lfreetype \
	-lbrcmEGL \
	-lpng \
	-lpthread \
	-lprotobuf \
	-lgrpc \
	-lgrpc++ \
	-lgpr \
	-lgcc_s \
	-lz \
	-lm \
	-lbcm_host \
	-lvcos \
	-lvchiq_arm \
	-lssl \
	-lcrypto \
	-lcares
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := .
TARGET   := dash
INCLUDE  := -I/usr/local/include/freetype2 \
 			-I/opt/vc/include \
 			-I/tmp/raspberrypi_root/raspberrypi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/include/freetype2 \
 			-I/tmp/raspberrypi_root/raspberrypi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/include \
 			-I/tmp/raspberrypi_root/stage/include
SRC      := $(wildcard *.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
