//
// Created by mrbgn on 4/18/21.
//

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#ifndef PRODUCER_CONSUMER_THREADPOOL_HPP
#define PRODUCER_CONSUMER_THREADPOOL_HPP

class ThreadPool {
 public:
  ThreadPool(size_t);
  template<class F, class... Args>
  void enqueue(F&& f, Args&& ...args);
//  -> std::future<typename std::result_of<F(Args...)>::type>;
  void Stop();
  ~ThreadPool() = default;
 private:
  // need to keep track of threads so we can join them
  std::vector< std::thread > workers;
  // the task queue
  std::queue< std::function<void()> > tasks;

  // synchronization
  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
    :   stop(false)
{
  for(size_t i = 0;i<threads;++i)
    workers.emplace_back(
        [this]
        {
          for(;;)
          {
            std::function<void()> task;

            {
              std::unique_lock<std::mutex> lock(this->queue_mutex);
              this->condition.wait(lock,
                                   [this]{ return this->stop || !this->tasks.empty(); });
              if(this->stop && this->tasks.empty())
                return;
              task = std::move(this->tasks.front());
              this->tasks.pop();
            }

            task();
          }
        }
    );
}

// add new work item to the pool
template<class F, class... Args>
void ThreadPool::enqueue(F&& f, Args&& ...args)
{

  auto task = std::make_shared< std::packaged_task<void()> >(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...)
  );

  {
    std::unique_lock<std::mutex> lock(queue_mutex);

    // don't allow enqueueing after stopping the pool
    if(stop)
      throw std::runtime_error("enqueue on stopped ThreadPool");

    tasks.emplace([task](){ (*task)(); });
  }
  condition.notify_one();
}

// the destructor joins all threads
inline void ThreadPool::Stop()
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }
  condition.notify_all();
  for(std::thread &worker: workers)
    worker.join();
}

#endif  // PRODUCER_CONSUMER_THREADPOOL_HPP
