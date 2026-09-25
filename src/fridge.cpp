#include "fridge.hpp"
#include <iostream>

namespace kitchen {

Fridge::Fridge(std::string_view model)
    : m_model{ model }
{
    std::cout << "Холодильник создан: " << m_model << "\n";
}

Fridge::~Fridge() {
    std::cout << "Холодильник уничтожен: " << m_model << "\n";
}

bool Fridge::AddProduct(std::string_view name, double quantity, int shelfLifeDays) {
    if (static_cast<int>(m_products.size()) >= MAX_CAPACITY) {
        std::cerr << "Ошибка: холодильник переполнен!\n";
        return false;
    }
    m_products.emplace_back(name, quantity, shelfLifeDays);
    return true;
}

bool Fridge::CookDish(std::string_view productName, double amount) {
    for (auto& product : m_products) {
        if (product.GetName() == productName) {
            return product.Use(amount);
        }
    }
    std::cerr << "Продукт не найден: " << productName << "\n";
    return false;
}

int Fridge::CheckAllFreshness() const {
    int freshCount = 0;
    for (const auto& product : m_products) {
        if (product.CheckFreshness()) {
            ++freshCount;
        }
    }
    return freshCount;
}

} // namespace kitchen