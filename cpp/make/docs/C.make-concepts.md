# Make concepts

If you are new to C/C++ builds, start with [Building C/C++ programs (basics)](A.building-cpp-basics.md) (compile vs link, objects, executables). Then read [C/C++ compiler concepts](B.compiler-concepts.md) for the usual compiler flags, then return to this file for how `make` automates the graph. [ccache](D.ccache.md) is optional: how the compiler cache speeds repeated compiles on POSIX in this tree; you can read it any time after the basics.

Suggested order (filenames use `A.`–`D.` prefixes for the same sequence):

1. [A.building-cpp-basics.md](A.building-cpp-basics.md) — pipeline in plain language.
2. [B.compiler-concepts.md](B.compiler-concepts.md) — `-std=`, `-MMD`, `-I`, `-c`, `-o`, linking on the command line.
3. This document (`C.make-concepts.md`): dependency trees, pattern rules, `wildcard`, `.d` files, `make -j`, and this repo’s shared makefiles.
4. [D.ccache.md](D.ccache.md): optional; how the cache speeds up repeated compiles.

---

A build is a web of “before” relationships: which files must be up to date before others can be built. `make` is the tool that reads those relationships, compares file times, and runs only the commands that are still needed. This note walks from that idea to the patterns used in this repository: variables, pattern rules, discovering sources, linking one binary, header dependencies, and parallel runs.

You will read: what a dependency picture is; what `make` does and how it chooses work; a small example program; pattern rules and automatic variables; naming values in a makefile; splitting lists across lines; discovering and transforming file lists; `.d` files and parallel `-j`; how the shared makefile layer fits together at the end.

---

## What is a dependency tree?

A dependency tree is a picture of what has to happen before what: which files must be built (or fresh) before another file can exist. We draw it as a tree because it is easy to read. In real projects one header can sit under more than one branch; the drawing is simplified, but the rule is the same: anything listed as a prerequisite must be satisfied before the thing that depends on it.

## What does `make` do?

`make` is a program that reads the steps and relationships you (or generated files) wrote for the project, looks at when files last changed on disk, and decides which commands need to run again after an edit. It does not invent your layout; it follows what the makefile says.

## How does `make` decide what to build again?

The usual rule is simple. If something you depend on is newer than the file that depends on it, that dependent file is out of date and must be rebuilt (recompiled, relinked, or whatever the makefile’s recipe does). The shell commands that perform that work are the ones attached to that target in the makefile.

## Example: program `test`

Imagine `test` is produced by linking `main.o` and `life.o`. The object `main.o` comes from `main.cpp`, and that source includes `life.h`, so building `main.o` really depends on both `main.cpp` and `life.h`. Similarly, `life.o` comes from `life.cpp` and also depends on `life.h`. Each line in the diagram below means “needs” or “is built from”:

```text
                 test
            ┌──────┴──────┐
         main.o         life.o
        /      \       /      \
   main.cpp   life.h life.cpp life.h
```

If you change `life.h`, both objects may need rebuilding, then `test` must be linked again. If you only change `life.cpp`, usually only `life.o` and then `test` need to update.

## Pattern rules and automatic variables

Instead of writing a separate recipe for every object file, `make` lets you write a pattern: a rule that says how to build any `%.o` from a matching `%.cpp` or `%.c`. The percent sign is a stem; for `main.o`, the stem is `main`, so the prerequisite becomes `main.cpp` or `main.c` depending on which pattern rule matches. GNU make uses one source suffix per pattern rule, so C and C++ are often two rules with the same recipe shape, similar to how the shared Windows rules in this tree are written.

```makefile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

After the colon come the prerequisites. Inside the recipe, `$<` is the first prerequisite (the source file), `$@` is the target (the object file), and `$^` is the full prerequisite list. Those names let one short recipe stand for many files. One hard rule: recipe lines must start with a tab character, not spaces, or `make` will reject them. That detail is easy to trip over until it becomes habit.

## Giving names to settings (make variables)

A makefile can give a name to a value and reuse it in rules and commands so options live in one place. A common pattern is a default people can override from the environment or the command line:

```makefile
MAC_BUILD ?= default
```

Read this as: if `MAC_BUILD` is not already set, set it to `default`; if it is set, leave it alone. You can run `make MAC_BUILD=release` or export the variable in your shell. Other assignment forms exist (`=`, `:=`, `+=`, …); the core idea is names and reuse.

## Lists split across lines (backslash at end of line)

Long values read more clearly when each piece sits on its own row. A backslash at the very end of a line tells `make` to continue on the next line without ending the value; the newline is thrown away. You get a list of directory names or modules without one endless line.

```makefile
DIRS=\
TEST\
BAS
```

The last line does not need a backslash unless something follows. The variable still holds one string; this is formatting for humans. If you need to see the expanded value while debugging, a temporary recipe with `echo` is enough.

## Discovering source files (`wildcard`)

To list every `.cpp` file in the directory of the makefile that is running:

```makefile
SRCS := $(wildcard *.cpp)
```

That uses GNU `make`’s `wildcard` function. Once you see it, maintaining hand written source lists feels like unnecessary friction: every new file would be another thing to remember. You can layer extra patterns on top for platform specific exclusions. The shared rules here extend the same idea by searching several directories via `DIRS`, not only `*.cpp` next to one makefile.

## Transforming a list (sources → objects → one link)

One list (your sources) can drive another: object filenames with the same paths and a different suffix. That avoids two lists drifting apart. If `SRCS` holds `.cpp` paths, a single assignment can build the matching object list:

```makefile
OBJS    := $(subst .cpp,.o,$(SRCS))
```

`subst` replaces the substring `.cpp` with `.o` everywhere in the string (so `path/foo.cpp` becomes `path/foo.o`). It is text replacement, not shell globbing. If you also compile `.c` files, add another `subst` for `.c` → `.o`, as the shared makefiles do.

Here, sources discovered from the tree become object names by swapping the extension; dependency filenames follow the same idea. The executable is built by passing all of those object files to the linker in one step. There is no intermediate “build static libraries per folder, then link only libraries” on this path. The final link sees every object.

```makefile
SRCS := main.cpp life.cpp
OBJS := $(subst .cpp,.o,$(SRCS))

test: $(OBJS)
	$(CC) $(OBJS) -o test
```

The dependency picture from the example earlier still applies: each `.o` depends on its source and on headers (via `.d` rules when those exist); `test` depends on every `.o` it needs, and one link command ties them together.

## Header dependencies and `.d` files

When headers change, the sources that include them must be recompiled. Dependency files, often named with a `.d` suffix, contain makefile rules that say so. A small example:

```makefile
main.o: main.cpp ../FOO/FOOblah.h ../DST/DSTutils.h
```

That is an ordinary `make` rule: `main.o` depends on the source and on the headers the compiler saw. Maintaining those lines by hand would be brittle; compilers can emit them automatically, commonly with a flag like `-MMD` (details vary by compiler).

To pull them in:

```makefile
# Include generated .d files for header dependencies
-include *.d
```

When objects live in many directories, you typically include a variable that lists every `.d` file, such as `-include $(DEPENDS)` in this tree’s `makefile.common`, where `DEPENDS` is built in parallel with `OBJECTS`. Then `make` can rebuild only what a header change actually touches.

Stale `.d` files can hurt: if a header is deleted or renamed, an old rule might still mention it and `make` can error. A thorough `clean` removes `.d` files along with objects and other artifacts.

## Parallel builds (`make -j`)

`make -j` runs independent recipe lines in parallel (you can cap with `make -j8` or let it match the machine). It shines when many object files do not depend on each other yet: compilation work spreads across cores. Prerequisites must be accurate, especially edges from `.d` files, or parallel builds expose missing dependencies as intermittent failures. For throughput, designing the graph so lots of work can run in parallel usually beats micro optimizing a single compile; wide, safe parallelism scales.

## Putting the build principles together

Putting these ideas together, the makefile layer here is deliberately small: you describe directories and include shared rules; the system finds sources, compiles, and links one static binary. It helps to read [Building C/C++ programs (basics)](A.building-cpp-basics.md) and [C/C++ compiler concepts](B.compiler-concepts.md) if the pipeline is new to you, then the wiki’s [Make Concepts](https://interfaceware.atlassian.net/wiki/spaces/EC/pages/2104165400/Make+-+Concepts) page; the makefiles are mostly that model written down. A short tutorial video also walks through it with the team.

Building an executable called `test` is typically: put your `.c` and `.cpp` files in a directory next to a tiny makefile, set `DIRS` to the folders (under `../`) that hold shared code you want in the build, and include the core makefile:

```makefile
DIRS=\
TEST\
BAS\

include ../make/makefile.core
```

From there the machinery discovers sources, compiles, and links `test` or `test.exe` on Windows. The approach stays fast and direct: no nested extra `make` invocations on Windows, GNU make plus the platform compiler, `.d` files on macOS and Linux for minimal rebuilds, optional [ccache](D.ccache.md) when installed, and `wildcard` so source lists maintain themselves. One deliberate choice is to avoid intermediate static libraries for this path. Everything goes into a single executable, which is often simpler to ship and reason about.

The upstream `makefile.core` lives at [makefile.core](../makefile.core); this repository keeps the same layer at `cpp/make/makefile.core`. For a hands-on path, the C++ tracing sandbox is a good entry point once you know where your team points newcomers.

---

The wiki’s [Make Concepts](https://interfaceware.atlassian.net/wiki/spaces/EC/pages/2104165400/Make+-+Concepts) page adds extra notes on lists, patterns, and related topics beyond this file.
