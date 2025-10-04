#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <algorithm>

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    for (size_t i = 0; i < products_.size(); ++i) {
        delete products_[i];
    }
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
}

void MyDataStore::addUser(User* u)
{
    users_[convToLower(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::set<Product*> result;
    for (size_t i = 0; i < terms.size(); ++i) {
        std::set<Product*> temp;
        std::string term = convToLower(terms[i]);
        for (size_t j = 0; j < products_.size(); ++j) {
            std::set<std::string> keys = products_[j]->keywords();
            if (keys.find(term) != keys.end()) {
                temp.insert(products_[j]);
            }
        }

        if (i == 0) {
            result = temp;
        } else {
            if (type == 0) {
                result = setIntersection(result, temp);
            } else {
                result = setUnion(result, temp);
            }
        }
    }

    std::vector<Product*> hits(result.begin(), result.end());
    return hits;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << std::endl;
    for (size_t i = 0; i < products_.size(); ++i) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(const std::string& username, Product* product)
{
    std::string uname = convToLower(username);
    if (users_.find(uname) != users_.end()) {
        carts_[uname].push_back(product);
    } else {
        std::cout << "Invalid request" << std::endl;
    }
}

void MyDataStore::viewCart(const std::string& username)
{
    std::string uname = convToLower(username);
    if (users_.find(uname) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    std::vector<Product*>& cart = carts_[uname];
    for (size_t i = 0; i < cart.size(); ++i) {
        std::cout << "Item " << (i + 1) << std::endl;
        std::cout << cart[i]->displayString() << std::endl;
        std::cout << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username)
{
    std::string uname = convToLower(username);
    if (users_.find(uname) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    std::vector<Product*>& cart = carts_[uname];
    std::vector<Product*> remaining;
    User* user = users_[uname];

    for (size_t i = 0; i < cart.size(); ++i) {
        Product* prod = cart[i];
        if (prod->getQty() > 0 && user->getBalance() >= prod->getPrice()) {
            user->deductAmount(prod->getPrice());
            prod->subtractQty(1);
        } else {
            remaining.push_back(prod);
        }
    }
    cart = remaining;
}
