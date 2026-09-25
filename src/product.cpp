#include "product.hpp"
#include <iostream>

namespace kitchen {

Product::Product(std::string_view name, double quantity, int shelfLifeDays)
    : m_name{ name }
    , m_quantity{ quantity }
    , m_shelfLifeDays{ shelfLifeDays }
    , m_isSpoiled{ false }
{
    if (quantity < 0) {
        std::cerr << "Ошибка: количество не может быть отрицательным!\n";
        m_quantity = 0;
    }
    if (shelfLifeDays < 0) {
        std::cerr << "Ошибка: срок годности не может быть отрицательным!\n";
        m_shelfLifeDays = 0;
    }
    std::cout << "Продукт создан: " << m_name << "\n";
}

Product::~Product() {
    std::cout << "Продукт уничтожен: " << m_name << "\n";
}

bool Product::Use(double amount) {
    if (m_isSpoiled) {
        std::cerr << "Нельзя использовать испорченный продукт: " << m_name << "\n";
        return false;
    }
    if (amount <= 0 || amount > m_quantity) {
        std::cerr << "Недостаточно продукта: " << m_name << "\n";
        return false;
    }
    m_quantity -= amount;
    std::cout << "Использовано " << amount << " " << m_name 
              << ". Осталось: " << m_quantity << "\n";
    return true;
}

bool Product::CheckFreshness() const {
    return !m_isSpoiled;
}

void Product::Spoil() {
    m_isSpoiled = true;
    std::cout << "Продукт испортился: " << m_name << "\n";
}

} // namespace kitchen