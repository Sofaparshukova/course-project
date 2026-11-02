#pragma once

#include "base_product.hpp"

namespace kitchen {

class DairyProduct : public BaseProduct {
private:
    std::string m_fatContent;  

public:
    DairyProduct(std::string_view name, double quantity, std::string_view fatContent);
    DairyProduct(const DairyProduct& other);
    ~DairyProduct() override;

    int GetShelfLifeDays() const override { return 7; }
    std::string Describe() const override;   
    std::unique_ptr<BaseProduct> Clone() const override;

    std::string_view GetFatContent() const { return m_fatContent; }
};

} 