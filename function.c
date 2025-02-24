#include <stdio.h>
#include <string.h>
#include "function.h"
#include <stdlib.h>
int current = 0, count = 0;
Book books[MAX_BOOK];
Member members[MAX_MEMBR];


void showBookMenu(){
	system("color e");
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

//10,30,30,10,10,20.
void showListBook(Book *book, int current){
	FILE *file = fopen("book.bin","rb");
	if(file == NULL){
		printf("Cannot open file!");
		return;
	}
	
	printf("\n\t\t\t\t\t\t*******All book*******\n");
	printf("|==========|==============================|==============================|==========|==========|====================|\n");
	printf("|    %-6s|             %-17s|            %-18s| %-9s|  %-8s|  %-18s|\n", "Id", "Title", "Author", "Quantity", "Price", "Date publication");
	printf("|==========|==============================|==============================|==========|==========|====================|\n");
	for(int i = 0; i < current; i++){
		char rs[11];
		snprintf(rs, sizeof(rs), "%d/%d/%d", book[i].publication.day, book[i].publication.month, book[i].publication.year);
		
		printf("|%-10s|%30s|%30s|%10d|%10d|%20s|\n", book[i].bookid, book[i].title, book[i].author, book[i].quantity, book[i].price, rs);
		printf("|----------|------------------------------|------------------------------|----------|----------|--------------------|\n");
	}
	fclose(file);
	return;
};


void saveFile(char *filePath){
	FILE *fileBook = fopen(filePath,"wb");
	if(fileBook == NULL){
		printf("Cannot open file!");
		exit(1);
	}
	
	fwrite(&current, sizeof(int), 1, fileBook);
	
	if(current > 0){
		fwrite(&books, sizeof(books), current, fileBook);	
	}
	fclose(fileBook);
	return;
};

void openFile(char *filePath){
	FILE *fileBook = fopen(filePath,"rb");
	if(fileBook == NULL){
		printf("Cannot open file!");
		exit(1);
	}
	
	fread(&current, sizeof(int), 1, fileBook);
	
	if(current > 0){
		fread(&books, sizeof(books), current, fileBook);	
	}
	fclose(fileBook);
	return;
};

void addBook(Book *book, int *current){
    while(1) {
        char id[10];
        checkChar(id, 11, "enter the id");
            
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
            break;
        }
    }    
    while(1){
        char title[30];
        checkChar(title, 29, "enter the title");

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
            checkChar(book[*current].author, 29, "enter the author");
            checkInt(&book[*current].quantity, "enter the quantity");
            checkInt(&book[*current].price, "enter the price");
            checkInt(&book[*current].publication.day, "enter the Day");
            checkInt(&book[*current].publication.month, "enter the Month");
            checkInt(&book[*current].publication.year, "enter the Year");

            (*current)++;
            break;
        }			
    } 	
	saveFile("book.bin");
	printf("\nSuccessfully added book\n");
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
	    while(1){
	        char title[30];
	        checkChar(title, 29, "enter the title");
	
	        int checkTitle = 0;
	        for(int j = 0; j < current; j++){
	            if(strcmp(title, book[j].title) == 0){
	                checkTitle = 1;
	                break;
	            }
	        }
	        if(checkTitle){
	            printf("\nTitle cannot be duplicated!\n");
	            continue;
	        } else {
	            strcpy(book[i].title, title);
	            checkChar(book[i].author, 29, "enter the author");
	            checkInt(&book[i].quantity, "enter the quantity");
	            checkInt(&book[i].price, "enter the price");
	            checkInt(&book[i].publication.day, "enter the Day");
	            checkInt(&book[i].publication.month, "enter the Month");
	            checkInt(&book[i].publication.year, "enter the Year");
	            
	            break;
	        }
	    }			
	}
	saveFile("book.bin");
	printf("\nfix success!\n"); //sua thanh cong
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
					saveFile("book.bin");
					printf("\nDelete Successfully\n"); //Xóa thanh cong
					return;
				default:
					printf("\nChoose 0 or 1!\n");
					break;		
			}
		}
	}
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
	while(1) {
		fflush(stdin);
		printf("%s: ", input);
		if (fgets(value1, sizeof(value1), stdin) == NULL) {
			printf("Error!\n");
			continue;
		}
		value1[strcspn(value1, "\n")] = '\0';
				
		if (strlen(value1) >= max) {
			printf("Error, exceeding character limit!\n");
			continue;
		}
		if(value1[0] == '\0'){
			printf("cannot be left blank!\n");
			continue;
		}
		strcpy(value, value1);
		break;
	}
};

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
};

//member
void showListMember(Member *member, int count){
    FILE *fileMember = fopen("member.bin", "rb");
    if(fileMember == NULL){
        printf("Cannot open file!\n");
        return;
    }

    printf("\n\t\t\t\t*******All member*******\n");
    printf("|==========|==============================|==============================|==========|\n");
    printf("|    %-6s|             %-17s|            %-18s| %-9s|\n", "Id", "Name", "Phone", "Status");
    printf("|==========|==============================|==============================|==========|\n");
    for(int i = 0; i < count; i++){
        printf("|%-10s|%30s|%30s|%10s|\n", member[i].memberId, member[i].name, member[i].phone, member[i].status ? "Dang hoat dong":"Da khoa");
        printf("|----------|------------------------------|------------------------------|----------|\n");      
    }
    fclose(fileMember);
}

void showCustomersMenu(){
	system("color e");
	int choice;
	
	while(true){
		system("cls");
		
		printf("\n========MENU MEMBER========\n");
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
				showListMember(members, count);
				break;
			case 2:
				addMember(members, &count);
				break;
			case 3:
				fixMember(members, count);
				break;
			case 4:
				break;
			case 5:
				searchMember(members, count);
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

void addMember(Member *member, int *count){
    while(1) {
        char id[11];
        checkChar(id, 11, "enter the id");
            
        int checkId = 0; 
        for(int i = 0; i < *count; i++){
            if(strcmp(id, member[i].memberId) == 0){
                checkId = 1;
                break;                                        
            } 
        }
        if(checkId){
            printf("\nid cannot be duplicated!\n");
            continue; 
        } else {
            strcpy(member[*count].memberId, id);
            break;
        }
    }
    checkChar(member[*count].name, 19, "enter the name");
    while(1){
        char phone[10];
        checkChar(phone, 11, "enter the phone");

        int checkPhone = 0;
        for(int i = 0; i < *count; i++){
            if(strcmp(phone, member[i].phone) == 0){
                checkPhone = 1;
                break;
            }
        }
        if(checkPhone){
            printf("\nPhone cannot be duplicated!\n");
            continue;
        } else {
            strcpy(member[*count].phone, phone);
            member[*count].status = 0;
            (*count)++;
            break;
        }			
    } 
	saveFileMember("member.bin");
	printf("\nSuccessfully added book\n");
	return;	
};

void fixMember(Member *member, int count){
	char id[10];
	int i = 0;
	printf("enter the id: ");
	fflush(stdin);
	fgets(id, 10, stdin);
	id[strcspn(id,"\n")] = '\0';
	int checkId = 1;
	for(; i < count; i++){
		if(strcmp(id, member[i].memberId) == 0){
			checkId = 0;
			break;										
		} 
	}
	if(checkId){
		printf("\nid does not exist!\n"); //id khong ton tai
	}else{
	    checkChar(member[i].name, 19, "enter the name");
	    checkChar(member[i].phone, 11, "enter the phone");
	    member[i].status = 0;
	}
	saveFileMember("member.bin");
	printf("\nfix success!\n"); //sua thanh cong
	return;			
};

void searchMember(Member *member, int count){
	char name[20];
	printf("Enter the title: ");
	fflush(stdin);
	fgets(name, 20, stdin);
	name[strcspn(name,"\n")] = '\0';	
	
	printf("\n\t\t\t\t*******All member*******\n");
	printf("|==========|==============================|==============================|==========|\n");
	printf("|    %-6s|             %-17s|            %-18s| %-9s|\n", "Id", "Name", "Phone", "Status");
	printf("|==========|==============================|==============================|==========|\n");	
	for(int i = 0; i < count; i++){
		if(strstr(member[i].name,name) != NULL){
			printf("|%-10s|%30s|%30s|%10s|\n", member[i].memberId, member[i].name, member[i].phone, member[i].status ? "Dang hoat dong":"Da khoa");
			printf("|----------|------------------------------|------------------------------|----------|\n");	
		}
	}
	return;
};
