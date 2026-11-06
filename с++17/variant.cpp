// cd "с++17"
// g++ -std=c++17 -Wall variant.cpp -o variant
// ./variant

#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

using namespace std;
// с++17/std_variant.cpp: get, emplace, holds_alternative, get_if

int main() {
    // в один момент времени variant - это int, double или string
    std::vector<std::variant<int, double, std::string>> vec{42, 2.5, "hi", 7};
    // или
    // container.push_back(7);

    // с использованием лямбды
    // std::visit( лямбда , variant )
    for (auto& item : vec) { // item - это variant
        // ищет активный тип
        // std::visit(function, v);
        std::visit([](const auto& x) { std::cout << x << '\n'; }, item); // x - содержимое variant
    }

    //----------------------------------------------------------------------------------------------------------------
    struct Printer {
        int num;
        double dbl;
        std::string hi;

        // перегрузка оператора вызова
        void operator()(int x) const { std::cout << "int: " << x << '\n'; }
        void operator()(double x) const { std::cout << "double: " << x << '\n'; }
        void operator()(std::string& x) const { std::cout << "string: \"" << x << "\"\n"; }
    };
    // без использования лямбды
    for (auto& item : vec) {
        std::visit(Printer{}, item); // создаем объект Printer{} на месте
    }
    //----------------------------------------------------------------------------------------------------------------
    double sum = 0;
    for(auto& item : vec) {
        sum += std::visit([](const auto& x){
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::string>) { // тип x без const и &, c чем сравниваем
                return 0.0;
            } else {
                return static_cast<double>(x);
            }
        }, item);
    }
    std::cout << "sum: " << sum << '\n';

    return 0;
}