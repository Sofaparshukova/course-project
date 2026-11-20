#pragma once

#include "product.hpp"
#include <vector>
#include <string_view>
#include <memory>

namespace kitchen {

class Recipe {
private:
    std::string m_name;
    std::vector<std::weak_ptr<Product>> m_ingredients;
    int m_cookingTimeMinutes;

public:
    Recipe() = delete;
    Recipe(std::string_view name, int cookingTimeMinutes);
    ~Recipe();

    void AddIngredient(const std::shared_ptr<Product>& product);
    bool CanCook() const;
    void ShowIngredients() const;

    std::string_view GetName() const { return m_name; }
};

} // namespace kitchen