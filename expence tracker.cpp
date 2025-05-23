#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Expense structure
struct Expense {
    int id;
    string description;
    double amount;
    string date;
    Expense* next;
};

class ExpenseTracker {
private:
    Expense* head;
    int nextId;

public:
    ExpenseTracker() {
        head = NULL;
        nextId = 1;
    }

    // Add expense to linked list
    void addExpense(const string& description, double amount, const string& date) {
        Expense* newExpense = new Expense{nextId++, description, amount, date, NULL};
        if (head == NULL) {
            head = newExpense;
        } else {
            Expense* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newExpense;
        }
        cout << "Expense added successfully.\n";
    }

    // Show all expenses
    void showExpenses() {
        if (head == NULL) {
            cout << "No expenses to show.\n";
            return;
        }
        Expense* temp = head;
        cout << "ID\tDescription\tAmount\tDate\n";
        while (temp != NULL) {
            cout << temp->id << "\t" << temp->description << "\t" << temp->amount << "\t" << temp->date << "\n";
            temp = temp->next;
        }
    }

    // Find expense by ID
    Expense* findExpense(int id) {
        Expense* temp = head;
        while (temp != NULL) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return NULL;
    }

    // Edit expense by ID
    void editExpense(int id) {
        Expense* expense = findExpense(id);
        if (expense == NULL) {
            cout << "Expense with ID " << id << " not found.\n";
            return;
        }

        cin.ignore();  // Clear input buffer
        cout << "Enter new description: ";
        getline(cin, expense->description);

        cout << "Enter new amount: ";
        cin >> expense->amount;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount. Enter again: ";
            cin >> expense->amount;
        }

        cin.ignore();  // Clear buffer again
        cout << "Enter new date: ";
        getline(cin, expense->date);

        cout << "Expense updated successfully.\n";
    }

    // Delete expense by ID
    void deleteExpense(int id) {
        if (head == NULL) {
            cout << "No expenses to delete.\n";
            return;
        }

        if (head->id == id) {
            Expense* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Expense deleted successfully.\n";
            return;
        }

        Expense* temp = head;
        while (temp->next != NULL && temp->next->id != id) {
            temp = temp->next;
        }

        if (temp->next != NULL && temp->next->id == id) {
            Expense* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Expense deleted successfully.\n";
        } else {
            cout << "Expense with ID " << id << " not found.\n";
        }
    }

    // Destructor to free memory
    ~ExpenseTracker() {
        Expense* temp = head;
        while (temp != NULL) {
            Expense* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

void showMenu() {
    cout << "\nExpense Tracker Menu:\n";
    cout << "1. Add Expense\n";
    cout << "2. Show Expenses\n";
    cout << "3. Edit Expense\n";
    cout << "4. Delete Expense\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string description, date;
                double amount;
                cin.ignore(); // clear input buffer
                cout << "Enter description: ";
                getline(cin, description);
                cout << "Enter amount: ";
                cin >> amount;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid amount. Enter again: ";
                    cin >> amount;
                }
                cin.ignore(); // clear buffer before getline
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                tracker.addExpense(description, amount, date);
                break;
            }
            case 2:
                tracker.showExpenses();
                break;
            case 3: {
                int id;
                cout << "Enter expense ID to edit: ";
                cin >> id;
                tracker.editExpense(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter expense ID to delete: ";
                cin >> id;
                tracker.deleteExpense(id);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

