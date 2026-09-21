#include "five_rule_test.hpp"

#include <iostream>
#include <string_view>
#include <utility>

// const Buffer& = ссылка только для чтения:
//   & - объект не копируется (иначе на каждый вызов print срабатывал бы конструктор копирования)
//   const - функция обещает не менять буфер, компилятор это проверяет
// внутри buf[i] вызывает const-версию operator[], get_size() тоже const-метод
void print(std::string_view name, const Buffer& buf) {
    std::cout << name << " (size " << buf.get_size() << "):";
    for (std::size_t i = 0; i < buf.get_size(); ++i) {
        std::cout << ' ' << buf[i];
    }
    std::cout << '\n';
}

int main() {
    Buffer a(5);
    for (std::size_t i = 0; i < a.get_size(); ++i) {
        a[i] = static_cast<int>(i * 10);
    }
    print("a", a);

    // 1. конструктор копирования
    Buffer b = a;
    b[0] = 111; // меняем копию - оригинал не должен измениться
    print("b = copy of a", b);
    print("a after copy", a);

    // 2. копирующее присваивание
    Buffer c(2);
    c = a;
    print("c = a", c);

    // самоприсваивание не должно ничего сломать
    c = c;
    print("c = c", c);

    // 3. конструктор перемещения: d забирает память a, a остается пустым
    Buffer d = std::move(a);
    print("d = move(a)", d);
    print("a after move", a);

    // 4. перемещающее присваивание
    Buffer e(1);
    e = std::move(b);
    print("e = move(b)", e);
    print("b after move", b);

    return 0;
    // 5. деструкторы: каждый блок памяти освобождается ровно один раз
}
