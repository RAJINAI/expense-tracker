# Expense Tracker (C++)

A simple command-line Expense Tracker written in C++ that demonstrates core Object-Oriented Programming (OOP) concepts like **Inheritance**, **Polymorphism**, **Abstraction**, and **Encapsulation**.

---

## What This Program Does

This program helps you keep track of different types of expenses (like Food and Travel). You can:
- Add expenses with an amount, category, and date
- Display all recorded expenses
- Calculate the total amount spent

---

## OOP Principles Used

This project uses all **four core OOP principles**. Here's a simple explanation of each, with exactly where you can find it in the code.

---

### 1. Encapsulation
> **"Keep the data safe inside the class."**

Encapsulation means hiding the internal data of a class and only exposing what's necessary through methods (functions).

In this code, the fields `amount`, `category`, and `date` are declared as `protected` inside the `Expense` class. This means they **cannot be accessed directly** from outside the class — you must go through a method like `getAmount()`.

```cpp
// Data is hidden (protected) — not directly accessible from outside
protected:
    float amount;
    string category;
    string date;

// Only accessible through a public method
float getAmount() {
    return amount;
}
```

 **Why it matters:** Prevents accidental changes to important data. The `ExpenseTracker` class can read the amount using `getAmount()` but cannot accidentally overwrite it.

---

### 2.Inheritance
> **"Child classes reuse code from the parent class."**

Inheritance lets a new class (child) take all the properties and methods of an existing class (parent), without rewriting them.

Here, `FoodExpense` and `TravelExpense` both inherit from `Expense`. They automatically get `amount`, `category`, `date`, and `getAmount()` for free — they only define what's different about themselves.

```cpp
// FoodExpense inherits everything from Expense
class FoodExpense : public Expense {
public:
    FoodExpense(float a, string d) : Expense(a, "Food", d) {}
    // ...
};

// TravelExpense does the same
class TravelExpense : public Expense {
public:
    TravelExpense(float a, string d) : Expense(a, "Travel", d) {}
    // ...
};
```

**Why it matters:** Avoids repeating code. If you need to change how expenses store a date, you only update the `Expense` class — all child classes get the update automatically.

---

### 3. Polymorphism
> **"Same function name, different behavior depending on the object."**

Polymorphism means one method name can behave differently based on which class it belongs to. In C++, this is done using `virtual` functions.

The `display()` method is defined in `Expense` as `virtual`, and each subclass **overrides** it with its own version. When `ExpenseTracker` calls `e->display()`, C++ automatically runs the right version for that object.

```cpp
// Base class — virtual means "can be overridden"
virtual void display() {
    cout << "Amount: " << amount << ", Category: " << category << endl;
}

// FoodExpense overrides it with its own version
void display() override {
    cout << "[Food Expense] Rs." << amount << " on " << date << endl;
}

// Called the same way, but runs the right version automatically
for (auto e : expenses) {
    e->display();  // 🎭 Polymorphism in action
}
```

 **Why it matters:** You can add new expense types (like `ShoppingExpense`) without changing `ExpenseTracker` at all. It just works.

---

### 4. Abstraction
> **"Show only what's necessary, hide the complexity."**

Abstraction means designing a class to expose a simple interface while hiding the internal details. Users of the class don't need to know *how* it works — just *what* it does.

The `Expense` class acts as an abstract blueprint. It defines that every expense *must have* an amount, category, date, and a `display()` method — but leaves the specific display behavior to each subclass. Similarly, `ExpenseTracker` hides the internal `vector` and memory management from `main()`.

```cpp
// main() only uses simple methods — doesn't care how they work internally
tracker.addExpense(new FoodExpense(4000, "2026-04-11"));
tracker.showExpenses();
tracker.totalExpense();
```

 **Why it matters:** `main()` stays clean and simple. All the complexity (looping, memory, display logic) is hidden inside the classes.

---

### 🔁 Quick Summary Table

| Principle | Simple Meaning | Where in Code |
|---|---|---|
| **Encapsulation** | Data is protected inside the class | `protected` fields in `Expense`; `getAmount()` method |
| **Inheritance** | Child classes reuse parent class code | `FoodExpense` and `TravelExpense` extend `Expense` |
| **Polymorphism** | Same call, different behavior per class | `virtual display()` overridden in each subclass |
| **Abstraction** | Hide complexity, show simple interface | `ExpenseTracker` methods hide internal logic from `main()` |

---

##  Project Structure

```
ExpenseTracker/
│
├── main.cpp          # All source code is in this single file
└── README.md         # This file
```

---

##  How the Code is Organized

### 1. `Expense` (Base Class)
The **parent class** for all expense types. It holds:
- `amount` — how much money was spent
- `category` — what type of expense it is (e.g., Food, Travel)
- `date` — when the expense happened

It has a `display()` method that prints expense details, and a `getAmount()` method to return the amount.

---

### 2. `FoodExpense` (Derived Class)
Inherits from `Expense`. Automatically sets the category to `"Food"`.  
Its `display()` prints: `[Food Expense] Rs.<amount> on <date>`

---

### 3. `TravelExpense` (Derived Class)
Inherits from `Expense`. Automatically sets the category to `"Travel"`.  
Its `display()` prints: `[Travel Expense] Rs.<amount> on <date>`

---

### 4. `ExpenseTracker` (Manager Class)
This class manages a **list of expenses**. It can:
- `addExpense(Expense* e)` — add a new expense to the list
- `showExpenses()` — display all expenses
- `totalExpense()` — calculate and print the total

It also **frees memory** automatically when the program ends (no memory leaks).

---

##  How to Run

### Requirements
- A C++ compiler (like `g++`)

### Steps

```bash
# Step 1: Compile the program
g++ main.cpp -o expense_tracker

# Step 2: Run it
./expense_tracker
```

> On Windows, use `expense_tracker.exe` instead.

---

## Expected Output

```
All Expenses:
[Food Expense] Rs.4000 on 2026-04-11
[Travel Expense] Rs.300 on 2026-04-12
Amount: 5000, Category: Other, Date: 2026-04-18

Total Expense: Rs.9300
```

---

##  How to Add a New Expense Type

Want to add a new category, like `ShoppingExpense`? Here's how:

**Step 1:** Create a new class that inherits from `Expense`:

```cpp
class ShoppingExpense : public Expense {
public:
    ShoppingExpense(float a, string d) : Expense(a, "Shopping", d) {}

    void display() override {
        cout << "[Shopping Expense] Rs." << amount
             << " on " << date << endl;
    }
};
```

**Step 2:** Add it in `main()`:

```cpp
tracker.addExpense(new ShoppingExpense(1500, "2026-04-20"));
```

That's it! No other changes needed.

---

##  Notes

- All amounts are in **Nepali Rupees (Rs.)**
- Dates should follow the format: `YYYY-MM-DD`
- Memory is managed automatically — no manual cleanup needed

---

##  Good For Learning

This project is a great starting point if you're learning:
- C++ classes and objects
- Inheritance and method overriding
- Pointers and dynamic memory (`new` / `delete`)
- Using `vector` to store objects

