#include <iostream>
#include <vector>
using namespace std;

// Base Class (Abstraction)
class Expense {
protected:
    float amount;
    string category;
    string date;

public:
    Expense(float a, string c, string d) {
        amount = a;
        category = c;
        date = d;
    }

    // Virtual function (Polymorphism)
    virtual void display() {
        cout << "Amount: " << amount
             << ", Category: " << category
             << ", Date: " << date << endl;
    }

    float getAmount() {
        return amount;
    }

    // Virtual destructor (IMPORTANT)
    virtual ~Expense() {}
};

// Derived Class (Inheritance)
class FoodExpense : public Expense {
public:
    FoodExpense(float a, string d) : Expense(a, "Food", d) {}

    void display() override {
        cout << "[Food Expense] Rs." << amount
             << " on " << date << endl;
    }
};

class TravelExpense : public Expense {
public:
    TravelExpense(float a, string d) : Expense(a, "Travel", d) {}

    void display() override {
        cout << "[Travel Expense] Rs." << amount
             << " on " << date << endl;
    }
};

// Manager Class
class ExpenseTracker {
private:
    vector<Expense*> expenses;

public:
    void addExpense(Expense* e) {
        expenses.push_back(e);
    }

    void showExpenses() {
        if (expenses.empty()) {
            cout << "No expenses found." << endl;
            return;
        }

        for (auto e : expenses) {
            e->display();  // Polymorphism
        }
    }

    void totalExpense() {
        float total = 0;
        for (auto e : expenses) {
            total += e->getAmount();
        }
        cout << "Total Expense: Rs." << total << endl;
    }

    // Destructor (Fixes memory leak)
    ~ExpenseTracker() {
        for (auto e : expenses) {
            delete e;
        }
    }
};

// Main Function
int main() {
    ExpenseTracker tracker;

    tracker.addExpense(new FoodExpense(4000, "2026-04-11"));
    tracker.addExpense(new TravelExpense(300, "2026-04-12"));
    tracker.addExpense(new Expense(5000, "Other", "2026-04-18"));

    cout << "All Expenses:\n";
    tracker.showExpenses();

    cout << endl;
    tracker.totalExpense();

    return 0;
}