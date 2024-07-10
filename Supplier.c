#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Functions.h"

void initSupplierManager(char* fName, SupplierManager* manager) {
	printf("\n======Initializing Supplier Manager=====\n");

	if (!readSupplierfromText(fName,manager))
	{
		manager->suppliers = NULL;
		manager->numOfSuppliers = 0;

		char choice;
		do {
			printf("\nDo you want to add a supplier? (y/n): ");
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
	printf("\nEnter supplier name: ");
	strcpy(supplier->name, getStr());

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
	printf("%-20s|%d\n", supplier->name, supplier->code);
}

void printSupplierManager(SupplierManager* manager)
{
	printf("\n# |supplier name       |supplier code    \n");
	for (int i = 0; i < manager->numOfSuppliers; i++)
	{
		printf("%d |", i + 1);
		printSupplier(manager->suppliers[i]);
	}
}

int writeSupplierToText(char* fName, int count, SupplierManager* manager)
{
	FILE* textF = fopen(fName, "w");
	if (!textF)
	{
		printf("failed to open file");
		return 0;
	}

	fprintf(textF, "%d\n", count);
	for (size_t i = 0; i < count; i++)
	{
		fprintf(textF, "%s\n", manager->suppliers[i]->name);
		fprintf(textF, "%d\n", manager->suppliers[i]->code);
		fprintf(textF, "%d\n", manager->suppliers[i]->numOfProducts);
		writeProductsToText(textF, manager->suppliers[i]->numOfProducts, manager->suppliers[i]->productsArr);
	}
	fprintf(textF, "\n");

	fclose(textF);
	return 1;
}

Supplier** readSupplierfromText(char* fName , SupplierManager* manager)
{
	FILE* readF = fopen(fName, "r");
	if (!readF)
	{
		return NULL;
	}

	fscanf(readF,"%d",&manager->numOfSuppliers);
	manager->suppliers = (Supplier**)malloc(manager->numOfSuppliers * sizeof(Supplier*));
	if (!manager->suppliers)
	{
		return NULL;

	}


	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		manager->suppliers[i] = (Supplier*)malloc(sizeof(Supplier));
		if (!manager->suppliers[i])
		{
			free(manager->suppliers);
			return NULL;
		}

		fscanf(readF, "%s", manager->suppliers[i]->name);
		fscanf(readF, "%d", &manager->suppliers[i]->code);
		fscanf(readF, "%d", &manager->suppliers[i]->numOfProducts);

		manager->suppliers[i]->productsArr = readProductsFromText(readF, manager->suppliers[i]->numOfProducts, manager->suppliers[i]->productsArr);

	}
	fclose(readF);
	printf("suppliers initialized from text file\n");
	return manager->suppliers;
}

