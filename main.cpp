#include <iostream>
#include <functional>
#include <future>
#include <thread>

void produce_data(std::promise<int> &p)
{
    int i = 42;
    p.set_value(i);
}

void consume_data(std::future<int> &f)
{
    std::cout << "got data: " << f.get();
}

int main(void)
{
    //std::packaged_task<int(int,int)> task(add);
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::thread my_thread(produce_data, std::ref(promise));
    std::thread my_thread2(consume_data, std::ref(future));

    my_thread.join();
    my_thread2.join();

    return 0;
}
