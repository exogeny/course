# architecture
HOST_ARCH  := $(shell uname -m)
BUILD_TYPE := release
MPI_CC := mpixx
MPI_CXX := mpicxx

# Target rules
targets := $(patsubst %.c, %, $(wildcard *.c))

.c:
	@$(MPI_CC) -o $@ $<
	@$(EXEC) mkdir -p ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework3
	@$(EXEC) cp $@ ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework3

.cpp:
	@$(MPI_CXX) -o $@ $<
	@$(EXEC) mkdir -p ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework3
	@$(EXEC) cp $@ ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework3

all: $(targets) dist_clean

dist_clean:
	@rm -rf $(targets)

clean: dist_clean
	@rm -rf ../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework3
