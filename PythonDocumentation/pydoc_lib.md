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
- p23