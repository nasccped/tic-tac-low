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
ObjDir          = $(OutDir)/objs
SourceFiles     = $(wildcard $(SourceDir)/*.c)
ExeName         = tic-tac-low
AbsoluteExeName = $(OUT_DIR)/$(tic-tac-low)


# our not-so important variables
rstEsc = \e[0m
redEsc = \e[1;41m
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



# testing if output directories was already created
# initial start as empty string
thisOutFolderNotExists =

# if this dir have content, it already exists, right? ---------------
ifeq ("$(wildcard $(OutDir))", "")

	# if it doesn't exists, append dir to `mkdir` todos
	thisOutFolderNotExists += $(OutDir)

endif # end conditional ---------------------------------------------


# same of previouly mentioned ---------------------------------------
ifeq ("$(wildcard $(ObjDir))", "")

	thisOutFolderNotExists += $(ObjDir)

endif # end conditional ---------------------------------------------



# procedure to generate the exe file
# build output directory if doesn't exists | source files required
build: $(SourceFiles)
	@printf "\n";                                                      \
	if [ ! -z "$(thisOutFolderNotExists)" ] ; then                     \
		printf "It looks like $(redEsc) you are missing $(rstEsc) some"; \
		printf " output folders: "; \
		printf "$(itlEsc)"; \
		printf "< $(thisOutFolderNotExists) >";\
		printf "$(rstEsc)"; \
	fi;                                                                \
	printf "\n";

# procedure to run our exe file
run: $(FINAL_EXE).* # final exe required
	$(FINAL_EXE)      # command
