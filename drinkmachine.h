/*
 * drinkmachine.h
 *
 *  Created on: Oct 9, 2016
 *      Author: superhhu
 */
//in this file, I put my types and function prototypes as the promopt suggests.
#include <stdbool.h>
#ifndef DRINKMACHINE_H_
#define DRINKMACHINE_H_
typedef struct _DrinkItem
{
	int id;
	char name[128];
	float price;
	int numofdrinks;
	int drinkspurchased;
} DrinkItem;

typedef struct _DrinkMachine
{
	int version;
	int numDrinkItems;
	DrinkItem * dkitem;
	int location;
} DrinkMachine;
DrinkMachine * create(void);
void destroy(DrinkMachine *DrinkMachine);
DrinkItem * firstDrink(DrinkMachine * DrinkMachine);
DrinkItem * nextDrink(DrinkMachine *DrinkMachine);
int items(DrinkMachine *DrinkMachine);
bool available(DrinkMachine *DrinkMachine,int id);
double cost(DrinkMachine *DrinkMachine,int id);
enum buy purchase(DrinkMachine *DrinkMachine,int id, double moneyspent, double *change);
void dumpDrinkMachine(DrinkMachine *DrinkMachine);



#endif /* DRINKMACHINE_H_ */
