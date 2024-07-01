#ifndef _SUPERMARKET_H
#define _SUPERMARKET_H

#define MAX_NAME_LENGTH 255
#define MAX_ADDRESS_LENGTH 255

typedef struct {
    char name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    int code;
	Product** productsArr;
    int numOfProducts;
} Supermarket;

typedef struct {
    Supermarket** supermarkets;
    int numOfSupermarkets;
} SupermarketManager;

void initSupermarketManager(SupermarketManager* manager);

int isSameSuprmarket(Supermarket* super1, Supermarket* super2);
int isSupermarketName(Supermarket* super, char* nameStr);
int isSupermarketCode(Supermarket* super, int code);

void addProductToSupermarket(Product* add, SupermarketManager* manager);
int isProductInSupermarket(Product* product, Supermarket* super);
int addSupermarket(SupermarketManager* manager);
int removeSupermarket(SupermarketManager* manager, Supermarket* delete);
int updateSupermarket(SupermarketManager* manager, Supermarket* update);
Supermarket* findSupermarketByNameOrCode(SupermarketManager* manager, char* str, int code);

void printSupermarket(Supermarket* super);
void printSupermarketManager(SupermarketManager* manager);
void printSupermarketProducts(Supermarket* super);


#endif // !_SUPERMARKET_H