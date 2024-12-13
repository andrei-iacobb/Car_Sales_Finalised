#ifndef MAIN_H
#define MAIN_H

#define MAX_CARS 50
#define MAX_SALES 100
#define MAX_NAME_LENGTH 100
#define DISCOUNT_MIN_AGE 17
#define DISCOUNT_MAX_AGE 25
#define DISCOUNT_PERCENTAGE 0.10f
#define SALES_FILE "sales_data.txt"
#define FEEDBACK_FILE "feedback.txt"


#include <stdbool.h>

typedef struct {
    char model[MAX_NAME_LENGTH];
    int year;
    float price;
    int remaining;
} Car;

typedef struct {
    char customerName[MAX_NAME_LENGTH];
    int customerAge;
    char carModel[MAX_NAME_LENGTH];
    float totalPrice;
    bool discountGiven;
    int numberOfCars;
    char date[MAX_NAME_LENGTH];
} Sale;

void initialiseCars();
void loadSalesData();
void saveSalesData();
void viewCarStock();
void buyCar();
void viewSalesData();
void leaveFeedback();
int getValidatedInt(const char *prompt, int min, int max);
float getValidatedFloat(const char *prompt, float min, float max);
void getValidatedString(const char *prompt, char *input, int length);
void sortCarsByYearDescending();
void sortSalesByTotalPriceDescending();
void clearInputBuffer();

#endif //MAIN_H
