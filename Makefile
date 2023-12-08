CC=gcc

ROOT=./src
TARGET_DIR=./bin

vpath %.c $(ROOT)
vpath %.h $(ROOT)/include

main: main.c
	mkdir -p $(TARGET_DIR)
	$(CC) -o $(TARGET_DIR)/$@ $^

clean:
	rm -r $(TARGET_DIR)

debug:
	$(CC) -g -o $(TARGET_DIR)/main main.c
