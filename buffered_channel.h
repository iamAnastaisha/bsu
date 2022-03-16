#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#ifndef CHANNEL_BUFFERED_CHANNEL_H
#define CHANNEL_BUFFERED_CHANNEL_H


template<class T>
class BufferedChannel {
 public:
    explicit BufferedChannel(int size) : size(size) {}

    void Send(T value) {
        std::unique_lock<std::mutex> locker(mtx);
        cond_var.wait(locker, [this] { return (!is_open && !isFree()); });
        if (!is_open)
            throw std::runtime_error("Channel is closed.");
        buffered_queue.push(value);
        mtx.unlock();
        cond_var.notify_one();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> locker(mtx);
        cond_var.wait(locker, [this] { return (!is_open &&!isEmpty()); });
        T value = buffered_queue.front();
        buffered_queue.pop();
        mtx.unlock();
        cond_var.notify_one();
        return std::make_pair<T, bool>(value, is_open);
    }

    void Close() {
        mtx.lock();
        is_open = false;
        mtx.unlock();
        cond_var.notify_all();
    }

 private:
    bool isFree() {return buffered_queue.size() < size; }
    bool isEmpty() {return buffered_queue.empty();}

    std::mutex mtx;
    int size;
    std::queue<T> buffered_queue;
    std::condition_variable cond_var;
    bool is_open = true;
};


#endif //CHANNEL_BUFFERED_CHANNEL_H
