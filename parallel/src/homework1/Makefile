# architecture
HOST_ARCH  := $(shell uname -m)
BUILD_TYPE := release
GCC := cc

# Target rules
all: build

build: homework1 dist_clean

homework1: homework1.c
	@$(EXEC) $(GCC) -o $@ $< -fopenmp
	@$(EXEC) mkdir -p ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)
	@$(EXEC) cp $@ ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)

dist_clean:
	@rm -rf homework1

clean: dist_clean
	@rm -rf ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework1
