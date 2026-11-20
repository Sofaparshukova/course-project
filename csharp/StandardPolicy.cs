namespace Kitchen
{
    public class StandardPolicy : IIssuePolicy
    {
        public bool CanIssue(string user) => true;
        public string Name => "стандартная (всем)";
    }
}