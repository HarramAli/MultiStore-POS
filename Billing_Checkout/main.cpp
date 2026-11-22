
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
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

    // Getter functions
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

    // Calculates subtotal of all products
    double calculateSubtotal() const {
        double subtotal = 0;

        for (const CartItem& item : items) {
            subtotal += item.calculateTotal();
        }

        return subtotal;
    }

    // Displays shopping cart
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

// Abstract base class for discount strategies
class DiscountStrategy {
public:
    virtual double applyDiscount(double amount) const = 0;

    virtual ~DiscountStrategy() {}
};

// Fixed amount discount
class FlatDiscount : public DiscountStrategy {
private:
    double discountAmount;

public:
    FlatDiscount(double amount) {
        discountAmount = amount;
    }

    double applyDiscount(double amount) const override {
        return (discountAmount > amount) ? amount : discountAmount;
    }
};

// Percentage-based discount
class PercentageDiscount : public DiscountStrategy {
private:
    double percentage;

public:
    PercentageDiscount(double percent) {
        percentage = percent;
    }

    double applyDiscount(double amount) const override {
        return amount * percentage / 100;
    }
};

// Buy One Get One discount
class BuyOneGetOne : public DiscountStrategy {
private:
    int quantity;

public:
    BuyOneGetOne(int q) {
        quantity = q;
    }

    double applyDiscount(double amount) const override {
        if (quantity < 2) {
            return 0;
        }

        double unitPrice = amount / quantity;
        int freeItems = quantity / 2;

        return unitPrice * freeItems;
    }
};

// Generates invoice and calculates tax
class Invoice {
private:
    double subtotal;
    double discountAmount;
    double taxRate;

public:
    // Constructor
    Invoice(double sub, double discount, double tax) {
        subtotal = sub;
        discountAmount = (discount > sub) ? sub : discount;
        taxRate = tax;
    }

    // Calculates tax after discount
    double calculateTax() const {
        double amountAfterDiscount = subtotal - discountAmount;
        return amountAfterDiscount * taxRate / 100;
    }

    // Calculates final bill
    double calculateFinalTotal() const {
        return subtotal - discountAmount + calculateTax();
    }

    // Displays final invoice
    void displayInvoice() const {
        cout << "\n===== FINAL INVOICE =====\n";

        cout << "Subtotal: $" << subtotal << endl;
        cout << "Discount: $" << discountAmount << endl;

        cout << "Amount After Discount: $"
             << subtotal - discountAmount << endl;

        cout << "Tax (" << taxRate << "%): $"
             << calculateTax() << endl;

        cout << "-------------------------\n";

        cout << "Final Amount: $"
             << calculateFinalTotal() << endl;
    }
};

int main() {

    cout << fixed << setprecision(2);

    // Creating product objects
    CartItem item1("Wireless Mouse", 25.0, 2);
    CartItem item2("Keyboard", 30.0, 1);

    // Creating shopping cart object
    ShoppingCart cart;

    // Adding products to cart
    cart.addItem(item1);
    cart.addItem(item2);

    // Displaying shopping cart
    cart.displayCart();

    double subtotal = cart.calculateSubtotal();

    // Creating discount objects
    FlatDiscount flat(5.0);
    PercentageDiscount percentage(10.0);

    BuyOneGetOne bogo(item1.getQuantity());

    cout << "\n===== DISCOUNT OPTIONS =====\n";

    cout << "Flat Discount: $"
         << flat.applyDiscount(subtotal) << endl;

    cout << "Percentage Discount: $"
         << percentage.applyDiscount(subtotal) << endl;

    cout << "Buy One Get One Discount: $"
         << bogo.applyDiscount(item1.calculateTotal()) << endl;

    // Demonstrating polymorphism
    DiscountStrategy* selectedDiscount = &percentage;

    double discountAmount =
        selectedDiscount->applyDiscount(subtotal);

    cout << "\nSelected Discount: $"
         << discountAmount << endl;

    // Creating invoice object
    Invoice invoice(subtotal, discountAmount, 8.0);

    // Displaying invoice
    invoice.displayInvoice();

    return 0;
}
