#include <iostream>
#include <string>
using namespace std;

// Abstract base class for common product information
class Item {
private:
    string sku;
    string name;
    double price;
    int stock;
    int reorderLevel;
    string warehouse;

public:
    Item(string productSKU, string productName, double productPrice,
         int stockCount, int threshold, string warehouseLocation) {
        sku = productSKU;
        name = productName;

        if (productPrice < 0)
            price = 0;
        else
            price = productPrice;

        if (stockCount < 0)
            stock = 0;
        else
            stock = stockCount;

        if (threshold < 0)
            reorderLevel = 0;
        else
            reorderLevel = threshold;

        warehouse = warehouseLocation;
    }

    string getSKU() const {
        return sku;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getStock() const {
        return stock;
    }

    string getWarehouse() const {
        return warehouse;
    }

    int getReorderLevel() const {
        return reorderLevel;
    }

    bool updateStock(int newStock) {
        if (newStock < 0) {
            return false;
        }

        stock = newStock;
        return true;
    }

    bool isLowStock() const {
        return stock < reorderLevel;
    }

    virtual void displayDetails() const = 0;
    virtual ~Item() {}
};

// Physical products have a batch number and expiry date
class PhysicalProduct : public Item {
private:
    string batchNumber;
    string expiryDate;

public:
    PhysicalProduct(string sku, string name, double price, int stock,
                    int threshold, string warehouse, string batch, string expiry)
        : Item(sku, name, price, stock, threshold, warehouse) {
        batchNumber = batch;
        expiryDate = expiry;
    }

    void displayDetails() const override {
        cout << "Product Type: Physical" << endl;
        cout << "Name: " << getName() << endl;
        cout << "SKU: " << getSKU() << endl;
        cout << "Price: $" << getPrice() << endl;
        cout << "Batch Number: " << batchNumber << endl;
        cout << "Expiry Date: " << expiryDate << endl;
        cout << "Stock: " << getStock() << endl;
        cout << "Reorder Level: " << getReorderLevel() << endl;
        cout << "Warehouse: " << getWarehouse() << endl;
    }
};

// Digital products have a file size
class DigitalProduct : public Item {
private:
    int fileSizeMB;

public:
    DigitalProduct(string sku, string name, double price, int stock,
                   int threshold, string warehouse, int size)
        : Item(sku, name, price, stock, threshold, warehouse) {
        fileSizeMB = size;
    }

    void displayDetails() const override {
        cout << "Product Type: Digital" << endl;
        cout << "Name: " << getName() << endl;
        cout << "SKU: " << getSKU() << endl;
        cout << "Price: $" << getPrice() << endl;
        cout << "Available Licenses: " << getStock() << endl;
        cout << "File Size: " << fileSizeMB << " MB" << endl;
        cout << "Reorder Level: " << getReorderLevel() << endl;
    }
};

// Stores product references and manages stock
class Inventory {
private:
    Item* products[10];
    int productCount;

public:
    Inventory() {
        productCount = 0;
    }

    bool addProduct(Item* product) {
        if (product == nullptr || productCount >= 10) {
            return false;
        }

        products[productCount] = product;
        productCount++;
        return true;
    }

    void displayInventory() const {
        cout << "\n===== PRODUCT INVENTORY =====" << endl;

        for (int i = 0; i < productCount; i++) {
            products[i]->displayDetails();
            cout << "-----------------------------" << endl;
        }
    }

    void displayLowStock() const {
        cout << "\n===== LOW STOCK CHECK =====" << endl;
        bool found = false;

        for (int i = 0; i < productCount; i++) {
            if (products[i]->isLowStock()) {
                cout << products[i]->getName()
                     << " (" << products[i]->getSKU() << ")"
                     << " - Stock: " << products[i]->getStock()
                     << " - Reorder Level: " << products[i]->getReorderLevel()
                     << " - REORDER REQUIRED" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No products need reordering." << endl;
        }
    }

    bool updateProductStock(string productSKU, int newStock) {
        for (int i = 0; i < productCount; i++) {
            if (products[i]->getSKU() == productSKU) {
                return products[i]->updateStock(newStock);
            }
        }

        return false;
    }
};

int main() {
    // Create product objects
    PhysicalProduct mouse("SKU-101", "Wireless Mouse", 25, 4, 5,
                          "Warehouse North", "BATCH-001", "2027-12-31");

    PhysicalProduct keyboard("SKU-102", "Keyboard", 30, 12, 5,
                             "Warehouse South", "BATCH-002", "2028-06-30");

    DigitalProduct software("SKU-103", "Office Software", 50, 20, 3,
                             "Digital Store", 750);

    // Create inventory object and register products
    Inventory inventory;
    inventory.addProduct(&mouse);
    inventory.addProduct(&keyboard);
    inventory.addProduct(&software);

    // Demonstrate inventory functions
    inventory.displayInventory();
    inventory.displayLowStock();

    cout << "\n===== STOCK UPDATE =====" << endl;

    if (inventory.updateProductStock("SKU-101", 10)) {
        cout << "Wireless Mouse stock updated to 10." << endl;
    }

    if (!inventory.updateProductStock("SKU-101", -2)) {
        cout << "Invalid quantity: negative stock is not allowed." << endl;
    }

    inventory.displayLowStock();

    return 0;
}
