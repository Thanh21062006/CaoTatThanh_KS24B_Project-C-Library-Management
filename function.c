#include <stdio.h>
#include <string.h>
#include "function.h"
#include <stdlib.h>
 int current = 0;
Book books[MAX];

void showBookMenu(){
	int choice;
	
	while(true){
		system("cls");
		
		printf("\n========MENU BOOK========\n");
		printf("1. Show list of books\n");
		printf("2. Add book\n");
		printf("3. Edit book information\n");
		printf("4. Delete Book\n");
		printf("5. Search books by name\n");
		printf("6. Sort books by price\n");
		printf("7. return\n");
		
		printf("Enter the choice: ");
		scanf("%d", &choice);
		
		switch(choice){
				
			case 1:
				showListBook(books, current);
				break;
			case 2:
				addBook(books, &current);
				break;
			case 3:
				fixBook(books, current);
				break;
			case 4:
				deleteBook(books, &current);
				break;
			case 5:
				searchBook(books, current);
				break;
			case 6:
				sortBook(books, current);
				break;
			case 7:
				return;
			default:
				printf("Invaild choice!\n");
				break;			
		}
		while (1) {
			char answer = confirmExitOrBack();
			if (answer == '0') {
				return;
			}else if (answer == 'b') {
				break;
			}
		}	
	}
};

void showCustomersMenu(){
	int choice;
	
	while(true){
		printf("\n========MENU BOOK========\n");
		printf("1. Show list of customers\n");
		printf("2. Add customers\n");
		printf("3. Edit customers information\n");
		printf("4. lock (unlock) customers\n");
		printf("5. Search customers by name\n");
		printf("6. Book lending\n");  //Cho muon sach
		printf("7. Return borrowed books\n");  //Tra lai sach da muon
		printf("8. Return\n");
		
		printf("Enter the choice: ");
		scanf("%d", &choice);
		switch(choice){
				
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				return;
			default:
				printf("Invaild choice!\n");
				break;			
		}			
	}	
};

//10,30,30,10,10,20.
void showListBook(Book *book, int current){
	FILE *file = fopen("book.bin","rb");
	if(file == NULL){
		printf("Cannot open file!");
	}
	
	printf("\n\t\t\t\t\t\t******All book*******\n");
	printf("|==========|==============================|==============================|==========|==========|====================|\n");
	printf("|    %-6s|             %-17s|            %-18s| %-9s|  %-8s|   %-15s |\n", "Id", "Title", "Author", "Quantity", "Price", "Date publication");
	printf("|==========|==============================|==============================|==========|==========|====================|\n");
	for(int i = 0; i < current; i++){
		char rs[11];
		snprintf(rs, sizeof(rs), "%d/%d/%d", book[i].publication.day, book[i].publication.month, book[i].publication.year);
		
		printf("|%-10s|%30s|%30s|%10d|%10d|%20s|\n", book[i].bookid, book[i].title, book[i].author, book[i].quantity, book[i].price, rs);
		printf("|----------|------------------------------|------------------------------|----------|----------|--------------------|\n");
	}
	fclose(file);
};


void saveFile(){
	FILE *fileBook = fopen("book.bin","wb");
	if(fileBook == NULL){
		printf("Cannot open file!");
		exit(1);
	}
	
	fwrite(&current, sizeof(int), 1, fileBook);
	
	if(current > 0){
		fwrite(&books, sizeof(books), current, fileBook);	
	}
	fclose(fileBook);
};

void openFile(){
	FILE *fileBook = fopen("book.bin","rb");
	if(fileBook == NULL){
		printf("Cannot open file!");
		exit(1);
	}
	
	fread(&current, sizeof(int), 1, fileBook);
	
	if(current > 0){
		fread(&books, sizeof(books), current, fileBook);	
	}
	fclose(fileBook);
};

void addBook(Book *book, int *current){
{
    int check = 1;
    do {
        char id[10];
        checkChar(id, 10, "enter the id");
            
        int checkId = 0; 
        for(int i = 0; i < *current; i++){
            if(strcmp(id, book[i].bookid) == 0){
                checkId = 1;
                break;                                        
            } 
        }
        if(checkId){
            printf("\nid cannot be duplicated!\n");
            continue; 
        } else {
            strcpy(book[*current].bookid, id);

            char title[30];
            checkChar(title, 30, "enter the title");

            int checkTitle = 0;
            for(int i = 0; i < *current; i++){
                if(strcmp(title, book[i].title) == 0){
                    checkTitle = 1;
                    break;
                }
            }
            if(checkTitle){
                printf("\nTitle cannot be duplicated!\n");
                continue;
            } else {
                strcpy(book[*current].title, title);
                checkChar(book[*current].author, 30, "enter the author");
                checkInt(&book[*current].quantity, "enter the quantity");
                checkInt(&book[*current].price, "enter the price");
                checkInt(&book[*current].publication.day, "enter the Day");
                checkInt(&book[*current].publication.month, "enter the Month");
                checkInt(&book[*current].publication.year, "enter the Year");

                (*current)++;

                printf("\nSuccessfully added book\n");
                break;
            }
        }
    } while(check);
}
		
	saveFile();
	return;
};

void fixBook(Book *book, int current){
	char id[10];
	int i = 0;
	printf("enter the id: ");
	fflush(stdin);
	fgets(id, 10, stdin);
	id[strcspn(id,"\n")] = '\0';
	int checkId = 1;
	for(; i < current; i++){
		if(strcmp(id, book[i].bookid) == 0){
			checkId = 0;
			break;										
		} 
	}
	if(checkId){
		printf("\nid does not exist!\n"); //id khong ton tai
	}else{
		showBook(book, i);
		printf("\n");
		
		printf("enter the title: ");
		fgets(book[i].title,30,stdin);
		book[i].title[strcspn(book[i].title, "\n")] = '\0';
		printf("enter the author: ");
		fgets(book[i].author,30,stdin);
		book[i].author[strcspn(book[i].author, "\n")] = '\0';
		printf("enter the quantity: ");
		fflush(stdin);
		scanf("%d", &book[i].quantity);
		printf("enter the price: ");
		scanf("%d", &book[i].price);	
		printf("enter the Day: ");
		scanf("%d", &book[i].publication.day);
		printf("enter the month: ");
		scanf("%d", &book[i].publication.month);
		printf("enter the year: ");
		scanf("%d", &book[i].publication.year);	
		
		printf("\nfix success!\n"); //sua thanh cong
	}
	saveFile();
	return;	
};

void showBook(Book *book, int index){
	printf("\nTitle: %s\n", book[index].title);
	printf("Author: %s\n", book[index].author);
	printf("Quantity: %d\n", book[index].quantity);
	printf("Price: %d\n", book[index].price);
	printf("Date publication: %d/%d/%d\n", book[index].publication.day, book[index].publication.month, book[index].publication.year);
	
	return;
};

void deleteBook(Book *book, int *current){
	char id[10];
	int i = 0, select = 0;
	printf("enter the id: ");
	fflush(stdin);
	fgets(id, 10, stdin);
	id[strcspn(id,"\n")] = '\0';
	int checkId = 1;
	for(; i < *current; i++){
		if(strcmp(id, book[i].bookid) == 0){
			checkId = 0;
			break;										
		} 
	}
	if(checkId){
		printf("\nid does not exist!\n"); //id khong ton tai
	}else{
		while(true){
			printf("Enter select 1(Yes) 0(No): ");
			scanf("%d", &select);
			switch(select){
				case 0:
					printf("\nchoose successfully\n");
					return;
				case 1:
					for(int j = i; j < *current - 1; j++){
						book[j] = book[j+1];
					}
					(*current)--;
					printf("\nDelete Successfully\n"); //Xóa thanh cong
					return;
				default:
					printf("\nChoose 0 or 1!\n");
					break;		
			}
		}

	}
	saveFile();
	return;	
};

void searchBook(Book *book, int current){
	char title[30];
	printf("Enter the title: ");
	fflush(stdin);
	fgets(title, 30, stdin);
	title[strcspn(title,"\n")] = '\0';	
	
	printf("\n\t\t\t\t\t\t******Book Imformation*******\n");
	printf("|==========|==============================|==============================|==========|==========|====================|\n");
	printf("|    %-6s|             %-17s|            %-18s| %-9s|  %-8s|  %-18s|\n", "Id", "Title", "Author", "Quantity", "Price", "Date publication");
	printf("|==========|==============================|==============================|==========|==========|====================|\n");	
	for(int i = 0; i < current; i++){
		if(strstr(book[i].title,title) != NULL){
			printf("|%-10s|%30s|%30s|%10d|%10d|%13d/%d/%d|\n", book[i].bookid, book[i].title, book[i].author, book[i].quantity, book[i].price, book[i].publication.day, book[i].publication.month, book[i].publication.year);
			printf("|----------|------------------------------|------------------------------|----------|----------|--------------------|\n");	
		}
	}
	return;
};

void sortBook(Book *book, int current){
	int select = 0;
	while(1){
		printf("\n==========SORT MENU==========\n");
		printf("\t1. Ascending\n"); //Tang dan
		printf("\t2. Descending\n");  //Giam dan
		printf("\t0. return!\n");
		
		printf("Enter select: ");
		scanf("%d", &select);
		
		switch(select){
			case 1: {
				for(int i = 0;i < current - 1;i++){
					for(int j = 0;j < current - i - 1;j++){
						if(book[j].price > book[j+1].price){
							Book temp = book[j];
							book[j] = book[j+1];
							book[j+1] = temp;
						}
					}	
				}
				showListBook(books, current);
				return;	
			}
			case 2:{
				for(int i = 0;i < current - 1;i++){
					for(int j = 0;j < current - i - 1;j++){
						if(book[j].price < book[j+1].price){
							Book temp = book[j];
							book[j] = book[j+1];
							book[j+1] = temp;
						}
					}	
				}
				showListBook(books, current);
				return;				
			}
			case 0:
				return;
			default: 
				break;
		}
	}
};

char confirmExitOrBack() {
	char choice;
	printf(">> Go back(b)? or exit(0)?: ");
	fflush(stdin);
	scanf("%c", &choice);
	fflush(stdin);
	return choice;
};

void checkChar(char *value, int max, char *input) {
	char value1[max+1];
	do {
		fflush(stdin);
		printf("%s: ", input);
		fgets(value1, max+1, stdin);
		if (strlen(value1) == max) {
			printf("Error character limit exceeded!\n");
			continue;
		}else if (strcmp(value1, "\n") == 0) {
			printf("Do not enter empty!\n");
			continue;
		}
		value1[strcspn(value1, "\n")] = '\0';
		strcpy(value, value1);
		break;
	}while(1);
}

void checkInt(int *value, char *input) {
	int value1;
	do {
		fflush(stdin);
		printf("%s: ", input);
		scanf("%d", &value1);
		if (value1 < 0) {
			printf("number cannot be negative!\n");
			continue;
		}
		*value = value1;
		break;
	}while(1);	
}
