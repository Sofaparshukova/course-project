#pragma once
#include "i_issue_policy.hpp"
#include <string_view>

namespace kitchen {

// Объект поведения: выдавать только гостям кухни.
class GuestPolicy : public IIssuePolicy {
public:
    bool CanIssue(std::string_view user) const override {
        return user.find("гость") != std::string_view::npos;
    }
    std::string Name() const override { return "только гостям"; }
};

} 