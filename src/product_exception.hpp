#pragma once
#include <stdexcept>
#include <string>
#include <string_view>

namespace kitchen {

// Ошибка времени выполнения
class NoPortionsAvailable : public std::runtime_error {
public:
    explicit NoPortionsAvailable(std::string_view name)
        : std::runtime_error("нет свободных порций: " + std::string(name)) {}
};

// Нарушение логики
class InvalidQuantity : public std::logic_error {
public:
    explicit InvalidQuantity(double q)
        : std::logic_error("количество не может быть отрицательным: " + std::to_string(q)) {}
};

} 