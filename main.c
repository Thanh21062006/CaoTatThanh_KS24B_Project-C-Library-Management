#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	openFile();
	char username[20], password[20];
	int choice = 0;
	FILE *admin = fopen("Admin.txt", "r");
	if(admin == NULL){
		printf("Cannot open file!");
		return(0);
	}
	
	fgets(username,20,admin);
	username[strcspn(username, "\n")] = '\0';
	printf("%s", username);
	fgets(password,20,admin);
	password[strcspn(password, "\n")] = '\0';
	fclose(admin);
	
	while(1){
		char checkUsername[20], checkPassword[20];
		printf("--------HELLO WORD--------\n");
		printf("Welcome to the login page\n");
		printf("Enter uername: ");
		fgets(checkUsername, sizeof(checkUsername), stdin);
		checkUsername[strcspn(checkUsername, "\n")] = '\0';
		printf("Enter password: ");
		fgets(checkPassword, sizeof(checkPassword), stdin);
		checkPassword[strcspn(checkPassword, "\n")] = '\0';
		
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
				}
			
			}
			break;
		}else{
			printf("login falled!\n");
		}		
	}
	

	return 0;
}
