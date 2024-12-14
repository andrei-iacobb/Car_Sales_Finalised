#ifndef MAIN_H
#define MAIN_H

#define MAX_CARS 50
#define MAX_SALES 100
#define MAX_TEXT_LENGTH 200
#define DISCOUNT_MIN_AGE 17
#define DISCOUNT_MAX_AGE 25
#define DISCOUNT_PERCENTAGE 0.10f
#define SALES_FILE "sales_data.csv"
#define FEEDBACK_FILE "feedback.txt"
#define SECUREKEY "iloveraz"

#include <stdbool.h>

typedef struct {
    char model[MAX_TEXT_LENGTH];
    int year;
    float price;
    int remaining;
} Car;

typedef struct {
    char customerName[MAX_TEXT_LENGTH];
    int customerAge;
    char carModel[MAX_TEXT_LENGTH];
    float totalPrice;
    bool discountGiven;
    int numberOfCars;
    char date[MAX_TEXT_LENGTH];
} Sale;

void initialiseCars();
void loadSalesData();
void saveSalesData();
void clearConsole();
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
void pauseProgram();
void handleEncryption(char* data);

#endif //MAIN_H
