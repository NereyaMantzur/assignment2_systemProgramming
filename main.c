#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"

#define SUPPLIER_TEXT "suppliers.txt"



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
	strcpy(name, getStr());
	printf("enter supermarket code:\n");
	scanf("%d", &code);
	Supermarket* super = findSupermarketByNameOrCode(manager, name, code);
	printf("\n%s products are:\n" , super->name);
	printSupermarketProducts(super);
} 

void q4(SupermarketManager* manager)
{
	printf("\nall supermarket info:\n");
	printSupermarketManager(manager);
}

void q5(SupplierManager* manager)
{
	char name[MAX_NAME];
	int code;
	printSupplierManager(manager);
	printf("please enter supplier name: ");
	strcpy(name, getStr());
	printf("please enter supplier code: ");
	scanf("%d", &code);
	Supplier* supplier = findSupplierByNameOrCode(manager, name, code);
	printf("\n%s products are:\n",supplier->name);
	printf("\n# |product name        |product code        |product Type\n");
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
	printf("\nall products of a specific type in all supermarkets:\n");

	Supermarket* temp = manager->supermarketList;
	while (!temp)
	{
		for (size_t j = 0; j < temp->numOfProducts; j++)
		{
			if (temp->productsArr[j]->specs->type == (Type*)&choice)
			{
				printProduct(temp->productsArr[j]);
			}
		}
		temp = temp->next;
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
	
	printf("\nall products of a specific type in all suppliers:\n");
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		for (size_t j = 0; j < manager->suppliers[i]->numOfProducts; j++)
		{
			if (manager->suppliers[i]->productsArr[j]->specs->type == (Type*)&choice)
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
	strcpy(name,getStr());
	printf("please enter supermarket code: ");
	scanf("%d", &code);
	Supermarket* temp = manager->supermarketList;
	while (!temp)
	{
		if ((!strcmp(temp->name, name)) || temp->code == code)
		{
			Supermarket* super = temp;
			printf("\nall product of a specific type in %s: \n",super->name);
			for (size_t j = 0; j < super->numOfProducts; j++)
			{
				printProduct(super->productsArr[j]);
			}
		}
	}
}

void q9(ProductManager* manager)
{
	sortProductArr(manager);
}

void q12(ProductManager* manager)
{
	int choice;
	char* name;
	printf("please enter type of search:\n");
	printf("1 - NAME\n");
	printf("2 - CODE\n");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		printf("what is the name of the product\n");
		name = getStr();
		bsearch(, manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByName);
		break;
	case 2:
		break;
	default:
		printf("Invalid choice. Please enter a number between 1 and 13.\n");
	}

}

int main() {
	SupermarketManager supermarketManager;
	SupplierManager supplierManager;
	ProductManager productManager;

	initSupermarketManager(&supermarketManager);
	initSupplierManager(SUPPLIER_TEXT, &supplierManager);
	initProductManager(&productManager);

	int choice;
	do {
		printf("\nMain Menu\n");
		printf("1. Add a supermarket \n");
		printf("2. Add a product to supplier or supermarket\n");
		printf("3. print supermarket products\n");
		printf("4. print all supermarkets \n");
		printf("5. Print all products of a supplier\n");
		printf("6. Print all products of a specific type in supermarkets\n");
		printf("7. Print all products of a specific type in suppliers\n");
		printf("8. Print products by type in a specific supermarket\n");
		printf("9. sort products by chosen rule\n");
		printf("10. print all products \n");
		printf("11. print all suppliers \n");
		printf("12. search product by ");
		printf("13. Exit\n");


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
			q9(&productManager);
			break;
		case 10:
			generalArrayFunction(productManager.productArr, productManager.numOfProducts, sizeof(Product*), printProduct);
			break;
		case 11:
			generalArrayFunction(supplierManager.suppliers, supplierManager.numOfSuppliers, sizeof(Supplier*), printSupplier);
			break;
		case 12:
			
			break;
		case 13:
			printf("Exiting the program.\n");
			break;
		default:
			printf("Invalid choice. Please enter a number between 1 and 13.\n");
		}
		writeSupplierToText(SUPPLIER_TEXT, supplierManager.numOfSuppliers, &supplierManager);
	} while (choice != 13);

	return 0;
}