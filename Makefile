CC=gcc
CFLAGS=-I$(ROOT)/include -std=c2x

ROOT=./src
TARGET_DIR=./.bin

vpath %.c $(ROOT)
vpath %.h $(ROOT)/include

task_manager: $(ROOT)/*.c
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $(TARGET_DIR)/$@ $^

clean:
	rm -r $(TARGET_DIR)

debug: $(ROOT)/*.c
	$(CC) -g -o $(TARGET_DIR)/debug $^
