Tic Tac Low
===========

Attempt to make a high-performance simulation of tic-tac-toe using
relatively low-level technology (C language was chosen 💀)!

How to Use?
-----------

Here we have two different ways to use this, project:
  1. Using **Docker** and **GNU Make** _(Extremely Recommended)_
  2. Using your own computer where can result in
     compilation/execution bugs

There's a different requirement list and steps for each one of the
ways that you can use the project, use the following `\<details\>`
tag to get more info!

<details>
<summary>Docker 🐳 + Make 🐐</summary>

### Requirements

- [Git](https://git-scm.com/) _(mandatory)_
- [Docker](https://www.docker.com) _(mandatory)_
- [GNU Make](https://www.gnu.org/software/make/) _(optional)_

### Steps

1. Clone the repository + remove git folder:
  ```sh
  git clone https://github.com/nasccped/tic-tac-low
  cd tic-tac-low
  rm -rf .git # use `Remove-Item -Recurse -Force .git` if you're at Windows PowerShell
  ```
2. Within the cloned repo, build the image using the make command:
  ```sh
  make buildimage
  # if you don't have make, try using: `docker build -t tic-tac-low .`
  ```
3. Run the container from the build image:
  ```sh
  make runimage
  # if you don't have make, try using: `docker run -it --name tic-tac-low-container tic-tac-low`
  ```
3. Have fun! If you also want to remove the created image/container, use:
  ```sh
  make cleanimage
  # if you don't have make, try using:
  # `docker rm tic-tac-low-container to remove the container`
  # `docker rmi tic-tac-low to remove the image`
  ```

</details>

<details>
<summary>On your computer 👨‍💻👩‍💻</summary>

### Requirements

- [Git](https://git-scm.com/) _(mandatory)_
- [GNU Make](https://www.gnu.org/software/make/) _(mandatory)_
- [GCC](https://gcc.gnu.org/) _(mandatory)_

The dependencies instalation can difer from OS to OS, so I won't
specify how to get it. Use your **package manager**, **winget**, ...

### Steps

1. Clone the repository + remove git folder:
  ```sh
  git clone https://github.com/nasccped/tic-tac-low
  cd tic-tac-low
  rm -rf .git # use `Remove-Item -Recurse -Force .git` if you're at Windows PowerShell
  ```
2. Within the cloned repo, compile the program using the make command:
  ```sh
  make build
  ```
3. Run the compiled program:
  ```sh
  make run
  ```
3. Have fun! If you also want to remove the created binaires, use:
  ```sh
  make clean
  ```
</details>

> [!CAUTION]
>
> Using Docker is Highly recommended. It's the only way I can
> guarantee it will work on your machine the same way it works on
> mine.
>
> Also, Windows OS is having trouble with the `make clean` command +
> program control flux during runtime! Basically, Running the program
> on Windows can differ from running it on a UNIX like OS, even if
> there's no errors durring compilations. I don't know how to fix it
> and I don't intend. Just learn Docker 🫡
