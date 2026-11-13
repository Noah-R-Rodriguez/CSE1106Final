
#include <stdio.h>
#include <string.h>
#include <pigpio.h>

#define GREEN_LED 17
#define RED_LED 27
#define MAX_INPUTS 100

float MIN_TEMP = 68;
float MAX_TEMP = 76;

struct TemperatureReading {
    float Temperature;
    char status[30];
};

struct TemperatureReading readings[MAX_INPUTS];
int count = 0;

void inputTemperature();
void calcAvg();
void expReadings();
void updateLED(float temperature);
void chngRange();

void inputTemperature() {
    int num;

    printf("How many temperatures would you like to enter? ");
    scanf("%d", &num);

    if (num <= 0 || num > MAX_INPUTS - count) {
        printf("Invalid number of readings!\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        printf("Enter temperature: ");
        scanf("%f", &readings[count].Temperature);

        updateLED(readings[count].Temperature);

        if (readings[count].Temperature >= MIN_TEMP &&
            readings[count].Temperature <= MAX_TEMP) {
            strcpy(readings[count].status, "Acceptable Temperature");
        } else {
            strcpy(readings[count].status, "Unacceptable");
        }

        printf("Temperature Status: %s\n", readings[count].status);
        count++;
    }
}

void calcAvg() {
    float sum = 0;

    if (count == 0) {
        printf("No temperatures entered yet.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        sum += readings[i].Temperature;
    }

    printf("Average Temperature: %.2f\n", sum / count);
}

void expReadings() {
    FILE *file = fopen("temperature_readings.txt", "w");

    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }

    fprintf(file, "CLASSROOM TEMPERATURE READINGS\n");
    fprintf(file, "-------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "Temperature: %.2f | Status: %s\n",
                readings[i].Temperature,
                readings[i].status);
    }

    fclose(file);
    printf("Readings successfully exported!\n");
}

void updateLED(float temperature) {
    if (temperature >= MIN_TEMP && temperature <= MAX_TEMP) {
        gpioWrite(GREEN_LED, 1);
        gpioWrite(RED_LED, 0);
        printf("STATUS: NORMAL - Green LED ON\n");
    } else {
        gpioWrite(GREEN_LED, 0);
        gpioWrite(RED_LED, 1);
        printf("WARNING! Temperature out of range - Red LED ON\n");
    }
}

void chngRange() {
    float newMin, newMax;

    printf("Enter new minimum temperature: ");
    scanf("%f", &newMin);

    printf("Enter new maximum temperature: ");
    scanf("%f", &newMax);

    if (newMin >= newMax) {
        printf("Invalid temperature range!\n");
        return;
    }

    MIN_TEMP = newMin;
    MAX_TEMP = newMax;

    printf("Temperature limits updated successfully!\n");
}

int main() {
    int choice;

    if (gpioInitialise() < 0) {
        printf("Error initializing pigpio.\n");
        return 1;
    }

    gpioSetMode(GREEN_LED, PI_OUTPUT);
    gpioSetMode(RED_LED, PI_OUTPUT);

    do {
        printf("\n===== CLASSROOM TEMPERATURE SYSTEM =====\n");
        printf("1. Enter Temperature(s)\n");
        printf("2. Calculate Average\n");
        printf("3. Export Readings\n");
        printf("4. Change Temperature Range\n");
        printf("5. Exit Program\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputTemperature();
                break;
            case 2:
                calcAvg();
                break;
            case 3:
                expReadings();
                break;
            case 4:
                chngRange();
                break;
            case 5:
                printf("Exiting Program... Thank you!\n");
                break;
            default:
                printf("Invalid input. Enter a number from 1-5.\n");
        }

    } while (choice != 5);

    gpioWrite(GREEN_LED, 0);
    gpioWrite(RED_LED, 0);

    gpioTerminate();

    return 0;
}
