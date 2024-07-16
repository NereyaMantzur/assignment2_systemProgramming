#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Product.h"
#include "Functions.h"

void initProductManager(ProductManager* productManager ,SupplierManager* supplierManager) {
	printf("\n=====Initializing Product Manager=====\n");

	productManager->productArr = NULL;
	productManager->numOfProducts = 0;

	addProductFromText(productManager , supplierManager);

	char choice;
	do {
		printf("\nDo you want to add a product? (y/n): ");
		scanf(" %c", &choice);
		getchar();

		switch (choice) {
		case 'y':
		case 'Y':
			if (addProduct(productManager) == 0) {
				printf("Failed to add Product.\n");
			}
			break;
		case 'n':
		case 'N':
			printf("Exiting product initialization.\n");
			break;
		default:
			printf("Invalid input. Please enter 'y' or 'n'.\n");
			break;
		}
	} while (choice != 'n' && choice != 'N');
}

void initProductInfo(Product* product, ProductManager* manager) {
	productInfo* newInfo = (productInfo*)malloc(sizeof(productInfo));
	if (!newInfo) {
		printf("allocation failed\n");
		return;
	}

	printf("\nplease enter product name: ");
	strcpy(newInfo->productName, getStr());

	initProductCode(newInfo, manager);

	int choice;
	while (1) {
		printf("Please enter product type (1 for FOOD, 2 for CLEANING, 3 for GENERAL): ");
		if (scanf("%d", &choice) == 1 && (choice == FOOD || choice == CLEANING || choice == GENERAL)) {
			newInfo->type = (Type*)malloc(sizeof(Type));
			if (newInfo->type != NULL) {
				*newInfo->type = (Type)choice;
			}
			break;
		}
		printf("Invalid choice. Try again.\n");
	}

	product->specs = newInfo;
}

void initProductCode(productInfo* newInfo, ProductManager* manager) {
	int isUnique;
	while (1) {
		printf("Enter product code (6 digits): ");

		if (scanf("%d", &newInfo->productCode) == 1 && getchar() == '\n' &&
			newInfo->productCode >= 100000 && newInfo->productCode <= 999999) {
			isUnique = 1;
			for (int i = 0; i < manager->numOfProducts; i++) {
				if (manager->productArr[i]->specs->productCode == newInfo->productCode) {
					isUnique = 0;
					break;
				}
			}

			if (isUnique) {
				break;
			}
			else {
				printf("Code already exists. Try again.\n");
			}
		}
		else {
			printf("Code not valid. Try again.\n");
		}
	}
}

void addProductFromText(ProductManager* productManager, SupplierManager* supplierManager)
{
	int index = 0;
	for (size_t i = 0; i < supplierManager->numOfSuppliers; i++)
	{
		for (size_t j = 0; j < supplierManager->suppliers[i]->numOfProducts; j++)
		{
			productManager->productArr = (Product**)realloc(productManager->productArr, (productManager->numOfProducts + 1) * sizeof(Product*));
			productManager->productArr[index] = supplierManager->suppliers[i]->productsArr[j];
			productManager->numOfProducts++;
			index++;
		}
	}
}

Product* addProduct(ProductManager* manager) {
	manager->productArr = (Product**)realloc(manager->productArr, (manager->numOfProducts + 1) * sizeof(Product*));
	if (!manager->productArr) {
		printf("Memory allocation for product list failed.\n");
		return NULL;
	}

	Product* product = (Product*)malloc(sizeof(Product));
	if (!product) {
		printf("Memory allocation for product failed.\n");
		return NULL;
	}

	product->nameOfSupers = NULL;
	product->numOfSupers = 0;

	initProductInfo(product ,manager);

	product->exp = (Date*)malloc(sizeof(Date));
	if (!product->exp) {
		printf("Memory allocation for expiry date failed.\n");
		free(product);
		return NULL;
	}
	printf("Please enter expiry date:\n");
	while (!initDate(product->exp)) {
		printf("Invalid date. Please enter expiry date again:\n");
	}

	product->mfg = (Date*)malloc(sizeof(Date));
	if (!product->mfg) {
		printf("Memory allocation for manufacture date failed.\n");
		free(product->exp);
		free(product);
		return NULL;
	}
	printf("Please enter manufacture date:\n");
	while (!initDate(product->mfg)) {
		printf("Invalid date. Please enter manufacture date again:\n");
	}

	manager->productArr[manager->numOfProducts] = product;
	manager->numOfProducts++;

	printf("Product added successfully!\n");
	return product;
}

int isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(Date* date) {
	if (date->year < 1900 || date->year > 2100) {
		return 0;
	}

	if (date->month < 1 || date->month > 12) {
		return 0;
	}

	int daysInMonth;
	switch (date->month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		daysInMonth = 31;
		break;
	case 4: case 6: case 9: case 11:
		daysInMonth = 30;
		break;
	case 2:
		daysInMonth = isLeapYear(date->year) ? 29 : 28;
		break;
	default:
		return 0;
	}

	if (date->day < 1 || date->day > daysInMonth) {
		return 0;
	}

	return 1;
}

Date* initDate() {
	Date* date = (Date*)malloc(sizeof(Date));
	if (date == NULL) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	char input[11];

	do {
		printf("Enter date (DD/MM/YYYY): ");
		scanf("%10s", input);

		memset(date, 0, sizeof(Date));

		if (sscanf(input, "%2d/%2d/%4d", &(date->day), &(date->month), &(date->year)) != 3) {
			printf("Invalid format. Please enter again.\n");
			continue;
		}

		if (!isValidDate(date)) {
			printf("Invalid date. Please enter again.\n");
		}
	} while (!isValidDate(date));

	return date;
}

void deleteProdcutFromSupermarket(Product* product, char* delete)
{
	for (size_t i = 0; i < product->numOfSupers; i++)
	{
		if (!strcmp(product->nameOfSupers[i], delete))
		{
			product->nameOfSupers[i] = "";
			return;
		}
	}
	printf("Product Not found...\n");
}

void doPrintSupermarketWithProductCode(ProductManager* manager)
{
	if (!manager->productArr)
	{
		printf("No Products in the system..\n");
	}
	int code;
	printf("Enter product code (6 digits): ");
	while (1) {
		scanf("%d", &code);
		getchar();

		if (code >= 100000 && code <= 999999) {
			break;
		}
		printf("Code not valid. Try again.\n");
		printf("Enter product code (6 digits): ");
	}
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		if (manager->productArr[i]->specs->productCode == code)
		{
			for (size_t j = 0; j < manager->productArr[i]->numOfSupers; j++)
			{
				printf("%s\n", manager->productArr[i]->nameOfSupers[j]);
			}
		}
	}
}

void doPrintSupermarketWithProductName(ProductManager* manager)
{
	if (!manager->productArr)
	{
		printf("No supermarket in the system..\n");
	}
	char name[MAX_NAME];
	printf("Please enter a Product Name to see where it can be found:");
	scanf(" %s", &name);
	for (size_t i = 0; i < strlen(name); i++)
	{
		toupper(name[i]);
	}
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		if (strcpy(manager->productArr[i]->specs->productName, name))
		{
			for (size_t j = 0; j < manager->productArr[i]->numOfSupers; j++)
			{
				printf("%s", manager->productArr[i]->nameOfSupers[j]);
			}
		}
	}
	return;
}

void doPrintSupplierWithProductCode(SupplierManager* manager)
{
	int choice;
	printf("please enter product code: ");
	scanf("%d", &choice);
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		for (size_t j = 0; j < manager->suppliers[i]->numOfProducts; j++)
		{
			if (manager->suppliers[i]->productsArr[j]->specs->productCode == choice)
			{
				printProduct(manager->suppliers[i]->productsArr[j]);
			return;
			}
		}
	}
	printf("code not valid!");
	return;
}

void doPrintSupplierWithProductName(SupplierManager* manager)
{
	char choice[MAX_NAME];
	printf("please enter product code: ");
	scanf("%s", &choice);
	getchar();
	for (size_t i = 0; i < manager->numOfSuppliers; i++)
	{
		for (size_t j = 0; j < manager->suppliers[i]->numOfProducts; j++)
		{
			if (!strcmp(manager->suppliers[i]->productsArr[j]->specs->productName ,choice))
			{
				printProduct(manager->suppliers[i]->productsArr[j]);
				return;
			}
		}
	}
	printf("name not valid!");
	return;
}

void doPrintProductsWithProductType(ProductManager* manager)
{
	int choice;
	printf("please enter product type (1 FOOD , 2 CLEANING , 3 GENERAL) : ");
	scanf("%d", &choice);
	getchar();
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		if ((manager->productArr[i]->specs->type, choice))
		{
			for (size_t j = 0; j < manager->productArr[i]->numOfSupers; j++)
			{
				printf("%s", manager->productArr[i]->nameOfSupers[j]);
			}
			return;
		}
	}
	printf("name not valid!");
	return;
}

int isProductType(ProductManager* manager)
{
	char* name = getStr();
	int code;
	printf("please enter product code:\n");
	scanf("%d", &code);
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		if (!strcmp(manager->productArr[i]->specs->productName, name) || manager->productArr[i]->specs->productCode == code)
		{
			return *(manager->productArr[i]->specs->type);
		}
	}
	return -1;
}

int isProductCode(ProductManager* manager)
{
	char* name = getStr();
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		if (!strcmp(manager->productArr[i]->specs->productName, name))
		{
			return manager->productArr[i]->specs->productCode;
		}
	}
	return -1;
}

Product* findProductByIndex(ProductManager* manager, int index)
{
	if (index < 0 || index > manager->numOfProducts)
	{
		printf("error! invalid choice");
		return NULL;
	}
	else
	{
		return manager->productArr[index - 1];
	}
}

int printProduct(Product* product)
{
	char typeStr[10]="";
	switch (* product->specs->type)
	{
	case FOOD:
		strcat(typeStr, "FOOD");
		break;
	case CLEANING:
		strcat(typeStr, "CLEANING");
		break;
	case GENERAL:
		strcat(typeStr, "GENERAL");
		break;
	default:
		break;
	}
	printf("%-20s|%-20d|%s\n", product->specs->productName, product->specs->productCode , &typeStr);
	return 1;
}

void printProductManager(ProductManager* manager)
{
	printf("\n# |product name        |product code        |product Type\n");
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		printf("%d |", (int)i + 1);
		printProduct(manager->productArr[i]);
	}
}

int compareProductByName(const void* a, const void* b)
{
	const Product* productA = *(const Product**)a;
	const Product* productB = *(const Product**)b;
	return strcmp(productA->specs->productName, productB->specs->productName);
}

int compareProductByCode(const void* a, const void* b)
{
	const Product* productA = *(const Product**)a;
	const Product* productB = *(const Product**)b;
	return productA->specs->productCode - productB->specs->productCode;
}

int compareProductByType(const void* a, const void* b)
{
	const Product* productA = *(const Product**)a;
	const Product* productB = *(const Product**)b;

	return *(productA->specs->type) - *(productB->specs->type);
}

void sortProductArr(ProductManager* manager )
{
		do
	{
		int choice;
		printf("which sortion you want?\n");
		printf("1) by name\n");
		printf("2) by code\n");
		printf("3) by type\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case BY_NAME:
			qsort(manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByName);
			printProductManager(manager);
			return;
		case BY_CODE:
			qsort(manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByCode);
			printProductManager(manager);
			return;
		case BY_TYPE:
			qsort(manager->productArr, manager->numOfProducts, sizeof(Product*), compareProductByType);
			printProductManager(manager);
			return;
		default:
			printf("invalid choice!\n");
			break;
		}
	} while (1);
}

int writeProductsToText(FILE* fp, int count, Product** productArr)
{
	for (int i = 0; i < count; i++)
	{
		fprintf(fp, "%s\n", productArr[i]->specs->productName);
		fprintf(fp, "%d\n",productArr[i]->specs->productCode);
		fprintf(fp, "%d\n",*productArr[i]->specs->type);
	}
	return 1;
}

Product** readProductsFromText(FILE* readF,int count, Product** productArr)
{

	productArr = (Product**)malloc(count * sizeof(Product*));
	if (!productArr)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		productArr[i] = (Product*)malloc(sizeof(Product));
		if (!productArr[i])
		{
			return NULL;
		}

		productArr[i]->specs = (productInfo*)malloc(sizeof(productInfo));
		if (!productArr[i]->specs)
		{
			return NULL;
		}

		productArr[i]->specs->type = (Type*)malloc(sizeof(Type));
		if (!productArr[i]->specs->type)
		{
			return NULL;
		}

		int type;
		fscanf(readF, "%s\n", productArr[i]->specs->productName);
		fscanf(readF, "%d\n", &productArr[i]->specs->productCode);
		fscanf(readF, "%d\n", &type);

		*productArr[i]->specs->type = type;
	}
	return productArr;
}


