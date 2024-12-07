CC=gcc
SRC=./src
SRC_FLS=$(wildcard $(SRC)/*.c)
OUT=./out
FINAL=tic-tac-low

REPO_URL=https://github.com/nasccped/tic-tac-low

RESET_ESCAPE=\033[0m
RED_ESCAPE=\033[1;31m
GREEN_ESCAPE=\033[1;32m
YELLOW_ESCAPE=\033[1;33m
BLUE_ESCAPE=\033[1;34m

define ptf
	echo "$(1) > $(RESET_ESCAPE)$(2)"
endef

all:
	@echo                                                                            ;
	@$(call ptf,$(BLUE_ESCAPE),"Welcome to the Tic-Tac-Low\'s Makefile!")            ;
	@echo                                                                            ;
	@$(call ptf,$(BLUE_ESCAPE),"You can use the following options:")                 ;
	@echo "        |> make build"                                                    ;
	@echo "        |> make run"                                                      ;
	@echo "        |> make clean"                                                    ;
	@echo                                                                            ;
	@$(call ptf,$(GREEN_ESCAPE),"You can also check the project repository by going");
	@$(call ptf,$(GREEN_ESCAPE),"to the $(REPO_URL) link")                           ;
	@echo                                                                            ;

build: $(SRC_FLS)
	@if ! [ -d $(OUT) ]                                                                ; then \
		echo                                                                             ;      \
		$(call ptf,$(YELLOW_ESCAPE),"Output dir not found. Generating one!")             ;      \
		mkdir $(OUT)                                                                     ;      \
	fi                                                                                 ;
	@echo                                                                              ;
	@if [ -f $(OUT)/$(FINAL) ]                                                         ; then \
		$(call ptf,$(RED_ESCAPE),"It looks like there is already a file called $(FINAL)");      \
		echo                                                                             ;      \
		$(call ptf,$(BLUE_ESCAPE),"Try use \'make clean build\' instead...")             ;      \
	else                                                                                      \
		$(call ptf,$(BLUE_ESCAPE),"Compiling the following files:")                      ;      \
		for fl in $^                                                                     ; do   \
			echo "        |> $$fl"                                                         ;      \
		done                                                                             ;      \
		echo                                                                             ;      \
		$(call ptf,$(YELLOW_ESCAPE),"This can take a while...")                          ;      \
		echo                                                                             ;      \
		$(CC) $^ -o $(OUT)/$(FINAL)                                                      ;      \
		if ! [ -f $(OUT)/$(FINAL) ]                                                      ; then \
			$(call ptf,$(RED_ESCAPE),"Something went wrong...")                            ;      \
		else                                                                                    \
			$(call ptf,$(GREEN_ESCAPE),"Success!")                                         ;      \
			$(call ptf,$(GREEN_ESCAPE),"Try using \'make run\' now!")                      ;      \
		fi                                                                               ;      \
	fi                                                                                 ;
	@echo                                                                              ;

run:
	@echo                                                         ;
	@if ! [ -d $(OUT) ]                                           ; then \
		$(call ptf,$(RED_ESCAPE),"Output dir not found")            ;      \
		echo                                                        ;      \
		$(call ptf,$(YELLOW_ESCAPE),"Use \'make build\' instead")   ;      \
	else                                                                 \
		if ! [ -f $(OUT)/$(FINAL) ]                                 ; then \
			$(call ptf,$(RED_ESCAPE),"Program executable not found!") ;      \
			echo                                                      ;      \
			$(call ptf,$(YELLOW_ESCAPE),"Use \'make build\' instead") ;      \
		else                                                               \
			$(call ptf,$(GREEN_ESCAPE),"The program is ready to run!");      \
			printf "   "                                              ;      \
			for i in 3 2 1                                            ; do   \
				printf " $$i"                                           ;      \
				sleep .5                                                ;      \
			done                                                      ;      \
			echo                                                      ;      \
			echo                                                      ;      \
			$(OUT)/$(FINAL)                                           ;      \
		fi                                                          ;      \
	fi                                                            ;
	@echo                                                         ;

clean:
	@echo                                                                  ;
	@if ! [ -d $(OUT) ]                                                    ; then \
		$(call ptf,$(RED_ESCAPE),"$(OUT) dir was not found")                 ;      \
		$(call ptf,$(RED_ESCAPE),"Nothing to clear")                         ;      \
		$(call ptf,$(RED_ESCAPE),"Exiting!")                                 ;      \
	elif ! [ -f $(OUT)/$(FINAL) ]                                          ; then \
		$(call ptf,$(RED_ESCAPE),"Executable file was not found")            ;      \
		$(call ptf,$(RED_ESCAPE),"Nothing to clear")                         ;      \
		$(call ptf,$(RED_ESCAPE),"Exiting!")                                 ;      \
	else                                                                          \
		$(call ptf,$(YELLOW_ESCAPE),"Executable file was found")             ;      \
		rm $(OUT)/$(FINAL)                                                   ;      \
		if [ -f $(OUT)/$(FINAL)o ]                                           ; then \
			$(call ptf,$(RED_ESCAPE),"Something went wrong...")                ;      \
			$(call ptf,$(RED_ESCAPE),"Exe file could not be removed :^| ")     ;      \
			$(call ptf,$(RED_ESCAPE),"Try removing it manualy:") 				       ;      \
			$(call ptf,$(RED_ESCAPE),"   - cd $(OUT)")           				       ;      \
			$(call ptf,$(RED_ESCAPE),"   - rm $(FINAL)")         				       ;      \
			$(call ptf,$(RED_ESCAPE),"")                         				       ;      \
			$(call ptf,$(RED_ESCAPE),"Removing via file explorer may work too");      \
		else                                                                        \
			$(call ptf,$(GREEN_ESCAPE),"Exe file was successfuly removed!")    ;      \
		fi                                                                   ;      \
	fi
	@echo                                                                  ;

.PHONY: all build run clean
