#pragma once

#include "product.hpp"
#include <vector>
#include <string_view>

namespace kitchen {

class Recipe {
private:
    std::string m_name;
    std::vector<Product*> m_ingredients;
    int m_cookingTimeMinutes;

public:
    Recipe() = delete;
    Recipe(std::string_view name, int cookingTimeMinutes);
    ~Recipe();

    void AddIngredient(Product* product);
    bool CanCook() const;
    void ShowIngredients() const;

    [[nodiscard]] std::string_view GetName() const { return m_name; }
    [[nodiscard]] int GetTime() const { return m_cookingTimeMinutes; }
    [[nodiscard]] int GetIngredientCount() const { return static_cast<int>(m_ingredients.size()); }
};

} // namespace kitchen