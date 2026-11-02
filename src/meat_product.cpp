#include "meat_product.hpp"
#include <iostream>
#include <memory>

namespace kitchen {

MeatProduct::MeatProduct(std::string_view name, double quantity, std::string_view origin)
    : BaseProduct{ name, quantity }
    , m_origin{ origin }
{
    std::cout << "MeatProduct(): " << GetName() << "\n";
}

MeatProduct::MeatProduct(const MeatProduct& other)
    : BaseProduct{ other }
    , m_origin{ other.m_origin }
{
    std::cout << "MeatProduct(const&): " << GetName() << "\n";
}

MeatProduct::~MeatProduct() {
    std::cout << "~MeatProduct(): " << GetName() << "\n";
}

std::string MeatProduct::Describe() const {
    
    return "Мясо «" + std::string(GetName()) + "» из " + m_origin 
         + ", срок хранения " + std::to_string(GetShelfLifeDays()) + " дн.";
}

std::unique_ptr<BaseProduct> MeatProduct::Clone() const {
    return std::make_unique<MeatProduct>(*this);
}

} 