#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std::string category, const std::string name, double price, int qty,
             const std::string genre, const std::string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating)
{
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> nameWords = parseStringToWords(name_);
    nameWords.insert(genre_);
    return nameWords;
}

std::string Movie::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;
}
