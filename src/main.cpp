#include "pong.hpp"

#include <iostream>
#include <exception>
#include <memory>

int main() {
    std::unique_ptr<Pong::Pong> pong = std::make_unique<Pong::Pong>();

    try {
        pong->run();
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }

    return 0;
}
