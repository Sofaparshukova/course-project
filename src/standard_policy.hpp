#pragma once
#include "i_issue_policy.hpp"

namespace kitchen {

class StandardPolicy : public IIssuePolicy {
public:
    bool CanIssue(std::string_view /*user*/) const override { return true; }
    std::string Name() const override { return "стандартная (всем)"; }
};

} 