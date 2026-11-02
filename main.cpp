#include "src/base_product.hpp"
#include "src/dairy_product.hpp"
#include "src/meat_product.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>

using namespace kitchen;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "ЛАБА 4. Часть 1\n\n";

    // 1. КОНСТРУКТОРЫ:
    std::cout << "1. Создание объектов\n";
    auto milk = std::make_unique<DairyProduct>("Молоко", 2.0, "3.2%");
    auto beef = std::make_unique<MeatProduct>("Говядина", 1.5, "Россия");

    // 2. МАССИВ УКАЗАТЕЛЕЙ 
    std::cout << "\n2. Массив unique_ptr<BaseProduct>\n";
    std::vector<std::unique_ptr<BaseProduct>> products;
    products.push_back(std::make_unique<DairyProduct>("Сыр", 0.5, "45%"));
    products.push_back(std::make_unique<MeatProduct>("Курица", 1.0, "Беларусь"));
    products.push_back(std::make_unique<DairyProduct>("Кефир", 1.0, "1%"));

    for (const auto& p : products) {
        std::cout << "  " << p->Describe() << "\n";
    }

    // 3. через конструктор копирования
    std::cout << "\n3. Поверхностное копирование\n";
    DairyProduct original("Йогурт", 1.0, "2.5%");
    DairyProduct copy = original;  
    std::cout << "  Оригинал: " << original.Describe() << "\n";
    std::cout << "  Копия:    " << copy.Describe() << "\n";

    // 4. КОПИРОВАНИЕ ЧЕРЕЗ Clone()
    std::cout << "\n4. Глубокое копирование через Clone()\n";
    std::unique_ptr<BaseProduct> cloned = original.Clone();
    std::cout << "  Клон: " << cloned->Describe() << "\n";

    // 5. ПОЛИМОРФИЗМ
    std::cout << "\n5. Полиморфизм\n";
    BaseProduct* ptr1 = milk.get();
    BaseProduct* ptr2 = beef.get();
    std::cout << "  Через базовый указатель: " << ptr1->Describe() << "\n";
    std::cout << "  Через базовый указатель: " << ptr2->Describe() << "\n";

    // 6. ВИРТУАЛЬНЫЙ ДЕСТРУКТОР
    std::cout << "\n6. Удаление через unique_ptr<BaseProduct>\n";
    {
        std::unique_ptr<BaseProduct> temp = std::make_unique<MeatProduct>("Свинина", 2.0, "Россия");
    }
    std::cout << "(объект удалён - деструкторы вызваны в правильном порядке)\n";

    // 7. СТАТИЧЕСКИЕ ЧЛЕНЫ
    std::cout << "\n7. Статические члены\n";
    std::cout << "  Всего создано продуктов: " << BaseProduct::GetTotalCount() << "\n";

    std::cout << "\n Программа завершена\n";
    return 0;
}