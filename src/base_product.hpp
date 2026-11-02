#pragma once
#include <memory>
#include <string>
#include <string_view>

namespace kitchen {

class BaseProduct {
private:
    static inline int m_lastId = 0;

    int m_id;
    std::string m_name;
    double m_quantity;

protected:
        std::string Header() const;

public:
    BaseProduct(std::string_view name, double quantity);
    BaseProduct(const BaseProduct& other);
    BaseProduct(BaseProduct&& other) noexcept;
    BaseProduct& operator=(const BaseProduct& other);
    BaseProduct& operator=(BaseProduct&& other) noexcept;
    virtual ~BaseProduct();

    virtual int GetShelfLifeDays() const = 0;

  
    virtual std::string Describe() const;

    virtual std::unique_ptr<BaseProduct> Clone() const = 0;

    int GetId() const { return m_id; }
    std::string_view GetName() const { return m_name; }
    double GetQuantity() const { return m_quantity; }
    void SetQuantity(double q) { m_quantity = q; }

    
    static int NextId() { return ++m_lastId; }
    static int GetTotalCount() { return m_lastId; }
};

} // namespace kitchen