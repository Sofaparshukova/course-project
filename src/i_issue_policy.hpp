#pragma once
#include <string>

namespace kitchen {

// Объект поведения: кому можно выдавать продукт
class IIssuePolicy {
public:
    virtual ~IIssuePolicy() = default;
    virtual bool CanIssue(std::string_view user) const = 0;
    virtual std::string Name() const = 0;
};

} 