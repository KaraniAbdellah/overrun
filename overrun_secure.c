#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct myData {
    char public_info[20]; // publicly available stuff
    char fav_color[21];
    int pin;
    int age;
};

// Safely initialize my information values
void setData(struct myData *data) {
    strncpy(data->public_info, "I yam what I yam.", sizeof(data->public_info) - 1);
    data->public_info[sizeof(data->public_info) - 1] = '\0';

    strncpy(data->fav_color, "red", sizeof(data->fav_color) - 1);
    data->fav_color[sizeof(data->fav_color) - 1] = '\0';

    data->pin = 99;
    data->age = 61;
}

// Safe memory access with offset bounds check
void showMemory(struct myData data) {
    int offset;
    int result;

    while (1) {
        printf("Enter an offset into your public data (0-%lu), or q to quit:\n", sizeof(data.public_info) - 1);
        result = scanf("%d", &offset);
        if (result == 0) {
            break;
        }

        if (offset < 0 || offset >= sizeof(data.public_info)) {
            printf("Invalid offset! Stay within bounds.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        printf("Hex value at offset %d (address 0x%p) is 0x%x\n",
               offset, &data.public_info[offset], data.public_info[offset]);
    }
}

// Main logic
void handleMyStuff() {
    struct myData my_data;
    setData(&my_data);

    printf("Address of public data:\t0x%p\n", (void*)&my_data.public_info[0]);
    printf("Address of secret PIN:\t0x%p\n", (void*)&my_data.pin);
    printf("\n");

    printf("Public data is: %s\n", my_data.public_info);
    printf("Hex value of PIN is: 0x%x\n", my_data.pin);
    printf("\n");

    showMemory(my_data);
}

int main(int argc, char *argv[]) {
    handleMyStuff();
    printf("\nBye\n");
    return 0;
}

// gcc -m32 -g -fstack-protector-all -D_FORTIFY_SOURCE=2 -O2 -o mystuff mystuff.c
