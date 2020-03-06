# CMore
#### _Utils in "cross-platform" C11_

## Overview
These are some common utilities that I frequently reuse across projects, so separating them out into their own repo makes it easier to incorporate them.  
Currently defined in their own .c files, but may later change to a *single file library* type design to remove need for messing about with sub-Makefiles and shared/static linking.  
"Cross-platform" in quotation marks since the utilities are written exclusively as C11-standard conformant with no platform-specific dependencies, but MSVC does not support C11 (or even C99) so usage with Windows is a little trickier; more on that in [Notes on cross-platform usage](#x-plat-usage).  

## Current Status
**Data structures:**

| Data structure| Single-thread | Thread-safe (lock) | Thread-safe (lock-free) |
|:-------------:|:-------------:|:-----:|:----:|
| Stack       | ✓ | ✓ | ✗ |
| Queue       | ✓ | ✗ | ✓ |
| Hashmap     | ✓ | ✗ | ✗ |
| Linked list | ✓ | ✗ | ✗ |

**Utilities:**
  * **Hazard Pointers**
   Hazard pointer support for solving ABA problems (and others) in lock-free data structures.
  * **Threadpool**
   A lock-free threadpool using CMore's data structures for (hopefully) fast and efficient job scheduling. 

**Notes:**
  * Hashmap is currently string->string key/value mapping since the original use-case was for configuration file loading/handling. Data is all copied when pairs are added to a single dynamically resized block for cache-friendliness, and to avoid unnecessary memory allocations/freeing.
  * As with the hashmap, other data structure may have weird data-types for their values. This is largely because they were originally implemented to solve a specific problem requiring a specific data-type and were made general as an afterthrought. Future revisions may fix this.
  * Other data structures are based around a common node type which allows for nice (threadsafe maybe) node-reuse, again avoiding unnecessary allocations/frees.
  * CMore's lock-free systems makes heavy use of C11's atomic standard. Currently, memory ordering is kept strict as the library is still in development. The ordering may at some point be relaxed where possible to hopefully increase performance.

## Usage
**Overview:**
Default buildsystem is Make, but any other system will also work (as in, the Makefile doesn't do any fancy defines).

**Standalone build:**
CMore can be built standalone by just calling `make`. By default, this will compile the source and tests, and create a shared/static library. The shared/static paths can be changed by setting `CMORE_SHARED_LIB`/`CMORE_STATIC_LIB` environment variables, respectively. By default, these are `./cmore.a` and `./cmore.so`.

**Incorporated build:**
CMore can also be incorportated into an existing build system as a sub-make file. The parent Makefile can export the `CMORE_SHARED_LIB`/`CMORE_STATIC_LIB` variables and add a rule that calls the CMore makefile. For example usage, see [this repository](https://github.com/platinum95/Burner).  
Alternatively, the parent Makefile can set/export the `CMORE_OBJ_DIR` environment variable and link directly against the compiled object files.

**Using CMore:**
To include CMore's header files in a separate project, add the root directory of the repository to the include path. CMore's components can then be included using `"cmore/`" as prefix, for example `#include "cmore/hashmap.h"`.  
This added degree of separation is mainly as a namespace-ish distinction since the current filenames are very generic and may interfere with other libraries. This may be changed later by making the header files more uniquely named.  
Naturally, this sub-path malarky can be avoided by just adding the `"cmore/"` directory to your include path.

**Notes on cross-platform usage**
(#x-plat-usage)
Development was done mainly on Linux, with frequent swapping to Windows to ensure the library remains cross-platform. An important note is that, as of this writing, Visual Studio's MSVC does not support the C11 features used here. Visual Studio also recently added built-in support for switching to Clang for compilation, but feature-support with Clang in this way is also incomplete; calls to various Atomic-library functions throw an error at compile-time with a helpful message telling us to use Window's platform-specific functions instead. This may change in the future which would allow us to incorporate straight into VS, but for now we need an alternate solution.  
One method that works is msys2. After a bit of setting up we can get a nice bash shell running that allows us to use the library's `Makefile` which compiles down to a nice `.exe`. The WSL system also works, but we resultant binary files cannot be natively used by Windows executables. An important caveat here, however, is that to get this working an additional Atomic-wrapper had to be included. For this, [`tinycthreads`](https://tinycthread.github.io/) was used due to its portability and small footprint. Note that this is only used for the Windows build, and we'll hopefully be able to remove it altogether at a later date.

As far as OSX support goes, I've not yet been able to test it out. At a later date I may get a VM running or find someone who has a Mac to test it on, but for now we'll just call it unsupported.