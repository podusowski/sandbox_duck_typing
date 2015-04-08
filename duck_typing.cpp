#include <string>
#include <map>
#include <iostream>
#include <functional>


struct function
{
    function & operator = (std::function<void()> f)
    {
        this->f = f;
        return *this;
    }

    ~function()
    {
        f();
    }

private:
    std::function<void()> f;
};

struct object
{
    function & operator / (const std::string & name)
    {
        return members[name];
    }

private:
    std::map<std::string, function> members;
};

int main()
{
    object obj;
    obj / "hello" = [] { std::cout << "hello"; };
    obj / "hello";
}
