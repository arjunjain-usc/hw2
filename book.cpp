#include "book.h"
#include "util.h"
#include <sstream>

Book::Book(const std::string category, const std::string name, double price, int qty,
           const std::string isbn, const std::string author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author)
{
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> nameWords = parseStringToWords(name_);
    std::set<std::string> authorWords = parseStringToWords(author_);
    std::set<std::string> result = setUnion(nameWords, authorWords);
    result.insert(isbn_);
    return result;
}

std::string Book::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << isbn_ << std::endl;
    os << author_ << std::endl;
}
