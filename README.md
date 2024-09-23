Tic Tac Low
===========

Attempt to make a high-performance simulation of tic-tac-toe using
relatively low-level technology (C language was chosen 💀)!

---



## How to Use?

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

Let's do this together:


1. Choose some secure / easy access path at your machine 🔎
  - You can choose the path you think is best
  - Generally, i like to use the **Desktop path**
  - So, you can run `cd "C:\Users\your_username\Desktop"` if you're on
  **Windows**
  - `cd "/home/your_username/desktop"` if you're on **Linux**
  - You can also go to desktop path by:
    - file explorer
    - right click
    - open terminal here

> [!WARNING]
>
> For the **cd command** to work, don't forget to replace
> `your_username` with **your actual username**! OuO


2. Clone the remote repository 📦
  - Use git commands inside terminal to clone this repo:
  ```bash
  git clone https://github.com/nasccped/tic-tac-low
  ```


3. Enter the new folder 🚪
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


4. Build binaries / objects 🧮
  - We'll build our binaries by Makefile script
  - At your terminal, type `make build`. This will:
    - generate the **out/** dir if it doesn't exist
    - build objects / exes by the files located at **src/** dir


5. Run the program 🏃
  - Finally, you can type `make run` to run the program
  - In a few words, this will do a exe call like:
  `.out/executable.exe`
  - If it doesn't work by some reason, you can try:
    - Go to output directory by typing `cd out`
    - Run the exe within the **out/** dir: `executable` or
    `./executable`



---

> [!WARNING]
>
> The project isn't finalized. I uploaded this content just to save my
> progress remotely!
