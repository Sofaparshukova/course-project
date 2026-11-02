#include "base_product.hpp"
#include <iostream>
#include <utility>

namespace kitchen {

BaseProduct::BaseProduct(std::string_view name, double quantity)
    : m_id{ NextId() }
    , m_name{ name }
    , m_quantity{ quantity }
{
    if (quantity < 0) {
        std::cerr << "Ошибка: количество не может быть отрицательным\n";
        m_quantity = 0;
    }
    std::cout << "BaseProduct(): " << m_name << " (id=" << m_id << ")\n";
}

BaseProduct::BaseProduct(const BaseProduct& other)
    : m_id{ NextId() }
    , m_name{ other.m_name }
    , m_quantity{ other.m_quantity }
{
    std::cout << "BaseProduct(const&): " << m_name << " (id=" << m_id << ")\n";
}

BaseProduct::BaseProduct(BaseProduct&& other) noexcept
    : m_id{ other.m_id }
    , m_name{ std::move(other.m_name) }
    , m_quantity{ other.m_quantity }
{
    other.m_quantity = 0;
    std::cout << "BaseProduct(&&): " << m_name << "\n";
}

BaseProduct& BaseProduct::operator=(const BaseProduct& other) {
    if (this == &other) {
        return *this;
    }
    m_name = other.m_name;
    m_quantity = other.m_quantity;
    std::cout << "BaseProduct::operator=(const&): " << m_name << "\n";
    return *this;
}

BaseProduct& BaseProduct::operator=(BaseProduct&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    m_name = std::move(other.m_name);
    m_quantity = other.m_quantity;
    other.m_quantity = 0;
    std::cout << "BaseProduct::operator=(&&): " << m_name << "\n";
    return *this;
}

BaseProduct::~BaseProduct() {
    std::cout << "~BaseProduct(): " << m_name << "\n";
}

std::string BaseProduct::Header() const {
    return m_name + " (id=" + std::to_string(m_id) + ")";
}

std::string BaseProduct::Describe() const {
    return Header() + ", срок хранения " + std::to_string(GetShelfLifeDays()) + " дн.";
}

} 