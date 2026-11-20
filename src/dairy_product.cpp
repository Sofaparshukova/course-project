#include "dairy_product.hpp"
#include "product_exception.hpp"
#include "standard_policy.hpp"
#include <iostream>
#include <memory>

namespace kitchen {

DairyProduct::DairyProduct(std::string_view name, double quantity,
                           std::string_view fatContent,
                           std::unique_ptr<IIssuePolicy> policy)
    : BaseProduct{ name, quantity }
    , m_fatContent{ fatContent }
    , m_policy{ policy ? std::move(policy) : std::make_unique<StandardPolicy>() }
{
    std::cout << "DairyProduct(): " << GetName() << "\n";
}

DairyProduct::DairyProduct(const DairyProduct& other)
    : BaseProduct{ other }
    , m_fatContent{ other.m_fatContent }
    , m_policy{ std::make_unique<StandardPolicy>() }
    , m_available{ other.m_available }
{
    std::cout << "DairyProduct(const&): " << GetName() << "\n";
}

DairyProduct::DairyProduct(DairyProduct&& other) noexcept
    : BaseProduct{ std::move(other) }
    , m_fatContent{ std::move(other.m_fatContent) }
    , m_policy{ std::move(other.m_policy) }
    , m_available{ other.m_available }
{
    std::cout << "DairyProduct(&&): " << GetName() << "\n";
}

DairyProduct::~DairyProduct() {
    std::cout << "~DairyProduct(): " << GetName() << "\n";
}

std::string DairyProduct::Describe() const {
    return BaseProduct::Describe() + ", жирность " + m_fatContent
         + ", политика: " + PolicyName();
}

std::unique_ptr<BaseProduct> DairyProduct::Clone() const {
    return std::make_unique<DairyProduct>(*this);
}

void DairyProduct::Consume(std::string_view user) {
    if (!m_available) {
        throw NoPortionsAvailable(GetName());
    }
    if (!m_policy->CanIssue(user)) {
        throw std::runtime_error("политика не разрешает выдачу пользователю: "
                                 + std::string(user));
    }
    m_available = false;
    std::cout << "  выдано «" << GetName() << "» пользователю " << user << "\n";
}

} 