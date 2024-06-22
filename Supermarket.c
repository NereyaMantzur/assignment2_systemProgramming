#include <string.h>
#include <string.h>
#include <ctype.h>

#include "Supermarket.h"

int isSameSuprmarket(SuperMarket* super1Ptr, SuperMarket* super2Ptr)
{
	return strcmp(super1Ptr->superName, super2Ptr->superName) == 0;;

}
int isSupermarketName(SuperMarket* superPtr, char* superStr)
{
	return strcmp(superPtr->superName , superPtr);

}
int isSupermarketCode(SuperMarket* superPtr, int superCode)
{
	return superPtr->superCode == superCode;
}

