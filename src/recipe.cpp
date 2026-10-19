#include "recipe.hpp"
#include <iostream>

namespace kitchen {

Recipe::Recipe(std::string_view name, int cookingTimeMinutes)
    : m_name{ name }, m_cookingTimeMinutes{ cookingTimeMinutes }
{
    if (cookingTimeMinutes <= 0) {
        std::cerr << "Ошибка: время приготовления должно быть положительным!\n";
        m_cookingTimeMinutes = 1;
    }
    std::cout << "Рецепт создан: " << m_name << "\n";
}

Recipe::~Recipe() {
    std::cout << "Рецепт уничтожен: " << m_name 
              << " (продукты живы — агрегация)\n";
}

void Recipe::AddIngredient(const std::shared_ptr<Product>& product) {
    if (!product) {
        std::cerr << "Ошибка: нельзя добавить пустой продукт!\n";
        return;
    }
    m_ingredients.push_back(product);
    std::cout << "В рецепт " << m_name << " добавлен: " 
              << product->GetName() << "\n";
}

bool Recipe::CanCook() const {
    for (const auto& weak : m_ingredients) {
        if (auto product = weak.lock()) {
            if (!product->CheckFreshness()) {
                std::cerr << "Нельзя приготовить: продукт испорчен — " 
                          << product->GetName() << "\n";
                return false;
            }
        } else {
            std::cerr << "Нельзя приготовить: продукт уже уничтожен\n";
            return false;
        }
    }
    return true;
}

void Recipe::ShowIngredients() const {
    std::cout << "Ингредиенты рецепта " << m_name << ":\n";
    for (const auto& weak : m_ingredients) {
        if (auto product = weak.lock()) {
            std::cout << "  - " << product->GetName() 
                      << " (" << product->GetQuantity() << ")\n";
        } else {
            std::cout << "  - (уничтожен)\n";
        }
    }
}

} // namespace kitchen