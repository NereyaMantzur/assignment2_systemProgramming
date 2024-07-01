#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
void q1(SupermarketManager* supermarketManager)
{
	addSupermarket(supermarketManager);
}

void q2(SupermarketManager* supermarketManager, SupplierManager* supplierManager, ProductManager* productManager) {
	int choice;
	printf("please enter your choice:\n");
	printf("1 - for adding product to a supermarket :\n");
	printf("2 - for adding product to a supplier :\n");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		printProductManager(productManager);
		printf("please choose number of product: \n");
		scanf("%d", &choice);
		getchar();
		printSupermarketManager(supermarketManager);
		addProductToSupermarket(findProductByIndex(productManager, choice), supermarketManager);
		break;
	case 2:
		printProductManager(productManager);
		printf("please choose number of product: \n");
		scanf("%d", &choice);
		getchar();
		printSupplierManager(supplierManager);
		addProductToSupplier(findProductByIndex(productManager, choice), supplierManager);
		break;
	default:
		break;
	}
}

void q3(SupermarketManager* manager)
{
	char name[MAX_NAME];
	int code;
	printSupermarketManager(manager);
	printf("enter supermarket name:\n");
	scanf("%s", &name);
	getchar();
	printf("enter supermarket code:\n");
	scanf("%d", &code);
	printSupermarketProducts(findSupermarketByNameOrCode(manager, name, code));
}

void q4(SupermarketManager* manager)
{
	printSupermarketManager(manager);
}

void q5(SupplierManager* manager)
{
	char name[MAX_NAME];
	int code;
	printSupplierManager(manager);
	printf("please enter supplier name: ");
	scanf("%s", &name);
	getchar();
	printf("please enter supplier code: ");
	scanf("%d", &code);
	Supplier* supplier = findSupplierByNameOrCode(manager, name, code);
	for (size_t i = 0; i < supplier->numOfProducts; i++)
	{
		printProduct(supplier->productsArr[i]);
	}
}

void q6(SupermarketManager* manager)
{
	int choice;
	printf("please choose Product Type:\n");
	printf("1 - FOOD\n");
	printf("2 - CLEANING\n");
	printf("3 - GENERAL\n");
	scanf("%d", &choice);
	for (size_t i = 0; i < manager->numOfSupermarkets; i++)
	{
		for (size_t j = 0; j < manager->supermarkets[i]->numOfProducts; j++)
		{
			if ((int)manager->supermarkets[i]->productsArr[j]->specs->type == choice)
			{
				printProduct(manager->supermarkets[i]->productsArr[j]);
			}
		}
	}
}

void q7(SupplierManager* manager)
{
	int choice;
	printf("please choose Product Type:\n");
	printf("1 - FOOD\n");
	printf("2 - CLEANING\n");
	printf("3 - GENERAL\n");
	scanf("%d", &choice);
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		for (size_t j = 0; j < manager->suppliers[i]->numOfProducts; j++)
		{
			if (((int)manager->suppliers[i]->productsArr[j]->specs->type) == choice)
			{
				printProduct(manager->suppliers[i]->productsArr[j]);
			}
		}
	}
}

void q8(SupermarketManager* manager)
{
	char name[MAX_NAME];
	int code;
	printSupermarketManager(manager);
	printf("please choose supermarket name: ");
	scanf("%s", &name);
	getchar();
	printf("please enter supermarket code: ");
	scanf("%d", &code);
	for (size_t i = 0; i < manager->numOfSupermarkets; i++)
	{
		if ((!strcmp(manager->supermarkets[i]->name, name)) || manager->supermarkets[i]->code == code)
		{
			for (size_t j = 0; j < manager->supermarkets[i]->numOfProducts; j++)
			{
				printProduct(manager->supermarkets[i]->productsArr[j]);
			}
		}
	}
}

int main() {
	SupermarketManager supermarketManager;
	SupplierManager supplierManager;
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
			q2(&supermarketManager, &supplierManager, &productManager);
			break;
		case 3:
			q3(&supermarketManager);
			break;
		case 4:
			q4(&supermarketManager);
			break;
		case 5:
			q5(&supplierManager);
			break;
		case 6:
			q6(&supermarketManager);
			break;
		case 7:
			q7(&supplierManager);
			break;
		case 8:
			q8(&supermarketManager);
			break;
		case 9:
			printf("Exiting the program.\n");
			break;
		default:
			printf("Invalid choice. Please enter a number between 1 and 11.\n");
		}

	} while (choice != 9);

	return 0;
}




