using System;

namespace Kitchen
{
    public class DairyProduct : BaseProduct
    {
        public string FatContent { get; }

        // Вызов конструктора базового класса 
        public DairyProduct(string name, double quantity, string fatContent)
            : base(name, quantity)
        {
            FatContent = fatContent;
            Console.WriteLine($"DairyProduct(): {Name}");
        }

        // Переопределение абстрактного свойства
        public override int ShelfLifeDays => 7;

        // Переопределение с вызовом базового метода
        public override string Describe()
        {
            return base.Describe() + $", жирность {FatContent}";
        }

        // Клонирование
        public override BaseProduct Clone()
        {
            // Глубокая копия
            var copy = (DairyProduct)MemberwiseClone();
            return copy;
        }
    }
}