# C++ OOP Visual Study Guide — Vansh

> Diagrams pehle, redraw se recall. C++ OOP = mechanics; picture banao.

## Object in memory + vtable (MEMORIZE)
```
class Base { virtual void f(); int x; };
obj layout:  [ vptr ] -> vtable: [ &Base::f ]
             [  x   ]
Derived overrides f -> vtable: [ &Derived::f ]
base_ptr->f()  => follow vptr -> vtable -> correct fn (RUNTIME dispatch)
non-virtual call => resolved at COMPILE time (by static type)
```

## Rule of 5 (the big one)
```
If a class manages a resource (raw ptr), define all 5 (or use RAII/Rule of 0):
1 destructor          ~T()
2 copy constructor    T(const T&)
3 copy assignment     T& operator=(const T&)
4 move constructor    T(T&&) noexcept
5 move assignment     T& operator=(T&&) noexcept
Rule of 0: hold members that manage themselves (unique_ptr/vector) -> define NONE.
```

## Deep vs shallow copy
```
shallow: copy the pointer  -> two objects share buffer -> double free / aliasing  ✗
deep   : copy the pointed-to data -> independent buffers                          ✓
```

## Object slicing
```
Derived d;
Base b = d;          // SLICED: only Base part copied, vptr is Base's -> polymorphism lost
void f(Base b)       // by value = slices
void f(Base& b) / Base*  // by ref/ptr = keeps the Derived (no slice)  ✓
```

## Smart pointers
```
unique_ptr<T>  sole owner, move-only          (default choice)
shared_ptr<T>  ref-counted, shared ownership  (count==0 -> delete)
weak_ptr<T>    non-owning observer            (breaks shared_ptr CYCLES)
A.shared->B, B.shared->A  => cycle, never freed.  Make one weak_ptr -> fixed.
```

## Casts
```
static_cast      compile-time, related types / numeric (no runtime check)
dynamic_cast     runtime, safe downcast (ptr->nullptr, ref->throw); needs virtual/RTTI
const_cast       add/remove const
reinterpret_cast bit reinterpret (danger)
```

## overload vs override vs hide
```
overload : same name, diff params, SAME scope (compile-time)
override : derived re-defines a VIRTUAL base fn, same signature (runtime)
hide     : derived declares same name -> hides ALL base overloads (use `using`)
```

## Spaced-rep recall bank
1. virtual destructor — kab + kyun?
2. Rule of 5 — kaunse 5?
3. deep vs shallow copy?
4. vtable se dispatch kaise?
5. object slicing kab hota?
6. unique vs shared vs weak_ptr?
7. dynamic_cast vs static_cast?
8. override vs overload vs hide?
