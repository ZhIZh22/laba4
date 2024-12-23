#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <memory>

using namespace std;

// Базовый класс Product
class Product {
protected:
    string name;
    double price;
    int quantity;

public:
    Product(const string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    virtual ~Product() = default;

    virtual void displayInfo() const {
        cout << "Name: " << name << ", Price: " << price << ", Quantity: " << quantity << '\n';
    }

    const string& getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setPrice(double newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
};

// Шаблонный класс Pair
template <typename T1, typename T2>
class Pair {
    T1 first;
    T2 second;

public:
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }
};

// Классы-наследники
class Clothing : public Product {
    string size;

public:
    Clothing(const string& name, double price, int quantity, const string& size)
        : Product(name, price, quantity), size(size) {}

    void displayInfo() const override {
        Product::displayInfo();
        cout << "Size: " << size << '\n';
    }
};

class Electronics : public Product {
    int warranty; // срок гарантии в месяцах

public:
    Electronics(const string& name, double price, int quantity, int warranty)
        : Product(name, price, quantity), warranty(warranty) {}

    void displayInfo() const override {
        Product::displayInfo();
        cout << "Warranty: " << warranty << " months" << '\n';
    }
};

// Меню и обработка данных
class Store {
    vector<shared_ptr<Product>> products;

public:
    void addProduct() {
        int choice;
        cout << "1. Clothing\n2. Electronics\nChoose product type: ";
        cin >> choice;

        string name;
        double price;
        int quantity;

        cout << "Enter name: ";
        cin >> name;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter quantity: ";
        cin >> quantity;

        if (choice == 1) {
            string size;
            cout << "Enter size: ";
            cin >> size;
            products.push_back(make_shared<Clothing>(name, price, quantity, size));
        } else if (choice == 2) {
            int warranty;
            cout << "Enter warranty (months): ";
            cin >> warranty;
            products.push_back(make_shared<Electronics>(name, price, quantity, warranty));
        }
    }

    void searchProduct() const {
        string name;
        cout << "Enter product name to search: ";
        cin >> name;

        auto it = find_if(products.begin(), products.end(), [&name](const shared_ptr<Product>& product) {
            return product->getName() == name;
        });

        if (it != products.end()) {
            (*it)->displayInfo();
        } else {
            cout << "Product not found.\n";
        }
    }

    void sortProductsByPrice() {
        sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
            return a->getPrice() < b->getPrice();
        });
        cout << "Products sorted by price.\n";
    }

    void displayAllProducts() const {
        for (const auto& product : products) {
            product->displayInfo();
            cout << "----------------------\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (const auto& product : products) {
            file << "Name: " << product->getName() << ", Price: " << product->getPrice()
                 << ", Quantity: " << product->getQuantity() << '\n';
        }
        cout << "Data saved to " << filename << '\n';
    }
};

int main() {
    Store store;
    int choice;

    do {
        cout << "\n1. Add product\n2. Search product\n3. Sort products by price\n4. Display all products\n5. Save to file\n0. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            store.addProduct();
            break;
        case 2:
            store.searchProduct();
            break;
        case 3:
            store.sortProductsByPrice();
            break;
        case 4:
            store.displayAllProducts();
            break;
        case 5:
            store.saveToFile("output.txt");
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
