// Курсовой проект. Умная кухня.
// Автор: Паршукова С.М., группа ПИ-52

#include <iostream>
using namespace std;

int main() {
    int choice;
    
    do {
        cout << "\n=== Умная кухня ===\n";
        cout << "1. Показать продукты\n";
        cout << "2. Приготовить блюдо\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Список продуктов...\n";
                break;
            case 2:
                cout << "Приготовление...\n";
                break;
            case 0:
                cout << "Выход.\n";
                break;
            default:
                cout << "Нет такого пункта.\n";
        }
    } while (choice != 0);
    
    return 0;
}