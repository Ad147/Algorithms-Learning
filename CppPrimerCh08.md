C++ Primer Notas de Estudio
===========================
Ad  
init: May09.2018

Chapter8 The IO Library
---------------------------
### 8.1 The IO Classes

##### IO library types and headers
Header      | Type
------------|------------------------------------------
`iostream`  | `istream`, `wistream` reads from a stream
|           | `ostream`, `wostream` writes to a stream
|           | `iostream`, `wiostream` reads and writes a stream
`fstream`   | `ifstream`, `wifstream` reads from a file
|           | `ofstream`, ... writes to a file
|           | `fstream`, ... reads and writes a file
`sstream`   | `istringstream` ... reads from a string (in memory)
|           | `ostringstream` ... writes to a string
|           | `stringstream`, ... reads and writes a string

`ifstream` and `istringstream` are inherit from `istream`

#### 8.1.1 No Copy or Assign for IO Objects

#### 8.1.2 Condition States

||IO Library Condition State
-|----------------------------
`stream::iostate`   | a machine-dependent integral type that represent the condition state
`stream::badbit`    | `iostate` value used to indicate that a stream is corrupted
`stream::failbit`   | indicate that an IO operation failed
`stream::eofbit`    | a stream hit end-of-file
`stream::goodbit`   | not in an error state. guaranteed to be zero
s.eof()             | true if `eofbit` in the stream s is set
s.fail()            | if `failbit` or `badbit` is set
s.bad()             | if `badbit` is set
s.good()            | if s is in valid state
s.clear()           | Reset all condition values to valid state. return void
s.clear(flags)      | Reset the condition of s to flags (of type `iostate`). return void
s.setstate(flags)   | Adds specified condition(s) to s. return void
s.rdstate()         | returns current condition of s as a stream::iostate value

##### Interrogating the state of a stream
`iostate` is a type used to convey information about the state of a stream,   
it is used as a collection of bits,   
the IO classes define four `constexpr` values to represent the states.

- determine the overall state of a stream is to use either `good` or `fail`

i.e. turns off fialbit and badbit but all other bits unchanged:  
`cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);`

#### 8.1.3 Managing the Output Buffer

The system might store the data in a buffer to be printed later.  
Several conditions that cause the buffer to be flushed:
- the program completes normally. All output buffers flushed as part of return from main
- the buffer can become full at some indeterminate time.
- flush the buffer explicitly using a manipulator `endl` (new line and flush) `flush` (just flush) `ends` (writes a null and flush)
- using the `unitbuf` manipulator to set the stream's internal state to empty the buffer after each output operation. (`unitbuf` is default for `cerr`)  
`cout << unitbuf;` `cout << nounitbuf;`
- An output stream might be tied to another stream. by default, `cin` and `cerr` are both tied to `cout`. hence, reading `cin` or writing to `cerr` flushes `cout`  
`cin.tie(&cout);`

### 8.2 File Input and Output

||`fstream`-Specific Operations
-|-----------------------------
`fstream fstrm;`    | creates an unbound file stream
`fstream fstrm(s);` | creates an fstream and opens the file named s. s can be `string` or C char string
`fstream fstrm(s, mode);`   | open s in the given mode
`fstrm.open(s)`     | opens the file by the s and bind it to fstrm
`fstrm.open(s, mode)`| returns void
`fstrm.close()`     | closes the file to which fstrm is bound. returns void
`fstrm.is_open()`   | return bool indicating whether the file associated with fstrm was sucessfully opened and has not been closed

#### 8.2.1 Using File Stream Objects

`C++11` allows file name to be string or C char string rather than only the latter.

##### The `open` and `close` members
Once a file stream has been opened, it remains associated with the specified file.  
call open on a file stream that is already open will fial.  
To associate a file stream with a different file, must close the existing file.

##### Automatic construction and destruction
> When an fstream object is destroyed, close() is called automatically.

#### 8.2.2 File Modes

||File Modes
-|----------
in      | open for input (only for ifstream and fstream)
out     | open for output (only for ofstream and fstream) default trunc
app     | seek to the end before every write (always opened in output mode if set app)
ate     | seek to the end immediately after the open (combined with other mode)
trunc   | truncate the file (only when out is also set)
binary  | do IO operations in binary mode (combined with other mode)

##### Opening a file in out mode discards existing data
`ofstream out("file", ofstream::app);`

##### File mode is determined each time open is called

### 8.3 `string` Streams

||`stringstream`-Specified Operations
-|-----------------------------------
`sstream strm;` | strm is an unbound stringstream
`sstream strm(s);`  | strm holds a copy of the strings s
`strm.str()`    | returns a copy of the string that strm holds
`strm.str(s)`   | copies the string s into strm. returns void

#### 8.3.1 Using an `istringstream`

> An `istringstream` is often used when we have some work to do on an entire line, and other work to do with individual words within a line.

#### 8.3.2 Using `ostringstream`s

> An `ostringstream` is useful when we need to build up our output a little at a time but donot want to print the output until later.
