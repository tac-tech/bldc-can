CC=gcc
# -g = debug;  -Wall =  enables all compiler's warning messages;  -I = include folders
CFLAGS=-g -Wall -I.
BUILD_DIR ?= ./build

$(BUILD_DIR)/%.o: %.c bldc.h
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

all : $(BUILD_DIR)/bldclog $(BUILD_DIR)/bldccantest $(BUILD_DIR)/bldcconfigure $(BUILD_DIR)/speedtest

$(BUILD_DIR)/bldclog: $(BUILD_DIR)/bldclog.o $(BUILD_DIR)/bldc.o
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/bldccantest: $(BUILD_DIR)/bldccantest.o $(BUILD_DIR)/bldc.o
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/bldcconfigure: $(BUILD_DIR)/bldcconfigure.o $(BUILD_DIR)/bldc.o
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/speedtest: $(BUILD_DIR)/speedtest.o $(BUILD_DIR)/bldc.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)