#pragma once

#include <string>
#include <string_view>

namespace kitchen {

class Product {
private:
    std::string m_name;
    double m_quantity;
    int m_shelfLifeDays;
    bool m_isSpoiled;

public:
    Product() = delete;
    Product(std::string_view name, double quantity, int shelfLifeDays);
    ~Product();

    bool Use(double amount);
    bool CheckFreshness() const;
    void Spoil();

    [[nodiscard]] std::string_view GetName() const { return m_name; }
    [[nodiscard]] double GetQuantity() const { return m_quantity; }
    [[nodiscard]] bool IsSpoiled() const { return m_isSpoiled; }
};

} // namespace kitchen