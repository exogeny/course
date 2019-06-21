# architecture
HOST_ARCH  := $(shell uname -m)
BUILD_TYPE := release
CC := gcc

# Target rules
targets := $(patsubst %.c, %, $(wildcard *.c))

.c:
	@$(CC) -o $@ $< -fopenmp -Wall
	@$(EXEC) mkdir -p ../../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework2/test1_Pi
	@$(EXEC) cp $@ ../../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework2/test1_Pi

all: $(targets) dist_clean

dist_clean:
	@rm -rf $(targets)

clean: dist_clean
	@rm -rf ../../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework2/test1_Pi
