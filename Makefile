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

# procedure to generate the exe file
# build output directory if doesn't exists
build: $(SRC_FILES)                # source files required
	@if [ ! -d $(OUT_DIR) ]; then \
		mkdir $(OUT_DIR); \
	fi
	$(CC) $^ -o $(FINAL_EXE) # command

# procedure to run our exe file
run: $(FINAL_EXE).* # final exe required
	$(FINAL_EXE)      # command
