CXX      := g++
CXXFLAGS := -std=c++1z -O3
LDFLAGS  := -L/usr/local/lib -L/opt/vc/lib/ -lSDL2 -lbrcmGLESv2 -lfreetype -lbrcmEGL -lflatbuffers
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := ./
TARGET   := dash
INCLUDE  := -I/usr/local/include/freetype2
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
