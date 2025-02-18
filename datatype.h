#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_BOOK 100
#define MAX_MEMBR 100

typedef struct {
	int month,day,year;
} Date;

typedef struct {
	char bookid[10];
	char title[30];
	char author[30];
	int quantity;
	int price;
	Date publication;
} Book;

typedef struct {
	char memberId[10];
	char name[20];
	char phone[10];
	int status; // tinh trang
	Book Borrowedbooks[10]; // Sach muon
} Member;
