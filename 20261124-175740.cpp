
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Function to simulate authorization callback
void authorizationCallback(bool approved)
{
    cout << "\n--- Authorization Callback ---" << endl;

    if (approved)
    {
        cout << "Payment Approved!" << endl;
        cout << "Status: SUCCESS" << endl;
    }
    else
    {
        cout << "Payment Declined!" << endl;
        cout << "Status: FAILED" << endl;
    }
}

// Function to process cash payment
void cashPayment(double amount)
{
    double cashReceived;

    cout << "\nEnter cash received: Rs. ";
    cin >> cashReceived;

    if (cashReceived >= amount)
    {
        double change = cashReceived - amount;

        cout << "\nCash Payment Successful!" << endl;
        cout << "Change Returned: Rs. " << change << endl;

        authorizationCallback(true);
    }
    else
    {
        cout << "\nInsufficient Cash!" << endl;

        authorizationCallback(false);
    }
}

// Function to process credit card payment
void cardPayment(double amount)
{
    char response;

    cout << "\nCredit Card Payment" << endl;
    cout << "Amount: Rs. " << amount << endl;

    cout << "Simulate card authorization? (Y/N): ";
    cin >> response;

    if (response == 'Y' || response == 'y')
    {
        authorizationCallback(true);
    }
    else
    {
        authorizationCallback(false);
    }
}

// Function to process digital wallet payment
void walletPayment(double amount)
{
    char response;

    cout << "\nDigital Wallet Payment" << endl;
    cout << "Amount: Rs. " << amount << endl;

    cout << "Simulate wallet authorization? (Y/N): ";
    cin >> response;

    if (response == 'Y' || response == 'y')
    {
        authorizationCallback(true);
    }
    else
    {
        authorizationCallback(false);
    }
}

// Main function
int main()
{
    int choice;
    double amount;
    int transactionID = 1001;

    cout << "================================" << endl;
    cout << "   PAYMENT GATEWAY SYSTEM" << endl;
    cout << "================================" << endl;

    // Get total bill amount
    cout << "\nEnter Total Bill Amount: Rs. ";
    cin >> amount;

    // Validate bill amount
    if (amount <= 0)
    {
        cout << "Invalid Bill Amount!" << endl;
        return 0;
    }

    // Display payment options
    cout << "\nSelect Payment Method:" << endl;
    cout << "1. Cash Payment" << endl;
    cout << "2. Credit Card Payment" << endl;
    cout << "3. Digital Wallet Payment" << endl;

    cout << "\nEnter your choice: ";
    cin >> choice;

    // Set decimal precision
    cout << fixed << setprecision(2);

    cout << "\nTransaction ID: " << transactionID << endl;

    // Process selected payment method
    switch (choice)
    {
        case 1:
            cashPayment(amount);
            break;

        case 2:
            cardPayment(amount);
            break;

        case 3:
            walletPayment(amount);
            break;

        default:
            cout << "\nInvalid Payment Option!" << endl;
            return 0;
    }

    cout << "\n================================" << endl;
    cout << "       TRANSACTION END" << endl;
    cout << "================================" << endl;

    return 0;
}
