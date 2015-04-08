# Duct taping in C++ (huh?!)

Some loose experiment on creating duct taping object model in C++ :)

## The idea

The crazy idea is to create object which can store functions which are string-addressed, something similar to dynamic languages like `python` or `JavaScript`.

## Basic API

In C++ we cannot override function call because it has to be something known by the compiler. We do however have operators, lets say `/` will be our base for the experiments. So we want to achieve something like:

```
object / "hello_world";
```

as a equivalent of

```
object.hello_world();
```

(which actually, doesn't look that bad :))
