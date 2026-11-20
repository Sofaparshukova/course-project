using System;

namespace Kitchen
{
    public class DairyProduct : BaseProduct, IConsumable
    {
        public string FatContent { get; }
        private IIssuePolicy _policy;
        private bool _available = true;

        // Вызов конструктора базового класса 
        public DairyProduct(string name, double quantity, string fatContent, IIssuePolicy? policy = null)
            : base(name, quantity)
        {
            FatContent = fatContent;
            _policy = policy ?? new StandardPolicy();
            Console.WriteLine($"DairyProduct(): {Name}");
        }
        // Раннее связывание: скрывает BaseProduct.GetKind() new
        public new string GetKind() => "молочный продукт";

        // Переопределение абстрактного свойства
        public override int ShelfLifeDays => 7;

        public override string Describe()
            => base.Describe() + $", жирность {FatContent}, политика: {_policy.Name}";

        public override BaseProduct Clone() => (DairyProduct)MemberwiseClone();

        // IConsumable
        public void Consume(string user)
        {
            if (!_available)
                throw new NoPortionsAvailableException(Name);
            if (!_policy.CanIssue(user))
                throw new InvalidOperationException($"политика не разрешает выдачу: {user}");

            _available = false;
            Console.WriteLine($"  выдано «{Name}» пользователю {user}");
        }

        public void Return() => _available = true;
        public bool IsAvailable => _available;

        public void SetPolicy(IIssuePolicy policy) => _policy = policy;
        public string PolicyName => _policy.Name;
    
    }
}