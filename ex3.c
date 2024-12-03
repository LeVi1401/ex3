/******************
Name: Roei Lev
ID: 216015164
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

//inputs the brand and sales for each type for the brand and adds it to the current day(this is part 1 - addOne)
int addOneSale(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int daysInYear ,int days[], int useBrands[]);
//adds the specific sales to the specific brand on the current day (sub function for addOneSales function)
void addSales(int brand, int sales[], int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfTypes, int days[]);
//prints the required text for part 2 (addAll), (use brands allows to know what brands to print)
void printAll(int useBrands[], int numOfBrands);
//prints the name of a specific brand
void printBrand(int index);
//prints the name of a specific type
void printType(int index);
//returns the total sales sum for all brands in a specific day (part 3)
int salesTotal(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);
//returns the index of the brand with the most sales on a specific day (part 3)
int maxSalesBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);
//returns the total sales sum for a specific brand on a specific day
int salesBrand(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);
//returns the index of the type with the most sales on a specific day (part 3)
int maxSalesType(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);
//returns the total sales sum for a specific type on a specific day
int salesType(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);
//prints the sales of a specific brand on a specific day in the format of part 4
void printSalesForBrand(int brand, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfTypes, int day);
//returns the average delta of a specific brand
double brandDelta(int brand, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int days[]);

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}




int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    //a list so when I add a day to the counter in a function it will change here too
    int days[NUM_OF_BRANDS] = {0};

    //reseting the values in cube to -1
    for(int i = 0; i < DAYS_IN_YEAR; i++)
        for(int j = 0; j < NUM_OF_BRANDS; j++)
            for(int k = 0 ; k < NUM_OF_TYPES; k++)
                cube[i][j][k] = -1;

    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        scanf("%*[^\n]%*c");
        switch(choice){
            case addOne:
                break;
            case addAll:
                {
                    //a list that checks what brand names I need to print
                    //if the brand was already used then the value on its index would be 1 and 0 if not
                    int useBrands[NUM_OF_BRANDS] = {0};
                    int brandHolder, flag;
                    do
                    {
                        //check when to leave the function
                        flag = 1;
                        //returns a brand index if the brand input is valid and returns -1 if not
                        brandHolder = addOneSale(cube, NUM_OF_BRANDS, NUM_OF_TYPES, DAYS_IN_YEAR, days, useBrands);
                        if(brandHolder != -1)
                        {
                            //update the current brand to 1 to specify it was already used
                            useBrands[brandHolder] = 1;
                        }
                        //checks if there are any other brands left to update
                        for(int i = 0 ; i < 5 ; i++)
                        {
                            if(useBrands[i] == 0)
                            {
                                flag = 0;
                                break;
                            }
                        }
                    }while(flag == 0);
                    break;
                }
            case stats:
                {
                    int analyzeDay, salesSum, maxBrand, maxType, brandSalesMax, typeSalesMax;
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &analyzeDay);
                    //change the day input from 1-365 to 0-364 for calculations
                    analyzeDay--;
                    //check if day input is valid
                    while (analyzeDay < 0 || analyzeDay >= days[0])
                    {
                        scanf("%*[^\n]%*c");
                        printf("Please enter a valid day.\n");
                        printf("What day would you like to analyze?\n");
                        scanf("%d", &analyzeDay);
                        analyzeDay--;
                    }
                    //gets the sales total
                    salesSum = salesTotal(cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);
                    //gets the indexes of the type and brand with most sales
                    maxBrand = maxSalesBrand(cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);
                    maxType = maxSalesType(cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);
                    //gets the amount of sales of the max type and brand
                    brandSalesMax = salesBrand(maxBrand, cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);
                    typeSalesMax = salesType(maxType, cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);

                    printf("In day number %d:\nThe sales total was %d\n", analyzeDay+1, salesSum);
                    printf("The best sold brand with %d sales was ", brandSalesMax);
                    printBrand(maxBrand);
                    printf("\nThe best sold type with %d sales was ", typeSalesMax);
                    printType(maxType);
                    printf("\n");

                    break;
                }
            case print:
                {
                    printf("*****************************************\n");
                    //prints the data for each brand
                    for(int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        printf("Sales for ");
                        printBrand(i);
                        printf(":\n");
                        //prints data for all days for the current brand
                        for(int j = 1; j <= days[i]; j++)
                            printSalesForBrand(i, cube, NUM_OF_TYPES, (j - 1));
                    }
                    printf("*****************************************\n");
                    break;
                }
            case insights:
                {
                    int mostProfBrand = 0, profBrandNum = 0, mostProfType = 0, profTypeNum = 0, mostProfDay = 0, profDayNum = 0;
                    //gets the most selling brand
                    for (int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        //getting the sales total for each brand
                        int sumBrand = 0;
                        for (int j = 0; j < days[i]; j++)
                        {
                            int profBrand = salesBrand(i, cube, NUM_OF_BRANDS, NUM_OF_TYPES, j);
                            sumBrand += profBrand;
                        }
                        //initializing first best-selling brand
                        if (i == 0)
                        {
                            mostProfBrand = i;
                            profBrandNum = sumBrand;
                        }
                        //checking which brand sales total is the maximum
                        else if (sumBrand > profBrandNum)
                        {
                            mostProfBrand = i;
                            profBrandNum = sumBrand;
                        }
                    }

                    //gets the most selling type
                    for (int i = 0; i < NUM_OF_TYPES; i++)
                    {
                        //getting the sales total for each type
                        int sumType = 0;
                        for (int j = 0; j < days[i]; j++)
                        {
                            int profType = salesType(i, cube, NUM_OF_BRANDS, NUM_OF_TYPES, j);
                            sumType += profType;
                        }
                        //initializing first best-selling type
                        if (i == 0)
                        {
                            mostProfType = i;
                            profTypeNum = sumType;
                        }
                        //checking which type sales total is the maximum
                        else if (sumType > profTypeNum)
                        {
                            mostProfType = i;
                            profTypeNum = sumType;
                        }
                    }

                    //gets the best-selling day
                    for (int i = 0; i < days[0]; i++)
                    {
                        //getting the sales total for each day
                        int profDay = salesTotal(cube, NUM_OF_BRANDS, NUM_OF_TYPES, i);
                        //initializing first best-selling day
                        if (i == 0)
                        {
                            mostProfDay = i;
                            profDayNum = profDay;
                        }
                        //checking which day sales total is the maximum
                        else if (profDay > profDayNum)
                        {
                            mostProfDay = i;
                            profDayNum = profDay;
                        }
                    }
                    //change the day from 0-364 to 1-365 for print
                    mostProfDay++;


                    printf("The best-selling brand overall is ");
                    printBrand(mostProfBrand);
                    printf(": %d$\n", profBrandNum);
                    printf("The best-selling type of car is ");
                    printType(mostProfType);
                    printf(": %d$\n", profTypeNum);
                    printf("The most profitable day was day number %d: %d$\n", mostProfDay, profDayNum);
                    break;
                }
            case deltas:
                {
                    double avgDelta;
                    //prints the average delta for each brand
                    for(int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        avgDelta = brandDelta(i, cube, NUM_OF_BRANDS, NUM_OF_TYPES, days);
                        printf("Brand: ");
                        printBrand(i);
                        printf(", Average Delta: %f\n", avgDelta);
                    }
                    break;
                }
            default:
                {
                    printf("Invalid input\n");
                    scanf("%*[^\n]%*c");
                }
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
//inputs the brand and sales for each type for the brand and adds it to the current day(this is part 1 - addOne)
int addOneSale(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int daysInYear ,int days[], int useBrands[])
{
    int brand;
    int sales[numOfTypes];
    //getting the brand and the sales for each type
    printAll(useBrands, numOfBrands);
    scanf("%d", &brand);
    scanf("%d %d %d %d", &sales[0], &sales[1], &sales[2], &sales[3]);
    //checks if the brand input is valid
    if (brand >= 0 && brand <= numOfTypes && useBrands[brand] == 0)
    {
        addSales(brand, sales, cube, numOfTypes, days);
    }
    //input is not valid prints the right message and returns the right number
    else
    {
        scanf("%*[^\n]%*c");
        printf("This brand is not valid\n");
        return -1;
    }
    //adds one day to the counter for the inputted day and returns the right number(the brand), (only when the input is valid)
    if(days[brand] != daysInYear - 1)
        days[brand]++;
    return brand;
}
//adds the specific sales to the specific brand on the current day (sub function for addOneSales function)
void addSales(int brand, int sales[], int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfTypes, int days[])
{
    int day = days[brand];
    for(int i = 0 ; i < numOfTypes ; i++)
    {
        cube[day][brand][i] = sales[i];
    }
}
//prints the required text for part 2 (addAll), (use brands allows to know what brands to print)
void printAll(int useBrands[], int numOfBrands)
{
    printf("No data for brands");
    for (int i = 0 ; i < numOfBrands ; i++)
    {
        //checks for each brand whether it was already used or not in order to print the right message for part 2 with the use of the array useBrands
        if(useBrands[i] == 0)
        {
            printf(" ");
            printBrand(i);
        }
    }
    printf("\nPlease complete the data\n");
}
//prints the name of a specific brand
void printBrand(int index)
{
    if(index >= 0 && index < NUM_OF_BRANDS)
    {
        for(int i = 0 ; i <  BRANDS_NAMES; i++)
        {
            //goes over the name of the brand and prints each character until \0
            if(brands[index][i] == '\0')
                break;
            printf("%c", brands[index][i]);
        }
    }
}
//prints the name of a specific type
void printType(int index)
{
    if(index >= 0 && index < NUM_OF_TYPES)
    {
        for(int i = 0 ; i < TYPES_NAMES; i++)
        {
            //goes over the name of the type and prints each character until \0
            if(types[index][i] == '\0')
                break;
            printf("%c", types[index][i]);
        }
    }
}
//returns the total sales sum for all brands in a specific day (part 3)
int salesTotal(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int sumSales = 0;
    for(int i = 0 ; i < numOfBrands ; i++)
    {
        //sums the sales of all brands for the specified day
        for(int j = 0 ; j < numOfTypes ; j++)
        {
            sumSales += cube[day][i][j];
        }
    }
    return sumSales;
}
//returns the index of the brand with the most sales on a specific day (part 3)
int maxSalesBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    //initializing the best-selling brand to the first one
    int maxBrand = 0, tempSale;
    int maxSalesBrand = salesBrand(maxBrand, cube, numOfBrands, numOfTypes, day);

    //checking which brand is the best-selling one
    for(int i = 1 ; i < numOfBrands ; i++)
    {
        tempSale = salesBrand(i, cube, numOfBrands, numOfTypes, day);
        if(tempSale > maxSalesBrand)
        {
            maxSalesBrand = tempSale;
            maxBrand = i;
        }
    }
    //returns the index of the best-selling brand
    return maxBrand;
}
//returns the total sales sum for a specific brand on a specific day
int salesBrand(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int salesBrand = 0;
    //getting the sales total of the specified brand on the specified day
    if(index >= 0 && index < numOfBrands)
    {
        for(int i = 0 ; i < numOfTypes ; i++)
            salesBrand += cube[day][index][i];
    }
    return salesBrand;
}
//returns the index of the type with the most sales on a specific day (part 3)
int maxSalesType(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    //initializing the best-selling type to the first one
    int maxType = 0, tempSale;
    int maxSalesType = salesType(maxType, cube, numOfBrands, numOfTypes, day);

    //checking which type is the best-selling one
    for(int i = 1 ; i < numOfBrands ; i++)
    {
        tempSale = salesType(i, cube, numOfBrands, numOfTypes, day);
        if(tempSale > maxSalesType)
        {
            maxSalesType = tempSale;
            maxType = i;
        }
    }
    //returns the index of the best-selling type
    return maxType;
}
//returns the total sales sum for a specific type on a specific day
int salesType(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int salesType = 0;
    //getting the sales total of the specified type on the specified day
    if(index >= 0 && index < numOfTypes)
    {
        for(int i = 0 ; i < numOfBrands ; i++)
            salesType += cube[day][i][index];
    }
    return salesType;
}
//prints the sales of each type for a specific brand on a specific day in the format of part 4
void printSalesForBrand(int brand, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfTypes, int day)
{
    int sale;
    printf("Day %d- ", (day + 1));
    for (int i = 0 ; i < numOfTypes ; i++)
    {
        sale = cube[day][brand][i];
        printType(i);
        printf(": %d ", sale);
    }
    printf("\n");
}
//returns the average delta of a specific brand
double brandDelta(int brand, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int days[])
{
    double deltaSum = 0, avgDelta;
    int sales1, sales2;
    for(int i = 0 ; i < days[brand] - 1 ; i++)
    {
        //getting the sales of the current day and the next day
        sales1 = salesBrand(brand, cube, numOfBrands, numOfTypes, i);
        sales2 = salesBrand(brand, cube, numOfBrands, numOfTypes, (i + 1));
        //adds the current delta to the sum
        deltaSum += (double)(sales2 - sales1);
    }

    //returns the right average delta (return 0 automatically when the day count is 0 or 1 and the average delta from the calculation otherwise)
    if (days[brand] - 1 <= 0)
        return 0;
    avgDelta = deltaSum / (days[brand] - 1);
    return avgDelta;
}