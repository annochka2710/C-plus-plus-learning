# using в разных стандартах C++

У `using` несколько применений: сделать существующее имя доступным без
квалификатора, задать псевдоним типа, наследовать конструкторы или сократить
обращение к элементам перечисления. Сначала смотри на форму записи.

| Начиная со стандарта | Запись | Назначение |
|---|---|---|
| C++98 | `using namespace std;` | Учитывать имена пространства при поиске без квалификатора |
| C++98 | `using std::cout;` | Ввести конкретное имя в текущую область |
| C++98 | `using Base::print;` | Сделать доступными перегрузки из базового класса |
| C++11 | `using Id = unsigned long;` | Объявить псевдоним типа |
| C++11 | `template<class T> using List = std::vector<T>;` | Объявить шаблон псевдонима |
| C++11 | `using Base::Base;` | Наследовать конструкторы |
| C++14 | Те же основные формы, что в C++11 | Для примеров этого модуля нового синтаксиса нет |
| C++17 | `using std::cout, std::endl;` | Перечислить несколько имён в одном объявлении |
| C++17 | `using Bases::operator()...;` | Раскрыть пакет в using-объявлении |
| C++20 | `using enum Color;` | Ввести все элементы перечисления |
| C++20 | `using Color::red;` | Ввести отдельный элемент scoped enum |
| C++23 | `if (using T = int; условие)` | Объявить псевдоним в начальной инструкции |

Запускаемый [examples.cpp](examples.cpp) собирается в шести режимах:
C++98, C++11, C++14, C++17, C++20 и C++23. Препроцессор оставляет только
те части, которые доступны выбранному стандарту.

## C++98: пространство имён и отдельное имя

```cpp
#include <iostream>

void print() {
    using std::cout;
    cout << "hello\n";
}
```

`using std::cout;` — using-объявление. Оно позволяет обращаться к
существующему объекту `std::cout` как к `cout` внутри блока после объявления.
Объект не копируется. Если имя обозначает функцию, доступны найденные
этим объявлением перегрузки. См. [правила using-объявлений](https://eel.is/c++draft/namespace.udecl).

```cpp
void print_all() {
    using namespace std;
    cout << "hello" << endl;
}
```

`using namespace std;` — using-директива: она влияет на поиск имён из
пространства `std`, но не копирует его содержимое в текущую область.
Директиву можно писать в блоке или пространстве имён, но не внутри класса.
См. [правила using namespace](https://eel.is/c++draft/namespace.udir).

Для учебного и рабочего кода обычно удобнее `std::cout` либо локальное
`using std::cout;`: видно, откуда взялось имя. Не размещай
`using namespace std;` на уровне пространства имён в заголовке:
директива повлияет на подключающий код и может вызвать неоднозначность.

```cpp
namespace first { int value = 1; }
namespace second { int value = 2; }

void conflict() {
    using namespace first;
    using namespace second;
    // int result = value; // Ошибка: какое именно value?
    int result = first::value; // Явно выбрано нужное имя.
    (void)result;
}
```

## C++98: перегрузки базового класса

```cpp
struct Base {
    void print(int) const {}
};

struct Derived : Base {
    using Base::print;
    void print(const char*) const {}
};
```

Без `using Base::print;` функция `Derived::print` скрывает имя `print`
из базы: вызов `object.print(42)` не найдёт подходящей перегрузки.
С `using` доступны обе функции. Это не переопределение виртуального метода.
Через `using` в секции `public` также можно открыть доступ к `protected`
члену базы; получить доступ к её `private` члену так нельзя.
См. [using в классах](https://eel.is/c++draft/namespace.udecl).

## C++11: псевдоним типа и отличие от typedef

```cpp
typedef unsigned long OldId;       // Доступно ещё в C++98.
using Id = unsigned long;          // Начиная с C++11.
using Callback = void (*)(int);    // Псевдоним указателя на функцию.
```

В записи `using Имя = Тип;` слева находится новое имя, справа — тип.
Как и `typedef`, такое объявление не создаёт отдельный тип:
`Id` и `unsigned long` обозначают один тип. Поэтому перегрузки
`void save(Id);` и `void save(unsigned long);` объявляют одну функцию.
Если нужны несовместимые типы `UserId` и `OrderId`, создай отдельные
классы или структуры. См. [псевдонимы типов](https://eel.is/c++draft/dcl.typedef).

Не путай три записи:

```cpp
using std::string;                  // Ввести существующее имя string.
using Text = std::string;           // Дать типу имя Text.
namespace io = std;                 // Псевдоним пространства имён, без using.
```

`using answer = 42;` некорректно: справа нужен тип.
Для константы подойдёт `constexpr int answer = 42;`.

## C++11: шаблон псевдонима

```cpp
#include <vector>

template<class T>
using List = std::vector<T>;

List<int> numbers;                  // Тот же тип, что std::vector<int>.
List<double> measurements;
```

Псевдоним может зависеть от параметра шаблона. Записи
`template<class T> typedef ...` в языке нет. До C++11 применяли обёртку:

```cpp
template<class T>
struct ListType {
    typedef std::vector<T> type;
};

ListType<int>::type numbers;
```

Сам шаблон псевдонима нельзя явно или частично специализировать.
Если нужно выбирать реализацию по типу, специализируй вспомогательный
шаблон класса и через `using` обращайся к его `type`.
См. [шаблоны псевдонимов](https://eel.is/c++draft/temp.alias).

## C++11: наследование конструкторов

```cpp
struct Base {
    explicit Base(int number) : value(number) {}
    int value;
};

struct Derived : Base {
    using Base::Base;
    int calls = 0;
};

Derived object(42); // Base::value == 42, Derived::calls == 0.
```

`using Base::Base;` позволяет создавать производный объект с аргументами
конструктора базы. Остальные базы и поля инициализируются обычным образом:
здесь `calls` получает значение из инициализатора поля.
Наследование конструктора само по себе не инициализирует все поля числом
ноль: без `= 0` у обычного поля `int calls;` значение здесь было бы неопределённым.
См. [инициализация через унаследованный конструктор](https://eel.is/c++draft/class.inhctor.init).

## C++14: продолжаем пользоваться формами C++11

Псевдонимы типов, шаблоны псевдонимов и наследование конструкторов уже
доступны. Не нужно повышать стандарт до C++14 ради `using T = ...;`.
Например, библиотечный `std::decay_t<T>` появился в C++14, но это
применение шаблона псевдонима, а не новый синтаксис `using`.

## C++17: список имён и раскрытие пакета

```cpp
using std::cout, std::endl; // Раньше нужны были два using-объявления.

template<class... Bases>
struct Overload : Bases... {
    using Bases::operator()...;
};
```

`Bases...` — пакет базовых классов. Последняя строка делает операторы
вызова всех этих баз доступными как перегрузки в `Overload`.
Так можно объединить несколько обработчиков в один объект; это полезно
для `std::visit`. В [examples.cpp](examples.cpp) используются два простых
функциональных объекта. Расширение предложено в
[P0195R2: Pack expansions in using-declarations](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0195r2.html).

## C++20: using enum и отдельный элемент enum class

```cpp
enum class Color { red, green, blue };

void choose() {
    using enum Color;
    Color selected = red; // Тип остаётся Color.
    (void)selected;
}

void choose_one() {
    using Color::green;
    Color selected = green;
    (void)selected;
}
```

`using enum Color;` делает доступными все элементы перечисления в текущей
области. `using Color::green;` вводит только один элемент. Для scoped enum
обе возможности появились в C++20; само `enum class` существует с C++11.
Без этих объявлений можно писать `Color::green`.

`using enum` применим и к обычным перечислениям. Он не превращает
`enum class` в `int`, а совпадающие имена элементов разных перечислений
могут конфликтовать. См. [P1099R5: Using Enum](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1099r5.html).

## C++23: псевдоним в начальной инструкции

```cpp
if (using Count = unsigned; Count{3} > 0) {
    Count remaining = 3;
    (void)remaining;
}
// Здесь Count уже недоступен.
```

Объявление псевдонима теперь разрешено в начальной инструкции `if`,
`switch`, обычного `for` и range-based `for`. У `if` имя доступно также
в ветке `else`. До C++23 можно было создать внешний блок и объявить
псевдоним перед условием. Расширение описано в
[P2360R0: alias-declaration в init-statement](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2360r0.html).

## Сборка и наблюдение за выводом

Из корня проекта:

```bash
cmake -S . -B build
cmake --build build --target cpp98_using_examples cpp11_using_examples cpp14_using_examples cpp17_using_examples cpp20_using_examples cpp23_using_examples
./build/c++11/using/cpp98_using_examples
./build/c++11/using/cpp23_using_examples
```

Для цели C++23 нужен компилятор с поддержкой используемой возможности.
Можно собрать только нужную цель или напрямую один файл:

```bash
c++ -std=c++20 -pedantic-errors -Wall -Wextra -Wshadow -Wconversion \
    c++11/using/examples.cpp -o /tmp/using_examples
/tmp/using_examples
```

В C++98 выводятся отдельное имя, локальная директива и две перегрузки.
В C++11/C++14 добавляются псевдонимы и унаследованный конструктор;
в C++17 — список имён и раскрытие пакета; в C++20 — элементы перечисления;
в C++23 — локальный псевдоним внутри `if`.

## Практика

1. Объясни разницу между `using std::string;`, `using Text = std::string;`
   и `using namespace std;`. С какого стандарта доступна каждая запись?
2. Убери `using Base::print;` в примере и объясни ошибку вызова с числом.
   Затем восстанови строку.
3. Добавь `using Matrix = List<List<int>>;`. Какой тип он обозначает?
4. Объяви `UserId` и `OrderId` псевдонимами `unsigned long`. Проверь,
   можно ли присвоить одно другому. Затем замени их отдельными структурами.
5. В C++17 добавь третий обработчик в `Overload` для `const char*`.
6. В C++20 замени `using enum Color;` на `using Color::green;`.
   Какие имена теперь требуют квалификатора?
7. Попробуй использовать `Count` после `if` из примера C++23.
   Объясни ошибку через область видимости.
