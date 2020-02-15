tcpl_8unix.md

TCPL Notes: 8 The UNIX System Interface
================================================================================

A~0b14

--------------------------------------------------------------------------------

- [8.1 File Descriptors](#81-file-descriptors)
- [8.2 Low Level I/O -- Read and Write](#82-low-level-io----read-and-write)
- [8.3 Open, Creat, Close, Unlink](#83-open-creat-close-unlink)
- [8.4 Random Access -- Lseek](#84-random-access----lseek)
- [8.5 Example -- An Implementation of Fopen and Getc](#85-example----an-implementation-of-fopen-and-getc)
- [8.6 Example -- Listing Directories](#86-example----listing-directories)

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

The system call `lseek`: move around in a file without reading or writing any data:

`long lseek(int fd, long offset, int origin);`

sets the current position in file fd to offset, which is taken relative to the location specified by origin (0/1/2 for from beginning/current position/end).

```cxx
#include "syscalls.h"

/* get: read n bytes from position pos */
int get(int fd, long pos, char *buf, int n)
{
    if (lseek(fd, pos, 0) >= 0)     /* get to pos */
        return read(fd, buf, n);
    else
        return -1;
}
```

the std lib func `fseek` is similar except that the 1st argument is a FILE * and the return is non-zero if error.

8.5 Example -- An Implementation of Fopen and Getc
--------------------------------------------------------------------------------

> In the following excerpt from a typical <stdio.h>, names that are intended for use only by functions of the library begin with an underscore so they are less likelyy to collide with names in a user's program.  
> This convention is used by all standard library routines.

#### Implementation of `getc`

```cxx
#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20  /* max #files open at once */

typedef struct _iobuf {
    int cnt;        /* character left */
    char *ptr;      /* next character position */
    char *base;     /* location of buffer */
    int flag;       /* mode of file access */
    int fd;         /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags {
    _READ   = 01,   /* file open for reading */
    _WRITE  = 02,   /* file open for writing */
    _UNBUF  = 04,   /* file is unbuffered */
    _EOF    = 010,  /* EOF has occurred on this file */
    _ERR    = 020   /* error occured on the file */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)
```

#### Implementation of `fopen`

```cxx
#include <fcntl.h>
#include "syscalls.h"
#define PERMS 0666      /* RW for owner, group, others */

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;      /* found free slot */
    if (fp >= _iob + OPEN_MAX)      /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)       /* couldnot access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}
```

This version does not handle all of the access mode.

#### Implementation of `_fillbuf`

```cxx
#include "syscalls.h"

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)       /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;     /* cannot get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}
```

The array `_iob` must be defined and initialized for stdin, stdout and stderr:

```cxx
FILE _iob [OPEN_MAX] = {        /* stdin, stdout, stderr: */
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};
```

8.6 Example -- Listing Directories
--------------------------------------------------------------------------------

p193