CC=gcc
SRC=./src
SRC_FLS=$(wildcard $(SRC)/*.c)
OUT=./out
FINAL=exe.tic-tac-low

REPO_URL=https://github.com/nasccped/tic-tac-low

RESET_ESCAPE=\033[0m
RED_ESCAPE=\033[1;31m
GREEN_ESCAPE=\033[1;32m
YELLOW_ESCAPE=\033[1;33m
BLUE_ESCAPE=\033[1;34m

all:
	@echo Welcome to the Tic-Tac-Low\'s Makefile!
	@echo You can use the following options:
	@echo . make build
	@echo . make run
	@echo . make clean
	@echo You can also check the project repository by going
	@echo to the [$(REPO_URL)] link

build: $(SRC_FLS)
	gcc $^ -o $(OUT)/$(FINAL)

run: $(OUT)/$(FINAL)
	$(OUT)/$(FINAL)

clean: $(OUT)/$(FINAL)
	@rm $^
	@echo "The file is gone :^D"

.PHONY: all build run clean
