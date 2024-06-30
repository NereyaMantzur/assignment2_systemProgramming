#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Functions.h"

void initSupermarketManager(SupermarketManager* manager) {
    printf("Initializing Supermarket Manager\n");

    // Initialize the supermarket manager's supermarkets array
    manager->supermarkets = NULL;
    manager->numOfSupermarkets = 0;

    char choice;
    do {
        printf("Do you want to add a supermarket? (y/n): ");
        scanf(" %c", &choice);
        getchar(); // Consume newline character left in the buffer

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


void addProdcutToSupermarket(Product* add, SupermarketManager* manager)
{
    if (!add || !manager)
    {
        return;
    }
    else
    {
        printf("please enter supplier name\n");
        char* str = getStr();
        for (size_t i = 0; i < manager->numOfSupermarkets; i++)
        {
            for (size_t j = 0; j < manager->supermarkets[i]->numOfProducts; j++)
            {
                if (!strcmp(manager->supermarkets[i]->name, str))
                {
                    printf("product exits already\n");
                    return;
                }
                else
                {
                    manager->supermarkets[i]->numOfProducts++;
					manager->supermarkets[i]->productsArr = (Product**)realloc(manager->supermarkets[i]->productsArr, manager->supermarkets[i]->numOfProducts * sizeof(Product*));
                    manager->supermarkets[i]->productsArr[-1] = add;
                }
            }
        }
    }
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

int addSupermarket(SupermarketManager* manager) {
    Supermarket* supermarket = (Supermarket*)malloc(sizeof(Supermarket));
    if (!supermarket) {
        printf("Memory allocation for supermarket failed.\n");
        return 0;
    }

    printf("Enter supermarket name: ");
    strcpy(supermarket->name , getStr());
    replaceSpaces(supermarket->name);

    printf("Enter supermarket address: ");
    strcpy(supermarket->address ,getStr());
    replaceSpaces(supermarket->address);

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

    for (int i = 0; i < manager->numOfSupermarkets; i++) {
        if (manager->supermarkets[i]->code == supermarket->code) {
            printf("Supermarket with this code already exists.\n");
            free(supermarket);
            return 0;
        }
    }

    Supermarket** temp = (Supermarket**)realloc(manager->supermarkets,
        (manager->numOfSupermarkets + 1) * sizeof(Supermarket*));
    if (!temp) {
        printf("Memory reallocation failed.\n");
        free(supermarket);
        return 0;
    }
    manager->supermarkets = temp;

    manager->supermarkets[manager->numOfSupermarkets] = supermarket;
    manager->numOfSupermarkets++;

    printf("Supermarket added successfully.\n");

    return 1;
}

int removeSupermarket(SupermarketManager* manager, Supermarket* delete)
{
    if (manager->numOfSupermarkets == 0)
    {
        printf("no supermarket to delete\n");
        return 0;
    }
    for (size_t i = 0; i < manager->numOfSupermarkets; i++)
    {
        if (manager->supermarkets[i] == delete)
        {
            manager->supermarkets[i] = manager->supermarkets[manager->numOfSupermarkets];
			manager->supermarkets = (Supermarket**)realloc(manager->supermarkets, (manager->numOfSupermarkets - 1) * sizeof(Supermarket*));
			manager->numOfSupermarkets--;
			return 1;
        }
    }
    printf("supermarkets not found\n");
    return 0;
}

int updateSupermarket(SupermarketManager* manager, Supermarket* update)
{
    if (manager->numOfSupermarkets == 0)
    {
        printf("no supermarket to delete");
        return 0;
    }
    for (size_t i = 0; i < manager->numOfSupermarkets; i++)
	{
        if (manager->supermarkets[i] == update) {
            printf("Enter supermarket name: ");
            fgets(manager->supermarkets[i]->name, MAX_NAME_LENGTH, stdin);
            getchar();

            printf("Enter supermarket address: ");
            fgets(manager->supermarkets[i]->address, MAX_ADDRESS_LENGTH, stdin);
            getchar();

            printf("Enter supermarket code: ");
			scanf(" %d", &manager->supermarkets[i]->code);
        }
    }
    return 1;
}

Supermarket* findSupermarketByNameOrCode(SupermarketManager* manager, char* str, int code)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
    if (manager->numOfSupermarkets == 0)
    {
        printf("no supermarket to delete");
    }
    for (size_t i = 0; i < manager->numOfSupermarkets; i++)
    {
        if (manager->supermarkets[i]->code == code) {
            return manager->supermarkets[i];
        }
        else if (!strcmp(manager->supermarkets[i]->name , str))
        {
            return manager->supermarkets[i];
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
    printf("%s | %d|\n", super->name, super->code);
}

void printSupermarketManager(SupermarketManager* manager)
{
    printf("\n=====|supermarket name | supermarket code|=====\n");
    for (size_t i = 0; i < manager->numOfSupermarkets; i++)
    {
		printf("%d : |", (int)i + 1);
        printSupermarket(manager->supermarkets[i]);
    }
}