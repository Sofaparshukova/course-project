using System;

namespace Kitchen
{
    public class Product
    {
        public string Name { get; private set; }
        private double _quantity;
        public double Quantity
        {
            get => _quantity;
            private set => _quantity = Math.Max(0, value);
        }
        public int ShelfLifeDays { get; private set; }
        public bool IsSpoiled { get; private set; }

        public Product(string name, double quantity, int shelfLifeDays)
        {
            Name = name;
            Quantity = quantity;
            ShelfLifeDays = shelfLifeDays;
            IsSpoiled = false;

            if (quantity < 0)
            {
                Console.Error.WriteLine("Ошибка: количество не может быть отрицательным!");
                Quantity = 0;
            }
            if (shelfLifeDays < 0)
            {
                Console.Error.WriteLine("Ошибка: срок годности не может быть отрицательным!");
                ShelfLifeDays = 0;
            }
            Console.WriteLine($"Продукт создан: {Name}");
        }

        public bool Use(double amount)
        {
            if (IsSpoiled)
            {
                Console.Error.WriteLine($"Нельзя использовать испорченный продукт: {Name}");
                return false;
            }
            if (amount <= 0 || amount > Quantity)
            {
                Console.Error.WriteLine($"Недостаточно продукта: {Name}");
                return false;
            }
            Quantity -= amount;
            Console.WriteLine($"Использовано {amount} {Name}. Осталось: {Quantity}");
            return true;
        }

        public bool CheckFreshness() => !IsSpoiled;

        public void Spoil()
        {
            IsSpoiled = true;
            Console.WriteLine($"Продукт испортился: {Name}");
        }

        public override string ToString() => $"{Name} ({Quantity})";
    }
}