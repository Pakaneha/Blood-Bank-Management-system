#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    int choice;
    char blood_group[5];
    int quantity,blood_bank;
    while (1) {
        printf("1. Add donor\n");
        printf("2. Find highest donor grade\n");
        printf("3. Add acceptor\n");
        printf("4. Search donor by blood group\n");
        printf("5. Accept blood\n");
        printf("6. Print blood bank\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_donor();
                break;
            case 2:
                find_highest_donor_grade();
                break;
            case 3:
                add_acceptor();
                break;
            case 4:
                search_donor();
                break;
            case 5:
                printf("Enter blood group needed: ");
                scanf("%s", blood_group);
                printf("Enter quantity of blood needed (in ml): ");
                scanf("%d", &quantity);
                accept_blood(blood_group, quantity);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
