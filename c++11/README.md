# C++11

Краткий план изучения основных нововведений относительно C++03.
Для каждой темы — небольшой пример и самостоятельное упражнение.

## Язык

- [ ] `auto` и `decltype` — вывод и получение типа выражения.
- [ ] `nullptr` — нулевой указатель и отличие от `NULL`.
- [ ] Инициализация через `{}`, запрет сужающих преобразований и `std::initializer_list`.
- [ ] Range-based `for` — обход коллекций, значения и ссылки в цикле.
- [x] [Лямбды](functional/lambdas.md) — параметры, захваты по значению и по ссылке,
  `mutable`, время жизни данных, примеры и упражнения.
- [ ] Rvalue-ссылки, семантика перемещения и `std::move`.
- [ ] Правило пяти: копирующие и перемещающие операции, деструктор.
- [ ] `std::forward` и передача аргументов с сохранением категории значения.
- [ ] `= default`, `= delete`, `override`, `final`.
- [ ] Делегирующие конструкторы, наследование конструкторов и инициализаторы полей.
- [ ] `constexpr`, `static_assert`, `noexcept`.
- [ ] `enum class` — перечисления с областью видимости.
- [ ] Variadic templates — пакеты параметров шаблона.
- [x] [using в C++98–C++23](using/notes.md) — псевдонимы типов и шаблонов,
  наследование конструкторов, сравнение с `typedef` и практика.

## mutable

Для полей класса `mutable` существует с C++98:
теория и практика вынесены в [отдельный модуль](../c++98/mutable/notes.md).
В C++11 появилось его применение к лямбдам.

- [x] Поля класса: разрешение изменять поле в `const`-методе, например кеш результата.
- [x] [Лямбды](functional/lambdas.md): разрешение изменять захваченные по значению копии внутри лямбды;
  исходные переменные при этом не меняются.

## Стандартная библиотека

- [ ] `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, `std::make_shared` — владение ресурсами.
- [ ] `std::array`, `std::tuple`, `std::unordered_map`, `std::unordered_set`.
- [x] [std::function, std::bind и делегаты](functional/notes.md) — теория,
  [примеры](functional/examples.cpp) и [практика](functional/practice.md);
  `std::ref`, `std::cref`, время жизни обработчиков.
- [x] [Механизм событий](functional/events.md) — несколько подписчиков,
  идентификаторы подписок, отписка и изменение подписок при рассылке.
- [x] [Делегирование](../patterns/delegate.md) — передача работы другому объекту,
  варианты через callback и виртуальный интерфейс.
- [ ] `emplace` и `emplace_back` — создание элементов на месте.
- [ ] `std::chrono`, `<random>` и `std::to_string`.
- [ ] `std::thread`, мьютексы, `std::lock_guard`, `std::unique_lock`, `std::condition_variable`.
- [ ] `std::atomic`, гонки данных и основы модели памяти.
- [ ] `std::async`, `std::future`, `std::promise` — получение результатов асинхронных задач.

Отметка у модуля означает, что материалы подготовлены.
Самостоятельное выполнение практики отмечается отдельно.

## Сборка примеров C++11

Из корня проекта:

```bash
cmake -S . -B build
cmake --build build --target cpp11_functional_examples
./build/c++11/functional/cpp11_functional_examples
```

Дополнительные цели:

```bash
cmake --build build --target cpp11_lambda_examples cpp11_event_examples cpp11_event_checks cpp11_delegate_example
./build/c++11/functional/cpp11_lambda_examples
./build/c++11/functional/cpp11_event_examples
./build/c++11/functional/cpp11_event_checks
./build/c++11/functional/cpp11_delegate_example
```

Все эти цели собираются в режиме C++11 независимо от стандарта основной программы.

Для [модуля using](using/notes.md#сборка-и-наблюдение-за-выводом) есть отдельные
цели `cpp98_using_examples`, `cpp11_using_examples`, `cpp14_using_examples`,
`cpp17_using_examples`, `cpp20_using_examples` и `cpp23_using_examples`.
Они собирают один файл в разных стандартах для сравнения возможностей.
