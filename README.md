Tic Tac Low
===========

Attempt to make a high-performance simulation of tic-tac-toe using
relatively low-level technology (C language was chosen 💀)!

How to Use?
-----------

First things first, you'll need to check some:

### Requirements

- [**gcc 🤖**](https://gcc.gnu.org/)

  This will compile the C files on which the program was built

- [**make 🐐**](https://www.gnu.org/software/make/manual/make.html)

  Compile-like tool needed to run _Makefiles_ found within the project

- [**git 🏷️**](https://git-scm.com/)

  One of the most famous version control system. Needed to run
  `git clone ...`

- [**IDE 🖥️**](https://www.redhat.com/en/topics/middleware/what-is-ide) _(optional)_

  Some software that can handle source files, directory-tree and output
  terminal simultaneously. You can also run all commands / program
  at your own terminal (optional, of course)

### Step by Step

1. Clone the remote repository 📦
  - Use git commands inside terminal to clone this repo:
  ```bash
  git clone https://github.com/nasccped/tic-tac-low
  ```

2. Enter the new folder 🚪
  - If you're still on terminal, just type:
  ```bash
  cd ./tic-tac-toe
  ```
  - If you prefer to use some IDE, type:
  ```bash
  # enters the folder
  cd ./tic-tac-toe

  # open current dir within IDE by command
  # 'code .' if using vs code
  # 'nvim .' if using neovim
  # etc...
  #
  # you can also open the project folder by search inside IDE
  ```

3. Have fun!
  - The program isn't ready to be runned. You can type:
  ```bash
  make clean
  make build
  make run
  # the commands above will instantly compile and run the program
  # but, you can also just use:

  make
  # this will display some guide content. We have a `make help` too.
  # isn't soo important but it can help you through a bug behaviour!
  ```

> [!WARNING]
>
> Unfortunately, the `make clean` command does not work with GNU Make
> for Windows OS.
> 
> I don't know exactly why. Maybe I'll fix this soon, but it's not a
> fatal bug :^D
>
> ---
>
> Also, the GitHub repository is the same for both operating systems
> (Windows/Unix), but for some reason, when playing against a bot, it
> may make wrong moves (Windows only). This won't be fixed
