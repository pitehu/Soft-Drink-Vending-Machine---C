#include <stdio.h>
#include <stdlib.h>
#include <drinkmachine.h>
#include <stdbool.h>

//This is the file that I test almost all my functions on.
DrinkMachine *test;//for loops of input
int i;
int t;
double *ch;//this is for the output of the function purchase.
const int INVALID_INDEX=-1;
enum buy{PURCHASED=1, INVALID, NOT_AVAILABLE, INSUFFICIENT_FUNDS};//this is for the function purchase
DrinkItem *pDrink;
enum buy result;

DrinkItem * firstDrink(DrinkMachine * DrinkMachine)
{
	DrinkMachine->location=0;

	if (&(DrinkMachine->dkitem[0])==NULL)
			return NULL;
			else
				return &(DrinkMachine->dkitem[0]);
}
DrinkItem * nextDrink(DrinkMachine *DrinkMachine)
{
	if (DrinkMachine->location==INVALID_INDEX)
		return NULL;
		else
			DrinkMachine->location=(DrinkMachine->location)+1;
	if ((DrinkMachine->location)<(DrinkMachine->numDrinkItems))
		return &(DrinkMachine->dkitem[DrinkMachine->location]);
		else
		{
			DrinkMachine->location=INVALID_INDEX;
			return NULL;
		}
}
DrinkMachine * create(void)
{
	FILE * infile;
	DrinkMachine * drink1;
	infile=fopen("drink_machine.txt","r");
		if (!infile)
		{
			puts("Error opening file");
			free(drink1);
			return NULL;
		}
		else
			puts("successful");//successfully open file
	printf("%d\n",sizeof(DrinkMachine));//give the size of the DrinkMachine struct
	drink1=calloc(1,sizeof(DrinkMachine));
	if (drink1==NULL)
		{
			puts("Error allocating");
			return NULL;
		}
	else
		printf("%d\n",drink1);
	fscanf(infile,"%d",&(drink1->numDrinkItems));
	printf("%d\n",drink1->numDrinkItems);
	drink1->version=1;
	drink1->location=INVALID_INDEX;
	drink1->dkitem = calloc(drink1->numDrinkItems,sizeof(DrinkItem));
	if (drink1->dkitem==NULL)
		{
			puts("Error allocating");
			return NULL;
		}
	for (i=0;i<drink1->numDrinkItems;i++)
			{
				fscanf(infile,"%s",&(drink1->dkitem[i].name));
				fscanf(infile,"%f",&(drink1->dkitem[i].price));
				fscanf(infile,"%d",&(drink1->dkitem[i].numofdrinks));
				drink1->dkitem[i].id=i+1;
//this has a problem if I use the char* instead of char
//Why can I fscanf separately instead of as a whole line
			}//The following three lines are used to see if I successfully populate the drink1
	printf("%s",drink1->dkitem[2].name);
	printf("%d", drink1->dkitem[7].numofdrinks);
    printf("%f\n",drink1->dkitem[0].price);
	fclose(infile);
	fflush(stdout);
	return (drink1);
}
void destroy(DrinkMachine * dmashine1)
{
	for (i=0;i<dmashine1->numDrinkItems;i++)
		free(dmashine1->dkitem);
		free(dmashine1);
}
int items(DrinkMachine *DrinkMachine)
{
	return DrinkMachine->numDrinkItems;
}
bool available(DrinkMachine *DrinkMachine,int id)
{
	int difference;
	int num;
	num=DrinkMachine->numDrinkItems;
	if (id>num || id<=0)
			return 0;
			else
{
	difference=DrinkMachine->dkitem[id-1].numofdrinks-DrinkMachine->dkitem[id-1].drinkspurchased;
	if (difference>=1)
		return 1;
		else
			return 0;
}
}

double cost(DrinkMachine *DrinkMachine,int id)
{
	int num;
		num=DrinkMachine->numDrinkItems;
		if (id>num || id<=0)
	return 0;
	else
	return DrinkMachine->dkitem[id-1].price;
}
enum buy purchase(DrinkMachine *DrinkMachine,int id, double moneyspent, double *change)
		{
			int num,difference;
			num=DrinkMachine->numDrinkItems;
			if (id>num || id<=0)
			return 2;
			else
			{if (moneyspent <=0)
				return 2;
				difference=DrinkMachine->dkitem[id-1].numofdrinks-DrinkMachine->dkitem[id-1].drinkspurchased;
				if (difference<=0)
				return 3;
				else
					if (moneyspent < DrinkMachine->dkitem[id-1].price)
						return 4;
					else
					{
						*change=moneyspent-(DrinkMachine->dkitem[id-1].price);
						return 1;
					}
			}
		}
void dumpDrinkMachine(DrinkMachine *DrinkMachine)
{
	DrinkItem *pDrink;
	printf("%s","ID");
	printf("%12s","Name");
	printf("%13s","price");
	printf("%11s","Qty");
	printf("%12s\n","Sold");
	for (pDrink=firstDrink(test);pDrink!=NULL;pDrink=nextDrink(test))
	{
		printf("%d",pDrink->id);
		printf("%15s",pDrink->name);
		printf("%15.2f",pDrink->price);
		printf("%10d",pDrink->numofdrinks);
		printf("%10d\n",pDrink->drinkspurchased);
	}
}

int main(void)
{//These printfs are all for testing purpose.
test=create();
dumpDrinkMachine(test);
ch=calloc(1,sizeof(double));
result=purchase(test,-1,100,ch);
printf("%d\n",result);
printf("%f\n",*ch);
printf("%f\n",cost(test,8));
printf("%d\n",available(test,9));
printf("%d\n",items(test));
result=purchase(test,1,-1,ch);
printf("%d\n",result);
result=purchase(test,1,1,ch);
printf("%d\n",result);
//The following four lines are for the test of the function destroy.
/*destroy(test);
printf("%d\n",test);
dumpDrinkMachine(test);
printf("%d\n",test);*/



return EXIT_SUCCESS;

}
