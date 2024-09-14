# -------------------------------------------------------------------
#
# Makefile
#
#     file responsible for store and run `compile shortcuts`
#     also run cmds too
#
# -------------------------------------------------------------------


# our compile consts
CompileCommand  = gcc
SourceDir       = ./src
OutDir          = ./out
SourceFiles     = $(wildcard $(SRC_DIR)/*.c)
ExeName         = tic-tac-low
AbsoluteExeName = $(OUT_DIR)/$(tic-tac-low)


# our not-so important variables
rstEsc = \e[0m
grnEsc = \e[32m
yelEsc = \e[1;33m
itlEsc = \e[3m

# when the argument isn't passed
all:
	@printf "\n";                                                        \
	printf  "Hi there! $(yelEsc)@nasccped$(rstEsc) here 👋\n";           \
	                                                                     \
	printf  "This is the $(grnEsc)Tic Tac Low$(rstEsc) compile & ";      \
	printf  "runner setup!\n\n";                                         \
	                                                                     \
	printf  "The task is simple:\n\n";                                   \
	                                                                     \
	printf  "    type $(itlEsc)'make build'$(rstEsc): will compile the ";\
	printf  "source code to a\n";                                        \
	printf  "                       binary/object ";                     \
	printf  "file\n\n";                                                  \
	printf  "    type $(itlEsc)'make run'$(rstEsc): will... well... ";   \
	printf  "run the generated\n";                                       \
	printf  "                       file\n\n";                           \
	                                                                     \
	printf  "$(yelEsc)Have fun!$(rstEsc)\n\n";



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
