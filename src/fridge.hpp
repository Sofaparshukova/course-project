#pragma once

#include "product.hpp"
#include <vector>
#include <string_view>

namespace kitchen {

class Fridge {
private:
    static constexpr int MAX_CAPACITY = 10;
    std::vector<Product> m_products;
    std::string m_model;

public:
    Fridge() = delete;
    explicit Fridge(std::string_view model);
    ~Fridge();

    bool AddProduct(std::string_view name, double quantity, int shelfLifeDays);
    bool CookDish(std::string_view productName, double amount);
    int CheckAllFreshness() const;

    [[nodiscard]] std::string_view GetModel() const { return m_model; }
    [[nodiscard]] int GetCount() const { return static_cast<int>(m_products.size()); }
};

} // namespace kitchen