#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <future>

std::mutex queue_mtx;
std::condition_variable queue_cv;
std::queue<std::packaged_task<int()>> task_queue;

void worker_task(void)
{
    while (true)
    {
        std::unique_lock lock(queue_mtx);
        queue_cv.wait(lock, [] { std::cout << task_queue.empty() << std::endl; return !task_queue.empty(); });
        auto work = std::move(task_queue.front());
        work();
        std::future work_future = work.get_future();
        std::cout << "result : " << work_future.get() << "\n";
        task_queue.pop();
    }
}

int geometric_sum(const int &num)
{
    int sum = 0;
    for (int i = 0; i < num;  ++i)
    {
        sum += i;
    }

    return sum;
}
int main(void)
{
    // Dispatch worker
    std::thread worker_thread(worker_task);
    std::packaged_task<int()> work(std::bind(geometric_sum, 5));
    {
        std::unique_lock<std::mutex> lock(queue_mtx);
        task_queue.push(std::move(work));
    }
    queue_cv.notify_one();
    worker_thread.join();
    return 0;
}
