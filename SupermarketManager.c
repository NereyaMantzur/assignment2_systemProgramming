#include <stdio.h>
#include <stdlib.h>

#include "SupermarketManager.h"

int addSupermarket(SupermarketManager* managerPtr, SuperMarket* marketPtr) {
    if (managerPtr == NULL || marketPtr == NULL) {
        printf("Invalid input\n");
        return 0; // Failure
    }

    // Reallocate memory to hold one more supermarket
    SuperMarket* newMarkets = (SuperMarket*)realloc(managerPtr->markets, (managerPtr->numMarkets + 1) * sizeof(SuperMarket));
    if (newMarkets == NULL) {
        printf("Memory reallocation failed\n");
        return 0; // Failure
    }
n             
    // Add the new market to the array
    manager->markets = newMarkets;
    manager->markets[manager->numMarkets] = *market;
    manager->numMarkets++;

    return 1; // Success
}

// Function to remove a supermarket from the SupermarketManager
int removeSupermarket(SupermarketManager* managerStr, SuperMarket* marketStr) {
    if (managerStr == NULL || marketStr == NULL) {
        printf("Invalid input\n");
        return 0; // Failure
    }

    int found = 0;
    for (int i = 0; i < managerStr->numMarkets; i++) {
        if (&managerStr->markets[i] == marketStr) {
            found = 1;
            // Replace with the last market in the array
            managerStr->markets[i] = managerStr->markets[managerStr->numMarkets - 1];
            break;
        }
    }

    if (!found) {
        printf("Market not found\n");
        return 0; // Failure
    }

    // Reallocate memory to shrink the array by one element
    SuperMarket* newMarkets = (SuperMarket*)realloc(managerStr->markets, (managerStr->numMarkets - 1) * sizeof(SuperMarket));
    if (newMarkets == NULL && managerStr->numMarkets > 1) {
        printf("Memory reallocation failed\n");
        return 0; // Failure
    }

    managerStr->markets = newMarkets;
    managerStr->numMarkets--;

    return 1; // Success
}


// Function to update an existing supermarket in the SupermarketManager
int updateSupermarket(SupermarketManager* managerStr, SuperMarket* marketStr) {
    if (managerStr == NULL || marketStr == NULL) {
        printf("Invalid input\n");
        return 0; // Failure
    }

    for (int i = 0; i < managerStr->numMarkets; i++) {
        if (managerStr->markets[i].code == marketStr->code) {
            // Update the supermarket details
            strcpy(managerStr->markets[i].name, marketStr->name);
            // Update other fields if necessary
            return 1; // Success
        }
    }

    printf("Supermarket not found\n");
    return 0; // Failure
}

SuperMarket* findSupermarket(SupermarketManager* managerStr, const char* nameStr, int code) {
    if (managerStr == NULL) {
        printf("Invalid input\n");
        return NULL;
    }

    for (int i = 0; i < managerStr->numMarkets; i++) {
        if ((nameStr != NULL && strcmp(managerStr->markets[i].name, nameStr) == 0) ||
            (code != -1 && managerStr->markets[i].code == code)) {
            return &managerStr->markets[i];
        }
    }

    return NULL;
}
