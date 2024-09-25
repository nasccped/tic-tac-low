References
==========

This is the `REFERENCE.md` file. Here, I will record the research
sources I used during the development of the project 😉

---

This file is structured by the following architecture:

```markdown

#### Content/Resorce name

Reasons why I had to research this and yada yada yada

- https://link.where/i.got.the/solution
- https://another.link/if.it.needs
- https://i.think/you.already/understand

```

And you can also use our:

<details>

<summary style="font-weight: bold">Table of contents 🔬</summary><br>

- [Makefiles](#makefiles)

  - [gnu make manual](#gnu-make-manual)
  - [conditionals](#conditionals)
  - [directory already Exists](#directory-already-exists)
  - [empty strings](#checking-empty-strings-in-bash)

- [C Lang](#c-lang)

  - [keypress detection](#keypress-detection)

</details>



Content
-------

### Makefiles

#### GNU Make Manual

How can I create a variable inside a script block? How can I updated
it? Why it's so hard? 😭

- [GNU Website](https://www.gnu.org/software/make/manual/make.html)


#### Conditionals

By the looks, I need to performe an `ifeq/ifneq` outside a recipe.

- [GNU Website](https://www.gnu.org/software/make/manual/html_node/Conditional-Syntax.html)


#### Directory Already Exists

I need to test it, store into a string-list variable to use it in a recipe
later. I need to test it outside a recipe previously. 💀

- [GitHub Website](https://github.com/naegelyd/til/blob/master/misc/check-if-directory-exists-in-makefile.md)


#### Checking Empty Strings In Bash

I know... I can just use `ifeq ("x", "")`, but Makefile recipes use
an _bash like_ env to run tasks. 🧑‍🔬

- [Dev.to Website](https://dev.to/dak425/how-to-check-if-a-string-is-empty-in-bash-264l#:~:text=To%20check%20if%20a%20string%20is%20empty%20in%20a%20Bash,it%20is%20greater%20than%200.&text=Alternatively%2C%20you%20can%20check%20if,and%20take%20the%20opposite%20using%20!%20.)


### C Lang

#### Keypress detection

How to detect which key are pressed

- [Youtube Video](https://www.youtube.com/watch?v=FPb1uQUrYQk)
