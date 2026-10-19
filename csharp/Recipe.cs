using System;
using System.Collections.Generic;

namespace Kitchen
{
    public class Recipe
    {
        public string Name { get; private set; }
        private readonly List<Product> _ingredients = new List<Product>();
        private int _cookingTimeMinutes;
        public int CookingTimeMinutes
        {
            get => _cookingTimeMinutes;
            private set => _cookingTimeMinutes = value > 0 ? value : 1;
        }

        public Recipe(string name, int cookingTimeMinutes)
        {
            Name = name;
            CookingTimeMinutes = cookingTimeMinutes;

            if (cookingTimeMinutes <= 0)
            {
                Console.Error.WriteLine("Ошибка: время приготовления должно быть положительным!");
            }
            Console.WriteLine($"Рецепт создан: {Name}");
        }

        public void AddIngredient(Product product)
        {
            if (product == null)
            {
                Console.Error.WriteLine("Ошибка: нельзя добавить пустой продукт!");
                return;
            }
            _ingredients.Add(product);
            Console.WriteLine($"В рецепт {Name} добавлен: {product.Name}");
        }

        public bool CanCook()
        {
            foreach (var product in _ingredients)
            {
                if (!product.CheckFreshness())
                {
                    Console.Error.WriteLine($"Нельзя приготовить: продукт испорчен — {product.Name}");
                    return false;
                }
            }
            return true;
        }

        public void ShowIngredients()
        {
            Console.WriteLine($"Ингредиенты рецепта {Name}:");
            foreach (var p in _ingredients)
                Console.WriteLine($"  - {p.Name} ({p.Quantity})");
        }

        public override string ToString() => $"{Name} (ингредиентов: {_ingredients.Count})";
    }
}