#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX 100
#define MAX_LENGTH 100

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
	bool status; // tinh trang
	Book Borrowedbooks[]; // Sach muon
} Member;
