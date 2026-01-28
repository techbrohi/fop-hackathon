/*
Mandatory Programming Concepts
Each project must clearly demonstrate the use of all the following C programming concepts:
1. Functions – Modular design and separation of logic
2. Arrays – Storage of multiple records
3. Strings – Handling names, descriptions, or textual data
4. Pointers – Used with arrays, functions, or structures
5. Structures – Representation of real-world entities
6. File Handling – Persistent storage using files (read/write/update)

Project Type & Scope
• The project must be a Management System (e.g., student, library, hospital, inventory,
etc.).
• The system should allow users to store, update, search, delete, and display records.
• The application must be menu-driven and console-based.

Title: Online Student Management System.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#define MAX_QUIZES 100
#define TOTAL_FIELDS 5
typedef struct Quiz_Structure {
char q_name[50];
unsigned int id;
bool hascompleted; /* 1 = true, 0 = false*/
} Quiz_s;

typedef struct User_Structure {
char u_name[50];
unsigned int u_id;
bool isActive;
Quiz_s quiz_details[MAX_QUIZES];
} User_s;

void saveToFile(User_s users[], unsigned int user_quantity, unsigned int quiz_quantity){
FILE *saveFile = fopen("saveToFileFuncCall.bin", "wb");
if (saveFile == NULL){
perror("Failed to Open File");
return;
}
//fwrite(*datatowrite, sizeofdata, quantityofdata, wheretowritedata);
//fread(*datatoread, sizeofdatatoread, quantityofdatatoread, wheretoreadthedata);
size_t uqb = fwrite(&user_quantity, sizeof(unsigned int), 1, saveFile);
size_t qqb = fwrite(&quiz_quantity, sizeof(unsigned int), 1, saveFile);
size_t aqb = fwrite(users, sizeof(User_s), user_quantity, saveFile);  // suppose 4 * 20. 80 bytes in total. 80/4 = 20 bytes each element.
printf("Total Items Wrote to File: %zu\n", uqb+aqb+qqb);
fclose(saveFile);
}
void loadFromFile(User_s **users, unsigned int *user_quantity, unsigned int *quiz_quantity){

FILE *loadFile = fopen("saveToFileFuncCall.bin", "rb");
if (loadFile == NULL){
perror("Failed to Open File");
}
size_t uqb = fread(user_quantity, sizeof(unsigned int), 1, loadFile);
size_t qqb = fread(quiz_quantity, sizeof(unsigned int), 1, loadFile);
if (uqb != 1 || qqb != 1){
printf("Error reading User and Quiz Quantity from the file.\n");
}

printf("Attempting to Load %u Users from File.\n", *user_quantity);
// CRITICAL: Allocate Memory Bytes to the array in correspondence to the items read to avoid segfault:
*users = malloc(*user_quantity * sizeof(User_s));

size_t aqb = fread(*users, sizeof(User_s), *user_quantity, loadFile);
if (aqb != uqb){
printf("Error reading Users. Total Users: %zu, Read only: %zu\n", uqb, aqb);
}
/* **users.
users = actual value.
*users = pointer to users, address of users.
**users = pointer to pointer to users, address of the pointer itself. Is used to manipulate where the pointer points as Pointer holds the memory address of the value it points to.
we used users to access the value, *users to access the users variable address, **users to access the address of the pointer itself.
When we took a **users parameter in the function, we essentially could access the value, and the address of the value.
We don't use a single pointer because then the function manipulates a copy of the original data, not the original data.
When we have a double pointer, we have access to the actual memory address of the value, not a copy of it, and can directly manipulate
it from a function.*/

}
void singleUserDisplay(User_s user, int quiz_quantity, int user_index){

    // Print user details ONCE per user
int i;
    printf("\t\tUser Index: %d\n", user_index);
    printf("\t\tYour User Details:\n");
    printf("1. Your Account Username: %s\n", user.u_name);
    printf("2. Your Account User ID: %u\n", user.u_id);
    
    // Then print all their quizzes
    printf("\t\tYour Quiz Details:\n");
    for (i=0; i<quiz_quantity; i++) {  // Quizzes loop
        printf("\t\tQuiz %d:\t\t\n", i+1);
        printf("3. Quiz ID: %u\n", user.quiz_details[i].id);
        printf("4. Quiz Title: %s\n", user.quiz_details[i].q_name);
        printf("5. Status: %d\n", user.quiz_details[i].hascompleted);
        printf("\n");
    }
    sleep(2);
}

void clearBuffer(){
int c;
while((c = getchar()) != '\n' && c != EOF){
/*clear buffer*/
}
}
void displayRecords(User_s user[],int user_n, int quiz_quantity){
int i,j;
for (j=0; j<user_n; j++) {        // Users loop
    // Print user details ONCE per user
   if(user[j].isActive){
    printf("\t\tUser Index: %d\n", j);
    printf("\t\tYour User Details:\n");
    printf("1. Your Account Username: %s\n", user[j].u_name);
    printf("2. Your Account User ID: %u\n", user[j].u_id);
    int count=3;
    // Then print all their quizzes
    printf("\t\tYour Quiz Details:\n");
    for (i=0; i<quiz_quantity; i++) {  // Quizzes loop
        printf("\t\tQuiz %d:\t\t\n", i+1);
        printf("%d. Quiz ID: %u\n",count++, user[j].quiz_details[i].id);
        printf("%d. Quiz Title: %s\n",count++, user[j].quiz_details[i].q_name);
        printf("%d. Status: %d\n",count++, user[j].quiz_details[i].hascompleted);
        printf("\n");


    }

    sleep(2);  // Sleep after each user, not each quiz
}
}
}
void inputUserStruct(User_s user[], int user_n, int quiz_n){
int i,j;

    
    for (i = 0; i < user_n; i++) {
        printf("\n===User Number: %d===\n", i);
	clearBuffer();        
        // User details
        printf("Enter Your Username: ");
        fgets(user[i].u_name, 50, stdin);
        user[i].u_name[strcspn(user[i].u_name, "\n")] = '\0';  // Remove newline
 	user[i].isActive = 1;
        printf("Enter Your User ID: ");
        scanf("%u", &user[i].u_id);
        clearBuffer();
        

        
        // Quiz details
        for (j = 0; j < quiz_n; j++) {
            printf("\n--- Quiz %d ---\n", j + 1);
            
            printf("Enter Quiz Name: ");
            fgets(user[i].quiz_details[j].q_name, 50, stdin);
            user[i].quiz_details[j].q_name[strcspn(user[i].quiz_details[j].q_name, "\n")] = '\0';
            
            printf("Enter Quiz ID: ");
            scanf("%u", &user[i].quiz_details[j].id);
            
            printf("Enter Completion Status (1 for yes, 0 for no): ");
            scanf("%d", &user[i].quiz_details[j].hascompleted);
            
            clearBuffer();
        }
        printf("=================\n");
    }
printf("Stored User and Quiz Details.\n");

}
void updateUDFunc(User_s *users, int user_index, int update_choice){
User_s *user = &users[user_index];
user->u_name[strcspn(user->u_name, "\n")] = '\0';
if (update_choice > 0 && update_choice <= 2){
switch(update_choice){
case 1:
	clearBuffer();
	printf("Current Username: %s, Updated Username: ", user->u_name);
	fgets(user->u_name, 50, stdin);
	break;

case 2:
	printf("Current ID: %u, Updated User ID: ", user->u_id);
	scanf("%u", &user->u_id);
	break;
default:
	printf("Invalid field");
	break;
}
}

}

void updateQDFunc(User_s *users, int user_index, int field_index, int quiz_index){
User_s *user = &users[user_index];
Quiz_s *quiz = &users[user_index].quiz_details[quiz_index];
quiz->q_name[strcspn(quiz->q_name, "\n")] = '\0';


switch(field_index){
case 0:
	printf("Current Quiz ID: %u, Updated Quiz ID: ", quiz->id);
	scanf("%u", &quiz->id);
	clearBuffer();
	break;
case 1:
	clearBuffer();
	printf("Current Quiz Title: %s, Updated Quiz Title: ", quiz->q_name);
	fgets(quiz->q_name, 50, stdin);
	break;
case 2:
	printf("Current Quiz Completion Status: %d, Updated Quiz Completion Status: ", quiz->hascompleted);
	scanf("%d", &quiz->hascompleted);
	break;
default:
	printf("Invalid Choice");
	break;
}

}
int searchByUserID(User_s users[], int uid, int users_arrbound, int quiz_n){
int i;
for(i=0; i<users_arrbound; i++){
if(users[i].u_id == uid){
singleUserDisplay(users[i], quiz_n, i);
return i;
}
}
return -1;
}

void deleteUserByIndex(User_s *users, int uindex){
users->isActive = 0;
printf("User Deleted.\n");
}
int main(){
unsigned int user_quantity=0;
unsigned int quiz_quantity=0;
unsigned int update_choice=0;
unsigned int menu_choice=0;
unsigned int update_selective=0;
unsigned int update_uindex=0;
unsigned int update_qindex=0;
unsigned int search_by_userid=0;
unsigned int delete_index=0;
User_s *users = NULL;
while(menu_choice !=  8){
printf("\t\tONLINE QUIZ MANAGEMENT SYSTEM\t\t\n");
printf("Available Options:\n");
printf("1. Input Quiz and User Details\n");
printf("2. Delete User/Quiz Details\n");
printf("3. Update User/Quiz Details\n");
printf("4. Display User/Quiz Details\n");
printf("5. Search for a Specific Username\n");
printf("6. Store User and Quiz Data in a file\n");
printf("7. Load Data from File.\n");
printf("8. Exit\n");
printf("Enter your choice: ");
scanf("%u", &menu_choice);
sleep(0.5);
if (menu_choice == 8){
printf("Exiting Gracefully...\n");
sleep(1);
return 0;
}
if (menu_choice == 1){
printf("Enter User Quantity to input: ");
scanf("%u", &user_quantity);
printf("Enter Quiz Quantity to input: ");
scanf("%u", &quiz_quantity);
users = malloc(user_quantity * sizeof(User_s)); // users point to the first byte of User_s struct. malloc gives contiguous memory blocks so user becomes an array of User_s struct.
if (users == NULL){
printf("Memory Allocation Failed.\n");
return 1;
}
inputUserStruct(users, user_quantity, quiz_quantity);
sleep(0.5);

}
if ( menu_choice == 4){
if(users == 0) {
printf("No active users to list.\n");
continue;
}
printf("Displaying All Active User and Quiz Information...\n");
sleep(0.5);
displayRecords(users, user_quantity, quiz_quantity);
}
if ( menu_choice == 3){
if (users == NULL){
printf("No Active Users Found.\n");
continue;
}
displayRecords(users, user_quantity, quiz_quantity);
printf("Enter User Index to Update: ");
scanf("%u", &update_uindex);
if (update_uindex < 0 || update_uindex > user_quantity){
printf("Invalid User Index. Index must be within Bounds.\n");
continue;
}
printf("Enter Sequence Number of the field you want to update: ");
scanf("%u", &update_selective);
if(update_selective > 0 && update_selective <=2){
updateUDFunc(users, update_uindex, update_selective);
}
else if (update_selective > 2){
update_qindex=(update_selective - 3)/3; // gives quotient.
int field_index = (update_selective-3)%3; // gives remainder.
if (update_qindex >= quiz_quantity){
	printf("Invalid Quiz Index.\n");
	continue;
}
updateQDFunc(users, update_uindex,field_index, update_qindex);
}

}
if (menu_choice == 5){
if(users == NULL){
printf("No Active users in the List.\n");
continue;
}
printf("Enter User ID to Search: ");
scanf("%u", &search_by_userid);

int found = searchByUserID(users, search_by_userid, user_quantity, quiz_quantity);
if (found != -1){
printf("User found at Index: %d\n", found);
}
else{
printf("Error: User ID did not matched any known User.\n");
}
}
if (menu_choice == 2){
if(users == NULL){
printf("No Active Users Found.\n");
continue;
}
displayRecords(users, user_quantity, quiz_quantity);
printf("Enter the Index of the User you want to DELETE: ");
scanf("%u", &delete_index);
if (delete_index >=0 && delete_index < user_quantity){
deleteUserByIndex(&users[delete_index], delete_index);
}
else {
printf("Error: Invalid Index Number.\n");
}
}
if (menu_choice == 6){
if(users == NULL){
printf("No Active Users to Save.\n");
continue;
}
saveToFile(users, user_quantity, quiz_quantity);
}
if (menu_choice == 7){
if (users != NULL){
printf("WARNING: This Action will OVERWRITE Existing Data. Do you want to Continue (y/n)? ");
clearBuffer();
char choice = getchar();

if (choice == 'y' || choice == 'Y') free(users);
if (choice != 'y' && choice != 'Y') continue;
}
loadFromFile(&users, &user_quantity, &quiz_quantity);
}
}
// since users is an array now, we free it with free(users) to take back the following allocated bytes in supposition:.
// it has a limit of, suppose 5 * 20 = 40 bytes, 40/4 = 10 bytes each element.
free(users);
return 0;
}

