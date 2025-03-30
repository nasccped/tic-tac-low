CC=gcc
DC=docker
SRC=./src
SRC_FLS=$(wildcard $(SRC)/*.c)
OUT=./out
DOCKER_NAMING=tic-tac-low
FINAL=tic-tac-low.exe

REPO_URL=https://github.com/nasccped/tic-tac-low

all:
	@echo Welcome to the Tic-Tac-Low\'s Makefile!
	@echo You can use the following options:
	@echo . make build
	@echo . make run
	@echo . make clean
	@echo You can also check the project repository by going
	@echo to the [$(REPO_URL)] link
	@echo --------------------------------------------------
	@echo Now, you can also build and run the program
	@echo through a docker container. Highly recommended!
	@echo Use the following commands:
	@echo . make buildimage
	@echo .      to build the docker image
	@echo . make runimage
	@echo .      to run the docker container
	@echo . make cleanimage
	@echo .      to delete the container + image

build: $(SRC_FLS)
	@echo The program is being compiled.
	@echo Any error message will be displayed bellow!
	@gcc $^ -o $(OUT)/$(FINAL)

run: $(OUT)/$(FINAL)
	$(OUT)/$(FINAL)

clean: $(OUT)/$(FINAL)
	@rm $^
	@echo "The file is gone :^D"

buildimage:
	$(DC) build -t $(DOCKER_NAMING) .

runimage:
	$(DC) run -it --name $(DOCKER_NAMING)-container $(DOCKER_NAMING)

cleanimage:
	$(DC) rm $(DOCKER_NAMING)-container
	$(DC) rmi $(DOCKER_NAMING)

.PHONY: all build run clean buildimage runimage cleanimage
