#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <map>
#include <set>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    void addToCart(const std::string& username, Product* product);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::vector<Product*> > carts_;
};

#endif
