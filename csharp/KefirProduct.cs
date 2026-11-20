using System;

namespace Kitchen
{
    public sealed class KefirProduct : BaseProduct, IConsumable
    {
        private bool _available = true;

        public KefirProduct(string name, double quantity)
            : base(name, quantity) { }

        public override int ShelfLifeDays => 5;
        public override string Describe() => base.Describe() + ", кефир";
        public override BaseProduct Clone() => (KefirProduct)MemberwiseClone();

        public void Consume(string user)
        {
            if (!_available)
                throw new NoPortionsAvailableException(Name);
            _available = false;
            Console.WriteLine($"  выдано «{Name}» пользователю {user}");
        }

        public void Return() => _available = true;
        public bool IsAvailable => _available;
    }
}