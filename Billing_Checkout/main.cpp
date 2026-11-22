
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Represents one product in the shopping cart
class CartItem {
private:
    string productName;
    double price;
    int quantity;

public:
    // Constructor
    CartItem(string name, double itemPrice, int itemQuantity) {
        productName = name;
        price = itemPrice;
        quantity = itemQuantity;
    }

    // Calculates total price of this product
    double calculateTotal() const {
        return price * quantity;
    }

    // Returns product information
    string getProductName() const {
        return productName;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }
};

// Manages multiple products in the shopping cart
class ShoppingCart {
private:
    vector<CartItem> items;

public:
    // Adds a product to the cart
    void addItem(const CartItem& item) {
        items.push_back(item);
    }

    // Calculates the subtotal of all products
    double calculateSubtotal() const {
        double subtotal = 0;

        for (const CartItem& item : items) {
            subtotal += item.calculateTotal();
        }

        return subtotal;
    }

    // Displays all cart products
    void displayCart() const {
        cout << "\n===== SHOPPING CART =====\n";

        for (const CartItem& item : items) {
            cout << "Product: " << item.getProductName() << endl;
            cout << "Price: $" << item.getPrice() << endl;
            cout << "Quantity: " << item.getQuantity() << endl;
            cout << "Total: $" << item.calculateTotal() << endl;
            cout << "-------------------------\n";
        }

        cout << "Subtotal: $" << calculateSubtotal() << endl;
    }
};

int main() {

    // Creating product objects
    CartItem item1("Wireless Mouse", 25.0, 2);
    CartItem item2("Keyboard", 30.0, 1);

    // Creating shopping cart object
    ShoppingCart cart;

    // Adding products to the cart
    cart.addItem(item1);
    cart.addItem(item2);

    // Displaying cart information
    cart.displayCart();

    return 0;
}
