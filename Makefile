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
	@printf "\n"                                                                                      ;
	@printf "Hi there! $(yelEsc)@nasccped$(rstEsc) here 👋\n"                                         ;
	@printf "This is the $(grnEsc)Tic Tac Low$(rstEsc) compile & runner setup!\n"                     ;
	@printf "\n"                                                                                      ;
	@printf "The task is simple:\n"                                                                   ;
	@printf ".\n"                                                                                     ;
	@printf "|-  Type $(itlEsc)$(grnEsc)'make build':$(rstEsc) will compile the source code to\n"     ;
	@printf "|                      object files\n"                                                   ;
	@printf "|\n"                                                                                     ;
	@printf "|-  Type $(itlEsc)$(grnEsc)'make compile':$(rstEsc) will compile the object files to a\n";
	@printf "|                        final binary\n"                                                 ;
	@printf "|\n"                                                                                     ;
	@printf "|-  Type $(itlEsc)$(grnEsc)'make run':$(rstEsc) will... well... run the generated\n"     ;
	@printf "|                    binary\n"                                                           ;
	@printf "|\n"                                                                                     ;
	@printf "|-  Type $(itlEsc)$(grnEsc)'make clear':$(rstEsc) will remove all the output\n"          ;
	@printf "|                      generated files\n"                                                ;
	@printf "|\n"                                                                                     ;
	@printf "|-  Type $(itlEsc)$(grnEsc)'make help':$(rstEsc) will display some help options\n"       ;
	@printf "\n"                                                                                      ;
	@printf  "$(yelEsc)Have fun!$(rstEsc)\n\n"                                                        ;



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
	@printf "\n"                                                                    ;
	@if [ ! -z "$(thisOutFolderNotExists)" ]                                        ; then \
		printf "It looks like $(redEsc) you are missing $(rstEsc) some"               ;      \
		printf " output folders: "                                                    ;      \
		printf "$(itlEsc)"                                                            ;      \
		printf "< $(thisOutFolderNotExists) >"                                        ;      \
		printf "$(rstEsc)"                                                            ;      \
		mkdir $(thisOutFolderNotExists)                                               ;      \
		printf "\n"                                                                   ;      \
		printf "\n"                                                                   ;      \
		printf "We $(grnEsc)will build it$(rstEsc) for you!\n\n"                      ;      \
	fi                                                                              ;
	@printf "$(yelEsc)Building objects:$(rstEsc) \n\n"                              ;
	@for cfile in $^                                                                ; do   \
		printf "  $(grnEsc)- $(rstEsc)$(itlEsc)\"$$cfile\"$(rstEsc) build status: "   ;      \
		defname="$${cfile##*/}"; defname="$${defname%%.*}"                            ;      \
		$(CompileCommand) -Wno-fatal-error -c $$cfile -o $(ObjDir)/$$defname          ;      \
		if ! [ -f $(ObjDir)/$$defname ]                                               ; then \
			printf "\nThe building target will be $(redEsc) terminated! $(rstEsc)\n\n"  ;      \
			exit                                                                        ;      \
		fi                                                                            ;      \
		printf "$(grnEsc)DONE!$(rstEsc)\n"                                            ;      \
	done                                                                            ;      \
	printf "\nType <$(yelEsc)make compile$(rstEsc)> to build the final application.";      \
	printf "\n\n"                                                                   ;


compile:
	@printf "\n"                                                                                   ;
	@if [[ -z "$(wildcard $(ObjDir)/*)" ]]                                                         ; then \
		printf "The $(itlEsc)Object Folder$(rstEsc) $(redEsc) is empty / doesn't exists! $(rstEsc)\n";      \
		printf "\nUse <$(yelEsc)make build$(rstEsc)> instead...\n"                                   ;      \
	else                                                                                                  \
		printf "Final $(itlEsc)'.exe'$(rstEsc) compilation status: $(redEsc)"                        ;      \
		$(CompileCommand) $(wildcard $(ObjDir)/*) -o $(AbsoluteExeName)                              ;      \
		if ! [ -f $(AbsoluteExeName) ]                                                               ; then \
			printf "$(rstEsc)\nTry using <$(yelEsc)make help$(rstEsc)>\n"                              ;      \
		else                                                                                                \
			printf "$(rstEsc)$(grnEsc2) SUCCESS! $(rstEsc)\n\n"                                        ;      \
			printf "Now, type <$(yelEsc)make run$(rstEsc)>\n"                                          ;      \
		fi                                                                                           ;      \
	fi                                                                                             ;
	@printf "\n"


# procedure to remove output files
clear:
	@printf "\n"                                                                    ;
	@if [ -d $(OutDir) ]                                                            ; then \
		rm -r $(OutDir)                                                               ;      \
		printf "Output folder $(grnEsc2) has been removed! $(rstEsc)\n"               ;      \
	else                                                                                   \
		printf "Output folder $(redEsc) was not found! $(rstEsc)\n"                   ;      \
		printf "\nNothing to remove...\n"                                             ;      \
	fi                                                                              ;
	@printf "\n"                                                                    ;


# procedure to run our exe file
run:
	@printf "\n"                                                                                                ;
	@if [ -f $(AbsoluteExeName) ]                                                                               ; then \
		cd $(OutDir)                                                                                              ;      \
		if ! [[ -x "$(ExeName)" ]]                                                                                ; then \
			printf "$(grnEsc)Final exe$(rstEsc) file $(redEsc) can't be executed! $(rstEsc)\n\n"                    ;      \
			printf "Maybe it's corrupted. Try <$(yelEsc)make help$(rstEsc)> to get the behaviour fix\n\n"           ;      \
			exit                                                                                                    ;      \
		fi                                                                                                        ;      \
		printf "$(yelEsc)$(ExeName)$(rstEsc) is $(grnEsc)ready to run!$(rstEsc) "                                 ;      \
		sleep 2s                                                                                                  ;      \
		printf "\n\n"                                                                                             ;      \
		./$(ExeName)                                                                                              ;      \
	else                                                                                                               \
		printf "$(grnEsc)Final exe$(rstEsc) file $(redEsc) was not found! $(rstEsc)\n\n"                          ;      \
		printf "You can try <$(yelEsc)make help$(rstEsc)> to get the behaviour fix\n"                             ;      \
	fi                                                                                                          ;      \
	printf "\n"                                                                                                 ;


# procedure to show help content
help:
	@printf "\nSomething $(redEsc) went wrong? $(rstEsc) Try these steps:\n"                                           ;
	@printf "\n"                                                                                                       ;
	@printf "   $(yelEsc)To run the project:$(rstEsc)\n"                                                               ;
	@printf "      $(grnEsc)1.$(rstEsc) make clear   $(itlEsc)(remove output folders, if it exists)$(rstEsc)\n"        ;
	@printf "      $(grnEsc)2.$(rstEsc) make build   $(itlEsc)(rebuild output folders and objects)$(rstEsc)\n"         ;
	@printf "      $(grnEsc)3.$(rstEsc) make compile $(itlEsc)(rebuild binary by objects)$(rstEsc)\n"                  ;
	@printf "      $(grnEsc)4.$(rstEsc) make run     $(itlEsc)(run the final program)$(rstEsc)\n"                      ;
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

