#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void checkbalance(char*);
void transfermoney(void);
void display(char*);
void person(char*);
void login(void);
void loginsu(void);
void account(void);
void accountcreated(void);
void afterlogin(void);
void logout(void);

// Set cursor position
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Structure for user data
struct pass {
    char username[50];
    int date, month, year;
    char pnumber[15];
    char adharnum[20];
    char fname[20];
    char lname[20];
    char fathname[20];
    char mothname[20];
    char address[50];
    char typeaccount[20];
};

// Structure for money transfer data
struct money {
    char usernameto[50];
    char userpersonfrom[50];
    long int money1;
};

struct userpass {
    char password[50];
};

// Main function
int main()
{
    int choice;

    gotoxy(20, 3);
    printf("WELCOME TO BANK SYSTEM\n\n");
    gotoxy(18, 5);
    printf("**********************************");
    gotoxy(25, 7);
    gotoxy(20, 10);
    printf("1. CREATE ACCOUNT");
    gotoxy(20, 12);
    printf("2. LOGIN");
    gotoxy(20, 14);
    printf("3. EXIT\n\n");

    printf("\n\nENTER CHOICE: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        system("cls");
        printf("\n\nUSERNAME 50 CHARS MAX!!");
        printf("\n\nPASSWORD 50 CHARS MAX!!");
        account();
        break;
    case 2:
        login();
        break;
    case 3:
        exit(0);
        break;
    default:
        printf("\nInvalid choice. Please try again.\n");
        break;
    }
}

// Account creation
void account(void)
{
    char password[50];  // Adjusted size to match the input loop
    int i;
    char ch;
    FILE *fp;
    struct pass u1;
    fp = fopen("userdetail.txt", "ab");

    system("cls");
    printf("\n\nCREATE ACCOUNT");
    printf("\n\nFIRST NAME: ");
    scanf("%s", u1.fname);
    printf("\n\nLAST NAME: ");
    scanf("%s", u1.lname);
    printf("\n\nFATHER'S NAME: ");
    scanf("%s", u1.fathname);
    printf("\n\nMOTHER'S NAME: ");
    scanf("%s", u1.mothname);
    printf("\n\nADDRESS: ");
    scanf("%s", u1.address);
    printf("\n\nACCOUNT TYPE: ");
    scanf("%s", u1.typeaccount);
    printf("\n\nDATE OF BIRTH\nDATE: ");
    scanf("%d", &u1.date);
    printf("MONTH: ");
    scanf("%d", &u1.month);
    printf("YEAR: ");
    scanf("%d", &u1.year);
    printf("\n\nADHAR NUMBER: ");
    scanf("%s", u1.adharnum);
    printf("\n\nPHONE NUMBER: ");
    scanf("%s", u1.pnumber);
    printf("\n\nUSERNAME: ");
    scanf("%s", u1.username);

    printf("\n\nPASSWORD: ");
    for (i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            password[i] = ch;
            printf("*");
        } else {
            break;
        }
    }
    password[i] = '\0';  
    fwrite(&u1, sizeof(u1), 1, fp);
    fclose(fp);
    accountcreated();
}

// Account creation confirmation
void accountcreated(void)
{
    int i;
    system("cls");
    printf("PROCESSING...\n");
    for (i = 0; i < 200000000; i++) {
        i++;
        i--;
    }
    gotoxy(30, 10);
    printf("ACCOUNT CREATED SUCCESSFULLY");
    getch();
    login();
}

// Login functionality
void login(void)
{
    system("cls");
    char username[50];
    char password[50];
    int i;
    char ch;
    FILE *fp;
    struct pass u1;
    fp = fopen("userdetail.txt", "rb");

    if (fp == NULL) {
        printf("ERROR IN OPENING FILE");
        return;
    }

    gotoxy(34, 2);
    printf("LOGIN");
    gotoxy(35, 12);
    printf("USERNAME: ");
    scanf("%s", username);
    gotoxy(35, 14);
    printf("PASSWORD: ");
    for (i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            password[i] = ch;
            printf("*");
        } else {
            break;
        }
    }
    password[i] = '\0';  
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username, u1.username) == 0) {
            loginsu();
            display(username);
            fclose(fp);
            return;
        }
    }

    printf("\n\nInvalid username or password. Please try again.\n");
    fclose(fp);
}

// After successful login
void loginsu(void)
{
    int i;
    system("cls");
    printf("LOADING ACCOUNT...\n");
    for (i = 0; i < 20000; i++) {
        i++;
        i--;
    }
    gotoxy(30, 10);
    printf("LOGIN SUCCESSFUL");
    getch();
}

// Display account information
void display(char username1[])
{
    system("cls");
    FILE* fp;
    fp = fopen("userdetail.txt", "rb");
    struct pass u1;

    if (fp == NULL) {
        printf("ERROR OPENING FILE");
        return;
    }

    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username1, u1.username) == 0) {
            gotoxy(30, 1);
            printf("WELCOME, %s %s", u1.fname, u1.lname);
        }
    }

    fclose(fp);
}

// Transfer money
void transfermoney(void)
{
    int i, j;
    FILE *fm, *fp;
    struct pass u1;
    struct money m1;
    char usernamet[50], usernamep[50];
    system("cls");

    fp = fopen("userdetail.txt", "rb");
    fm = fopen("money.txt", "ab");

    gotoxy(33, 4);
    printf("TRANSFER MONEY");
    gotoxy(33, 11);
    printf("FROM: ");
    scanf("%s", usernamet);
    gotoxy(33, 13);
    printf("TO: ");
    scanf("%s", usernamep);
    int senderExists = 0, receiverExists = 0;
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(usernamet, u1.username) == 0) {
            senderExists = 1;
        }
        if (strcmp(usernamep, u1.username) == 0) {
            receiverExists = 1;
            strcpy(m1.usernameto, u1.username);
            strcpy(m1.userpersonfrom, usernamet);
        }
    }
    if (senderExists && receiverExists) {
        gotoxy(33, 16);
        printf("AMOUNT: ");
        scanf("%ld", &m1.money1);
        fwrite(&m1, sizeof(m1), 1, fm);
       gotoxy(33, 18);
        printf("TRANSACTION SUCCESSFUL");
    } else {
        gotoxy(33, 18);
        printf("TRANSACTION FAILED: Invalid usernames.");
    }

    fclose(fp);
    fclose(fm);
}