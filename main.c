#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"

// Array to store available cars in stock
Car cars[MAX_CARS];

// Array to store sales data
Sale sales[MAX_SALES];

int salesCount = 0; // Counter for the number of sales recorded

// Main function to run the car sales system
int main() {
    initialiseCars();   // Initialize the car stock data
    loadSalesData();    // Load existing sales data from file

    char choice;
    do {
        // Display the main menu
        printf("\nCar Sales Menu:\n");
        printf("1. View Cars Stock\n");
        printf("2. Buy Car\n");
        printf("3. View Sales Data\n");
        printf("4. Leave Feedback\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf(" %c", &choice); // Get the user's choice
        clearInputBuffer();    // Clear any extra input characters

        // Handle the user's choice
        switch (choice) {
            case '1':
                viewCarStock();    // Show available car stock
                break;
            case '2':
                buyCar();          // Handle car purchase
                break;
            case '3':
                viewSalesData();   // Display sales data
                break;
            case '4':
                leaveFeedback();   // Collect user feedback
                break;
            case '5':
                saveSalesData();   // Save sales data to file before exiting
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '5'); // Loop until the user chooses to exit

    return 0;
}

// Initialize the car stock with predefined values
void initialiseCars() {
    strcpy(cars[0].model, "Audi A3"); cars[0].year = 2019; cars[0].price = 20000.0f; cars[0].remaining = 5;
    strcpy(cars[1].model, "BMW X1"); cars[1].year = 2020; cars[1].price = 25000.0f; cars[1].remaining = 3;
    strcpy(cars[2].model, "Mercedes C-Class"); cars[2].year = 2018; cars[2].price = 30000.0f; cars[2].remaining = 2;
    strcpy(cars[3].model, "Volkswagen Golf"); cars[3].year = 2017; cars[3].price = 18000.0f; cars[3].remaining = 4;
    strcpy(cars[4].model, "Ford Focus"); cars[4].year = 2019; cars[4].price = 17000.0f; cars[4].remaining = 6;
    strcpy(cars[5].model, "Toyota Corolla"); cars[5].year = 2021; cars[5].price = 22000.0f; cars[5].remaining = 5;
    strcpy(cars[6].model, "Honda Civic"); cars[6].year = 2020; cars[6].price = 21000.0f; cars[6].remaining = 7;
    strcpy(cars[7].model, "Nissan Qashqai"); cars[7].year = 2018; cars[7].price = 19000.0f; cars[7].remaining = 3;
    strcpy(cars[8].model, "Kia Sportage"); cars[8].year = 2021; cars[8].price = 23000.0f; cars[8].remaining = 4;
    strcpy(cars[9].model, "Hyundai Tucson"); cars[9].year = 2020; cars[9].price = 24000.0f; cars[9].remaining = 5;
    strcpy(cars[10].model, "Mazda CX-5"); cars[10].year = 2019; cars[10].price = 26000.0f; cars[10].remaining = 2;
    strcpy(cars[11].model, "Tesla Model 3"); cars[11].year = 2021; cars[11].price = 35000.0f; cars[11].remaining = 1;
    strcpy(cars[12].model, "Chevrolet Malibu"); cars[12].year = 2018; cars[12].price = 16000.0f; cars[12].remaining = 4;
    strcpy(cars[13].model, "Jeep Wrangler"); cars[13].year = 2020; cars[13].price = 32000.0f; cars[13].remaining = 2;
    strcpy(cars[14].model, "Porsche Macan"); cars[14].year = 2021; cars[14].price = 50000.0f; cars[14].remaining = 1;
    strcpy(cars[15].model, "Volvo XC90"); cars[15].year = 2019; cars[15].price = 48000.0f; cars[15].remaining = 3;
    strcpy(cars[16].model, "Subaru Outback"); cars[16].year = 2020; cars[16].price = 28000.0f; cars[16].remaining = 5;
    strcpy(cars[17].model, "Lexus RX"); cars[17].year = 2019; cars[17].price = 40000.0f; cars[17].remaining = 2;
    strcpy(cars[18].model, "Jaguar F-Pace"); cars[18].year = 2018; cars[18].price = 45000.0f; cars[18].remaining = 2;
    strcpy(cars[19].model, "Land Rover Discovery"); cars[19].year = 2021; cars[19].price = 55000.0f; cars[19].remaining = 1;
}

// Load sales data from a file
void loadSalesData() {
    FILE *file = fopen(SALES_FILE, "r");
    if (file == NULL) {
        printf("Warning: Could not open sales data file. Starting with no sales data.\n");
        return;
    }


    // Read sales data line by line
    while (fscanf(file, "%[^,],%d,%[^,],%f,%d,%d,%[^\n]\n", sales[salesCount].customerName, &sales[salesCount].customerAge,
                  sales[salesCount].carModel, &sales[salesCount].totalPrice, &sales[salesCount].discountGiven,
                  &sales[salesCount].numberOfCars, sales[salesCount].date) != EOF) {
        salesCount++;
    }

    fclose(file);
}

// Save sales data to a file
void saveSalesData() {
    FILE *file = fopen(SALES_FILE, "w");
    if (file == NULL) {
        printf("Error: Could not save sales data.\n");
        return;
    }

    // Write each sale to the file
    for (int i = 0; i < salesCount; i++) {
        fprintf(file, "%s,%d,%s,%.2f,%d,%d,%s\n", sales[i].customerName, sales[i].customerAge, sales[i].carModel,
                sales[i].totalPrice, sales[i].discountGiven, sales[i].numberOfCars, sales[i].date);
    }

    fclose(file);
}

// Display the current car stock
void viewCarStock() {
    sortCarsByYearDescending(); // Sort cars by year (newest first)
    printf("\nCar Stock:\n");
    for (int i = 0; i < MAX_CARS && strlen(cars[i].model) > 0; i++) {
        printf("Model: %s, Year: %d, Price: %.2f, Remaining: %d\n", cars[i].model, cars[i].year, cars[i].price, cars[i].remaining);
    }
}

// Handle a car purchase
void buyCar() {
    char customerName[MAX_NAME_LENGTH];
    getValidatedString("Enter your name: ", customerName, MAX_NAME_LENGTH); // Get customer's name

    int customerAge = getValidatedInt("Enter your age: ", 0, 120); // Get customer's age

    // Show available cars
    printf("\nAvailable Cars:\n");
    for (int i = 0; i < MAX_CARS && strlen(cars[i].model) > 0; i++) {
        printf("%d. %s (%d) - $%.2f, Remaining: %d\n", i + 1, cars[i].model, cars[i].year, cars[i].price, cars[i].remaining);
    }

    // Get the car choice and number of cars to buy
    int carChoice = getValidatedInt("Choose a car to buy (enter number): ", 1, MAX_CARS) - 1;
    if (cars[carChoice].remaining <= 0) {
        printf("Sorry, that car is out of stock.\n");
        return;
    }

    int numberOfCars = getValidatedInt("How many cars would you like to buy? ", 1, cars[carChoice].remaining);

    // Calculate total price and apply discount if eligible
    float totalPrice = cars[carChoice].price * numberOfCars;
    bool discountGiven = (customerAge >= DISCOUNT_MIN_AGE && customerAge <= DISCOUNT_MAX_AGE);
    if (discountGiven) {
        totalPrice *= (1 - DISCOUNT_PERCENTAGE);
        printf("You received a discount!\n");
    }

    // Update car stock and add the sale record
    cars[carChoice].remaining -= numberOfCars;

    // Record the sale date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[MAX_NAME_LENGTH];
    sprintf(date, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Save the sale details
    Sale newSale = {"", customerAge, "", totalPrice, discountGiven, numberOfCars, ""};
    strcpy(newSale.customerName, customerName);
    strcpy(newSale.carModel, cars[carChoice].model);
    strcpy(newSale.date, date);
    sales[salesCount++] = newSale;

    printf("Purchase successful!\n");
}

// View all recorded sales data
void viewSalesData() {
    sortSalesByTotalPriceDescending(); // Sort sales by total price (highest first)
    printf("\nSales Data:\n");
    for (int i = 0; i < salesCount; i++) {
        printf("Customer: %s, Car: %s, Total Price: %.2f, Date: %s\n", sales[i].customerName, sales[i].carModel, sales[i].totalPrice, sales[i].date);
    }
}

// Collect feedback from the user
void leaveFeedback() {
    FILE *file = fopen(FEEDBACK_FILE, "a");
    if (file == NULL) {
        printf("Error: Could not save feedback.\n");
        return;
    }

    char feedback[MAX_NAME_LENGTH];
    getValidatedString("Please enter your feedback: ", feedback, MAX_NAME_LENGTH);
    fprintf(file, "%s\n", feedback);
    fclose(file);

    printf("Thank you for your feedback!\n");
}

// Validate and get an integer input from the user
int getValidatedInt(const char *prompt, int min, int max) {
    int value;
    do {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        if (value < min || value > max) {
            printf("Input out of range. Please enter a value between %d and %d.\n", min, max);
        }
    } while (value < min || value > max);
    clearInputBuffer();
    return value;
}

// Validate and get a string input from the user
void getValidatedString(const char *prompt, char *input, int length) {
    printf("%s", prompt);
    fgets(input, length, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character
}

// Sort cars by year in descending order using a bubble sort
void sortCarsByYearDescending() {
    for (int i = 0; i < MAX_CARS - 1; i++) {
        for (int j = i + 1; j < MAX_CARS; j++) {
            if (cars[j].year > cars[i].year) {
                Car temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }
    }
}

// Sort sales by total price in descending order
void sortSalesByTotalPriceDescending() {
    for (int i = 0; i < salesCount - 1; i++) {
        for (int j = i + 1; j < salesCount; j++) {
            if (sales[j].totalPrice > sales[i].totalPrice) {
                Sale temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
            }
        }
    }
}

// Clear the input buffer to handle extraneous characters
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
