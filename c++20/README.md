# C++20

Краткий план изучения основных нововведений относительно C++17.
Для каждой темы — небольшой пример и сравнение с прежним подходом.

## Язык

- [ ] Concepts и `requires` — ограничения параметров шаблонов.
- [ ] Сокращённые шаблоны функций: параметры `auto` и ограничения concepts.
- [ ] Оператор `<=>` и автоматически генерируемые сравнения.
- [ ] Назначенные инициализаторы: `.field = value` для агрегатов.
- [ ] `consteval`, `constinit` и расширенные возможности `constexpr`.
- [ ] Лямбды с явными параметрами шаблона и захватом пакета параметров.
- [x] [using enum](../c++11/using/notes.md#c20-using-enum-и-отдельный-элемент-enum-class)
  и отдельные элементы scoped enum через `using`.
- [ ] Начальная инструкция в range-based `for`.

## Стандартная библиотека

- [ ] `std::bind_front` — привязка первых аргументов;
  сравнить с [std::bind и лямбдами из C++11](../c++11/functional/notes.md).
- [ ] Ranges: `std::ranges`, алгоритмы и ленивые представления `std::views`.
- [ ] `std::span` — представление непрерывной последовательности без владения.
- [ ] `std::format` — форматирование строк.
- [ ] `std::string::starts_with`, `ends_with`; `contains` у ассоциативных контейнеров.
- [ ] `std::erase`, `std::erase_if` — удаление элементов контейнеров.
- [ ] `<bit>`, `std::bit_cast`, `std::endian` и математические константы `std::numbers`.
- [ ] Расширения `std::chrono`: календарь и часовые пояса.

## Многопоточность и продвинутые темы

- [x] [std::jthread и std::stop_token](threads/notes.md) — автоматическое ожидание
  завершения, запрос остановки, `std::this_thread` и передача ссылок через `std::ref`.
- [ ] `std::latch`, `std::barrier`, семафоры — синхронизация потоков.
- [ ] Атомарные `wait`/`notify` и `std::atomic_ref`.
- [ ] Корутины: `co_await`, `co_yield`, `co_return` и жизненный цикл.
- [ ] Модули: `export`, `import` и отличие от заголовочных файлов.

Отметка означает, что материалы подготовлены. Самостоятельная практика
отмечается отдельно.

## Сборка примеров потоков

Из корня проекта:

```bash
cmake -S . -B build
cmake --build build --target cpp11_ref_examples cpp11_this_thread_examples cpp20_jthread_examples
./build/c++20/threads/cpp11_ref_examples
./build/c++20/threads/cpp11_this_thread_examples
./build/c++20/threads/cpp20_jthread_examples
```

Примеры `std::ref` и `std::this_thread` собираются в C++11, `std::jthread` — в C++20.
