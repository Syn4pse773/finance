#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


extern void encrypt_db(void* data, size_t size, char key);



typedef struct {
    char name[32];      
    char number[20];    
    long long balance;  
} Card;

typedef struct {
    char title[64];     
    long long target;   
    long long current;  
} Goal;

typedef struct {
    long long total_balance;
    int card_count;
    Card cards[10];     
    int goal_count;
    Goal goals[10];     
} FinanceDB;



int tui (FinanceDB *db) {
    int option;
    for (;;) {
        printf("Welcome to Finance Manager\n");
        printf("1. Show Balance\n");
        printf("2. Add Card\n");    
        printf("3. Add Goal\n");
        printf("4. Save & Exit\n");
        printf("Choose an option: ");

        scanf("%d", &option);
        switch(option) {
            case 1:
                printf("\n---- Current Balance ----\n");
                printf("Total Balance: %lld\n", db->total_balance);
                printf("Total Cards: %d\n", db->card_count);
                printf("-------------------------\n");
                
                for (int i = 0; i < db->card_count; i++) {
                    printf("[%d] Bank: %s\n", i + 1, db->cards[i].name);
                    printf("    Number: %s\n", db->cards[i].number);
                    printf("    Balance: %lld\n", db->cards[i].balance);
                }
                printf("\n---- Your Goals ----\n");
                printf("Total Goals: %d\n", db->goal_count);
                for (int i = 0; i < db->goal_count; i++) {
                    printf("[%d] Goal: %s\n", i + 1, db->goals[i].title);
                    printf("    Progress: %lld / %lld\n", db->goals[i].current, db->goals[i].target);
                }
                printf("-------------------------\n");
                break; 
            case 2:
                printf("\n---- Add Card ----\n");
                if (db->card_count < 10) {
                    printf("Enter card name: ");
                    scanf(" %31[^\n]", db->cards[db->card_count].name);
                    printf("Enter card number: ");
                    scanf("%19s", db->cards[db->card_count].number);
                    printf("Enter card balance: ");
                    scanf("%lld", &db->cards[db->card_count].balance);
                    db->total_balance += db->cards[db->card_count].balance;
                    db->card_count++;
                } else {
                    printf("Card limit reached!\n");
                }
                break;

            case 3:
                printf("\n---- Add Goal ----\n");
                if (db->goal_count < 10) {
                    printf("Enter goal title (e.g. New Car): ");
                    scanf(" %63[^\n]", db->goals[db->goal_count].title);
                    
                    printf("Enter target amount: ");
                    scanf("%lld", &db->goals[db->goal_count].target);
                    
                    printf("Enter current saved amount: ");
                    scanf("%lld", &db->goals[db->goal_count].current);
                    
                    db->goal_count++;
                    printf("Goal added successfully!\n");
                } else {
                    printf("Goal limit reached!\n");
                }
                break;
            case 4:
                
                printf("Encrypting and saving data...\n");
                
                encrypt_db(db, sizeof(FinanceDB), 0x5A);

                FILE *file = fopen("finance.enc", "wb");
                if (file != NULL) {
                    fwrite(db, sizeof(FinanceDB), 1, file);
                    fclose(file);
                    printf("Saved to finance.enc successfully!\n");
                } else {
                    printf("Error opening file for saving!\n");
                }
                return 0; 
            default:
                printf("Invalid option, please try again.\n");
        }
        sleep(3);
        printf("Press Enter to continue...");
        while (getchar() != '\n');
        getchar(); 
        system("clear");
        

    }

    return 0;
}


int main() {
    FinanceDB db = {0}; 

    FILE *file = fopen("finance.enc", "rb");
    if (file != NULL) {
        printf("Loading data from finance.enc...\n");
        fread(&db, sizeof(FinanceDB), 1, file);

        fclose(file);
        encrypt_db(&db, sizeof(FinanceDB), 0x5A); 
        printf("Data loaded and decrypted successfully!\n");
        
    } else {
        printf("No existing data found.\n");
    }

    return tui(&db);
}
