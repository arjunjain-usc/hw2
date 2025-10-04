#include "clothing.h"
#include "util.h"
#include <sstream>

Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
                   const std::string size, const std::string brand)
    : Product(category, name, price, qty), size_(size), brand_(brand)
{
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> nameWords = parseStringToWords(name_);
    std::set<std::string> brandWords = parseStringToWords(brand_);
    return setUnion(nameWords, brandWords);
}

std::string Clothing::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Size: " << size_ << " Brand: " << brand_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}
