# ccache (compiler cache)

Repeated builds while you edit should not always rerun the full compiler for work that has not really changed. [ccache](https://ccache.dev/) is a compiler cache: it stores object files keyed by a hash of the inputs that matter for a given compile. Roughly, it simulates enough of the preprocessor path to form that key, computes something like an MD5, and if a matching result exists, copies the cached object instead of invoking the real compiler. If not, it runs the compiler and stores the new result.

ccache can use a lot of disk space. Behavior also varies with version and with how your compiler is set up, so treat it as a strong default, not an absolute guarantee. The shared POSIX rules in this repository wrap the compiler with `ccache` when it is installed; see `../makefile.common`. Full documentation is at [ccache.dev](https://ccache.dev/). For flags and the compile pipeline, read [C/C++ compiler concepts](B.compiler-concepts.md); for how builds are driven here, read [Make concepts](C.make-concepts.md).

## Statistics (`ccache -s`)

To inspect behavior, `ccache -s` prints statistics: hits, misses, cache size, and other counters. A sample session might look like the block below; your numbers and paths will differ.

```text
~/cpp$ ccache -s
cache directory                     /Users/example/.ccache
primary config                      /Users/example/.ccache/ccache.conf
secondary config      (readonly)    /usr/local/Cellar/ccache/3.7.4/etc/ccache.conf
stats updated                       Wed Sep  1 11:35:53 2021
stats zeroed                        Sat Apr  3 17:41:13 2021
cache hit (direct)                110141
cache hit (preprocessed)            4424
cache miss                         22688
cache hit rate                     83.47 %
called for link                     5700
called for preprocessing              13
multiple source files                  3
compiler produced empty output         2
compile failed                       996
preprocessor error                   985
bad compiler arguments                 1
autoconf compile/link                 42
no input file                          5
cleanups performed                     0
files in cache                     55462
cache size                           2.5 GB
max cache size                       5.0 GB
```

