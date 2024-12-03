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

int addOneSale(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int daysInYear ,int days[], int useBrands[]);

void addSales(int brand, int sales[], int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfTypes, int days[]);

void printAll(int useBrands[], int numOfBrands);

void printBrand(int index);

void printType(int index);

int salesTotal(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);

int maxSalesBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);

int salesBrand(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);

int maxSalesType(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);

int salesType(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day);

void printSalesForBrand(int brand, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfTypes, int day);

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
    int days[NUM_OF_BRANDS] = {0};

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
                    //scanf("%*[^\n]%*c");
                    int useBrands[NUM_OF_BRANDS] = {0};
                    int brandHolder, flag;
                    do
                    {
                        flag = 1;
                        brandHolder = addOneSale(cube, NUM_OF_BRANDS, NUM_OF_TYPES, DAYS_IN_YEAR, days, useBrands);
                        if(brandHolder != -1)
                        {
                            useBrands[brandHolder] = 1;
                        }
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
                    //scanf("%*[^\n]%*c");
                    int analyzeDay, salesSum, maxBrand, maxType, brandSalesMax, typeSalesMax;
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &analyzeDay);
                    analyzeDay--;
                    while (analyzeDay < 0 || analyzeDay >= days[0])
                    {
                        scanf("%*[^\n]%*c");
                        printf("Please enter a valid day.\n");
                        printf("What day would you like to analyze?\n");
                        scanf("%d", &analyzeDay);
                        analyzeDay--;
                    }
                    salesSum = salesTotal(cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);

                    maxBrand = maxSalesBrand(cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);
                    maxType = maxSalesType(cube, NUM_OF_BRANDS, NUM_OF_TYPES, analyzeDay);

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
                    //scanf("%*[^\n]%*c");
                    printf("*****************************************\n");
                    for(int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        printf("Sales for ");
                        printBrand(i);
                        printf(":\n");
                        for(int j = 1; j <= days[i]; j++)
                            printSalesForBrand(i, cube, NUM_OF_TYPES, (j - 1));
                    }
                    printf("*****************************************\n");
                    break;
                }
            case insights:
                {
                    //scanf("%*[^\n]%*c");
                    int mostProfBrand, profBrandNum, mostProfType, profTypeNum, mostProfDay, profDayNum;

                    //most selling brand
                    for (int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        int sumBrand = 0;
                        for (int j = 0; j < days[i]; j++)
                        {
                            int profBrand = salesBrand(i, cube, NUM_OF_BRANDS, NUM_OF_TYPES, j);
                            sumBrand += profBrand;
                        }
                        if (i == 0)
                        {
                            mostProfBrand = i;
                            profBrandNum = sumBrand;
                        }
                        else if (sumBrand > profBrandNum)
                        {
                            mostProfBrand = i;
                            profBrandNum = sumBrand;
                        }
                    }

                    //most selling type
                    for (int i = 0; i < NUM_OF_TYPES; i++)
                    {
                        int sumType = 0;
                        for (int j = 0; j < days[i]; j++)
                        {
                            int profType = salesType(i, cube, NUM_OF_BRANDS, NUM_OF_TYPES, j);
                            sumType += profType;
                        }
                        if (i == 0)
                        {
                            mostProfType = i;
                            profTypeNum = sumType;
                        }
                        else if (sumType > profTypeNum)
                        {
                            mostProfType = i;
                            profTypeNum = sumType;
                        }
                    }

                    //best selling day
                    for (int i = 0; i < days[0]; i++)
                    {
                        int profDay = salesTotal(cube, NUM_OF_BRANDS, NUM_OF_TYPES, i);
                        if (i == 0)
                        {
                            mostProfDay = i;
                            profDayNum = profDay;
                        }
                        else if (profDay > profDayNum)
                        {
                            mostProfDay = i;
                            profDayNum = profDay;
                        }
                    }
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
                    //scanf("%*[^\n]%*c");
                    double avgDelta;
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

int addOneSale(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int daysInYear ,int days[], int useBrands[])
{
    int brand;
    int sales[numOfTypes];
    //scanf("%*[^\n]%*c");
    printAll(useBrands, numOfBrands);
    scanf("%d", &brand);
    scanf("%d %d %d %d", &sales[0], &sales[1], &sales[2], &sales[3]);
    if (brand >= 0 && brand <= numOfTypes && useBrands[brand] == 0)
    {
        addSales(brand, sales, cube, numOfTypes, days);
    }
    else
    {
        scanf("%*[^\n]%*c");
        printf("This brand is not valid\n");
        return -1;
    }
    if(days[brand] != daysInYear - 1)
        days[brand]++;
    return brand;
}

void addSales(int brand, int sales[], int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfTypes, int days[])
{
    int day = days[brand];
    for(int i = 0 ; i < numOfTypes ; i++)
    {
        cube[day][brand][i] = sales[i];
    }
}

void printAll(int useBrands[], int numOfBrands)
{
    printf("No data for brands");
    for (int i = 0 ; i < numOfBrands ; i++)
    {
        if(useBrands[i] == 0)
        {
            printf(" ");
            printBrand(i);
        }
    }
    printf("\nPlease complete the data\n");
}

void printBrand(int index)
{
    if(index >= 0 && index < NUM_OF_BRANDS)
    {
        for(int i = 0 ; i <  BRANDS_NAMES; i++)
        {
            if(brands[index][i] == '\0')
                break;
            printf("%c", brands[index][i]);
        }
    }
}

void printType(int index)
{
    if(index >= 0 && index < NUM_OF_TYPES)
    {
        for(int i = 0 ; i < TYPES_NAMES; i++)
        {
            if(types[index][i] == '\0')
                break;
            printf("%c", types[index][i]);
        }
    }
}

int salesTotal(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int sumSales = 0;
    for(int i = 0 ; i < numOfBrands ; i++)
    {
        for(int j = 0 ; j < numOfTypes ; j++)
        {
            sumSales += cube[day][i][j];
        }
    }
    return sumSales;
}

int maxSalesBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int maxBrand = 0, tempSale;
    int maxSalesBrand = salesBrand(maxBrand, cube, numOfBrands, numOfTypes, day);

    for(int i = 1 ; i < numOfBrands ; i++)
    {
        tempSale = salesBrand(i, cube, numOfBrands, numOfTypes, day);
        if(tempSale > maxSalesBrand)
        {
            maxSalesBrand = tempSale;
            maxBrand = i;
        }
    }
    return maxBrand;
}
int salesBrand(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int salesBrand = 0;
    if(index >= 0 && index < numOfBrands)
    {
        for(int i = 0 ; i < numOfTypes ; i++)
            salesBrand += cube[day][index][i];
    }
    return salesBrand;
}

int maxSalesType(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int maxType = 0, tempSale;
    int maxSalesType = salesType(maxType, cube, numOfBrands, numOfTypes, day);

    for(int i = 1 ; i < numOfBrands ; i++)
    {
        tempSale = salesType(i, cube, numOfBrands, numOfTypes, day);
        if(tempSale > maxSalesType)
        {
            maxSalesType = tempSale;
            maxType = i;
        }
    }
    return maxType;
}

int salesType(int index, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int day)
{
    int salesType = 0;
    if(index >= 0 && index < numOfTypes)
    {
        for(int i = 0 ; i < numOfBrands ; i++)
            salesType += cube[day][i][index];
    }
    return salesType;
}

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

double brandDelta(int brand, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int days[])
{
    double deltaSum = 0, avgDelta;
    int sales1, sales2;
    for(int i = 0 ; i < days[brand] - 1 ; i++)
    {
        sales1 = salesBrand(brand, cube, numOfBrands, numOfTypes, i);
        sales2 = salesBrand(brand, cube, numOfBrands, numOfTypes, (i + 1));
        deltaSum += (double)(sales2 - sales1);
    }

    if (days[brand] == 0 || days[brand] == 1)
        return 0;
    if (days[brand] - 1 != 0)
        avgDelta = deltaSum / (days[brand] - 1);
    else
        avgDelta = (double)(0);
    return avgDelta;
}