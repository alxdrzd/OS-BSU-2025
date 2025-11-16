#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <queue>
#include <condition_variable>
#include <mutex>
#include <stdexcept>

template <class T>
class BufferedChannel
{
public:
    explicit BufferedChannel(int size) : size_(size), closed_(false) {}

    void Send(T value)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        cv_can_send_.wait(lock, [this] {
            queue_.size() <= this->size_ || closed_;
        });

        if (closed_) {
            throw std::runtime_error("meow :(");
        }

        queue_.push(std::move(value));
        
        cv_can_receive_.notify_one();
    }

    std::pair<T, bool> Recv()
    {
    }

    void Close()
    {
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    int size_;
    std::condition_variable cv_can_send_;
    std::condition_variable cv_can_receive_;
    bool closed_;
};

#endif // BUFFERED_CHANNEL_H_