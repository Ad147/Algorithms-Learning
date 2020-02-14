tcpl_8unix.md

TCPL Notes: 8 The UNIX System Interface
================================================================================

A~0b14

--------------------------------------------------------------------------------

- [8.1 File Descriptors](#81-file-descriptors)
- [8.2 Low Level I/O -- Read and Write](#82-low-level-io----read-and-write)
- [8.3 Open, Creat, Close, Unlink](#83-open-creat-close-unlink)
- [8.4 Random Access -- Lseek](#84-random-access----lseek)

8.1 File Descriptors
--------------------------------------------------------------------------------

When the "shell" runs a program, 3 files are open, with file descriptors 0, 1, and 2, called the standard input, output, and error.

The user of a program can redirect IO to and from files with < and >:

`prog <infiel >outfile`

8.2 Low Level I/O -- Read and Write
--------------------------------------------------------------------------------

Input and output uses the `read` and `write` system calls, which are accessed from C programs through 2 functions `read` and `write`:

`int n_read = read(int fd, char *buf, int n);`  
`int n_written = write(int fd, char *buf, int n);`

The first aurgument is a file descriptor.

```cxx
#include "syscalls.h"

main()  /* copy input to output */
{
    char buf[BUFSIZ];
    int n;

    while ((n = read(0, buf, BUFSIZ)) > 0)
        write(1, buf, n);
    return 0;
}
```

```cxx
#include "syscalls.h"

/* getchar: unbuffered single character input */
int getchar(void)
{
    char c;

    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
```

```cxx
#include "syscalls.h"

/* getchar: simple buffered version */
int getchar(void)
{
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {   /* buffer is empty */
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
```

If these versions of `getchar` were to be compiled with <stdio.h> included, it would be necessary to #undef the name `getchar` in case it is implemented as a *macro*.

8.3 Open, Creat, Close, Unlink
--------------------------------------------------------------------------------

System call `open` is like fopen, returning a file descriptor.

```cxx
#include <fcntl.h>

int fd;
int open(char *name, int flags, int perms);

fd = open(name, flags, perms);
```

flags:

- O_RDONLY: read only
- O_WRONLY: writing only
- O_RDWR: both

It is an error to open a file does not exist.  
Use `creat` to create new files or re-write old ones.

`int creat(char *name, int perms);`  
`fd = creat(name, perms);`

Here is a simplified version of UNIX program cp:

```cxx
#include <stdio.h>
#include <fcntl.h>
#include "syscalls.h"
#define PERMS 0666  /* RW for owner, group, others */

void error(char *, ...);

/* cp: copy f1 to f2 */
main(int argc , char *argv[])
{
    int f1, f2, n;
    char buf[BUFSIZ];

    if (argc != 3)
        error("Usage: cp from to");
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
        error("cp: can't open %s", argv[1]);
    if ((f2 = creat(argv[2], PERMS)) == -1)
        error("cp: can't create %s, mode %03o", argv[2], PERMS);
    while ((n = read(f1, buf, BUFSIZ)) > 0)
        if (write(f2, buf, n) != n)
            error("cp: write error on file %s", argv[2]);
    return 0;
}
```

```cxx
#include <stdio.h>
#include <stdarg.h>

/* error: print an error message and die */
void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
```

There is a limit (often about 20) on the number of files that a program may have open simultaneously.  
Use `close(int fd)` to break the connection between a file descriptor and an open file, like `fclose`

The function `unlink(char *name)` removes the file `name` from the file system, corresponding to stdlib func `remove`.

8.4 Random Access -- Lseek
--------------------------------------------------------------------------------

p189