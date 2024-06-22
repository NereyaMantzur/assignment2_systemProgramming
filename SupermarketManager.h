#ifndef SUPERMARKETMANAGER_H
#define SUPERMARKETMANAGER_H

#include "supermarket.h"

typedef struct {
    SuperMarket* markets;
    int numMarkets; 
} SupermarketManager;

int addSupermarket(SupermarketManager* managerPtr, SuperMarket* marketPtr);
int removeSupermarket(SupermarketManager* managerStr, SuperMarket* marketStr);
int updateSupermarket(SupermarketManager* managerStr, SuperMarket* marketStr);
SuperMarket* findSupermarketByNameOrCode(char* superStr, int superCode);


#endif // !SUPERMARKETMANAGER_H
