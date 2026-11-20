using System;

namespace Kitchen
{
    public class NoPortionsAvailableException : Exception
    {
        public NoPortionsAvailableException(string name)
            : base($"нет свободных порций: {name}") { }
    }
}