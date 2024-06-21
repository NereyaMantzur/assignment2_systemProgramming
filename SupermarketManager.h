#ifndef SUPERMARKETMANAGER_H
#define SUPERMARKETMANAGER_H

#include "supermarket.h"

typedef struct {
    SuperMarket* markets;
    int numMarkets; 
} SupermarketManager;

int addSupermarket(SuperMarket *superPtr);
int removeSupermarket(SuperMarket* superPtr);
int updateSupermarket(SuperMarket* superPtr);
SuperMarket* findSupermarketByNameOrCode(char* superStr, int superCode);


#endif // !SUPERMARKETMANAGER_H
