namespace Kitchen
{
    // Контракт: продукт можно выдать/употребить на кухне.
    public interface IConsumable
    {
        void Consume(string user);
        void Return();
        bool IsAvailable { get; }
    }
}