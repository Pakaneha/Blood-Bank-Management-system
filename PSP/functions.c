#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// Global blood bank array definition
int blood_bank[8] = {0};

const char* calculate_donation_grade(int quantity) {
    if (quantity >= 500) {
        return "Gold";
    } else if (quantity >= 300) {
        return "Platinum";
    } else if (quantity >= 200) {
        return "Silver";
    } else {
        return "Bronze";
    }
}

void add_donor() {
    struct donor d;
    FILE* fp;
    fp = fopen("donors.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("Enter donor name: ");
    scanf("%s", d.name);
    printf("Enter donor age: ");
    scanf("%d", &d.age);
    printf("Enter donor blood group: ");
    scanf("%s", d.blood_group);
    printf("Enter donor phone number: ");
    scanf("%s", d.phone);
    printf("Enter quantity of blood donated (in ml): ");
    scanf("%d", &d.quantity);
    printf("Enter donation date (days ago): ");
    scanf("%d", &d.donation_date);
    strcpy(d.grade, calculate_donation_grade(d.quantity));
    fprintf(fp, "%s %d %s %s %d %d %s\n", d.name, d.age, d.blood_group, d.phone, d.quantity, d.donation_date, d.grade);
    fclose(fp);
    
    // Update blood bank inventory
    if (strcmp(d.blood_group, "A+") == 0) {
        blood_bank[0] += 1;
    } else if (strcmp(d.blood_group, "A-") == 0) {
        blood_bank[1] += 1;
    } else if (strcmp(d.blood_group, "B+") == 0) {
        blood_bank[2] += 1;
    } else if (strcmp(d.blood_group, "B-") == 0) {
        blood_bank[3] += 1;
    } else if (strcmp(d.blood_group, "AB+") == 0) {
        blood_bank[4] += 1;
    } else if (strcmp(d.blood_group, "AB-") == 0) {
        blood_bank[5] += 1;
    } else if (strcmp(d.blood_group, "O+") == 0) {
        blood_bank[6] += 1;
    } else if (strcmp(d.blood_group, "O-") == 0) {
        blood_bank[7] += 1;
    }
    
    printf("Donor added successfully\n");
}

void find_highest_donor_grade() {
    FILE* fp;
    fp = fopen("donors.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    struct donor d;
    char highest_grade[20] = "Bronze"; // Initialize with lowest grade
    int max_quantity = 0;
    
    while (fscanf(fp, "%s %d %s %s %d %d %s", d.name, &d.age, d.blood_group, d.phone, &d.quantity, &d.donation_date, d.grade) != EOF) {
        if (d.quantity > max_quantity) {
            max_quantity = d.quantity;
            strcpy(highest_grade, d.grade);
        }
    }
    fclose(fp);
    printf("The highest grade among the donors is: %s\n", highest_grade);
}

void add_acceptor() {
    struct acceptor a;
    FILE* fp;
    fp = fopen("acceptors.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("Enter acceptor name: ");
    scanf("%s", a.name);
    printf("Enter acceptor age: ");
    scanf("%d", &a.age);
    printf("Enter acceptor blood group: ");
    scanf("%s", a.blood_group);
    printf("Enter acceptor phone number: ");
    scanf("%s", a.phone);
    printf("Enter quantity of blood accepted (in ml): ");
    scanf("%d", &a.quantity);
    printf("Enter acceptance date (days ago): ");
    scanf("%d", &a.acceptance_date);
    fprintf(fp, "%s %d %s %s %d %d\n", a.name, a.age, a.blood_group, a.phone, a.quantity, a.acceptance_date);
    fclose(fp);
    printf("Acceptor added successfully\n");
}

void search_donor() {
    char blood_group[5];
    printf("Enter blood group to search: ");
    scanf("%s", blood_group);
    FILE* fp;
    fp = fopen("donors.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    struct donor d;
    int found = 0;
    printf("\n--- Donors with blood group %s ---\n", blood_group);
    while (fscanf(fp, "%s %d %s %s %d %d %s", d.name, &d.age, d.blood_group, d.phone, &d.quantity, &d.donation_date, d.grade) != EOF) {
        if (strcmp(d.blood_group, blood_group) == 0) {
            printf("Name: %s\nAge: %d\nBlood Group: %s\nPhone: %s\nQuantity: %d ml\nDonation Date: %d days ago\nGrade: %s\n\n", 
                   d.name, d.age, d.blood_group, d.phone, d.quantity, d.donation_date, d.grade);
            found = 1;
        }
    }
    fclose(fp);
    if (found == 0) {
        printf("No donor found with blood group %s\n", blood_group);
    }
}

void accept_blood(char* blood_group, int quantity) {
    FILE* fp1, * fp2;
    fp1 = fopen("donors.txt", "r");
    fp2 = fopen("acceptors.txt", "a");
    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    struct donor d;
    struct acceptor a;
    int found = 0;
    
    // Search for a compatible donor
    while (fscanf(fp1, "%s %d %s %s %d %d %s", d.name, &d.age, d.blood_group, d.phone, &d.quantity, &d.donation_date, d.grade) != EOF) {
        if (strcmp(d.blood_group, blood_group) == 0 && d.quantity >= quantity) {
            found = 1;
            break;
        }
    }
    fclose(fp1);
    
    if (found == 1) {
        printf("Compatible donor found: %s\n", d.name);
        printf("Enter acceptor name: ");
        scanf("%s", a.name);
        printf("Enter acceptor age: ");
        scanf("%d", &a.age);
        strcpy(a.blood_group, blood_group);
        printf("Enter acceptor phone number: ");
        scanf("%s", a.phone);
        a.quantity = quantity;
        printf("Enter acceptance date (days ago): ");
        scanf("%d", &a.acceptance_date);
        
        fprintf(fp2, "%s %d %s %s %d %d\n", a.name, a.age, a.blood_group, a.phone, a.quantity, a.acceptance_date);
        fclose(fp2);
        printf("Acceptor added successfully\n");
        
        // Update blood bank inventory
        if (strcmp(blood_group, "A+") == 0) {
            blood_bank[0] -= 1;
        } else if (strcmp(blood_group, "A-") == 0) {
            blood_bank[1] -= 1;
        } else if (strcmp(blood_group, "B+") == 0) {
            blood_bank[2] -= 1;
        } else if (strcmp(blood_group, "B-") == 0) {
            blood_bank[3] -= 1;
        } else if (strcmp(blood_group, "AB+") == 0) {
            blood_bank[4] -= 1;
        } else if (strcmp(blood_group, "AB-") == 0) {
            blood_bank[5] -= 1;
        } else if (strcmp(blood_group, "O+") == 0) {
            blood_bank[6] -= 1;
        } else if (strcmp(blood_group, "O-") == 0) {
            blood_bank[7] -= 1;
        }
        printf("Blood bank updated successfully\n");
    } else {
        printf("No compatible donor found with sufficient quantity\n");
    }
}

void print_blood_bank() {
    printf("\n--- Blood Bank Inventory ---\n");
    printf("Blood Group\tPackets Available\n");
    printf("A+\t\t%d\n", blood_bank[0]);
    printf("A-\t\t%d\n", blood_bank[1]);
    printf("B+\t\t%d\n", blood_bank[2]);
    printf("B-\t\t%d\n", blood_bank[3]);
    printf("AB+\t\t%d\n", blood_bank[4]);
    printf("AB-\t\t%d\n", blood_bank[5]);
    printf("O+\t\t%d\n", blood_bank[6]);
    printf("O-\t\t%d\n", blood_bank[7]);
    printf("---------------------------\n");
}
