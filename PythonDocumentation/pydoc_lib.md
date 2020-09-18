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
- p26