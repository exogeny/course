# architecture
HOST_ARCH  := $(shell uname -m)
BUILD_TYPE := release
CC := gcc

# Target rules
all: copy dist_clean

%.o: %c
	@$(CC) -c $^ -o $@

pi_mc: pi_mc.o
	@$(CC) -o $@ $^ -fopenmp -Wall

pi_mc_par: pi_mc_par.o random_par.o
	@$(CC) -o $@ $^ -fopenmp -Wall

pi_mc_par_seq: pi_mc_par.o random_seq_lcg.o
	@$(CC) -o $@ $^ -fopenmp -Wall

copy: pi_mc pi_mc_par pi_mc_par_seq
	@$(EXEC) mkdir -p ../../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework2/test3_Pi_mc
	@$(EXEC) cp $^ ../../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework2/test3_Pi_mc

dist_clean:
	@rm -f pi_mc pi_mc_par pi_mc_par_seq
	@rm -f *.o

clean: dist_clean
	@rm -rf ../../../bin/$(HOST_ARCH)/$(BUILD_TYPE)/homework2/test3_Pi_mc
