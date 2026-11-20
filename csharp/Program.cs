using System;
using System.Collections.Generic;
using Kitchen;

class Program
{
    static void IssueToUser(IConsumable item, string user)
    {
        if (item.IsAvailable)
            item.Consume(user);
    }

    // Проверка типа: is / as.
    static void TryConsume(BaseProduct item, string user)
    {
        if (item is IConsumable c)
        {
            try
            {
                c.Consume(user);
            }
            catch (NoPortionsAvailableException e)
            {
                Console.WriteLine($"  [исключение] {e.Message} — поставлен в очередь");
            }
            catch (Exception e)
            {
                Console.WriteLine($"  [исключение] {e.Message}");
            }
        }
        else
        {
            Console.WriteLine($"  {item.Name}: нельзя выдать (не IConsumable)");
        }
    }

    static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;

        Console.WriteLine(" ЛАБА 5. Часть 2 — Полиморфизм (C#)\n");

        // 1. Раннее и позднее связывание
        Console.WriteLine(" 1. Раннее и позднее связывание");
        var milk = new DairyProduct("Молоко", 2.0, "3.2%");
        var beef = new MeatProduct("Говядина", 1.5, "Россия");

        BaseProduct p1 = milk;
        BaseProduct p2 = beef;

        Console.WriteLine($"  p1.GetKind(): {p1.GetKind()}   (раннее)");
        Console.WriteLine($"  p1.Describe(): {p1.Describe()}   (позднее)");
        Console.WriteLine($"  p2.GetKind(): {p2.GetKind()}   (раннее)");
        Console.WriteLine($"  p2.Describe(): {p2.Describe()}   (позднее)");

        // 2. Работа через интерфейс
        Console.WriteLine("\n2. Работа через интерфейс IConsumable");
        try
        {
            IssueToUser(milk, "повар");
        }
        catch (Exception e)
        {
            Console.WriteLine($"  [исключение] {e.Message}");
        }

        // 3. Проверка типа: is / as
        TryConsume(milk, "повар");
        TryConsume(beef, "повар");

        // Чтобы использовать as, приводим к базовому типу BaseProduct
        BaseProduct beefAsBase = beef;
        var maybe = beefAsBase as IConsumable;
        Console.WriteLine($"  beef is IConsumable: {beef is IConsumable}");

        // 4. Исключение: порций больше нет
        Console.WriteLine("\n 4. Исключение NoPortionsAvailableException ");
        TryConsume(milk, "повар-2");

        // 5. Конфигурирование: смена объекта поведения
        Console.WriteLine("\n 5. Конфигурирование (динамическое)");
        var yogurt = new DairyProduct("Йогурт", 1.0, "2.5%");
        Console.WriteLine($"  Политика по умолчанию: {yogurt.PolicyName}");

        yogurt.SetPolicy(new GuestPolicy());
        Console.WriteLine($"  Новая политика: {yogurt.PolicyName}");

        TryConsume(yogurt, "повар Иванов");   // повару не выдаём — отказ политики
        TryConsume(yogurt, "гость Петров");   // гостю выдано

        // 6. Исключение из конструктора
        Console.WriteLine("\n 6. Исключение из конструктора ");
        try
        {
            var bad = new DairyProduct("Бракованный", -1.0, "0%");
        }
        catch (ArgumentException e)
        {
            Console.WriteLine($"  [исключение] {e.Message}");
        }
        finally
        {
            Console.WriteLine("  [finally] проверка конструктора завершена");
        }

        // 7. Стандартный интерфейс: IComparable
        Console.WriteLine("\n7. Сортировка через IComparable");
        var products = new List<BaseProduct>
        {
            new MeatProduct("Курица", 1.0, "Беларусь"),
            new DairyProduct("Сыр", 0.5, "45%"),
            new DairyProduct("Кефир", 1.0, "1%")
        };
        products.Sort();
        foreach (var p in products)
            Console.WriteLine($"  {p.Name}");

        // 8. USING: освобождение ресурса
        Console.WriteLine("\n8. Использование using");
        using (var log = new ProductLog("Кухня"))
        {
            log.Write("Начали готовку");
        }

        // 9. KefirProduct - второй класс с интерфейсом
        Console.WriteLine("\n 9. KefirProduct (второй IConsumable)");
        var kefir = new KefirProduct("Кефир", 1.0);
        TryConsume(kefir, "сотрудник Сидоров");

        Console.WriteLine("\nПрограмма завершена");
    }
}

// Вспомогательный класс для демонстрации using.
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