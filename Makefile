# -------------------------------------------------------------------
#
# Makefile
#
#     file responsible for store and run `compile shortcuts`
# -------------------------------------------------------------------

# our compile consts
CC        = gcc
SRC_DIR   = ./src
OUT_DIR   = ./out
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
FINAL_EXE = $(OUT_DIR)/executable

# procedure to generate the exe file
build: $(SRC_FILES)        # source files needed
	$(CC) $^ -o $(FINAL_EXE) # command

# procedure to run our exe file
run: $(FINAL_EXE).* # final exe needed
	$(FINAL_EXE)      # command
