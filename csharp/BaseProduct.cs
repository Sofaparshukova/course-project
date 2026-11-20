using System;

namespace Kitchen
{
    // Абстрактный класс
    public abstract class BaseProduct : IComparable<BaseProduct>
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
                throw new ArgumentException("количество не может быть отрицательным", nameof(quantity));

            Console.WriteLine($"BaseProduct(): {Name} (id={Id})");
        }

        // Статический метод
        public static int NextId() => ++_lastId;
        public static int GetTotalCount() => _lastId;

        // Невиртуальный метод — раннее связывание.
        public string GetKind() => "продукт";

        // Абстрактный метод
        public abstract int ShelfLifeDays { get; }

        // Виртуальный метод
        public virtual string Describe() => $"{Header}, срок хранения {ShelfLifeDays} дн.";

        // Абстрактный метод для клонирования
        public abstract BaseProduct Clone();

         public int CompareTo(BaseProduct? other)
            => string.Compare(Name, other?.Name, StringComparison.CurrentCulture);

        // Сравнение по содержимому.
        public override bool Equals(object? obj)
            => obj is BaseProduct other && Id == other.Id && Name == other.Name;

        public override int GetHashCode() => HashCode.Combine(Id, Name);

        protected BaseProduct ShallowCopy() => (BaseProduct)MemberwiseClone();
    }
    
}