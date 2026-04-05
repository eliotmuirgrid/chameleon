# Building C/C++ programs (basics)

First stop in `cpp/make/docs/`: read this if you are new to how C and C++ projects turn into programs you can run. You do not need a computer science background: only curiosity.

For many people today, the device that feels most like “the computer” is a phone: you open apps from a grid, update from a store, and never see filenames, folders, or anything called “build.” That is normal. When you use a laptop or desktop, the same habit often carries over: windows, trackpad, browser, and apps. You are not supposed to bump into the machinery that turns program text into something the machine can run.

On macOS, the Terminal application lives under Utilities. Plenty of Mac users go years without opening it; nothing in daily browsing or office work requires it. On Windows, everyday use looks the same: Start menu, apps, File Explorer. Some people, though, remember MS-DOS: a full screen of text where you typed commands like `DIR` or `CD` and the computer answered in text. That memory is useful. Modern Command Prompt or PowerShell on Windows, and Terminal on Mac or Linux, are the same kind of thing: you type a line, press Enter, and the machine does work without a ribbon of buttons. Building C and C++ often happens there, so this guide introduces that world gently before the hardware and file types.

The sections below still move from the hardware up to the files you see in a project, but you can read them with this picture in mind: phone first for daily life, typed commands when you build software.

---

## The command line

A command line is a window where everything happens in text: a prompt (a short line waiting for you), you type a command, press Enter, and more text comes back. No icons for that step, no carousel. If Terminal on a Mac feels foreign, that is expected. If MS-DOS or early Windows sounds familiar, you already know the mood: the computer is listening line by line.

On Windows today, people often use Command Prompt or PowerShell. On macOS or Linux, the app is usually called Terminal. Same idea everywhere.

Why mention it here? C and C++ builds are often driven from a command line: you type commands that start small programs whose job is to build your software (the build tools in the next section). The later docs in this folder show examples like `g++ …` or `make`. You do not need to be an expert. You only need to recognize that window as “where typed commands run,” not as a broken app with no pictures.

A few tiny examples of **invoking** programs that way (not C++ builds yet—just the pattern). The prompt at the start of each line is whatever your shell shows; you type the command after it and press Enter. The lines below the command are what the program prints back.

On macOS or Linux, using a typical Unix-style shell:

```text
$ pwd
/Users/example/work

$ echo Hello
Hello

$ date
Wed Apr  1 09:15:00 EDT 2026
```

`pwd`, `echo`, and `date` are separate programs. Each name is typed first; anything after the name is passed to that program (here, `Hello` for `echo`).

On Windows, Command Prompt uses a different prompt shape, but the same idea:

```text
C:\Users\example> echo Hello
Hello

C:\Users\example> cd
C:\Users\example
```

(`cd` with no folder name often shows the current directory.) PowerShell looks slightly different again; the point is still: **program name, optional arguments, output text**.

---

## What build tools are

When you download an app from a store, someone else already turned source code into a finished program and put it in your hands. When you write C or C++, you start from text files and need other programs whose whole purpose is to transform that text into something the machine can run. Those helpers are build tools. They are not the game or the chat app. They are more like the equipment in a workshop: invisible to most people, but essential while software is being made.

The ones you will see most often are the compiler (reads a `.cpp` or `.c` file and produces an object file), the linker (joins object files into one executable), and often make (follows a recipe so you do not retype long commands every time). You might never have opened any of them before. That is expected. Daily phone or desktop life does not require them; they show up when you compile code, follow a tutorial, or work in this repository.

---

## The CPU

Every phone, tablet, laptop, and desktop has a CPU (central processing unit). That is the main processor chip, the part people often call the machine’s brain. When you open an app, scroll a feed, or type a message, that chip is doing the work. Processor means the same thing in plain language.

Different devices use different CPU families. Many Android phones and iPhones use a design called ARM, tuned for battery life. Many traditional Windows PCs use another family (often Intel style x86). Newer Macs may use ARM too. You do not need to memorize names yet. You only need to know that the chip matters because it speaks a specific kind of instruction.

---

## The executable

An executable is a program in a form the machine can actually run: a file full of instructions meant for a CPU, packaged so the operating system can start it. On Windows, that file often ends in `.exe`. On phones, you rarely see the filename; you tap an icon, but underneath it is still a built program. On many Linux and macOS setups, an executable you run from the command line (see above) might have no extension. It is still one runnable file.

You do not “run” English, and you do not run the C++ text programmers type in an editor. You run the executable, or on a phone the installed app that was built from that work. Everything else in this page exists to explain how text becomes that runnable thing.

---

## Source code

Languages like C and C++ sit between two kinds of “thinking.” People need something we can read, reason about, and edit: something closer to natural structure than a sea of raw numbers. The machine, in contrast, only follows rigid, low level instructions in its own vocabulary. Programming languages in this family are a deliberate compromise: they are meant to be easy for humans to work with, yet strict and formal enough that every construct has a clear meaning. Then the program can be translated faithfully into machine language, the form the CPU understands directly.

Source code is that text: the files you keep in `.c` and `.cpp` (and related headers). The CPU does not execute source code by itself; it runs the output after translation.

---

## Machine code and the compiler

The CPU only understands machine code: very low level instructions in the chip’s native form. A compiler is a program that reads your source code and translates it toward that form. The result of compiling one source file is not yet the whole program; it is usually stored in an object file (next section). Machine code for one CPU family will not run on a different family. That is why “building for” a phone is different from building for an old style PC chip.

---

## Portability: the same language on many machines

C and C++ have another powerful idea baked in: the source code is largely abstracted away from any one piece of hardware. You still have to compile separately for each target. The executable must match the CPU and operating system, but the same program text can be carried from phones to laptops to servers to tiny embedded boards, and compiled again and again for whatever is underneath.

That is why C in particular has kept running everywhere for decades: it is not tied to a single vendor or chip family in the way raw machine code is. The language sits above the metal; compilers and linkers bridge down to each machine. Real projects still adjust for differences between platforms, but the core story holds: one human readable language, many places it can go.

---

## Object files

An object file is one compiled piece of the program: output from compiling a single `.c` or `.cpp` file (plus whatever it pulls in through `#include`). It is not the full runnable program yet. It is like one chapter before the book is bound. On Linux and macOS (and similar systems), object files often end in `.o`. On Windows when using Microsoft’s C++ build tools, the usual suffix is `.obj`.

---

## Headers

Header files (often `.h`) hold declarations: the names, types, and promises that several source files must share so the compiler can check that they agree. The usual definitions (the full bodies of functions, and so on) often live in `.cpp` files instead.

One way to picture a header is the index or catalog for a room full of books: it tells you what exists, how it is titled, and where to look. It does not print every page of every volume. Another is a theater program: it lists the roles and acts, not the whole spoken script. A third is a restaurant menu: it names the dishes and what they are; the kitchen still prepares the full plate when you order. In each case, the header is the short, shared summary; other files carry the rest of the story.

Source files pull headers in with `#include`. Headers can include other headers, so the full dependency picture can grow. Build tools track that.

There is a network effect: each `#include` is a link between files. When one header changes, every source file that includes it, directly or indirectly, may need recompiling. The more links each header has, the wider that ripple spreads.

During the COVID-19 pandemic, public health messaging often emphasized limiting in-person contacts and keeping social circles small: effects propagate along links, and a huge, loose network is harder to trace and contain than a few intentional connections. Header design has the same *shape*: each header should depend on as few other headers as it truly needs (forward declarations, smaller headers, avoiding giant “include everything” umbrellas). That keeps the dependency graph manageable, so one edit does not force half the tree to rebuild and the project stays easier to follow. The point is structural—how many links, how far ripples spread—not the medical context itself.

---

## Linking: from object files to one executable

Linking joins all the object files into one executable: one runnable program, with calls and references wired between the pieces. That final file is what you run (or what gets packaged like an app on a phone).

This repository’s shared makefiles usually compile many `.cpp` / `.c` files to object files, then link every object into a single binary. There is no separate “library archive” step on that path.

---

## What “building” means

Building means the whole pipeline: starting from source code, compiling to object files, then linking into one executable the CPU can run. Small projects hide that behind one command; larger ones repeat the same pattern. The other notes in this folder add the exact compiler flags and `make` automation.

One way to picture that pipeline is a fast-casual line at places like Subway or Chipotle: you move along a counter while each station adds the next layer (bread, fillings, sauces, wrap or bag), and only the last handoff gives you something you can walk away and eat. Your source files are what you bring to the start of the line; the compiler and linker are the stations in sequence—there is no runnable program until the final step. Building software follows the same rhythm: staged steps, each depending on the last, until the CPU has something it can run.

---

## Check your understanding

The points below are not a test. They are prompts you can use **alone or out loud**: if you can answer in plain language, you have likely absorbed the idea. If a question sticks, skim that section again or ask something more specific (see the next subsection).

### Questions to ask yourself

- **Command line:** In one sentence, what is the difference between the *prompt* and the *command* you type? What happens when you press Enter?
- **Build tools:** Name the three kinds of helper this guide called out (compiler, linker, and one more). What job does each do, in order?
- **CPU vs executable:** Why does “the same C++ source file” not automatically run on every device? What has to match between the executable and the hardware?
- **Source vs machine code:** If someone says “the CPU runs my `.cpp` file,” what would you correct?
- **Object files:** After compiling *one* `.cpp` file, do you always have a program you can double-click or run? Why or why not?
- **Headers:** What is the main difference in purpose between a `.h` header and a `.cpp` source file in the usual layout described here?
- **Includes and ripples:** Why might changing a header force more recompilation than changing a `.cpp` file that few other files touch?
- **Linking:** What does the linker add that the compiler already finished when it produced object files?
- **The full pipeline:** In order, name the stages from “text I edited” to “file the OS can launch,” using the words *source*, *object*, *link*, and *executable* where they fit.

### If you want more detail from an AI (ChatGPT, Gemini, and similar)

Large language models can explain things in different words, give extra examples, or walk through commands on a stack similar to yours. They can also be confidently wrong about flags, paths, or your exact setup. Use them as a **conversation partner**, then cross-check anything that affects real builds (compiler manuals, this repo’s make docs, or a colleague).

**Ways to get useful answers**

- Say what you already believe, and ask for a correction: *“I think linking happens before the compiler runs. Is that right? Explain the real order.”*
- Ask for an analogy tied to something you know: *“Explain object files vs executables using an analogy from cooking or music.”*
- Ground the model in your machine: *“I am on macOS with Apple Silicon, using Terminal. In that context, what is an object file and what suffix might I see?”*
- Ask for confusion points: *“What do beginners most often mix up between `#include` and linking? Keep the answer short.”*
- When you need steps, ask for **assumptions**: *“If I have `main.cpp` and `helpers.cpp` in one folder, what is the minimal conceptual sequence of commands to get one executable? Assume g++-style names.”*

**Clarifications worth asking when you are stuck**

- The difference between *compile* and *link*, and why both exist.
- What `#include` actually does before the compiler’s main work.
- Why header dependency graphs matter for **incremental** builds (only rebuilding what changed).
- What “portable source” means versus “portable executable.”

If an answer feels too technical, say so: *“Explain that again without jargon, in under ten sentences.”*

---

## Where to read next

You have walked through, in order: the command line, what build tools are, CPU, executable, source code, machine code and the compiler, portability across hardware, object files, headers, linking, and building. From here:

- [C/C++ compiler concepts](B.compiler-concepts.md): flags such as language standard, include paths, compile only, output names, and dependency files.
- [ccache](D.ccache.md): optional compiler cache on POSIX in this tree.
- [Make concepts](C.make-concepts.md): how `make` decides what to rebuild when.
