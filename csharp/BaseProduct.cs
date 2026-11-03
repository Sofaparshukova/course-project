using System;

namespace Kitchen
{
    // Абстрактный класс
    public abstract class BaseProduct
    {
        // Статическое поле
        private static int _lastId = 0;

        public int Id { get; }
        public string Name { get; }
        public double Quantity { get; protected set; }

        // Защищённое свойство
        protected string Header => $"{Name} (id={Id})";

        protected BaseProduct(string name, double quantity)
        {
            Id = NextId();
            Name = name;
            Quantity = quantity;

            if (quantity < 0)
            {
                Console.Error.WriteLine("Ошибка: количество не может быть отрицательным!");
                Quantity = 0;
            }
            Console.WriteLine($"BaseProduct(): {Name} (id={Id})");
        }

        // Статический метод
        public static int NextId() => ++_lastId;
        public static int GetTotalCount() => _lastId;

        // Абстрактный метод
        public abstract int ShelfLifeDays { get; }

        // Виртуальный метод
        public virtual string Describe() => $"{Header}, срок хранения {ShelfLifeDays} дн.";

        // Абстрактный метод для клонирования
        public abstract BaseProduct Clone();

        // Для глубокого клонирования
        protected BaseProduct ShallowCopy() => (BaseProduct)MemberwiseClone();
    }
}