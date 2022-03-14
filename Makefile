BUILD ?= ${PWD}/build

CC = gcc

CFLAGS=-I${PWD}/include
SOURCE = $(wildcard ${PWD}/src/*.c)
EXEC = $(BUILD)/tictactoe

$(EXEC):
	@mkdir $(BUILD) 2>/dev/null; true
	@$(CC) -g -O3 $(CFLAGS) $(SOURCE) -o $@

.PHONY: run
run: clean $(EXEC)
	@clear && $(EXEC)

.PHONY:clean
clean:
	@rm -rf $(BUILD)