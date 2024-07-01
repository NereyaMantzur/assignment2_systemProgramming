#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Functions.h"

void initSupplierManager(SupplierManager* manager) {
	printf("\nInitializing Supplier Manager\n");

	manager->suppliers = NULL;
	manager->numOfSuppliers = 0;

	char choice;
	do {
		printf("Do you want to add a supplier? (y/n): ");
		scanf(" %c", &choice);
		getchar();

		switch (choice) {
		case 'y':
		case 'Y':
			if (addSupplier(manager) == 0) {
				printf("Failed to add supplier.\n");
			}
			break;
		case 'n':
		case 'N':
			printf("Exiting supplier initialization.\n");
			break;
		default:
			printf("Invalid input. Please enter 'y' or 'n'.\n");
			break;
		}
	} while (choice != 'n' && choice != 'N');
}

void addProductToSupplier(Product* add, SupplierManager* manager) {
	if (!add || !manager) {
		return;
	}

	printf("Please enter supplier name:\n");
	char* str = getStr();
	int supplierFound = 0;

	for (size_t i = 0; i < manager->numOfSuppliers; i++) {
		Supplier* supplier = manager->suppliers[i];
		if (strcmp(supplier->name, str) == 0) {
			supplierFound = 1;
			for (size_t j = 0; j < supplier->numOfProducts; j++) {
				if (supplier->productsArr && supplier->productsArr[j] == add) {
					printf("Product already exists for this supplier.\n");
					free(str);
					return;
				}
			}
			supplier->numOfProducts++;
			Product** newArr = (Product**)realloc(supplier->productsArr, supplier->numOfProducts * sizeof(Product*));
			if (!newArr) {
				printf("Memory allocation for product list failed.\n");
				free(str);
				return;
			}
			supplier->productsArr = newArr;
			supplier->productsArr[supplier->numOfProducts - 1] = add;
			printf("Product added successfully to the supplier.\n");
			free(str);
			return;
		}
	}

	if (!supplierFound) {
		printf("Supplier not found.\n");
	}
	free(str);
}

void deleteProdcutFromSupplier(Product* add, SupplierManager* manager)
{
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		for (size_t j = 0; j < manager->suppliers[i]->numOfProducts; j++)
		{
			if (add->specs->productCode == manager->suppliers[i]->productsArr[j]->specs->productCode)
			{
				Product* temp = manager->suppliers[i]->productsArr[j];
				manager->suppliers[i]->productsArr[j] = manager->suppliers[i]->productsArr[manager->suppliers[i]->numOfProducts - 1];
				manager->suppliers[i]->numOfProducts--;
				free(temp);
				return;
			}
		}
	}
	printf("Product not found\n");
	return;
}

int isProductInSupplier(Product* add, SupplierManager* manager)
{
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		for (size_t j = 0; j < manager->suppliers[i]->numOfProducts; j++)
		{
			if (add->specs->productCode == manager->suppliers[i]->productsArr[j]->specs->productCode)
			{
				return 1;
			}
		}
	}
	return 0;
}

int isProductFromSupplier(ProductManager* managar, Supplier* supplier)
{
	for (size_t i = 0; i < managar->numOfProducts; i++)
	{
		if (!strcmp(managar->productArr[i]->supplier, supplier->name))
		{
			return 1;
		}
	}
	return 0;
}



int addSupplier(SupplierManager* manager) {
	Supplier* supplier = (Supplier*)malloc(sizeof(Supplier));
	if (!supplier) {
		printf("Memory allocation for supplier failed.\n");
		return 0;
	}

	supplier->numOfProducts = 0;
	supplier->productsArr = NULL;
	printf("Enter supplier name: ");
	strcpy(supplier->name, getStr());
	replaceSpaces(supplier->name);

	printf("Enter supplier code (6 digits): ");
	while (1) {
		scanf("%d", &supplier->code);
		getchar();

		if (supplier->code >= 100000 && supplier->code <= 999999) {
			break;
		}
		printf("Code not valid. Try again.\n");
		printf("Enter supplier code (6 digits): ");
	}

	for (int i = 0; i < manager->numOfSuppliers; i++) {
		if (manager->suppliers[i]->code == supplier->code) {
			printf("Supplier with this code already exists.\n");
			free(supplier);
			return 0;
		}
	}

	Supplier** temp = (Supplier**)realloc(manager->suppliers, (manager->numOfSuppliers + 1) * sizeof(Supplier*));
	if (!temp) {
		printf("Memory reallocation failed.\n");
		free(supplier);
		return 0;
	}
	manager->suppliers = temp;

	manager->suppliers[manager->numOfSuppliers] = supplier;
	manager->numOfSuppliers++;

	printf("Supplier added successfully!\n");

	return 1;
}

int removeSupplier(SupplierManager* manager, Supplier* delete)
{
	if (manager->numOfSuppliers == 0)
	{
		printf("no supplier to delete\n");
		return 0;
	}
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		if (manager->suppliers[i] == delete)
		{
			manager->suppliers[i] = manager->suppliers[manager->numOfSuppliers];
			manager->suppliers = (Supplier**)realloc(manager->suppliers, (manager->numOfSuppliers - 1) * sizeof(Supplier*));
			manager->numOfSuppliers--;
			return 1;
		}
	}
	printf("supplier not found\n");
	return 0;
}

int updateSupplier(SupplierManager* manager, Supplier* update)
{
	if (manager->numOfSuppliers == 0)
	{
		printf("no suppliers to delete");
		return 0;
	}
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		if (manager->suppliers[i] == update) {
			printf("Enter supermarket name: ");
			fgets(manager->suppliers[i]->name, MAX_NAME_LENGTH, stdin);
			getchar();

			printf("Enter supermarket code: ");
			scanf(" %d", &manager->suppliers[i]->code);
		}
	}
	return 1;
}

Supplier* findSupplierByNameOrCode(SupplierManager* manager, char* str, int code)
{
	char* temp = str;
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
	if (manager->numOfSuppliers == 0)
	{
		printf("no supermarket to delete");
	}
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		if (manager->suppliers[i]->code == code) {
			return manager->suppliers[i];
		}
		else if (!strcmp(manager->suppliers[i]->name, temp))
		{
			return manager->suppliers[i];
		}
	}
	return 0;
}


void printSupplier(Supplier* supplier)
{
	printf("%s : %d\n", supplier->name, supplier->code);
}

void printSupplierManager(SupplierManager* manager)
{
	printf("supplier name - supplier code:\n");
	for (int i = 0; i < manager->numOfSuppliers; i++)
	{
		printf("%d : ", i + 1);
		printSupplier(manager->suppliers[i]);
	}
}