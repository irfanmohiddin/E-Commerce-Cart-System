#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <ctime>
using namespace std;

class Product {
private:
    int quantity;

public:
    int id;
    string name;
    double price;

    Product(int id = 0, string name = "", double price = 0, int quantity = 0)
        : id(id), name(name), price(price), quantity(quantity) {}

    // Getters and Setters (Admin control)
    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }

    void displayForUser() const {
        cout << left << setw(10) << id << setw(25) << name
             << setw(10) << price;
        if (quantity == 0)
            cout << "Out of Stock";
        else if (quantity <= 4)
            cout << "Only " << quantity << " left in stock!";
        else
            cout << "In Stock";
        cout << endl;
    }

    void displayForAdmin() const {
        cout << left << setw(10) << id << setw(25) << name
             << setw(10) << price << setw(10) << quantity << endl;
    }
};

class User {
private:
    string password;
public:
    string username;
    User(string user = "", string pwd = "") : username(user), password(pwd) {}

    string getPassword() const { return password; }
    string getUsername() const { return username; }

    void registerUser() {
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter new password: ";
        cin >> password;

        ofstream outfile("users.txt", ios::app);
        outfile << username << " " << password << endl;
        outfile.close();

        cout << "Registration successful!\n";
    }

    bool login() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream infile("users.txt");
        string file_username, file_password;
        bool found = false;

        while (infile >> file_username >> file_password) {
            if (file_username == username && file_password == password) {
                found = true;
                break;
            }
        }
        infile.close();

        if (found) {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Invalid username or password.\n";
            return false;
        }
    }
};

// ---------------- ADMIN FUNCTIONALITIES ----------------
void viewAllProductsAdmin() {
    ifstream in("products.txt");
    if (!in) {
        cout << "No products available yet.\n";
        return;
    }

    Product p;
    int qty;
    cout << "\nAvailable Products (Admin View):\n";
    cout << left << setw(10) << "ID" << setw(25) << "Name"
         << setw(10) << "Price" << setw(10) << "Quantity\n";
    cout << "------------------------------------------------------------\n";

    while (in >> p.id) {
        in.ignore(); // Ignore the space after ID
        getline(in, p.name, '|'); // Read name until '|'
        in >> p.price >> qty;
        p.setQuantity(qty);
        p.displayForAdmin();
    }
    in.close();
    cout << "------------------------------------------------------------\n";
}

void addProduct() {
    Product p;
    int qty;
    
    cin.ignore(); // Clear input buffer
    
    cout << "Enter Product Name: ";
    getline(cin, p.name); // Read full name with spaces
    
    cout << "Enter Product Price: ";
    cin >> p.price;
    cout << "Enter Product Quantity: ";
    cin >> qty;
    p.setQuantity(qty);
    
    // Generate Product ID
    ifstream in("products.txt");
    int maxId = 0;
    Product temp;
    int tempQty;
    while (in >> temp.id) {
        in.ignore();
        getline(in, temp.name, '|');
        in >> temp.price >> tempQty;
        if (temp.id > maxId)
            maxId = temp.id;
    }

    p.id = maxId + 1;
    in.close();
    
    ofstream out("products.txt", ios::app);
    out << p.id << " " << p.name << "|" << p.price << " " << p.getQuantity() << endl;
    out.close();
    cout << "Product added successfully!\n";
}

void editProduct() {
    viewAllProductsAdmin();
    int id;
    cout << "Enter Product ID to edit: ";
    cin >> id;

    ifstream in("products.txt");
    ofstream out("temp.txt");
    Product p;
    bool found = false;
    int qty;

    while (in >> p.id) {
        in.ignore();
        getline(in, p.name, '|');
        in >> p.price >> qty;
        p.setQuantity(qty);
        
        if (p.id == id) {
            found = true;
            cout << "Editing Product - ID: " << p.id << ", Name: " << p.name
                 << ", Price: " << p.price << ", Quantity: " << p.getQuantity() << endl;

            cin.ignore(); // Clear buffer
            
            cout << "Enter new Name: ";
            getline(cin, p.name); // Read full name with spaces
            
            cout << "Enter new Price: ";
            cin >> p.price;
            cout << "Enter new Quantity: ";
            cin >> qty;
            int newQty = qty + p.getQuantity();
            p.setQuantity(newQty);
        }
        out << p.id << " " << p.name << "|" << p.price << " " << p.getQuantity() << endl;
    }
    in.close();
    out.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found)
        cout << "Product edited successfully!\n";
    else
        cout << "Product ID not found.\n";
}

void removeProduct() {
    int id;
    cout << "Enter Product ID to remove: ";
    cin >> id;

    ifstream in("products.txt");
    ofstream out("temp.txt");
    Product p;
    bool found = false;
    int qty;

    while (in >> p.id) {
        in.ignore();
        getline(in, p.name, '|');
        in >> p.price >> qty;
        p.setQuantity(qty);
        
        if (p.id == id) {
            found = true;
            continue;
        }
        out << p.id << " " << p.name << "|" << p.price << " " << p.getQuantity() << endl;
    }
    in.close();
    out.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found)
        cout << "Product removed successfully!\n";
    else
        cout << "Product ID not found.\n";
}


vector<Product> loadProducts() {
    vector<Product> products;
    ifstream in("products.txt");
    Product p;
    int qty;
    while (in >> p.id) {
        in.ignore();
        getline(in, p.name, '|');
        in >> p.price >> qty;
        p.setQuantity(qty);
        products.push_back(p);
    }
    in.close();
    return products;
}

void viewAllProductsUser() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }

    cout << "\nAvailable Products:\n";
    cout << left << setw(10) << "ID" << setw(25) << "Name"
         << setw(10) << "Price" << "Stock Info\n";
    cout << "------------------------------------------------------------\n";

    for (auto &p : products)
        p.displayForUser();

    cout << "------------------------------------------------------------\n";
}

// ---------------- NEW: SEARCH PRODUCTS BY NAME ----------------
void searchProductsByName() {
    cin.ignore(); // Clear input buffer
    string searchTerm;
    cout << "Enter product name to search: ";
    getline(cin, searchTerm);
    
    // Convert search term to lowercase for case-insensitive search
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
    
    vector<Product> products = loadProducts();
    vector<Product> matchedProducts;
    
    for (auto &p : products) {
        string productName = p.name;
        transform(productName.begin(), productName.end(), productName.begin(), ::tolower);
        
        // Check if search term is found in product name
        if (productName.find(searchTerm) != string::npos) {
            matchedProducts.push_back(p);
        }
    }
    
    if (matchedProducts.empty()) {
        cout << "\nNo products found matching '" << searchTerm << "'.\n";
        return;
    }
    
    cout << "\n========== Search Results ==========\n";
    cout << "Found " << matchedProducts.size() << " product(s) matching '" << searchTerm << "':\n\n";
    cout << left << setw(10) << "ID" << setw(25) << "Name"
         << setw(10) << "Price" << "Stock Info\n";
    cout << "------------------------------------------------------------\n";
    
    for (auto &p : matchedProducts) {
        p.displayForUser();
    }
    
    cout << "------------------------------------------------------------\n";
}

// ---------------- NEW: FILTER PRODUCTS BY PRICE RANGE ----------------
void filterProductsByPrice() {
    double minPrice, maxPrice;
    cout << "Enter minimum price: ";
    cin >> minPrice;
    cout << "Enter maximum price: ";
    cin >> maxPrice;
    
    if (minPrice < 0 || maxPrice < 0 || minPrice > maxPrice) {
        cout << "Invalid price range!\n";
        return;
    }
    
    vector<Product> products = loadProducts();
    vector<Product> filteredProducts;
    
    for (auto &p : products) {
        if (p.price >= minPrice && p.price <= maxPrice) {
            filteredProducts.push_back(p);
        }
    }
    
    if (filteredProducts.empty()) {
        cout << "\nNo products found in the price range Rs." << minPrice 
             << " - Rs." << maxPrice << ".\n";
        return;
    }
    
    // Sort by price (lowest to highest)
    sort(filteredProducts.begin(), filteredProducts.end(), 
         [](const Product &a, const Product &b) { return a.price < b.price; });
    
    cout << "\n========== Products in Price Range Rs." << minPrice 
         << " - Rs." << maxPrice << " ==========\n";
    cout << "Found " << filteredProducts.size() << " product(s):\n\n";
    cout << left << setw(10) << "ID" << setw(25) << "Name"
         << setw(10) << "Price" << "Stock Info\n";
    cout << "------------------------------------------------------------\n";
    
    for (auto &p : filteredProducts) {
        p.displayForUser();
    }
    
    cout << "------------------------------------------------------------\n";
}

// ---------------- USER FUNCTIONALITIES ----------------
void addToCart(string username) {
    vector<Product> products = loadProducts();
    
    // Give user options to browse products
    int browseChoice;
    cout << "\n--- Browse Products ---\n";
    cout << "1. View All Products\n";
    cout << "2. Search by Name\n";
    cout << "3. Filter by Price Range\n";
    cout << "Enter your choice: ";
    cin >> browseChoice;
    
    if (browseChoice == 1) {
        viewAllProductsUser();
    } else if (browseChoice == 2) {
        searchProductsByName();
    } else if (browseChoice == 3) {
        filterProductsByPrice();
    } else {
        cout << "Invalid choice. Showing all products.\n";
        viewAllProductsUser();
    }

    int id, qty;
    cout << "\nEnter Product ID to add to cart: ";
    cin >> id;
    cout << "Enter Quantity: ";
    cin >> qty;

    // Check if product exists and has enough stock
    bool productFound = false;
    for (auto &p : products) {
        if (p.id == id) {
            productFound = true;
            if (p.getQuantity() == 0) {
                cout << "Sorry, this item is out of stock.\n";
                return;
            }
            if (qty > p.getQuantity()) {
                cout << "Only " << p.getQuantity() << " items available. Try again.\n";
                return;
            }
            break;
        }
    }
    
    if (!productFound) {
        cout << "Invalid Product ID.\n";
        return;
    }

    // Read existing cart
    ifstream cartIn("cart.txt");
    vector<string> cartLines;
    string user;
    int cartId, cartQty;
    bool itemExists = false;

    while (cartIn >> user >> cartId >> cartQty) {
        if (user == username && cartId == id) {
            // Item already exists, increment quantity
            cartQty += qty;
            itemExists = true;
        }
        cartLines.push_back(user + " " + to_string(cartId) + " " + to_string(cartQty));
    }
    cartIn.close();

    // If item doesn't exist, add new line
    if (!itemExists) {
        cartLines.push_back(username + " " + to_string(id) + " " + to_string(qty));
    }

    // Write back to cart
    ofstream cartOut("cart.txt");
    for (const string &line : cartLines) {
        cartOut << line << endl;
    }
    cartOut.close();

    cout << "Product added to your cart successfully!\n";
}

void viewCart(string username) {
    ifstream cart("cart.txt");
    if (!cart) {
        cout << "Cart is empty.\n";
        return;
    }

    vector<Product> products = loadProducts();
    string user;
    int id, qty;
    double total = 0;
    bool found = false;

    cout << "\nYour Cart:\n";
    cout << left << setw(10) << "ID" << setw(20) << "Product" << setw(10) << "Qty"
         << setw(10) << "Price" << setw(10) << "Subtotal\n";
    cout << "------------------------------------------------------------\n";

    while (cart >> user >> id >> qty) {
        if (user == username) {
            found = true;
            for (auto &prod : products) {
                if (prod.id == id) {
                    double sub = prod.price * qty;
                    total += sub;
                    cout << left << setw(10) << prod.id << setw(20) << prod.name << setw(10)
                         << qty << setw(10) << prod.price << setw(10) << sub << endl;
                }
            }
        }
    }
    cart.close();

    if (!found)
        cout << "Your cart is empty.\n";
    else
        cout << "------------------------------------------------------------\nTotal: Rs." << total << endl;
}

void removeFromCart(string username) {
    ifstream cartIn("cart.txt");
    if (!cartIn) {
        cout << "Cart is empty.\n";
        return;   // return to user menu
    }

    bool hasItems = false;
    string u;
    int pid, pq;

    while (cartIn >> u >> pid >> pq) {
        if (u == username) {
            hasItems = true;
            break;
        }
    }

    if (!hasItems) {
        cout << "Your cart is empty.\n";
        cartIn.close();
        return;   
    }
    cartIn.clear();
    cartIn.seekg(0);

    viewCart(username);

    int removeId;
    cout << "\nEnter Product ID to remove from cart: ";
    cin >> removeId;

    int quant;
    cout << "Enter Quantity to remove: ";
    cin >> quant;

    vector<string> cartLines;
    string user;
    int id, qty;
    bool found = false;

    while (cartIn >> user >> id >> qty) {
        if (user == username && id == removeId) {
            found = true;

            if (qty > quant) {
                cartLines.push_back(user + " " + to_string(id) + " " + to_string(qty - quant));
            } 
            else if (qty < quant) {
                while (true) {
                    cout << "You only have " << qty << " of this item. Enter valid quantity: ";
                    cin >> quant;
                    if (quant <= qty) {
                        if (quant < qty) {
                            cartLines.push_back(user + " " + to_string(id) + " " + to_string(qty - quant));
                        }
                        break;
                    }
                }
            }

            continue; // skip adding original line
        }

        cartLines.push_back(user + " " + to_string(id) + " " + to_string(qty));
    }

    cartIn.close();

    if (!found) {
        cout << "Product not found in your cart.\n";
        return;
    }

    // Write updated cart
    ofstream cartOut("cart.txt");
    for (const string &line : cartLines) {
        cartOut << line << endl;
    }
    cartOut.close();

    cout << "Product removed from cart successfully!\n";
}


void checkout(string username) {
    ifstream cart("cart.txt");
    if (!cart) {
        cout << "No cart found.\n";
        return;
    }

    vector<Product> products = loadProducts();
    vector<string> remainingLines;
    string user;
    int id, qty;
    bool purchased = false;
    double totalCost = 0;

    // Get current time
    time_t now = time(0);
    string timestamp = ctime(&now);
    // Replace spaces with underscores for easy file reading
    for (char &c : timestamp) {
        if (c == ' ' || c == '\n')
            c = '_';
    }

    // Save order to orders.txt
    ofstream orders("orders.txt", ios::app);
    
    while (cart >> user >> id >> qty) {
        if (user == username) {
            purchased = true;
            for (auto &prod : products) {
                if (prod.id == id && prod.getQuantity() >= qty) {
                    prod.setQuantity(prod.getQuantity() - qty);
                    double itemCost = prod.price * qty;
                    totalCost += itemCost;
                    
                    // Write order details to file with timestamp
                    orders << username << " " << prod.name << "|" << qty << " " << itemCost << " " << timestamp << endl;
                }
            }
        } else {
            remainingLines.push_back(user + " " + to_string(id) + " " + to_string(qty));
        }
    }
    cart.close();
    orders.close();

    // Update cart (remove user's items)
    ofstream newCart("cart.txt");
    for (string &line : remainingLines)
        newCart << line << endl;
    newCart.close();

    // Update product quantities
    ofstream newProd("products.txt");
    for (auto &prod : products)
        newProd << prod.id << " " << prod.name << "|" << prod.price << " " << prod.getQuantity() << endl;
    newProd.close();

    if (purchased) {
        cout << "Checkout successful! Your order has been placed.\n";
        cout << "Total Amount Paid: Rs." << totalCost << endl;
    } else {
        cout << "No items to checkout.\n";
    }
}

void viewOrderHistory(string username) {
    ifstream orders("orders.txt");
    if (!orders) {
        cout << "No order history found.\n";
        return;
    }

    string user, productName, timestamp;
    int qty;
    double cost;
    bool found = false;

    cout << "\n========== Your Order History ==========\n";
    cout << left << setw(25) << "Product" << setw(8) << "Qty" << setw(12) << "Cost" << "Date\n";
    cout << "------------------------------------------------------------------------\n";

    while (orders >> user) {
        orders.ignore();
        getline(orders, productName, '|');
        orders >> qty >> cost >> timestamp;
        
        if (user == username) {
            found = true;
            // Replace underscores with spaces for display
            for (char &c : timestamp) {
                if (c == '_')
                    c = ' ';
            }
            cout << left << setw(25) << productName << setw(8) << qty 
                 << setw(12) << ("Rs." + to_string((int)cost)) << timestamp << endl;
        }
    }

    orders.close();

    if (!found) {
        cout << "You have no order history yet.\n";
    }
    cout << "========================================================================\n";
}

// ---------------- MAIN PROGRAM ----------------
int main() {
    User user;
    int mainChoice;

    while (true) {
        cout << "\n1. Admin Login\n2. User Login\n3. User Register\n4. Exit\nEnter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            string adminUser, adminPass;
            cout << "Enter Admin Username: ";
            cin >> adminUser;
            cout << "Enter Admin Password: ";
            cin >> adminPass;

            if (adminUser == "admin" && adminPass == "admin123") {
                int aChoice;
                while (true) {
                    cout << "\n--- Admin Menu ---\n1. Add Product\n2. View Products\n3. Edit Product\n4. Remove Product\n5. Logout\nEnter your choice: ";
                    cin >> aChoice;

                    if (aChoice == 1) addProduct();
                    else if (aChoice == 2) viewAllProductsAdmin();
                    else if (aChoice == 3) editProduct();
                    else if (aChoice == 4) removeProduct();
                    else if (aChoice == 5) break;
                    else cout << "Invalid choice.\n";
                }
            } else {
                cout << "Invalid Admin Credentials.\n";
            }

        } else if (mainChoice == 2) {
            if (user.login()) {
                int uChoice;
                while (true) {
                    cout << "\n--- User Menu ---\n";
                    cout << "1. View Products\n";
                    cout << "2. Search Products by Name\n";
                    cout << "3. Filter Products by Price Range\n";
                    cout << "4. Add to Cart\n";
                    cout << "5. View Cart\n";
                    cout << "6. Remove from Cart\n";
                    cout << "7. Checkout\n";
                    cout << "8. View Order History\n";
                    cout << "9. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> uChoice;

                    if (uChoice == 1) viewAllProductsUser();
                    else if (uChoice == 2) searchProductsByName();
                    else if (uChoice == 3) filterProductsByPrice();
                    else if (uChoice == 4) addToCart(user.getUsername());
                    else if (uChoice == 5) viewCart(user.getUsername());
                    else if (uChoice == 6) removeFromCart(user.getUsername());
                    else if (uChoice == 7) checkout(user.getUsername());
                    else if (uChoice == 8) viewOrderHistory(user.getUsername());
                    else if (uChoice == 9) { cout<<"Logged Out Successfully!!!!"<<endl; break; }
                    else cout << "Invalid choice.\n";
                }
            }

        } else if (mainChoice == 3) {
            user.registerUser();
        } else if (mainChoice == 4) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}