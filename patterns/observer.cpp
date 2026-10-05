#include <iostream>
#include <queue>
using namespace std;

struct Message {
    int value;
};

class IReader {
public:
    virtual void recv(const Message& m) = 0;
};

class Writer {
public:
    Writer(IReader* reader) : reader_(reader) {
        // Create test data
        for(int i = 0; i < 5; i++) {
            Message m{.value = i};
            q_.push(m);
        }
    }
    void send(const Message &m) {
        if(reader_) {
            reader_->recv(m);
        }
    }
    void exec() {
        if(!q_.empty()) {
            send(q_.front());
            q_.pop();
        }
    }
private:
    std::queue<Message> q_;
    IReader* reader_;
};

class Reader : public IReader {
public:
    void recv(const Message &msg) override {
        std::cout << " [" << msg.value << "] ";
    }
};

int main() 
{
    Reader r;
    Writer w(&r);

    for(int i = 0; i < 5; i++) {
        w.exec();
    }

    return 0;
}
