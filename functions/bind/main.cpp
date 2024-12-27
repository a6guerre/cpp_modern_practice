#include <iostream>
#include <functional>
#include <string>

void say_greeting(const std::string &greeting, const std::string &person)
{
    std::cout << greeting << " " << person << std::endl;
}

int main(void)
{
    auto callable = std::bind(say_greeting, "Hello", std::placeholders::_1);
    callable("Max"); 
    return 0;
}
