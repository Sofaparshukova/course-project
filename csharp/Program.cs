using System;
using Kitchen;

class Program
{
    static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        Console.WriteLine(" ЛАБА 3\n");

        Console.WriteLine(" 1. Ссылки и копии ");
        var egg = new Product("Яйцо", 10, 7);
        var milk = new Product("Молоко", 2.0, 5);
        var eggCopy = egg;
        eggCopy.Spoil();
        Console.WriteLine($"Оригинал испорчен? {egg.IsSpoiled}");

        Console.WriteLine("\n 2. Композиция ");
        var fridge = new Fridge("Samsung");
        fridge.AddProduct("Яйцо", 10, 7);
        fridge.AddProduct("Молоко", 2.0, 5);
        Console.WriteLine($"Продуктов в холодильнике: {fridge.Count}");

        Console.WriteLine("\n 3. Агрегация");
        var omelet = new Recipe("Омлет", 10);
        omelet.AddIngredient(egg);
        omelet.AddIngredient(milk);
        omelet.ShowIngredients();

        Console.WriteLine("\n4. Проверка правила");
        if (omelet.CanCook())
            Console.WriteLine("Всё свежее — можно готовить!");
        else
            Console.WriteLine("Приготовление отменено!");

        Console.WriteLine("\n 5. Освобождение ресурса (using)");
        using (var fridgeToUse = new Fridge("LG"))
        {
            fridgeToUse.Open();
            fridgeToUse.AddProduct("Яйцо", 10, 7);
            Console.WriteLine($"Продуктов в холодильнике: {fridgeToUse.Count}");
        }

        Console.WriteLine("\n6. Сборщик мусора");
        var tempRef = CreateTemporary();
        GC.Collect();
        GC.WaitForPendingFinalizers();
        Console.WriteLine($"Объект жив? {tempRef.TryGetTarget(out _)}");

        Console.WriteLine("\nПрограмма завершена");
    }

    [System.Runtime.CompilerServices.MethodImpl(
        System.Runtime.CompilerServices.MethodImplOptions.NoInlining)]
    static WeakReference<Product> CreateTemporary()
    {
        var temp = new Product("Просроченный кефир", 1, 1);
        return new WeakReference<Product>(temp);
    }
}