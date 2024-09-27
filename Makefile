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
ModsDir         = ./src/mods
ModsFiles       = $(wildcard $(ModsDir)/*.c)
OutDir          = ./out
ObjDir          = $(OutDir)/objs
SourceFiles     = $(wildcard $(SourceDir)/*.c)
ExeName         = tic-tac-low
AbsoluteExeName = $(OutDir)/$(ExeName)
RepoUrl         = https://github.com/nasccped/tic-tac-low


# our not-so important variables
rstEsc = \e[0m
redEsc = \e[0;41m
grnEsc = \e[32m
grnEsc2 = \e[30;42m
yelEsc = \e[1;33m
itlEsc = \e[3m

# when the argument isn't passed
all:
	@printf "\n"                                                                          ;
	@printf "Hi there! $(yelEsc)@nasccped$(rstEsc) here 👋\n"                             ;
	@printf "This is the $(grnEsc)Tic Tac Low$(rstEsc) compile & runner setup!\n"         ;
	@printf "\n"                                                                          ;
	@printf "The task is simple:\n"                                                       ;
	@printf "\n"                                                                          ;
	@printf "    type $(itlEsc)'make build'$(rstEsc): will compile the source code to a\n";
	@printf "                       binary/object file\n"                                 ;
	@printf "\n"                                                                          ;
	@printf "    type $(itlEsc)'make run'$(rstEsc): will... well... run the generated\n"  ;
	@printf "                     file\n"                                                 ;
	@printf "\n"                                                                          ;
	@printf "    type $(itlEsc)'make clear'$(rstEsc): will remove all the output\n"       ;
	@printf "                       generated files\n"                                    ;
	@printf "\n"                                                                          ;
	@printf "    type $(itlEsc)'make help'$(rstEsc): will display some help options\n"    ;
	@printf "\n"                                                                          ;
	@printf  "$(yelEsc)Have fun!$(rstEsc)\n\n"                                            ;



# testing if output directories was already created
# initial start as empty string
thisOutFolderNotExists =

# if this dir have content, it already exists, right? ---------------
ifeq ("$(wildcard $(OutDir))", "")

	# if it doesn't exists, append dir to `mkdir` todos
	thisOutFolderNotExists += $(OutDir)

endif # end conditional ---------------------------------------------


# same of previously mentioned ---------------------------------------
ifeq ("$(wildcard $(ObjDir))", "")

	thisOutFolderNotExists += $(ObjDir)

endif # end conditional ---------------------------------------------



# procedure to generate the exe file
build: $(SourceFiles) $(ModsFiles)
	@printf "\n"                                                          ;
	@if [ ! -z "$(thisOutFolderNotExists)" ]                              ; then \
		printf "It looks like $(redEsc) you are missing $(rstEsc) some"     ;      \
		printf " output folders: "                                          ;      \
		printf "$(itlEsc)"                                                  ;      \
		printf "< $(thisOutFolderNotExists) >"                              ;      \
		printf "$(rstEsc)"                                                  ;      \
		mkdir $(thisOutFolderNotExists)                                     ;      \
		printf "\n"                                                         ;      \
		printf "\n"                                                         ;      \
		printf "We $(grnEsc)will build it$(rstEsc) for you!\n\n"            ;      \
	fi                                                                    ;
	@printf "$(yelEsc)Compilation status:$(rstEsc) \n\n"                  ;
	@for cfile in $^                                                      ; do   \
		printf "  Compiling $(itlEsc)\"$$cfile\"$(rstEsc): "                ;      \
		defname="$${cfile##*/}"; defname="$${defname%%.*}"                  ;      \
		$(CompileCommand) -c $$cfile -o $(ObjDir)/$$defname                 ;      \
		printf "$(grnEsc)DONE!$(rstEsc)\n"                                  ;      \
	done                                                                  ;
	@printf "\n$(yelEsc)Final executable compilation:$(rstEsc) "          ;      \
	$(CompileCommand) -o $(AbsoluteExeName) $(wildcard $(ObjDir)/*)       ;
	@printf "\n  Compilation has been $(grnEsc2) finalized! $(rstEsc)\n\n";
	@printf "Try <$(yelEsc)make run$(rstEsc)> to run the application."    ;
	@printf "\n\n"                                                        ;


# procedure to remove output files
clear:
	@printf "\n"                                                                    ;
	@if [ -d $(OutDir) ]                                                            ; then \
		rm -r $(OutDir)                                                               ;      \
		printf "Output folder $(grnEsc) has been removed! $(rstEsc)\n"                ;      \
	else                                                                                   \
		printf "Output folder $(redEsc)was not found.$(rstEsc) Nothing to remove...\n";      \
	fi                                                                              ;
	@printf "\n"                                                                    ;


# procedure to run our exe file
run:
	@printf "\n"                                                                                                ;
	@if [ -f $(AbsoluteExeName) ]                                                                               ; then \
		cd $(OutDir)                                                                                              ;      \
		./$(ExeName)                                                                                              ;      \
	else                                                                                                               \
		printf "$(AbsoluteExeName) file $(redEsc) was not found! $(rstEsc)\n"                                     ;      \
		printf "You can try:\n"                                                                                   ;      \
		printf "   - $(grnEsc)make clear$(rstEsc) -> $(grnEsc)make build$(rstEsc) -> $(grnEsc)make run$(rstEsc)\n";      \
		printf "   - $(grnEsc)make help$(rstEsc)\n"                                                               ;      \
	fi                                                                                                          ;
	@printf "\n"                                                                                                ;      \


# procedure to show help content
help:
	@printf "\nSomething $(redEsc) went wrong? $(rstEsc) Try these steps:\n"                                           ;
	@printf "\n"                                                                                                       ;
	@printf "   $(yelEsc)To run the project:$(rstEsc)\n"                                                               ;
	@printf "      $(grnEsc)1.$(rstEsc) make clear $(itlEsc)(remove output folders, if it exists)$(rstEsc)\n"          ;
	@printf "      $(grnEsc)2.$(rstEsc) make build $(itlEsc)(rebuild output folders and binaries)$(rstEsc)\n"          ;
	@printf "      $(grnEsc)3.$(rstEsc) make run   $(itlEsc)(run the builded files)$(rstEsc)\n"                        ;
	@printf "\n"                                                                                                       ;
	@printf "\n"                                                                                                       ;
	@printf "   $(yelEsc)Still doesn't work!$(rstEsc)\n"                                                               ;
	@printf "      $(grnEsc)1.$(rstEsc) git fetche --prune $(itlEsc)(will sync local <-> remote repository)$(rstEsc)\n";
	@printf "      $(grnEsc)2.$(rstEsc) try the previously mentioned steps\n"                                          ;
	@printf "\n"                                                                                                       ;
	@printf "\n"                                                                                                       ;
	@printf "   $(yelEsc)Still doesn't work! $(itlEsc)(yeah... again)$(rstEsc)\n"                                      ;
	@printf "      $(grnEsc)o_O$(rstEsc)  Bro, just read the docs/open a issue at $(grnEsc)$(RepoUrl)$(rstEsc)\n"      ;
	@printf "\n"                                                                                                       ;

