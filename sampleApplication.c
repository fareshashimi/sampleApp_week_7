#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int accountNum;
    char name[20];
    char surname[20];
    double balance;
}node;

int insertChoice(void);
void textFile(FILE *);
void recUpdate(FILE *);
void newRecord(FILE *);
void recDelete(FILE *);
void printFiles(FILE *);

int main(){
    FILE *mp;
    int c;
    
    if((mp = fopen("customer.dat", "r+"))==NULL){
        printf("\n\n The file is not found in the computer.\n");
        return 0;
    }
    else{
        while((c = insertChoice()) != 6){
            switch(c){
                case 1:
                    textFile(mp);
                break;
                
                case 2:
                    recUpdate(mp);
                break;
                
                case 3:
                    newRecord(mp);
                break;
                
                case 4:
                    recDelete(mp);
                break;
                
                case 5:
                    printFiles(mp);
                break;    
            }
        }
        fclose(mp);
    }
    
    return 0;
}

int insertChoice(){
    int menuC;
    printf("1.The content of the customer.dat.\n2.Update the account.\n3.Add the new account.\n4.Delete the file.\n5.Print the contents of the customer.dat.\n6.Exit.\n\n");
    printf("Select your choice: ");
    scanf("%d", &menuC);
    printf("\n\n");
    
    return menuC;
}

void textFile(FILE *mp){
    FILE *wp;
    
    node accountInfo = {0, "", "", 0.0};
    if((wp = fopen("accounts.dat", "w"))==NULL){
        printf("\n\n The file is not opend.\n");
    }
    else{
        rewind(mp);
        fprintf(wp, "%s  -  %s %s  -  %.2s\n", "accountNum", "name", "surname", "balance");
        while(!feof(wp)){
            fread(&accountInfo, sizeof(node), 1, wp);
            if(accountInfo.accountNum!=0){
                fprintf(wp, "%d  -  %s %s  -  %.2f\n", accountInfo.accountNum, accountInfo.name, accountInfo.surname, accountInfo.balance);
            }
        }
        fclose(wp);
    }
}

void recUpdate(FILE *mp){
    int accountID;
    double tAmount;
    
    node accountInfo = {0, "", "", 0.0};
    printf("Insert the account number to be updated [1 - 100]:\n");
    scanf("%d", &accountID);
    
    fseek(mp, (accountID-1)*sizeof(node), SEEK_SET);
    fread(&accountInfo, sizeof(node), 1, mp);
    
    if(accountInfo.accountNum==0){
        printf("\n\n There is no information about account %d has been inserted for.\n", accountID);
    }
    else{
        printf("%d  -  %s %s  -  %.2f\n", accountInfo.accountNum, accountInfo.name, accountInfo.surname, accountInfo.balance);
        printf("\nInsert the amount to be deposited (+) or withdrawn (-) from the account:\n");
        scanf("%lf", &tAmount);
        
        accountInfo.balance += tAmount;
        
        printf("%d  -  %s %s  -  %.2f\n", accountInfo.accountNum, accountInfo.name, accountInfo.surname, accountInfo.balance);
        
        fseek(mp, (accountID-1)*sizeof(node), SEEK_SET);
        fwrite(&accountInfo, sizeof(node), 1, mp);
    }
}

void recDelete(FILE *mp){
    node accountInfo, empAccount = {0, "", "", 0.0};
    int accountID;
    
    printf("Insert the account number to be deleted [1 - 100]:\n");
    scanf("%d", &accountID);
    
    fseek(mp, (accountID-1)*sizeof(node), SEEK_SET);
    fread(&accountInfo, sizeof(node), 1, mp);
    
    if(accountInfo.accountNum==0){
        printf("\n\n There is no account %d to delete.\n", accountID);
    }
    else{
        fseek(mp, (accountID-1)*sizeof(node), SEEK_SET);
        fwrite(&empAccount, sizeof(node), 1, mp);
    }
}

void newRecord(FILE *mp){
    int accountID;
    node accountInfo = {0, "", "", 0.0};
    
    printf("Insert the new account number [1 - 100]:\n");
    scanf("%d", &accountID);
    
    fseek(mp, (accountID-1)*sizeof(node), SEEK_SET);
    fread(&accountInfo, sizeof(node), 1, mp);
    
    if(accountInfo.accountNum!=0){
        printf("\n\n Account %d is already exists.\n", accountID);
    }
    else{
        printf("Insert name, surname and balance:\n");
        scanf("%s%s%lf", accountInfo.name, accountInfo.surname, accountInfo.balance);
        
        fseek(mp, (accountID-1)*sizeof(node), SEEK_SET);
        fwrite(&accountInfo, sizeof(node), 1, mp);
    }
}

void printFiles(FILE *mp){
    node accountInfo = {0, "", "", 0.0};
    
    printf("%s  -  %s %s  -  %.2s\n", "accountNum", "name", "surname", "balance");
    while(!feof(mp)){
        fread(&accountInfo, sizeof(node), 1, mp);
        if(accountInfo.accountNum!=0){
            printf("%d  -  %s %s  -  %.2f\n", accountInfo.accountNum, accountInfo.name, accountInfo.surname, accountInfo.balance);
        }
        fclose(mp);
    }
    getchar();
}