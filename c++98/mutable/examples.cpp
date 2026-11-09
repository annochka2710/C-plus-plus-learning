// C++98. Сборка и упражнения описаны в notes.md.

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

class TextStatistics {
public:
    explicit TextStatistics(const std::string& text)
        : text_(text), cache_valid_(false), cached_words_(0), calculations_(0) {}

    std::size_t word_count() const {
        if (!cache_valid_) {
            cached_words_ = 0;
            bool inside_word = false;

            for (std::string::size_type index = 0; index < text_.size(); ++index) {
                // isspace принимает EOF либо значение, представимое unsigned char.
                const unsigned char character = static_cast<unsigned char>(text_[index]);
                if (std::isspace(character)) {
                    inside_word = false;
                } else if (!inside_word) {
                    ++cached_words_;
                    inside_word = true;
                }
            }

            cache_valid_ = true;
            ++calculations_;
        }

        return cached_words_;
    }

    void set_text(const std::string& text) {
        text_ = text;
        // После изменения исходных данных прежний результат больше не подходит.
        cache_valid_ = false;
    }

    unsigned int calculations() const {
        return calculations_;
    }

private:
    std::string text_;                    // Основное состояние объекта.
    mutable bool cache_valid_;            // Вычислен ли результат для текущего текста.
    mutable std::size_t cached_words_;    // Кеш результата.
    mutable unsigned int calculations_;  // Счётчик реальных вычислений для демонстрации.
};

void show(const char* label, const TextStatistics& statistics) {
    // Сначала выполняем запрос, затем читаем счётчик: порядок задан явно.
    const std::size_t words = statistics.word_count();
    const unsigned int calculations = statistics.calculations();

    std::cout << label << ": слов=" << words
              << ", вычислений=" << calculations << '\n';
}

int main() {
    TextStatistics statistics("one two");
    const TextStatistics& view = statistics;

    std::cout << "Через const-ссылку:\n";
    show("Первый запрос", view);
    show("Повторный запрос", view);

    statistics.set_text("one  two\nthree");
    show("После изменения текста", view);

    statistics.set_text("");
    show("Пустой текст", view);

    // Даже у изначально const-объекта разрешено изменять mutable-поля.
    const TextStatistics fixed("alpha beta");
    std::cout << "Изначально const-объект:\n";
    show("Первый запрос", fixed);
    show("Повторный запрос", fixed);

    // view.set_text("new text");  // Ошибка: метод set_text не является const.
    // fixed.set_text("new text"); // Ошибка по той же причине.

    return 0;
}
