namespace Kitchen
{
    // Объект поведения: выдавать только гостям кухни.
    public class GuestPolicy : IIssuePolicy
    {
        public bool CanIssue(string user) => user.Contains("гость");
        public string Name => "только гостям";
    }
}