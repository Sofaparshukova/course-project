using System;

namespace Kitchen
{
    //от этого класса нельзя наследоваться
    public sealed class MeatProduct : BaseProduct
    {
        public string Origin { get; }

        public MeatProduct(string name, double quantity, string origin)
            : base(name, quantity)
        {
            Origin = origin;
            Console.WriteLine($"MeatProduct(): {Name}");
        }

        // Переопределение абстрактного свойства
        public override int ShelfLifeDays => 3;

        // Переопределение без вызова базового метода
        public override string Describe()
        {
            return $"Мясо «{Name}» из {Origin}, срок хранения {ShelfLifeDays} дн.";
        }

        // Клонирование
        public override BaseProduct Clone()
        {
            return (MeatProduct)MemberwiseClone();
        }
    }
}