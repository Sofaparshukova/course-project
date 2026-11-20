#pragma once

#include "base_product.hpp"
#include "i_consumable.hpp"
#include "product_exception.hpp"
#include <iostream>

namespace kitchen {

class KefirProduct final : public BaseProduct, public IConsumable {
private:
    bool m_available = true;

public:
    KefirProduct(std::string_view name, double quantity)
        : BaseProduct{ name, quantity } {}

    int GetShelfLifeDays() const override { return 5; }

    std::string Describe() const override {
        return BaseProduct::Describe() + ", кефир";
    }

    std::unique_ptr<BaseProduct> Clone() const override {
        return std::make_unique<KefirProduct>(*this);
    }

    void Consume(std::string_view user) override {
        if (!m_available) throw NoPortionsAvailable(GetName());
        m_available = false;
        std::cout << "  выдано «" << GetName() << "» пользователю " << user << "\n";
    }

    void Return() override { m_available = true; }
    bool IsAvailable() const override { return m_available; }
};

} 