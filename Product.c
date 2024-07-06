#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Product.h"
#include "Functions.h"

void initProductManager(ProductManager* manager) {
	if (manager == NULL) {
        printf("Error: NULL pointer to ProductManager.\n");
        return;
    }
	printf("\n=====Initializing Product Manager=====\n");

	manager->productArr = NULL;
	manager->numOfProducts = 0;

	char choice;
	do {
		printf("\nDo you want to add a product? (y/n): ");
		scanf(" %c", &choice);
		getchar();

		switch (choice) {
		case 'y':
		case 'Y':
			if (addProduct(manager) == 0) {
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

Product* addProduct(ProductManager* manager) {
	Product** newArr = (Product**)realloc(manager->productArr, (manager->numOfProducts + 1) * sizeof(Product*));
	if (!newArr) {
		printf("Memory allocation for product list failed.\n");
		return NULL;
	}
	manager->productArr = newArr;

	Product* product = (Product*)malloc(sizeof(Product));
	if (!product) {
		printf("Memory allocation for product failed.\n");
		return NULL;
	}

	product->nameOfSupers = NULL;
	product->numOfSupers = 0;
	product->supplier = NULL;

	initProductInfo(product);

	//product->exp = (Date*)malloc(sizeof(Date));
	//if (!product->exp) {
	//	printf("Memory allocation for expiry date failed.\n");
	//	free(product);
	//	return NULL;
	//}
	//printf("Please enter expiry date:\n");
	//while (!initDate(product->exp)) {
	//	printf("Invalid date. Please enter expiry date again:\n");
	//}

	//product->mfg = (Date*)malloc(sizeof(Date));
	//if (!product->mfg) {
	//	printf("Memory allocation for manufacture date failed.\n");
	//	free(product->exp);
	//	free(product);
	//	return NULL;
	//}
	//printf("Please enter manufacture date:\n");
	//while (!initDate(product->mfg)) {
	//	printf("Invalid date. Please enter manufacture date again:\n");
	//}

	//getchar();
	//printf("Please enter supplier name: ");
	//product->supplier = getStr();

	manager->productArr[manager->numOfProducts] = product;
	manager->numOfProducts++;

	printf("Product added successfully!\n");
	return product;
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

void doPrintSupplierWithProductCode(ProductManager* manager)
{
	int choice;
	printf("please enter product code: ");
	scanf("%d", &choice);
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		if (manager->productArr[i]->specs->productCode == choice)
		{
			printf("%s", manager->productArr[i]->supplier);
			return;
		}
	}
	printf("code not valid!");
	return;
}

void doPrintSupplierWithProductName(ProductManager* manager)
{
	char choice[MAX_NAME];
	printf("please enter product code: ");
	scanf("%s", &choice);
	getchar();
	for (size_t i = 0; i < manager->numOfProducts; i++)
	{
		if (!strcmp(manager->productArr[i]->specs->productName, choice))
		{
			printf("%s", manager->productArr[i]->supplier);
			return;
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

void printProduct(Product* product)
{
	char* ptr = product->specs->productName;
	while (*ptr != '\0') {
		if (*ptr == '\n') {
			*ptr = '\0';
			break;
		}
		ptr++;
	}
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

int compareProductByName(const void* a, const void* b) {
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
