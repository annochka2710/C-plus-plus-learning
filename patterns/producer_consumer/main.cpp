#include "transponder.h"
#include "reader.h"
#include "writer.h"

int main() 
{
    Transponder transponder; // принимает от reader и выдаёт в writer
    Reader reader; // читает числа из cin
    Writer writer; // читает от transponder

    // Подписка
    Binder::connect(reader, transponder);
    Binder::connect(transponder, writer);
    
    // Чтение из стандартного потока ввода cin
    while(reader.exec()) {
        transponder.exec();
    }

    // Симуляция выдачи по таймеру в канал 0 и канал 1
    transponder.simulateCallBack0(42);
    transponder.simulateCallBack1(2026);

    return 0;
}