namespace Kitchen
{
    // Объект поведения: кому можно выдавать продукт.
    public interface IIssuePolicy
    {
        bool CanIssue(string user);
        string Name { get; }
    }
}