/*
Cameron Tyree
CIS 1202 101
March 15, 2024
*/



#include "personalLibrary.h"

const int NAME_SIZE = 40;
struct Product
{
	long number;
	char name[NAME_SIZE];
	double price;
	int quantity;
};

int showMenu();
void createFile(fstream&);
void displayFile(fstream&);
void displayRecord(fstream&, int);
void modifyRecord(fstream&);


int main() {

    fstream file("inventory.dat", ios::in | ios::out | ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    createFile(file);
    int userChoice;
    do {
        userChoice = showMenu();
        switch (userChoice) {
        case 1:
            displayFile(file);
            break;
        case 2: {
            int record;
            cout << "Enter your record you want to display: ";
            cin >> record;
            displayRecord(file, record);
            break;
        }
        case 3:
            modifyRecord(file);
            break;
        }
        
    }
    while (userChoice != 4);
    file.close();
    endProgram();
}


int showMenu() {
    int choice;
    cout << "Product Inventory" << endl;
    cout << "1. Display the entire inventory" << endl;
    cout << "2. Display a particular product" << endl;
    cout << "3. Modify a product" << endl;
    cout << "4. Exit" << endl;
    choice = validateIntRange("Enter your choice: ", 1, 4);
    return choice;
}
void createFile(fstream& file) {
     
    Product product;
    product.number = 1000;
    strcpy_s(product.name, "Dog");
    product.price = 34.99;
    product.quantity = 17;
    file.write(reinterpret_cast<char*>(&product), sizeof(product));

}
void displayFile(fstream& file) {

    file.clear();
    file.seekg(0, ios::beg);
    Product product;
    int record = 1;
    while (file.read(reinterpret_cast<char*>(&product), sizeof(product))) {
        cout << "Record #" << record++ << endl;
        cout << "Number: " << product.number << endl;
        cout << "Name: " << product.name << endl;
        cout << "Price: " << product.price << endl;
        cout << "Quantity: " << product.quantity << endl;
        cout << endl;
    }
}
void displayRecord(fstream& file, int record) {
    
    file.clear();
    file.seekg((record - 1) * sizeof(Product), ios::beg);

    Product product;
    if (file.read(reinterpret_cast<char*>(&product), sizeof(product))) {
        cout << "\nRecord #" << record++ << endl;
        cout << "Number: " << product.number << endl;
        cout << "Name: " << product.name << endl;
        cout << "Price: " << product.price << endl;
        cout << "Quantity: " << product.quantity << endl;
        cout << endl;
    }
    else {
        cerr << "Unable to find the record" << endl;
    }
}
void modifyRecord(fstream& file) {

    int record;
    record = validateFloat("Enter your record that you want to be modified: ");
    file.clear();
    file.seekg((record - 1) * sizeof(Product), ios::beg);
    Product product;
    if (file.read(reinterpret_cast<char*>(&product), sizeof(product))) {
        cout << "Enter your new data -" << endl;
        product.number = validateFloat("Number: ");
        cout << "Name: ";
        cin.ignore();
        cin.getline(product.name, NAME_SIZE);
        product.price = validateFloat("Price: ");
        product.quantity = validateFloat("Quantity: ");
        file.seekp((record - 1) * sizeof(Product), ios::beg);
        file.write(reinterpret_cast<char*>(&product), sizeof(product));
        cout << "Record changed successfully!\n" << endl;
    }
    else {
        cerr << "Unable to find the record" << endl;
    }
}