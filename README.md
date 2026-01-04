# 🛒 Terminal-Based E-Commerce Management System

A comprehensive command-line shopping platform built in C++ featuring role-based access control, inventory management, and complete transaction processing capabilities.

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg)

## 📋 Table of Contents
- [Features](#features)
- [Tech Stack](#tech-stack)
- [System Architecture](#system-architecture)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Screenshots](#screenshots)
- [Contributing](#contributing)
- [License](#license)

## ✨ Features

### 👤 User Features
- **Authentication System**
  - User registration and login
  - Secure password storage
  - Session management

- **Product Discovery**
  - View all available products
  - Search products by name (case-insensitive)
  - Filter products by price range with automatic sorting
  - Real-time stock availability indicators

- **Shopping Cart**
  - Add products to cart with quantity selection
  - View cart with price calculations
  - Update cart quantities
  - Remove items from cart
  - Duplicate item handling

- **Order Management**
  - Secure checkout process
  - Real-time inventory validation
  - Timestamped order history
  - Total cost calculation

### 🔐 Admin Features
- **Product Management (CRUD Operations)**
  - Add new products with auto-generated IDs
  - View all products with full inventory details
  - Edit product information (name, price, quantity)
  - Remove products from catalog

- **Inventory Control**
  - Real-time stock tracking
  - Quantity management
  - Out-of-stock prevention

## 🛠️ Tech Stack

- **Language:** C++ (C++11 or higher)
- **Data Structures:** STL Vectors, Strings
- **File I/O:** Text-based persistence layer
- **Algorithms:** Search, Sort, Filter with lambda expressions
- **Design Pattern:** Object-Oriented Programming (OOP)

## 🏗️ System Architecture

```
┌─────────────────────────────────────────┐
│         Main Application Loop           │
└────────────┬────────────────────────────┘
             │
    ┌────────┴────────┐
    │                 │
┌───▼────┐      ┌────▼────┐
│ Admin  │      │  User   │
│ Module │      │ Module  │
└───┬────┘      └────┬────┘
    │                │
    │    ┌───────────┴────────────┐
    │    │                        │
┌───▼────▼───┐            ┌──────▼──────┐
│  Product   │            │    Cart     │
│  Manager   │            │   Manager   │
└─────┬──────┘            └──────┬──────┘
      │                          │
      └────────┬─────────────────┘
               │
      ┌────────▼─────────┐
      │  File I/O Layer  │
      │                  │
      │ - users.txt      │
      │ - products.txt   │
      │ - cart.txt       │
      │ - orders.txt     │
      └──────────────────┘
```

## 🚀 Installation

### Prerequisites
- C++ Compiler (GCC, Clang, or MSVC)
- C++11 or higher support

### Steps

1. **Clone the repository**
```bash
git clone https://github.com/irfanmohiddin/terminal-cart.git
cd terminal-cart
```

2. **Compile the program**
```bash
# Using g++
g++ -std=c++11 terminal-cart.cpp -o ecommerce

# Or using clang++
clang++ -std=c++11 terminal-cart.cpp -o ecommerce
```

3. **Run the application**
```bash
./ecommerce       # On Linux/Mac
ecommerce.exe     # On Windows
```

## 📖 Usage

### Admin Login
**Default Credentials:**
- Username: `admin`
- Password: `admin123`

**Admin Menu Options:**
1. Add Product
2. View Products
3. Edit Product
4. Remove Product
5. Logout

### User Operations

**Registration:**
```
Main Menu → User Register → Enter credentials
```

**Shopping Flow:**
```
Login → Browse Products → Add to Cart → Checkout
```

**User Menu Options:**
1. View Products
2. Search Products by Name
3. Filter Products by Price Range
4. Add to Cart
5. View Cart
6. Remove from Cart
7. Checkout
8. View Order History
9. Logout

### Example Workflow

```bash
# 1. Admin adds products
Admin Login → Add Product
Name: "Laptop"
Price: 45000
Quantity: 10

# 2. User shops
User Login → Search Products → "Laptop"
Add to Cart → Quantity: 2
Checkout → Order Confirmed!

# 3. View order history
View Order History → See timestamped purchases
```

## 📁 File Structure

```
terminal-cart/
│
├── terminal-cart.cpp          # Main source code
├── README.md                  # This file
├── LICENSE                    # License file
│
├── users.txt                  # User credentials (auto-generated)
├── products.txt               # Product inventory (auto-generated)
├── cart.txt                   # Shopping carts (auto-generated)
└── orders.txt                 # Order history (auto-generated)
```

### Data File Formats

**users.txt:**
```
username password
```

**products.txt:**
```
id product_name|price quantity
```

**cart.txt:**
```
username product_id quantity
```

**orders.txt:**
```
username product_name|quantity cost timestamp
```

## 🖼️ Screenshots

### User View
```
Available Products:
ID        Name                     Price     Stock Info
------------------------------------------------------------
1         Laptop                   45000     In Stock
2         Mouse                    500       Only 3 left in stock!
3         Keyboard                 1200      Out of Stock
------------------------------------------------------------
```

### Cart View
```
Your Cart:
ID        Product             Qty       Price     Subtotal
------------------------------------------------------------
1         Laptop              2         45000     90000
2         Mouse               1         500       500
------------------------------------------------------------
Total: Rs.90500
```

## 🔧 Key Features Explained

### 1. **Case-Insensitive Search**
```cpp
transform(searchTerm.begin(), searchTerm.end(), 
          searchTerm.begin(), ::tolower);
```
Converts both search term and product names to lowercase for accurate matching.

### 2. **Price Range Filtering**
```cpp
sort(filteredProducts.begin(), filteredProducts.end(), 
     [](const Product &a, const Product &b) { 
         return a.price < b.price; 
     });
```
Uses lambda expressions for efficient sorting.

### 3. **Stock Validation**
```cpp
if (qty > p.getQuantity()) {
    cout << "Only " << p.getQuantity() << " items available.\n";
    return;
}
```
Prevents overselling by checking inventory in real-time.

### 4. **Atomic Checkout**
- Updates inventory
- Clears user cart
- Records timestamped order
- All operations complete together

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Potential Enhancements
- [ ] Database integration (SQLite/MySQL)
- [ ] Password encryption
- [ ] Product categories/tags
- [ ] Multiple payment methods
- [ ] User reviews and ratings
- [ ] Wishlist functionality
- [ ] Discount codes/coupons
- [ ] Admin analytics dashboard

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Shaik Irfan Mohiddin**
- GitHub: [@irfanmohiddin](https://github.com/irfanmohiddin)
- LinkedIn: [Shaik Irfan Mohiddin](https://www.linkedin.com/in/shaik-irfan-mohiddin-537589323/)
- Email: irfanloyola2019@gmail.com

## 🙏 Acknowledgments

- Inspired by real-world e-commerce systems
- Built as a learning project for C++ and OOP concepts
- Special thanks to the open-source community

## 📊 Project Stats

- **Lines of Code:** ~700+
- **Classes:** 2 (Product, User)
- **Functions:** 15+
- **Data Files:** 4
- **Features:** 13 (9 user + 4 admin)

---

⭐ If you found this project helpful, please consider giving it a star!

**Happy Shopping! 🛍️**
