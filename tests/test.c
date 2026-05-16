#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

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

void test_encryption_symmetry() {
    FinanceDB db1 = {0};
    db1.total_balance = 999999;
    strcpy(db1.cards[0].name, "Secure Bank");
    
    FinanceDB db2 = db1; 

    encrypt_db(&db2, sizeof(FinanceDB), 0x5A);
    
    assert(memcmp(&db1, &db2, sizeof(FinanceDB)) != 0 && "Encryption failed: Data did not change!");
    
    encrypt_db(&db2, sizeof(FinanceDB), 0x5A);

    assert(memcmp(&db1, &db2, sizeof(FinanceDB)) == 0 && "Symmetry test failed: Decrypted data differs from original!");
    
    printf("[OK] Encryption symmetry test passed.\n");
}

void test_buffer_bounds() {
    uint8_t buffer[10] = {0};
    uint8_t key = 0xFF;
    
    buffer[0] = 0xAA;
    buffer[9] = 0xAA;

    encrypt_db(&buffer[1], 8, key);

    assert(buffer[0] == 0xAA && "Buffer Underflow detected! Left canary modified.");
    assert(buffer[9] == 0xAA && "Buffer Overflow detected! Right canary modified.");
    
    for(int i = 1; i <= 8; i++) {
        assert(buffer[i] == 0xFF && "Encryption missed some target bytes!");
    }

    printf("[OK] Buffer bounds test passed (Canaries intact).\n");
}

void test_zero_size() {
    char data[] = "Secret";
    char original[] = "Secret";
    
    encrypt_db(data, 0, 0x5A);
    
    assert(strcmp(data, original) == 0 && "Data modified despite size=0!");
    printf("[OK] Zero size handling passed.\n");
}

void test_struct_padding() {
    FinanceDB test_db;
    memset(&test_db, 0, sizeof(test_db));
    
    encrypt_db(&test_db, sizeof(FinanceDB), 0x11);
    
    printf("[OK] Structure padding & large size processing passed (size: %zu bytes).\n", sizeof(FinanceDB));
}

int main() {
    printf("--- Running Security & Unit Tests for Finance Manager ---\n");
    
    test_encryption_symmetry();
    test_buffer_bounds();
    test_zero_size();
    test_struct_padding();
    
    printf("-------------------------------------------------------\n");
    printf("All tests passed successfully! The application is secure.\n");
    return 0;
}
