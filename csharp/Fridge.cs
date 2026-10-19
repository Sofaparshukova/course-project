using System;
using System.Collections.Generic;

namespace Kitchen
{
    public class Fridge : IDisposable
    {
        private const int MaxCapacity = 10;
        public string Model { get; private set; }
        private readonly List<Product> _products = new List<Product>();
        
        private bool _isOpen = false;

        public Fridge(string model)
        {
            Model = model;
            Console.WriteLine($"Холодильник создан: {Model}");
        }

        public void Open()
        {
            if (_isOpen) return;
            _isOpen = true;
            Console.WriteLine($"Холодильник {Model} открыт");
        }

        public void Close()
        {
            if (!_isOpen) return;
            _isOpen = false;
            Console.WriteLine($"Холодильник {Model} закрыт");
        }

        public void Dispose()
        {
            Close();
        }

        public bool AddProduct(string name, double quantity, int shelfLifeDays)
        {
            if (_products.Count >= MaxCapacity)
            {
                Console.Error.WriteLine("Ошибка: холодильник переполнен!");
                return false;
            }
            _products.Add(new Product(name, quantity, shelfLifeDays));
            return true;
        }

        public int Count => _products.Count;

        public override string ToString() => $"{Model}: {_products.Count} продуктов";
    }
}