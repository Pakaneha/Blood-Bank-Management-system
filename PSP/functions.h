#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Structure definitions
struct donor {
    char name[50];
    int age;
    char blood_group[5];
    char phone[15];
    int quantity;
    int donation_date;
    char grade[20];
};

struct acceptor {
    char name[50];
    int age;
    char blood_group[5];
    char phone[15];
    int quantity;
    int acceptance_date;
};

// Global blood bank array declaration
extern int blood_bank[8];

// Function declarations
const char* calculate_donation_grade(int quantity);
void add_donor();
void find_highest_donor_grade();
void add_acceptor();
void search_donor();
void accept_blood(char* blood_group, int quantity);
void print_blood_bank();

#endif
