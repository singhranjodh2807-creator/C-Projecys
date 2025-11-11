#include <stdio.h>


static void save_balance(float bal) {
    FILE *f = fopen("atm_data.txt", "w");

    if (!f) return;
    fprintf(f, "%f\n", bal);
    fclose(f);
}


static float load_balance(void) {
    FILE *f = fopen("atm_data.txt", "r");

    float bal = 1000.0f;     // default starting balance

    if (!f) return bal;
    if (fscanf(f, "%f", &bal) != 1) bal = 1000.0f;
    fclose(f);

    return bal;
}

int main() {
    float balance = load_balance(), amount;
    int choice = 0, pin, enteredPin;

    pin = 1234; // set ATM PIN

    printf("Enter ATM PIN: ");
    
    if (scanf("%d", &enteredPin) != 1) return 1;

    if (enteredPin != pin) {
        printf("Incorrect PIN. Access Denied!\n");

        return 1;
    }

    do {
        printf("\nATM Menu:\n");
        printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) { 
            int ch; while ((ch = getchar()) != EOF && ch != '\n') {}
            continue;
        }

        switch (choice) {
        case 1:
            printf("Balance: %.2f\n", balance);
            break;

        case 2:
            printf("Enter deposit amount: ");
            if (scanf("%f", &amount) != 1) { while (getchar() != '\n'); break; }
            balance += amount;
            save_balance(balance);
            printf("New Balance: %.2f\n", balance);
            break;

        case 3:
            printf("Enter withdrawal amount: ");
            if (scanf("%f", &amount) != 1) { while (getchar() != '\n'); break; }
            if (amount > balance)
                printf("Insufficient balance!\n");
            else {
                balance -= amount;
                save_balance(balance);
                printf("Withdrawn %.2f. New Balance: %.2f\n", amount, balance);
            }
            break;

        case 4:
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 4);

    return 0;
}