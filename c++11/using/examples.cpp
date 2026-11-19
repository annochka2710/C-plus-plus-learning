#include <iostream>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <type_traits>
#endif

struct Base {
    void print(int value) const {
        std::cout << "Base::print(int): " << value << '\n';
    }
};

struct Derived : Base {
    using Base::print;

    void print(const char* text) const {
        std::cout << "Derived::print(const char*): " << text << '\n';
    }
};

#if __cplusplus >= 201103L
using Id = unsigned long;
using Callback = void (*)(int);

template<class T>
using List = std::vector<T>;

struct Number {
    explicit Number(int number) : value(number) {}
    int value;
};

struct TrackedNumber : Number {
    using Number::Number;
    int calls = 0;
};

void show_id(int value) {
    std::cout << "Callback: " << value << '\n';
}
#endif

#if __cplusplus >= 201703L
struct PrintInt {
    void operator()(int value) const {
        std::cout << "Overload(int): " << value << '\n';
    }
};

struct PrintText {
    void operator()(const std::string& text) const {
        std::cout << "Overload(string): " << text << '\n';
    }
};

template<class... Bases>
struct Overload : Bases... {
    using Bases::operator()...;
};
#endif

#if __cplusplus >= 202002L
enum class Color { red, green, blue };
#endif

int main() {
    std::cout << std::boolalpha;
    {
        using std::cout;
        cout << "C++98: using std::cout\n";
    }
    {
        using namespace std;
        cout << "C++98: local using namespace std\n";
    }

    Derived printer;
    printer.print(42);
    printer.print("hello");

#if __cplusplus >= 201103L
    static_assert(std::is_same<Id, unsigned long>::value,
                  "A type alias does not create a distinct type");
    static_assert(std::is_same<List<int>, std::vector<int> >::value,
                  "An alias template names the substituted type");
    List<int> numbers{1, 2, 3};
    std::cout << "C++11: List<int> size = " << numbers.size() << '\n';
    Callback callback = &show_id;
    callback(7);
    TrackedNumber tracked(42);
    std::cout << "Inherited constructor: value = " << tracked.value
              << ", calls = " << tracked.calls << '\n';
#endif

#if __cplusplus >= 201703L
    {
        using std::cout, std::endl;
        cout << "C++17: multiple using-declarators" << endl;
    }
    Overload<PrintInt, PrintText> handler;
    handler(10);
    handler(std::string("hello"));
#endif

#if __cplusplus >= 202002L
    {
        using enum Color;
        Color selected = green;
        std::cout << "C++20: using enum, green = "
                  << (selected == Color::green) << '\n';
    }
    {
        using Color::red;
        Color selected = red;
        std::cout << "C++20: using Color::red = "
                  << (selected == Color::red) << '\n';
    }
#endif

// GCC may use a draft __cplusplus value in C++23 mode.
#if __cplusplus > 202002L
    if (using Count = unsigned; Count{3} > 0) {
        Count remaining = 3;
        std::cout << "C++23: local alias, remaining = " << remaining << '\n';
    }
#endif
}
