#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Functions.h"

void replaceSpaces(char* str) {
	while (*str != '\0') {
		if (*str == ' ') {
			*str = '$';
		}
		str++;
	}
}

void initProductInfo(Product* product) {
	productInfo* newInfo = (productInfo*)malloc(sizeof(productInfo));
	if (!newInfo) {
		printf("allocation failed\n");
		return;
	}
	printf("initializing new product:\n");

	printf("please enter product name: ");
	fgets(newInfo->productName, MAX_NAME, stdin);

	printf("Enter product code (6 digits): ");
	while (1) {
		if (scanf("%d", &newInfo->productCode) == 1 && getchar() && newInfo->productCode >= 100000 && newInfo->productCode <= 999999) {
			break;
		}
		printf("Code not valid. Try again.\n");
		printf("Enter product code (6 digits): ");
		while (getchar() != '\n');
	}

	int choice;
	do {
		printf("please enter product type (1 for FOOD, 2 for CLEANING, 3 for GENERAL): ");
		if (scanf("%d", &choice) == 1 && getchar()) {
			if (choice == FOOD || choice == CLEANING || choice == GENERAL) {
				newInfo->type = (Type*)choice;
				break;
			}
		}
		printf("Invalid choice. Try again.\n");
		while (getchar() != '\n');
	} while (1);

	product->specs = newInfo;
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