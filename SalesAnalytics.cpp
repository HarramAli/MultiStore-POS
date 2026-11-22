#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SalesRecord {
private:
    string productName;
    int quantity;
    double price;

public:
    SalesRecord(string name, int qty, double p) {
        productName = name;
        quantity = qty;
        price = p;
    }

    double calculateRevenue() {
        return quantity * price;
    }

    int getQuantity() {
        return quantity;
    }

    void displaySale() {
        cout << productName << "\t"
             << quantity << "\t"
             << price << "\t"
             << calculateRevenue() << endl;
    }
};

class SalesReport {
private:
    vector<SalesRecord> records;

public:
    void addSale(SalesRecord sale) {
        records.push_back(sale);
    }

    double calculateTotalRevenue() {
        double total = 0;

        for (int i = 0; i < records.size(); i++) {
            total += records[i].calculateRevenue();
        }

        return total;
    }

    int calculateTotalItemsSold() {
        int total = 0;

        for (int i = 0; i < records.size(); i++) {
            total += records[i].getQuantity();
        }

        return total;
    }

    void displayReport() {
        cout << "\n===== SALES REPORT =====\n";
        cout << "Product\tQty\tPrice\tRevenue\n";

        for (int i = 0; i < records.size(); i++) {
            records[i].displaySale();
        }

        cout << "\nTotal Items Sold: "
             << calculateTotalItemsSold();

        cout << "\nTotal Revenue: "
             << calculateTotalRevenue() << endl;
    }
};

int main() {
    SalesReport report;

    int n;
    string name;
    int quantity;
    double price;

    cout << "===== SALES ANALYTICS SYSTEM =====\n";
    cout << "Enter number of sales: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter product name: ";
        cin >> name;

        cout << "Enter quantity: ";
        cin >> quantity;

        cout << "Enter price per item: ";
        cin >> price;

        SalesRecord sale(name, quantity, price);
        report.addSale(sale);
    }

    report.displayReport();

    return 0;
}