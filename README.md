The crazy idea is to create object which can store functions which are string-addressed, something similar to dynamic languages like `python` or `JavaScript`.

```
object obj;

obj["say_hello"] = [] (int i, std::string s)
{
    std::cout << "hello " << i << " " << s << std::endl;
};

// ...

obj["say_hello"](2, std::string("Piotr"));
```
