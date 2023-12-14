#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024


char *trim(const char *str) {

    while (*str && isspace((unsigned char)*str)) {
        str++;
    }

    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        len--;
    }

    char *trimmed = malloc(len + 1);
    if (trimmed == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }

    strncpy(trimmed, str, len);
    trimmed[len] = '\0';

    return trimmed;
}


int main() {
    double carPrice, volume, environmentalTax, singleRate, totalPrice;
    int releaseYear, shipment, auction;
    char carBrand[100], carModel[100], fuelType[100];
    shipment = 2500;
    auction = 1000;

    printf("Enter the car's price: ");
    scanf("%lf", &carPrice);

    printf("Enter the year of car's release: ");
    scanf("%d", &releaseYear);

    printf("Enter the car's volume: ");
    scanf("%lf", &volume);

    printf("Enter the car's brand: ");
    scanf("%s", carBrand);

    printf("Enter the car's model: ");
    scanf("%s", carModel);
    
    printf("Enter the car's fuel type: ");
    scanf("%s", fuelType);


    struct Car {
        double price;
        int year;
        double volume;
        char brand[MAX_LINE_LENGTH];
        char model[MAX_LINE_LENGTH];
    };

    // Calculate environmental tax
    if (releaseYear >= 1990 && releaseYear <= 2009) {
        environmentalTax = carPrice * 0.2;
    }
    else if (releaseYear >= 2010 && releaseYear <= 2014) {
        environmentalTax = carPrice * 0.1;
    }
    else if (releaseYear >= 2015 && releaseYear <= 2018) {
        environmentalTax = carPrice * 0.02;
    }
    else if (releaseYear >= 2019 || fuelType == "Electric") {
        environmentalTax = 0;
    }

    // Calculate single rate
    if (volume >= 0 && volume <= 1000) {
        singleRate = volume * 3;
    }
    else if (volume >= 1001 && volume <= 1800) {
        singleRate = volume * 3.2;
    }
    else if (volume >= 1801 && volume <= 2300) {
        singleRate = volume * 4.8;
    }
    else if (volume >= 2301 && volume <= 3000) {
        singleRate = volume * 5;
    }
    else if (volume >= 3001 && volume <= 10000) {
        singleRate = volume * 5.7;
    }
    else {
        printf("Invalid volume range.\n");
        return 1;
    }

    // Calculate total price
    totalPrice = environmentalTax + singleRate + shipment + auction;


    FILE *file;
    char line[MAX_LINE_LENGTH];
    const char *filename = "C:\\Users\\Narek\\Desktop\\NarekScript\\auto_data_csv.csv"; 

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    const char *targetValue = carModel;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            if (strcasecmp(trim(targetValue), trim(token)) == 0) {
                printf("Model of brand '%s' '%s' exists.\n", carBrand, targetValue);
                    printf("\nCar's shipment price: $%.2f\n", shipment);
                    printf("Auction's price: $%.2f\n", auction);
                    printf("Car's Environmental Tax: $%.2f\n", environmentalTax);
                    printf("Car's Single Rate: $%.2f\n", singleRate);
                    printf("\nCar's Total Price: $%.2f\n", totalPrice);
                free(trim(token));
                fclose(file);
                return 0;
            }
            free(trim(token));
            token = strtok(NULL, ",");
        }
    }

    printf("Model '%s' does not exist.\n", targetValue);

    fclose(file);

    return 0;
}
