#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define FILENAME "products.txt"

// Product structure
typedef struct {
    int id;
    char name[MAX_NAME];
    float price;
    int quantity;
} Product;

// Function prototypes
void displayMenu();
void createProduct();
void readProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void saveToFile(Product products[], int count);
int loadFromFile(Product products[]);
void clearInputBuffer();

int main() {
    int choice;
    
    printf("===========================================\n");
    printf("   SUPERMARKET MANAGEMENT SYSTEM\n");
    printf("===========================================\n\n");
    
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n\n");
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                createProduct();
                break;
            case 2:
                readProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                deleteProduct();
                break;
            case 6:
                printf("\nThank you for using Supermarket Management System!\n");
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please select 1-6.\n\n");
        }
    }
    
    return 0;
}

void displayMenu() {
    printf("-------------------------------------------\n");
    printf("            MAIN MENU\n");
    printf("-------------------------------------------\n");
    printf("1. Add New Product (CREATE)\n");
    printf("2. View All Products (READ)\n");
    printf("3. Search Product by ID (READ)\n");
    printf("4. Update Product (UPDATE)\n");
    printf("5. Delete Product (DELETE)\n");
    printf("6. Exit\n");
    printf("-------------------------------------------\n");
}

void createProduct() {
    Product products[1000];
    int count = loadFromFile(products);
    Product newProduct;
    
    printf("\n=== ADD NEW PRODUCT ===\n");
    
    // Get product ID
    printf("Enter Product ID: ");
    if (scanf("%d", &newProduct.id) != 1) {
        clearInputBuffer();
        printf("Invalid ID! Product not added.\n\n");
        return;
    }
    clearInputBuffer();
    
    // Check if ID already exists
    for (int i = 0; i < count; i++) {
        if (products[i].id == newProduct.id) {
            printf("Error: Product with ID %d already exists!\n\n", newProduct.id);
            return;
        }
    }
    
    // Get product name
    printf("Enter Product Name: ");
    fgets(newProduct.name, MAX_NAME, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0; // Remove newline
    
    // Get product price
    printf("Enter Product Price: ");
    if (scanf("%f", &newProduct.price) != 1 || newProduct.price < 0) {
        clearInputBuffer();
        printf("Invalid price! Product not added.\n\n");
        return;
    }
    clearInputBuffer();
    
    // Get product quantity
    printf("Enter Product Quantity: ");
    if (scanf("%d", &newProduct.quantity) != 1 || newProduct.quantity < 0) {
        clearInputBuffer();
        printf("Invalid quantity! Product not added.\n\n");
        return;
    }
    clearInputBuffer();
    
    // Add product to array
    products[count] = newProduct;
    count++;
    
    // Save to file
    saveToFile(products, count);
    
    printf("\nProduct added successfully!\n\n");
}

void readProducts() {
    Product products[1000];
    int count = loadFromFile(products);
    
    printf("\n=== ALL PRODUCTS ===\n");
    
    if (count == 0) {
        printf("No products found in the system.\n\n");
        return;
    }
    
    printf("%-10s %-30s %-15s %-10s\n", "ID", "Name", "Price", "Quantity");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-10d %-30s $%-14.2f %-10d\n", 
               products[i].id, 
               products[i].name, 
               products[i].price, 
               products[i].quantity);
    }
    
    printf("\nTotal products: %d\n\n", count);
}

void searchProduct() {
    Product products[1000];
    int count = loadFromFile(products);
    int searchId;
    int found = 0;
    
    printf("\n=== SEARCH PRODUCT ===\n");
    printf("Enter Product ID to search: ");
    
    if (scanf("%d", &searchId) != 1) {
        clearInputBuffer();
        printf("Invalid ID!\n\n");
        return;
    }
    clearInputBuffer();
    
    for (int i = 0; i < count; i++) {
        if (products[i].id == searchId) {
            printf("\nProduct Found:\n");
            printf("--------------------------------------------------------------------\n");
            printf("ID:       %d\n", products[i].id);
            printf("Name:     %s\n", products[i].name);
            printf("Price:    $%.2f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);
            printf("--------------------------------------------------------------------\n\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("\nProduct with ID %d not found!\n\n", searchId);
    }
}

void updateProduct() {
    Product products[1000];
    int count = loadFromFile(products);
    int updateId;
    int found = 0;
    
    printf("\n=== UPDATE PRODUCT ===\n");
    printf("Enter Product ID to update: ");
    
    if (scanf("%d", &updateId) != 1) {
        clearInputBuffer();
        printf("Invalid ID!\n\n");
        return;
    }
    clearInputBuffer();
    
    for (int i = 0; i < count; i++) {
        if (products[i].id == updateId) {
            found = 1;
            
            printf("\nCurrent Product Details:\n");
            printf("ID:       %d\n", products[i].id);
            printf("Name:     %s\n", products[i].name);
            printf("Price:    $%.2f\n", products[i].price);
            printf("Quantity: %d\n\n", products[i].quantity);
            
            printf("Enter New Details:\n");
            
            // Update name
            printf("Enter New Name (or press Enter to keep current): ");
            char newName[MAX_NAME];
            fgets(newName, MAX_NAME, stdin);
            newName[strcspn(newName, "\n")] = 0;
            if (strlen(newName) > 0) {
                strcpy(products[i].name, newName);
            }
            
            // Update price
            printf("Enter New Price (or -1 to keep current): ");
            float newPrice;
            if (scanf("%f", &newPrice) == 1 && newPrice >= 0) {
                products[i].price = newPrice;
            }
            clearInputBuffer();
            
            // Update quantity
            printf("Enter New Quantity (or -1 to keep current): ");
            int newQuantity;
            if (scanf("%d", &newQuantity) == 1 && newQuantity >= 0) {
                products[i].quantity = newQuantity;
            }
            clearInputBuffer();
            
            // Save to file
            saveToFile(products, count);
            
            printf("\nProduct updated successfully!\n\n");
            break;
        }
    }
    
    if (!found) {
        printf("\nProduct with ID %d not found!\n\n", updateId);
    }
}

void deleteProduct() {
    Product products[1000];
    int count = loadFromFile(products);
    int deleteId;
    int found = 0;
    
    printf("\n=== DELETE PRODUCT ===\n");
    printf("Enter Product ID to delete: ");
    
    if (scanf("%d", &deleteId) != 1) {
        clearInputBuffer();
        printf("Invalid ID!\n\n");
        return;
    }
    clearInputBuffer();
    
    for (int i = 0; i < count; i++) {
        if (products[i].id == deleteId) {
            found = 1;
            
            printf("\nProduct to be deleted:\n");
            printf("ID:       %d\n", products[i].id);
            printf("Name:     %s\n", products[i].name);
            printf("Price:    $%.2f\n", products[i].price);
            printf("Quantity: %d\n\n", products[i].quantity);
            
            printf("Are you sure you want to delete this product? (y/n): ");
            char confirm;
            scanf(" %c", &confirm);
            clearInputBuffer();
            
            if (confirm == 'y' || confirm == 'Y') {
                // Shift all elements after the deleted one
                for (int j = i; j < count - 1; j++) {
                    products[j] = products[j + 1];
                }
                count--;
                
                // Save to file
                saveToFile(products, count);
                
                printf("\nProduct deleted successfully!\n\n");
            } else {
                printf("\nDeletion cancelled.\n\n");
            }
            break;
        }
    }
    
    if (!found) {
        printf("\nProduct with ID %d not found!\n\n", deleteId);
    }
}

void saveToFile(Product products[], int count) {
    FILE *file = fopen(FILENAME, "w");
    
    if (file == NULL) {
        printf("Error: Unable to save to file!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%.2f|%d\n", 
                products[i].id, 
                products[i].name, 
                products[i].price, 
                products[i].quantity);
    }
    
    fclose(file);
}

int loadFromFile(Product products[]) {
    FILE *file = fopen(FILENAME, "r");
    int count = 0;
    
    if (file == NULL) {
        // File doesn't exist yet, return 0 products
        return 0;
    }
    
    while (fscanf(file, "%d|%[^|]|%f|%d\n", 
                  &products[count].id, 
                  products[count].name, 
                  &products[count].price, 
                  &products[count].quantity) == 4) {
        count++;
        if (count >= 1000) break; // Prevent overflow
    }
    
    fclose(file);
    return count;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
