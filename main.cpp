#include "src/fridge.hpp"
#include "src/product.hpp"
#include "src/recipe.hpp"

#include <iostream>
#include <memory>
#include <windows.h>

using namespace kitchen;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Композиция и агрегация (Умные указатели)\n\n";

    // 1. СТАТИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ 
    std::cout << "Статическая инициализация\n";
    Product staticProduct("Хлеб", 1.0, 5);
    std::cout << "Создан: " << staticProduct.GetName() << "\n";

    // 2. РАБОТА ПО ССЫЛКЕ
    std::cout << "\n Работа по ссылке \n";
    Product& ref = staticProduct;
    std::cout << "Через ссылку: " << ref.GetName() << "\n";

    // 3. РАБОТА ПО УКАЗАТЕЛЮ
    std::cout << "\n3. Работа по указателю\n";
    Product* ptr = &staticProduct;
    std::cout << "Через указатель: " << ptr->GetName() << "\n";

    // 4. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ (shared_ptr вместо new)
    std::cout << "\n Динамическая инициализация\n";
    auto egg  = std::make_shared<Product>("Яйцо", 10, 7);
    auto milk = std::make_shared<Product>("Молоко", 2.0, 5);

    // 5. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ (unique_ptr)
    std::cout << "\n массив объектов (unique_ptr) \n";
    {
        // Используем unique_ptr для массива указателей на объекты
        auto productArray = std::make_unique<std::unique_ptr<Product>[]>(3);
        productArray[0] = std::make_unique<Product>("Сыр", 0.5, 10);
        productArray[1] = std::make_unique<Product>("Масло", 0.2, 7);
        productArray[2] = std::make_unique<Product>("Кефир", 1.0, 3);
        for (int i = 0; i < 3; ++i) {
            std::cout << "  arr[" << i << "] = " << productArray[i]->GetName() << "\n";
        }
    }

    // 6. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ
    std::cout << "\n массив динамических объектов (unique_ptr) \n";
    {
        auto ptrArray = std::make_unique<std::unique_ptr<Product>[]>(3);
        ptrArray[0] = std::make_unique<Product>("Мука", 2.0, 30);
        ptrArray[1] = std::make_unique<Product>("Сахар", 1.0, 60);
        ptrArray[2] = std::make_unique<Product>("Соль", 0.5, 365);
        for (int i = 0; i < 3; ++i) {
            std::cout << "  ptrArr[" << i << "] = " << ptrArray[i]->GetName() << "\n";
        }
    }

    // 7. КОМПОЗИЦИЯ 
    std::cout << "\n Композиция\n";
    {
        Fridge fridge("Samsung");
        fridge.AddProduct("Яйцо", 10, 7);
        fridge.AddProduct("Молоко", 2.0, 5);
        std::cout << "Продуктов в холодильнике: " << fridge.GetCount() << "\n";

        // 8. АГРЕГАЦИЯ 
        std::cout << " Агрегация \n";
        Recipe omelet("Омлет", 10);
        omelet.AddIngredient(egg);
        omelet.AddIngredient(milk);
        omelet.ShowIngredients();

        // 9. ПРОВЕРКА ПРАВИЛА 
        std::cout << "\n Проверка правила\n";
        if (omelet.CanCook()) {
            std::cout << "Всё свежее — можно готовить!\n";
        }

        // 10. НАРУШЕНИЕ ПРАВИЛА
        std::cout << "\n Нарушение правила \n";
        egg->Spoil();
        if (!omelet.CanCook()) {
            std::cout << "Приготовление отменено\n";
        }

        std::cout << "\nВыход из блока: холодильник уничтожается\n";
    }

    // 11. АГРЕГАЦИЯ: продукты живы
    std::cout << "\n Рецепт уничтожен, но продукты живы\n";
    std::cout << "Яйцо всё ещё существует: " << egg->GetName() << "\n";
    std::cout << "Молоко всё ещё существует: " << milk->GetName() << "\n";

    std::cout << "\nПрограмма завершена\n";
    return 0;
}