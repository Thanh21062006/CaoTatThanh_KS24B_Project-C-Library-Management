#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "function.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	openFile("book.bin");
	openFileMember("member.bin");
	char username[20], password[20], temp = 'l';
	int choice = 0, size = 0;
	FILE *admin = fopen("Admin.txt", "r");
	if(admin == NULL){
		printf("Cannot open file!");
		return(0);
	}
	
	fgets(username,20,admin);
	username[strcspn(username, "\n")] = '\0';
	fgets(password,20,admin);
	password[strcspn(password, "\n")] = '\0';
	fclose(admin);
	
	while(1){
		system("color e");
		char checkUsername[20] = "", checkPassword[20] = "";
		printf("--------HELLO WORD--------\n");
		printf("Welcome to the login page\n");
		
		printf("Enter uername: ");
		fgets(checkUsername, sizeof(checkUsername), stdin);
		checkUsername[strcspn(checkUsername, "\n")] = '\0';
		
		printf("Enter password: ");
        while(1) {
            temp = getch();
            if(temp == 13) {
                break;
            }
            printf("%c", temp);
            checkPassword[size] = temp;
            size++;
            printf("\b*");

        }
        checkPassword[size] = '\0';
		
		if(strcmp(username,checkUsername) == 0 && strcmp(password,checkPassword) == 0){
			printf("\nlogin successful\n");
			while(1){
				printf("\n======CHOOSE YOUR ROLE======\n");
				printf("[1]. Admin\n");
				printf("[2]. Member\n");
				printf("[0]. Exit!\n");
				
				printf("\nEnter the choice: ");
				scanf("%d", &choice);
				switch(choice){
					case 0:
						printf("\n============Thank you===========\n");
						printf("============See you soon========\n");
						return 0;
					case 1:
						showBookMenu();
						break;
					case 2:
						showCustomersMenu();
						break;
					default:
						printf("invalid choice!\n");
						break;
				}	
			}
			break;
		}else{
			printf("login falled!\n");
		}		
	}
	return 0;
}
