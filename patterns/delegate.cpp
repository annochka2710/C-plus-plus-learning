#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

// Получатель поручения: умеет доставлять сообщение в консоль.
class ConsoleSender {
public:
    void send(const std::string& message) const {
        std::cout << "console: " << message << '\n';
    }
};

// Делегирующий объект: знает, КОГДА нужно уведомить,
// а конкретный способ доставки получает извне.
class ReportService {
public:
    using Sender = std::function<void(const std::string&)>;

    explicit ReportService(Sender sender) : sender_(std::move(sender)) {
        if (!sender_) {
            throw std::invalid_argument("Report sender is required");
        }
    }

    void complete(const std::string& title) const {
        const std::string message = "Report ready: " + title;
        sender_(message); // Передаём часть работы делегату.
    }

private:
    Sender sender_;
};

int main() {
    const ConsoleSender console;
    const ReportService reports([&console](const std::string& message) {
        console.send(message);
    });
    reports.complete("sales");

    // Тот же сервис с другой реализацией доставки.
    std::string captured;
    const ReportService recording([&captured](const std::string& message) {
        captured = message;
    });
    recording.complete("inventory");
    std::cout << "recorded: " << captured << '\n';
}
