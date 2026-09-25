#include "recipe.hpp"
#include <iostream>

namespace kitchen {

Recipe::Recipe(std::string_view name, int cookingTimeMinutes)
    : m_name{ name }
    , m_cookingTimeMinutes{ cookingTimeMinutes }
{
    if (cookingTimeMinutes <= 0) {
        std::cerr << "Ошибка: время приготовления должно быть положительным!\n";
        m_cookingTimeMinutes = 1;
    }
    std::cout << "Рецепт создан: " << m_name << "\n";
}

Recipe::~Recipe() {
    std::cout << "Рецепт уничтожен: " << m_name 
              << " (продукты остались живы — агрегация)\n";
}

void Recipe::AddIngredient(Product* product) {
    if (product == nullptr) {
        std::cerr << "Ошибка: нельзя добавить пустой продукт!\n";
        return;
    }
    m_ingredients.push_back(product);
    std::cout << "В рецепт " << m_name << " добавлен: " 
              << product->GetName() << "\n";
}

bool Recipe::CanCook() const {
    for (const auto* product : m_ingredients) {
        if (!product->CheckFreshness()) {
            std::cerr << "Нельзя приготовить: продукт испорчен — " 
                      << product->GetName() << "\n";
            return false;
        }
    }
    return true;
}

void Recipe::ShowIngredients() const {
    std::cout << "Ингредиенты рецепта " << m_name << ":\n";
    for (const auto* product : m_ingredients) {
        std::cout << "  - " << product->GetName() 
                  << " (" << product->GetQuantity() << ")\n";
    }
}

} // namespace kitchen