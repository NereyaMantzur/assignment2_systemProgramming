#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
	strcpy(name, getStr());
	printf("enter supermarket code:\n");
	scanf("%d", &code);
	Supermarket* super = findSupermarketByNameOrCode(manager, name, code);
	if (!super)
	{
		printf("supermarket Not fount\n");
		return;
	}
	printf("\n%s products are:\n", super->name);
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
	printf("\n%s products are:\n", supplier->name);
	printf("\n# |product name        |product code        |product Type\n");
	for (int i = 0; i < supplier->numOfProducts; i++)
	{
		printf("%d |", i + 1);
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
	while (temp)
	{
		for (size_t j = 0; j < temp->numOfProducts; j++)
		{
			if (*temp->productsArr[j]->specs->type == *(Type*)&choice)
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
			if (*manager->suppliers[i]->productsArr[j]->specs->type == *(Type*)&choice)
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
	strcpy(name, getStr());
	printf("please enter supermarket code: ");
	scanf("%d", &code);
	Supermarket* temp = manager->supermarketList;
	while (!temp)
	{
		if ((!strcmp(temp->name, name)) || temp->code == code)
		{
			Supermarket* super = temp;
			printf("\nall product of a specific type in %s: \n", super->name);
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

void q10(ProductManager* manager)
{
	printf("\nproduct name        |product code        |product Type");
	generalArrayFunction(manager->productArr, manager->numOfProducts, sizeof(Product*), printProduct);
}

void q11(SupplierManager* manager)
{
	printf("\nsupplier name       |supplier code    ");
	generalArrayFunction(manager->suppliers, manager->numOfSuppliers, sizeof(Supplier*), printSupplier);
}

void q12(ProductManager* manager)
{
	Product* temp = (Product*)malloc(sizeof(Product));
	temp->specs = (productInfo*)malloc(sizeof(productInfo));
	int choice;
	Product** res;


	printf("please enter type of search:\n");
	printf("1 - NAME\n");
	printf("2 - CODE\n");
	scanf("%d", &choice);
	getchar();

	switch (choice) {
	case 1:
		qsort(manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByName);
		printf("what is the name of the product you want to search\n");
		strcpy(temp->specs->productName, getStr());
		res = (Product**)bsearch(&temp, manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByName);
		if (res)
		{
			printf("\nproduct name        |product code        |product Type\n");
			printProduct(*res);
			break;
		}
		printf("product Not found\n");
		break;
	case 2:
		qsort(manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByCode);
		printf("what is the code of the product you want to search (6 digits)\n");
		initProductCode(temp->specs, manager);
		res = (Product**)bsearch(&temp, manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByCode);
		if (res)
		{
			printf("\nproduct name        |product code        |product Type\n");
			printProduct(*res);
			break;
		}
		printf("product Not found\n");
		break;
	default:
		printf("Invalid choice. Please enter a number between 1 and 13.\n");
	}

}

void replaceSpaces(char* str) {
	while (*str != '\0') {
		if (*str == ' ') {
			*str = '$';
		}
		str++;
	}
}

char* getStr() {
	char temp[MAX_NAME];
	fgets(temp, MAX_NAME, stdin);

	temp[strcspn(temp, "\n")] = '\0';

	char* str = malloc(strlen(temp) + 1);
	strcpy(str, temp);

	if (*str) {
		*str = toupper(*str);
		for (char* p = str + 1; *p; ++p) {
			*p = tolower(*p);
		}
	}

	return str;
}

void generalArrayFunction(void** arr , int count , int size , int (*func)(void* element))
{
	printf("\n");
	for (size_t i = 0; i < count; i++)
	{
		func(arr[i]);
	}
}