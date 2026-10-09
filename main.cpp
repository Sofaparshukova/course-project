#include "src/fridge.hpp"
#include "src/product.hpp"
#include "src/recipe.hpp"

#include <iostream>

using namespace kitchen;

int main() {
    std::cout << "Композиция и агрегация\n\n";

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

    // 4. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ 

    std::cout << "\n Динамическая инициализация\n";
    Product* egg  = new Product("Яйцо", 10, 7);
    Product* milk = new Product("Молоко", 2.0, 5);


    // 5. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ 
    std::cout << "\n массив объектов \n";
    Product* productArray = new Product[3] {
        Product("Сыр", 0.5, 10),
        Product("Масло", 0.2, 7),
        Product("Кефир", 1.0, 3)
    };
    for (int i = 0; i < 3; ++i) {
        std::cout << "  arr[" << i << "] = " << productArray[i].GetName() << "\n";
    }


    // 6. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ
    std::cout << "\n массив динамических объектов \n";
    Product** ptrArray = new Product*[3];
    ptrArray[0] = new Product("Мука", 2.0, 30);
    ptrArray[1] = new Product("Сахар", 1.0, 60);
    ptrArray[2] = new Product("Соль", 0.5, 365);
    for (int i = 0; i < 3; ++i) {
        std::cout << "  ptrArr[" << i << "] = " << ptrArray[i]->GetName() << "\n";
    }


    // 7. КОМПОЗИЦИЯ 
    std::cout << "\n Композиция\n";
    {
        Fridge fridge("Samsung");
        fridge.AddProduct("Яйцо", 10, 7);
        fridge.AddProduct("Молоко", 2.0, 5);
        std::cout << "Продуктов в холодильнике: " << fridge.GetCount() << "\n";

        // 8. АГРЕГАЦИЯ 
        std::cout << "\n--- 8. Агрегация ---\n";
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


    // 12. ОЧИСТКА ПАМЯТИ
    std::cout << "\n Очистка памяти \n";
    delete egg;
    delete milk;
    delete[] productArray;

    for (int i = 0; i < 3; ++i) {
        delete ptrArray[i];
    }
    delete[] ptrArray;

    std::cout << "\nПрограмма завершена\n";
    return 0;
}