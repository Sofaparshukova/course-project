#include "src/fridge.hpp"
#include "src/product.hpp"
#include "src/recipe.hpp"

#include <iostream>

using namespace kitchen;

int main() {
    std::cout << "=== Демонстрация композиции и агрегации ===\n\n";

    std::cout << "--- Создание продуктов (вне рецепта) ---\n";
    Product* egg = new Product("Яйцо", 10, 7);
    Product* milk = new Product("Молоко", 2.0, 5);

    std::cout << "\n--- Создание холодильника (композиция) ---\n";
    {
        Fridge fridge("Samsung");

        fridge.AddProduct("Яйцо", 10, 7);
        fridge.AddProduct("Молоко", 2.0, 5);
        std::cout << "Продуктов в холодильнике: " << fridge.GetCount() << "\n";

        std::cout << "\n--- Создание рецепта (агрегация) ---\n";
        Recipe omelet("Омлет", 10);
        omelet.AddIngredient(egg);
        omelet.AddIngredient(milk);
        omelet.ShowIngredients();

        std::cout << "\n--- Проверка правила: можно ли приготовить? ---\n";
        if (omelet.CanCook()) {
            std::cout << "Всё свежее — можно готовить!\n";
        }

        std::cout << "\n--- Нарушение правила: портим продукт ---\n";
        egg->Spoil();

        if (!omelet.CanCook()) {
            std::cout << "Приготовление отменено!\n";
        }

        std::cout << "\n--- Конец блока: холодильник уничтожается ---\n";
    }

    std::cout << "\n--- Рецепт уничтожен, но продукты живы (агрегация) ---\n";
    std::cout << "Яйцо всё ещё существует: " << egg->GetName() << "\n";
    std::cout << "Молоко всё ещё существует: " << milk->GetName() << "\n";

    delete egg;
    delete milk;

    std::cout << "\n=== Программа завершена ===\n";
    return 0;
}