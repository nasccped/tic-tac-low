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
