#pragma once
#include <string_view>

namespace kitchen {

// Контракт: продукт можно выдать/употребить на кухне
class IConsumable {
public:
    virtual ~IConsumable() = default;
    virtual void Consume(std::string_view user) = 0;
    virtual void Return() = 0;
    virtual bool IsAvailable() const = 0;
};

} 