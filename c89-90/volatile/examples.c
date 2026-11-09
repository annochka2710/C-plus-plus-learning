/*
 * C89/C90. Запуск и просмотр ассемблера описаны в notes.md.
 * Функции оставлены внешними, чтобы их было легко найти в выводе -S.
 */

#include <stdio.h>

unsigned int read_twice(const unsigned int *value)
{
    unsigned int first;
    unsigned int second;

    first = *value;
    second = *value;
    return first + second;
}

unsigned int read_twice_volatile(const volatile unsigned int *value)
{
    unsigned int first;
    unsigned int second;

    /* Отдельные полные выражения: два отдельных чтения объекта. */
    first = *value;
    second = *value;
    return first + second;
}

void write_twice(unsigned int *value)
{
    *value = 1U;
    *value = 2U;
}

void write_twice_volatile(volatile unsigned int *value)
{
    /* Даже если итоговое значение равно 2, первая запись значима. */
    *value = 1U;
    *value = 2U;
}

int main(void)
{
    unsigned int ordinary = 10U;
    volatile unsigned int observed = 10U;

    printf("Обычное чтение: %u\n", read_twice(&ordinary));
    printf("Чтение volatile: %u\n", read_twice_volatile(&observed));

    write_twice(&ordinary);
    write_twice_volatile(&observed);
    printf("После обычных записей: %u\n", ordinary);
    printf("После volatile-записей: %u\n", observed);

    return 0;
}
