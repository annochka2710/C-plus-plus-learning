#include "transponder.h"
#include "reader.h"
#include "writer.h"

int main()
{
    // Цепочка передачи данных:
    //   cin -> Reader -> Transponder -> Writer -> cout
    Reader reader;            // источник: читает числа из cin
    Transponder transponder;  // посредник: принимает данные и передаёт дальше
    Writer writer;            // приёмник: печатает в cout

    // Подписка: соединяем звенья цепочки
    Binder::connect(reader, transponder);
    Binder::connect(transponder, writer);

    // Режим 1 - эхо: каждое прочитанное число сразу уходит дальше по цепочке
    while (reader.readNext()) {
        transponder.forwardQueued();
    }

    // Режим 2 - выдача по таймеру: значение приходит не из cin,
    // а от "железа" (Word), как будто сработало прерывание
    transponder.onTimer0(42);
    transponder.onTimer1(2026);

    return 0;
}
