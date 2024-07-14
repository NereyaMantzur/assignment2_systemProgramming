#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Functions.h"

void initSupermarketManager(SupermarketManager* manager) {
	printf("=====Initializing Supermarket Manager=====\n");

	manager->supermarketList = NULL;
	manager->numOfSupermarkets = 0;

	char choice;
	do {
		printf("\nDo you want to add a supermarket? (y/n): ");
		scanf(" %c", &choice);
		getchar();

		switch (choice) {
		case 'y':
		case 'Y':
			if (addSupermarket(manager) == 0) {
				printf("Failed to add supermarket.\n");
			}
			break;
		case 'n':
		case 'N':
			printf("Exiting supermarket initialization.\n");
			break;
		default:
			printf("Invalid input. Please enter 'y' or 'n'.\n");
			break;
		}
	} while (choice != 'n' && choice != 'N');
}


int isSameSuprmarket(Supermarket* super1, Supermarket* super2)
{
	return strcmp(super1->name, super2->name);
}

int isSupermarketName(Supermarket* super, char* nameStr)
{
	char* temp = nameStr;
	while (*nameStr)
	{
		*nameStr = toupper(*nameStr);
		nameStr++;
	}
	return strcmp(super->name, temp);
}

int isSupermarketCode(Supermarket* super, int code)
{
	return super->code == code;
}

void addProductToSupermarket(Product* add, SupermarketManager* manager) {
	if (!add || !manager) {
		printf("Invalid product or supermarket manager.\n");
		return;
	}

	printf("Please enter supermarket name:\n");
	char* str = getStr();
	if (!str) {
		printf("Failed to read supermarket name.\n");
		return;
	}

	Supermarket* temp = manager->supermarketList;
	while (temp) {
		if (strcmp(temp->name, str) == 0) {
			for (size_t j = 0; j < temp->numOfProducts; j++) {
				if (strcmp(temp->productsArr[j]->specs->productName, add->specs->productName) == 0) {
					printf("Product already exists in the supermarket.\n");
					free(str);
					return;
				}
			}

			Product** productArr = realloc(temp->productsArr, (temp->numOfProducts + 1) * sizeof(Product*));
			if (!productArr) {
				printf("Memory allocation failed.\n");
				free(str);
				return;
			}
			temp->productsArr = productArr;
			temp->productsArr[temp->numOfProducts++] = add;
			printf("Product added successfully.\n");
			free(str);
			return;
		}
		temp = temp->next;
	}

	printf("Supermarket not found.\n");
	free(str);
}

int isProductInSupermarket(Product* product, Supermarket* super)
{
	if (!super->productsArr)
	{
		printf("No Products in this supermarket");
		return 0;
	}
	for (size_t i = 0; i < super->numOfProducts; i++)
	{
		if (!strcmp(super->productsArr[i]->specs->productName, product->specs->productName))
		{
			return 1;
		}
		else if (super->productsArr[i]->specs->productCode == product->specs->productCode)
		{
			return 1;
		}
	}
	return 0;
}

char* initAddress() {
	char* country = (char*)malloc(MAX_NAME * 4 * sizeof(char));
	char city[MAX_NAME];
	char street[MAX_NAME];
	char number[MAX_NAME];

	if (country == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	printf("please enter country: ");
	strcpy(country, getStr());
	strcat(country, "#");

	printf("please enter city: ");
	strcpy(city, getStr());
	strcat(city, "#");

	printf("please enter street: ");
	strcpy(street, getStr());
	strcat(street, "#");

	printf("please enter number: ");
	strcpy(number, getStr());

	strcat(country, strcat(city, strcat(street, number)));
	replaceSpaces(country);
	return country;
}

int addSupermarket(SupermarketManager* manager) {
	Supermarket* supermarket = (Supermarket*)malloc(sizeof(Supermarket));

	if (!supermarket) {
		printf("Memory allocation for supermarket failed.\n");
		return 0;
	}

	supermarket->productsArr = NULL;
	supermarket->numOfProducts = 0;

	printf("\nEnter supermarket name: ");
	strcpy(supermarket->name, getStr());

	printf("Enter supermarket code (5 digits): ");
	while (1) {
		scanf("%d", &supermarket->code);
		getchar();

		if (supermarket->code >= 10000 && supermarket->code <= 99999) {
			break;
		}
		printf("Code not valid. Try again.\n");
		printf("Enter supermarket code (5 digits): ");
	}

	printf("Enter supermarket address - \n");
	strcpy(supermarket->address, initAddress());


	if (!manager->supermarketList || strcmp(supermarket->name, manager->supermarketList->name) < 0) {
		supermarket->next = manager->supermarketList;
		manager->supermarketList = supermarket;
	}
	else {
		Supermarket* temp = manager->supermarketList;
		while (temp->next && strcmp(supermarket->name, temp->next->name) < 0) {
			temp = temp->next;
		}
		supermarket->next = temp->next;
		temp->next = supermarket;
	}

	manager->numOfSupermarkets++;
	printf("Product added successfully!\n");

	return 1;
}

int removeSupermarket(SupermarketManager* manager, Supermarket* delete) {
	if (manager->numOfSupermarkets == 0) {
		printf("No supermarket to delete.\n");
		return 0;
	}

	Supermarket* temp = manager->supermarketList;
	Supermarket* prev = NULL;

	while (temp) {
		if (temp == delete) {
			if (prev) {
				prev->next = temp->next;
			}
			else {
				manager->supermarketList = temp->next;
			}
			free(temp);
			manager->numOfSupermarkets--;
			printf("Supermarket deleted successfully.\n");
			return 1;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("Supermarket not found.\n");
	return 0;
}

int updateSupermarket(SupermarketManager* manager, Supermarket* update)
{
	if (manager->numOfSupermarkets == 0)
	{
		printf("no supermarket to delete");
		return 0;
	}
	Supermarket* temp = manager->supermarketList;
	while (!temp)
	{
		if (temp == update) {
			printf("Enter supermarket name: ");
			fgets(temp->name, MAX_NAME_LENGTH, stdin);
			getchar();

			printf("Enter supermarket address: ");
			fgets(temp->address, MAX_ADDRESS_LENGTH, stdin);
			getchar();

			printf("Enter supermarket code: ");
			scanf(" %d", &temp->code);
		}
		temp = temp->next;
	}
	return 1;
}

Supermarket* findSupermarketByNameOrCode(SupermarketManager* manager, char* str, int code)
{
	if (manager->numOfSupermarkets == 0)
	{
		printf("no supermarket found");
	}
	Supermarket* temp = manager->supermarketList;
	while (temp) 
	{
		if (temp->code == code) 
		{
			return temp;
		}
		else if (!strcmp(temp->name, str))
		{
			return temp;
		}
	}
	return NULL;
}

void printSupermarket(Supermarket* super)
{
	if (super == NULL || super->name == NULL) {
		printf("Invalid supermarket data\n");
		return;
	}
	char* ptr = super->name;
	while (*ptr != '\0') {
		if (*ptr == '\n') {
			*ptr = '\0';
			break;
		}
		ptr++;
	}
	printf("%-20s|%-20d|%s\n", super->name, super->code ,super->address);
}

void printSupermarketManager(SupermarketManager* manager)
{
	printf("\n# |supermarket name    |supermarket code    |supermarket address  \n");
	int i = 1;
	Supermarket* temp = manager->supermarketList;
	while (temp) 
	{
		printf("%d |", i );
		printSupermarket(temp);
		i++;
		temp = temp->next;
	}
}

void printSupermarketProducts(Supermarket* super)
{
	for (size_t i = 0; i < super->numOfProducts; i++)
	{
		printProduct(super->productsArr[i]);
	}
}