#pragma once
#include "base_product.hpp"
#include "i_consumable.hpp"
#include "i_issue_policy.hpp"
#include <memory>
#include <string>

namespace kitchen {

// Множественное наследование
class DairyProduct : public BaseProduct, public IConsumable {
private:
    std::string m_fatContent;
    std::unique_ptr<IIssuePolicy> m_policy;   // объект поведения
    bool m_available = true;

public:
    DairyProduct(std::string_view name, double quantity, std::string_view fatContent,
                 std::unique_ptr<IIssuePolicy> policy = nullptr);
    DairyProduct(const DairyProduct& other);
    DairyProduct(DairyProduct&& other) noexcept;
    ~DairyProduct() override;

    // Раннее связывание
    std::string GetKind() const { return "молочный продукт"; }

    int GetShelfLifeDays() const override { return 7; }
    std::string Describe() const override;
    std::unique_ptr<BaseProduct> Clone() const override;

    // IConsumable
    void Consume(std::string_view user) override;
    void Return() override { m_available = true; }
    bool IsAvailable() const override { return m_available; }

    // Конфигурирование
    void SetPolicy(std::unique_ptr<IIssuePolicy> policy) { m_policy = std::move(policy); }
    std::string PolicyName() const { return m_policy ? m_policy->Name() : "нет"; }

    std::string_view GetFatContent() const { return m_fatContent; }
};

} 