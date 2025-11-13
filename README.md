# Supermarket Management System

A simple command-line supermarket management system written in C that allows you to perform CRUD (Create, Read, Update, Delete) operations on products. All data is stored in a text file (`products.txt`).

## Features

- **Create**: Add new products with ID, name, price, and quantity
- **Read**: View all products or search for a specific product by ID
- **Update**: Modify existing product details
- **Delete**: Remove products from the system
- **File Storage**: All data is automatically saved to and loaded from `products.txt`

## Product Information

Each product contains:
- **ID**: Unique integer identifier
- **Name**: Product name (up to 100 characters)
- **Price**: Product price (floating-point number)
- **Quantity**: Available quantity (integer)

## Requirements

- GCC compiler (or any C compiler)
- Unix/Linux environment (or Windows with MinGW)

## Compilation

### Using Make:
```bash
make
```

### Manual Compilation:
```bash
gcc -Wall -Wextra -std=c99 supermarket.c -o supermarket
```

## Usage

### Run the program:
```bash
./supermarket
```

Or using Make:
```bash
make run
```

### Menu Options:

1. **Add New Product (CREATE)**
   - Enter product ID, name, price, and quantity
   - Product ID must be unique

2. **View All Products (READ)**
   - Displays a table of all products in the system

3. **Search Product by ID (READ)**
   - Search for a specific product using its ID

4. **Update Product (UPDATE)**
   - Modify name, price, or quantity of an existing product
   - Press Enter to keep current values unchanged

5. **Delete Product (DELETE)**
   - Remove a product from the system
   - Requires confirmation before deletion

6. **Exit**
   - Exit the program

## Data Storage

Products are stored in `products.txt` with the following format:
```
ID|Name|Price|Quantity
```

Example:
```
1|Apple|1.50|100
2|Banana|0.75|150
3|Orange|2.00|80
```

## Example Usage

```
===========================================
   SUPERMARKET MANAGEMENT SYSTEM
===========================================

-------------------------------------------
            MAIN MENU
-------------------------------------------
1. Add New Product (CREATE)
2. View All Products (READ)
3. Search Product by ID (READ)
4. Update Product (UPDATE)
5. Delete Product (DELETE)
6. Exit
-------------------------------------------
Enter your choice: 1

=== ADD NEW PRODUCT ===
Enter Product ID: 1
Enter Product Name: Apple
Enter Product Price: 1.50
Enter Product Quantity: 100

Product added successfully!
```

## Clean Up

To remove the compiled program and data file:
```bash
make clean
```

## Notes

- The system can handle up to 1000 products
- Product IDs must be unique
- Prices and quantities must be non-negative
- All data is automatically saved to `products.txt` after each operation

## Author

Supermarket Management System - A simple C-based inventory management tool
