#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
void q1(SupermarketManager* supermarketManager)
{
	addSupermarket(supermarketManager);
}

void q2(SupermarketManager* supermarketManager, SupplierManager* supplierManager, ProductManager* productManager) {
    int choice;
	int super;
    printf("please enter your choice:\n");
    printf("1 - for adding product to a supermarket :\n");
    printf("2 - for adding product to a supplier :\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        addProdcutToSupermarket(addProduct(productManager), supermarketManager);
        break;
    case 2:
        addProdcutToSupermarket(addProduct(productManager), supplierManager);
        break;
    default:
        break;
    }
}

void q3(SupermarketManager* manager)
{
    char name[MAX_NAME];
    int code;
    printSupermarketManager(&manager);
    printf("enter supermarket name:\n");
    scanf("%s", &name);
    getchar();
    printf("enter supermarket code:\n");
	scanf("%d", &code);
    printSupermarket(findSupermarketByNameOrCode(&manager, name, code));
}


int main() {
    SupermarketManager supermarketManager ;
	SupplierManager supplierManager ;
    ProductManager productManager;

    initSupermarketManager(&supermarketManager);
    initSupplierManager(&supplierManager);
    initProductManager(&productManager);

    int choice;
    do {
        printf("\nMain Menu\n");
        printf("1. Add a supermarket \n");
        printf("2. Add a product to supplier or supermarket\n");
        printf("3. print supermarket products\n");
        printf("4. print all supermarkets info\n");
        printf("5. Print all products of a supplier\n");
        printf("6. Print all products of a specific type in supermarkets\n");
        printf("7. Print all products of a specific type in suppliers\n");
        printf("8. Print products by type in specific supermarket\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf(" %d", &choice);
        getchar();
        switch (choice) {
        case 1:
            q1(&supermarketManager);
            break;
        case 2: 
            q2(&supermarketManager, &supplierManager,&productManager);
            break;
        case 3:
            q3(&supermarketManager);
        break;
        case 4:
            printSupermarketManager(&supermarketManager);
        break;
        //case 5:
        //{
        //    char supermarketName[MAX_NAME_LENGTH];
        //    int supermarketCode;
        //    // Code to input supermarket details
        //    printProductsSoldBySupermarket(&supermarketManager, supermarketName, supermarketCode);
        //}
        //break;
        //case 6:
        //    printAllSupermarkets(&supermarketManager);
        //    break;
        //case 7:
        //{
        //    char supplierName[MAX_NAME_LENGTH];
        //    // Code to input supplier name
        //    printSupplierProducts(&supplierManager, supplierName);
        //}
        //break;
        //case 8:
        //{
        //    int productType;
        //    // Code to input product type
        //    printProductsByTypeInSupermarkets(&supermarketManager, productType);
        //}
        //break;
        case 9: // Exit
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 11.\n");
        }

    } while (choice != 9);

    return 0;
}




