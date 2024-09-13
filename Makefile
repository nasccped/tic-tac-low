# -------------------------------------------------------------------
#
# Makefile
#
#     file responsible for store and run `compile shortcuts`
#     also run cmds too
#
# -------------------------------------------------------------------


# our compile consts
CC        = gcc
SRC_DIR   = ./src
OUT_DIR   = ./out
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
FINAL_EXE = $(OUT_DIR)/tic-tac-low


# when the argument isn't passed
all:
	@echo "Hi there!"; \
	echo "" ; \
	echo "You're calling make with no arguments |:^B"


# procedure to generate the exe file
# build output directory if doesn't exists | source files required
build: $(SRC_FILES)
	@if [ ! -d $(OUT_DIR) ]; then \
		mkdir $(OUT_DIR); \
	fi
	$(CC) $^ -o $(FINAL_EXE) # command


# procedure to run our exe file
run: $(FINAL_EXE).* # final exe required
	$(FINAL_EXE)      # command
