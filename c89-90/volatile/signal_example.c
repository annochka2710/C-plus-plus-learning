/* C89/C90. Запустить в терминале и один раз нажать Ctrl+C. */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static volatile sig_atomic_t stop_requested = 0;

static void handle_interrupt(int signal_number)
{
    (void)signal_number;

    /* Обработчик только присваивает флагу значение. Здесь нет printf. */
    stop_requested = 1;
}

int main(void)
{
    if (signal(SIGINT, handle_interrupt) == SIG_ERR) {
        fputs("Не удалось установить обработчик SIGINT.\n", stderr);
        return EXIT_FAILURE;
    }

    puts("Ожидаю SIGINT. Нажми Ctrl+C один раз.");
    fflush(stdout);

    while (!stop_requested) {
        /* Учебное активное ожидание: условие снова читает флаг. */
    }

    puts("Флаг получен. Программа завершилась через main.");
    return EXIT_SUCCESS;
}
