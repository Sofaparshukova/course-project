#include "src/base_product.hpp"
#include "src/dairy_product.hpp"
#include "src/meat_product.hpp"
#include "src/kefir_product.hpp"
#include "src/i_consumable.hpp"
#include "src/standard_policy.hpp"
#include "src/guest_policy.hpp"
#include "src/product_exception.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>

using namespace kitchen;
// Функция работает через интерфейс и не знает конкретных классов
void IssueToUser(IConsumable& item, std::string_view user) {
    if (item.IsAvailable()) {
        item.Consume(user);
    }
}

// Проверка типа во время выполнения
void TryConsume(BaseProduct& item, std::string_view user) {
    if (auto* c = dynamic_cast<IConsumable*>(&item)) {
        try {
            c->Consume(user);
        } catch (const NoPortionsAvailable& e) {
            std::cout << "  [исключение] " << e.what() << " — поставлен в очередь\n";
        } catch (const std::exception& e) {
            std::cout << "  [исключение] " << e.what() << "\n";
        }
    } else {
        std::cout << "  " << item.GetName() << ": нельзя выдать (не IConsumable)\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "ЛАБА 5. Часть 1 — Полиморфизм\n\n";

    // 1. Раннее и позднее связывание
    std::cout << "1. Раннее и позднее связывание\n";
    auto milk = std::make_unique<DairyProduct>("Молоко", 2.0, "3.2%");
    auto beef = std::make_unique<MeatProduct>("Говядина", 1.5, "Россия");

    BaseProduct* p1 = milk.get();
    BaseProduct* p2 = beef.get();
    std::cout << "  ptr1->GetKind(): " << p1->GetKind() << "  (раннее)\n";
    std::cout << "  ptr1->Describe(): " << p1->Describe() << "  (позднее)\n";
    std::cout << "  ptr2->GetKind(): " << p2->GetKind() << "  (раннее)\n";
    std::cout << "  ptr2->Describe(): " << p2->Describe() << "  (позднее)\n";

    // 2. Работа через интерфейс
    std::cout << "\n2. Работа через интерфейс IConsumable\n";
    try {
        IssueToUser(*milk, "повар");
    } catch (const std::exception& e) {
        std::cout << "  [исключение] " << e.what() << "\n";
    }

    // 3. dynamic_cast: мясо не реализует IConsumable
    std::cout << "\n3. dynamic_cast\n";
    TryConsume(*milk, "повар");
    TryConsume(*beef, "повар");

    // 4. Исключение: порций больше нет
    std::cout << "\n4. Исключение NoPortionsAvailable\n";
    TryConsume(*milk, "повар-2");

    // 5. Конфигурирование: смена объекта поведения
    std::cout << "\n5. Конфигурирование (динамическое)\n";
    auto yogurt = std::make_unique<DairyProduct>("Йогурт", 1.0, "2.5%");
    std::cout << "  Политика по умолчанию: " << yogurt->PolicyName() << "\n";

    yogurt->SetPolicy(std::make_unique<GuestPolicy>());
    std::cout << "  Новая политика: " << yogurt->PolicyName() << "\n";

    TryConsume(*yogurt, "повар Иванов");   
    TryConsume(*yogurt, "гость Петров");   

    // 6. Исключение из конструктора: отрицательное количество
    std::cout << "\n6. Исключение InvalidQuantity\n";
    try {
        DairyProduct bad("Бракованный", -1.0, "0%");
    } catch (const InvalidQuantity& e) {
        std::cout << "  [исключение] " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "  [исключение] " << e.what() << "\n";
    }

    // 7. Клонирование и второй класс с интерфейсом
    std::cout << "\n7. Клонирование и KefirProduct\n";
    auto kefir = std::make_unique<KefirProduct>("Кефир", 1.0);
    TryConsume(*kefir, "повар");

    std::vector<std::unique_ptr<BaseProduct>> products;
    products.push_back(milk->Clone());
    products.push_back(beef->Clone());
    products.push_back(kefir->Clone());
    for (const auto& p : products) {
        std::cout << "  " << p->Describe() << "\n";
    }

    std::cout << "\nПрограмма завершена\n";
    return 0;
}