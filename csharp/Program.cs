using System;
using System.Collections.Generic;
using Kitchen;

class Program
{
    static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;

        Console.WriteLine("ЛАБА 4. Часть 2 \n");

        // 1. СОЗДАНИЕ ОБЪЕКТОВ
        Console.WriteLine("1. Создание объектов");
        var milk = new DairyProduct("Молоко", 2.0, "3.2%");
        var beef = new MeatProduct("Говядина", 1.5, "Россия");

        // 2. ПОЛИМОРФИЗМ: массив базового класса
        Console.WriteLine("\n2. Полиморфизм: массив базового класса");
        var products = new List<BaseProduct>
        {
            new DairyProduct("Сыр", 0.5, "45%"),
            new MeatProduct("Курица", 1.0, "Беларусь"),
            new DairyProduct("Кефир", 1.0, "1%")
        };

        foreach (var p in products)
        {
            Console.WriteLine($"  {p.Describe()}");
        }

        // 3. ПОВЕРХНОСТНОЕ КОПИРОВАНИЕ (MemberwiseClone)
        Console.WriteLine("\n3. Поверхностное копирование");
        var original = new DairyProduct("Йогурт", 1.0, "2.5%");
        var shallowCopy = (DairyProduct)original.Clone();
        Console.WriteLine($"  Оригинал: {original.Describe()}");
        Console.WriteLine($"  Копия:    {shallowCopy.Describe()}");

        // 4. СРАВНЕНИЕ ПО СОДЕРЖИМОМУ 
        Console.WriteLine("\n4. Сравнение по содержимому");
        var milk1 = new DairyProduct("Молоко", 2.0, "3.2%");
        var milk2 = new DairyProduct("Молоко", 2.0, "3.2%");
        Console.WriteLine($"  milk1 == milk2 (ссылки): {ReferenceEquals(milk1, milk2)}");
        Console.WriteLine($"  milk1.Equals(milk2): {milk1.Equals(milk2)}");

        // 5. СТАТИЧЕСКИЕ ЧЛЕНЫ
        Console.WriteLine("\n5. Статические члены");
        Console.WriteLine($"  Всего создано продуктов: {BaseProduct.GetTotalCount()}");

        // 6. ОСВОБОЖДЕНИЕ РЕСУРСА
        Console.WriteLine("\n6. Использование using");
        using (var log = new ProductLog("Кухня"))
        {
            log.Write("Начали готовку");
        }

        Console.WriteLine("\nПрограмма завершена");
    }
}

// Вспомогательный класс для демонстрации using
public class ProductLog : IDisposable
{
    private readonly string _title;
    
    public ProductLog(string title)
    {
        _title = title;
        Console.WriteLine($"[+] Журнал открыт: {_title}");
    }
    
    public void Write(string line) => Console.WriteLine($"  {line}");
    
    public void Dispose() => Console.WriteLine($"[-] Журнал закрыт: {_title}");
}