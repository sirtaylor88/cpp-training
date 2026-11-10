#include <iostream>

int main() {
    std::string username;
    int user_age;

    std::cout << "What is your name? ";
    std::cin >> username;

    std::cout << "What is your age? ";
    std::cin >> user_age;

    std::cout << "Hello, " << username
            << "! You are " << user_age << " years old." << std::endl;

    return 0;
}
