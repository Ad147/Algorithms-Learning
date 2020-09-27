pydoc_lib.md

Python Library Reference (3.8.3)
================================================================================

A~0v07

2 Built-in Functions
--------------------------------------------------------------------------------

- abs(x)
- all(iterable): true if all elems are true
- any(iterable): true if any elem is true
- ascii(obj)
- bin(x): convert int to binary string
- class bool([x])
- breakpoint(*args, **kws)
- class bytearray([source[, encoding[, errors]]]): mutable seq of ints in [0, 256)
- class bytes([source[, encoding[, errors]]]): immutable seq if ints
- callable(obj)
- chr(i): return str representing a char of Unicode i; inverse of ord()
- @classmethod: decorator, transform a method into a class method
- compile(...)
- class complex([real[, imag]])
- delattr(ob, name) == del obj.name
- class dict(**kwarg)
- class dict(mapping, **kwarg)
- class dict(iterable, **kwarg)
- dir([obj]): without args, return list of names in current local scope; with arg, return list of valid attrs for that obj
- divmod(a, b) == (a // b, a % b)
- enumerate(itr, start=0)
- eval(...): evaluate Python expression
- exec(...)
- filter(func, iter) == (item for item in iter if func(item))
- class float([x]); ("inf")
- class frozenset([iter]) (?)
- getattr(obj, name[, default]) == obj.name
- globals() return a dict representing current global symbol table
- hasattr(obj, name): check if obj has attr name (by calling getattr())
- hash(obj): return hash value of the obj
- help([obj]) (interactive)
- hex(x): convert to "0xaaaa...", other ways:
  - `'%#x' % 255, '%x' % 255, '%X' % 255` -> ('0xff', 'ff', 'FF')
  - `format(255, '#x'), format(255, 'x'), format(255, 'X')` -> ('0xff', 'ff', 'FF')
  - `f'{255:#x}', f'{255:x}', f'{255:X}'` -> ('0xff', 'ff', 'FF')
  - for a float, `float.hex()`
- id(obj): return "identity" (an unique int) of obj; in CPython, it is memory address
- input([prompt])
- class int([x])
- class int(x, base=10)
- isinstance(obj, classinfo)
- issubclass(class, classinfo)
- iter(obj[, sentinel]): return an iterator obj
- len(s)
- class list([iterable])
- locals(): return a dict representing local symbol table
- map(func, iter,...): return an iterator applies func to every item of iter
- max(iter, *[,key, default])
- max(arg1, arg2, *args[, key])
- class memoryview(obj)
- min(iter, *[,key, default])
- min(arg1, arg2, *args[, key])
- next(iter[, default])
- class object: return a new featureless object
- oct(x): similar to hex()
- open()
- ord(c): unicode of c, inverse of chr()
- pow(base, exp[, mod]) == base**exp, efficient than pow(base, exp) % mod
- print()
- class property(fget=None, fset=None, fdel=None, doc=None): return a property attribute, typically used to define a managed attr:
```py
class C:
    def __init__(self):
        self._x = None

    def getx(self):
        return self._x

    def setx(self, value):
        self._x = value

    def delx(self):
        del self._x

    x = property(getx, setx, delx, "I am the "x" property.")

# property() can be used as a decorator
# below is equivalent to above

class C:
    def __init__(self):
        self._x = None

    @property
    def x(self):
        """I am the "x" property."""
        return self._x

    @x.setter
    def x(self, value):
        self._x = value

    @x.deleter
    def x(self):
        del self._x
```

- class range()
- repr(obj): a string containing a printable representation of obj
- reversed(seq)
- round(number[, ndigits]): round to ndigits precision
- class set([iterable])
- setattr(obj, name, value)
- class slice(stop)
- class slice(start, stop[, step]): generated when extende indexing syntax is used
- sorted(iterable, *, key=None, reverse=False): stable sort, key take 1 arg
- @staticmethod: transform a method into static
- class str()
- sum(iter, /, start=0)
- super([type[, obj-or-type]])
- class tuple([iter])
- class type(obj)
- class type(name, bases, dict)
- vars([obj]): return `__dict__`
- zip(*iter)

3 Built-in Constants
--------------------------------------------------------------------------------

4 Built-in Types
--------------------------------------------------------------------------------

- 4.1 Truth Value Testing
  - None or False
  - 0, 0.0, 0j...
  - empty seq
- 4.2 Boolean Operations -- and, or, not
- 4.3 Comparisons
- 4.4 Numeric Types -- int, float, complex
  - 4.4.1 Bitwise Operations on Integer Types
  - 4.4.2 Additional Methods on Integer Types
  - 4.4.3 Additional Methods on Float
  - 4.4.4 Hashing of Numeric Types
- 4.5 Iterator Types
  - 4.5.1 Generator Types
- 4.6 Sequence Types -- list, tuple, range
  - 4.6.1 Common Sequence Operations
  - 4.6.2 Immutable Sequence Types
  - 4.6.3 Mutable Sequence Types
  - 4.6.4 Lists
  - 4.6.5 Tuples
  - 4.6.6 Ranges
- 4.7 Text Sequence Type -- str
  - 4.7.1 String Methods
  - 4.7.2 printf-style String Formatting
- 4.8 Binary Sequence Types -- bytes, bytearray, memoryview
  - 4.8.1 Bytes Object
  - 4.8.2 Bytearray Objects
  - 4.8.3 Bytes and Bytearray Operations
  - 4.8.4 printf-style Bytes Formatting
  - 4.8.5 Memory Views
- 4.9 Set Types -- set, frozenset
- 4.10 Mapping Types -- dict
  - 4.10.1 Dictionary View Objects
- 4.11 Context Manager Types
- 4.12 Other Built-in Types
  - 4.12.1 Modules
  - 4.12.2 Claases and Class Instance
  - 4.12.3 Functions
  - 4.12.4 Methods
  - 4.12.5 Code Objects
  - 4.12.6 Type Objects
  - 4.12.7 The Null Object
  - 4.12.8 The Ellipsis Object
  - 4.12.9 The NotImplemented Object
  - 4.12.10 Boolean Values
  - 4.12.11 Internal Objects
- 4.13 Special Attributes

5 Built-in Exceptions
--------------------------------------------------------------------------------

6 Text Processing Sercvices
--------------------------------------------------------------------------------

7 Binary Data Services
--------------------------------------------------------------------------------

8 Data Types
--------------------------------------------------------------------------------

### 8.3 collections -- Container Datatypes

- namedtuple()
- deque
- ChainMap
- Counter
- OrderedDict
- defaultdict
- UserDict
- UserList
- UserString

### 8.5 heapq -- Heap Queue Algorithm

--------------------------------------------------------------------------------

EOF
