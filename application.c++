#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>
#include <sstream>

using namespace std;

class Message {
    private:
        string name;
        string message;

    public:
        Message();
        Message(string name, string message);
        void setName(string name);
        string getName();
        void setMessage(string message);
        string getMessage();
};

Message::Message() {}

Message::Message(string name, string message) {
    setName(name);
    setMessage(message);
}

void Message::setName(string name) {
    this->name = name;
}

string Message::getName() {
    return name;
}

void Message::setMessage(string message) {
    this->message = message;
}

string Message::getMessage() {
    return message;
}

class Logger {
  private:
    Logger();
    Logger(const Logger& log) = delete; // non construction-copyable
    Logger& operator=(const Logger& log) = delete; // non copyable
    queue<Message> q; // Queue which multiple threads might add/remove from
    mutex m; // Mutex to protect this queue

    // Lazy initialization
  public:
    static Logger* getInstance();

    void AddToQueue(Message msg);

    void RemoveFromQueue();
};

Logger::Logger() {}

Logger* Logger::getInstance() {
    static Logger instance;
    return &instance;
}

void Logger::AddToQueue(Message msg) {
    std::lock_guard<std::mutex> guard(m);
    std::ostringstream ss;
    ss << std::this_thread::get_id();
    msg.setName(ss.str());
    q.push(msg);
}

void Logger::RemoveFromQueue() {
    Message msg;
    {
        std::lock_guard<std::mutex> guard(m);
        while (!q.empty()) {
            msg = q.front();
            cout << msg.getName() << ": " << msg.getMessage() << endl;
            q.pop();
        }
    }
}

int main() {
    Message M[5];
    for (int msg_num = 0; msg_num < 5; msg_num++)
        M[msg_num].setMessage("Message-" + to_string(msg_num));

    Logger* log = Logger::getInstance();
    try {
        thread t1(&Logger::AddToQueue, log, M[0]);
        thread t2(&Logger::AddToQueue, log, M[1]);
        thread t3(&Logger::AddToQueue, log, M[2]);
        thread t4(&Logger::AddToQueue, log, M[3]);
        thread t5(&Logger::AddToQueue, log, M[4]);

        this_thread::sleep_for(chrono::milliseconds(100));

        thread t6(&Logger::RemoveFromQueue, log);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
    }
    catch (const std::exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    return 0;
}
