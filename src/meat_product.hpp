#pragma once

#include "base_product.hpp"

namespace kitchen {

class MeatProduct final : public BaseProduct {   
private:
    std::string m_origin;  

public:
    MeatProduct(std::string_view name, double quantity, std::string_view origin);
    MeatProduct(const MeatProduct& other);
    ~MeatProduct() override;

    int GetShelfLifeDays() const override { return 3; }
    std::string Describe() const override;   
    std::unique_ptr<BaseProduct> Clone() const override;

    std::string_view GetOrigin() const { return m_origin; }
};

} 