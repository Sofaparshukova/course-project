#include "dairy_product.hpp"
#include <iostream>
#include <memory>

namespace kitchen {

DairyProduct::DairyProduct(std::string_view name, double quantity, std::string_view fatContent)
    : BaseProduct{ name, quantity }   
    , m_fatContent{ fatContent }
{
    std::cout << "DairyProduct(): " << GetName() << "\n";
}

DairyProduct::DairyProduct(const DairyProduct& other)
    : BaseProduct{ other }            
    , m_fatContent{ other.m_fatContent }
{
    std::cout << "DairyProduct(const&): " << GetName() << "\n";
}

DairyProduct::~DairyProduct() {
    std::cout << "~DairyProduct(): " << GetName() << "\n";
}

std::string DairyProduct::Describe() const {
    return BaseProduct::Describe() + ", жирность " + m_fatContent;
    
}

std::unique_ptr<BaseProduct> DairyProduct::Clone() const {
    return std::make_unique<DairyProduct>(*this);
}

} 