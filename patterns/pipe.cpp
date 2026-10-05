#include <iostream>
#include <queue>
using namespace std;

template<class T, class A, class B>
class Pipe {
public:
    Pipe(A& a, B& b)
    : a_(a), b_(b) {

    }
    void exec(void) {
        T m;
        while(a_.get(m)) { // potentially stuck
            b_.recv(m);
        }
    }

private:
    A& a_;
    B& b_;
};

struct Message {
    int value;
};

class Writer {
public:
    Writer() {
        // Create test data
        for(int i = 0; i < 5; i++) {
            Message m{.value = i};
            q_.push(m);
        }
        std::cout << std::endl;
    }
    bool get(Message &m) {
        if(!q_.empty()) {
            m = q_.front();
            q_.pop();
            return true;
        } else {
            return false;
        }
    }
private:
    std::queue<Message> q_;
};

class Reader {
public:
    void recv(const Message &msg) {
        std::cout << " [" << msg.value << "] ";
    }
};

int main() 
{
    Writer w;
    Reader r;
    Pipe<Message, Writer, Reader> pipe(w, r);

    for(int i = 0; i < 5; i++) {
        pipe.exec();
    }

    return 0;
}
