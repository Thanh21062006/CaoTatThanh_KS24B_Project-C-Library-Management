#include "datatype.h"

void showBookMenu();
void showCustomersMenu();
void showListBook(Book *book, int current);  //Hien thi danh sach

void addBook(Book *book, int *current);  //them thong tin

void fixBook(Book *book, int current);  //sua thong tin

void showBook(Book *book, int index);  //Hien thi thong tin sach

void deleteBook(Book *book, int *current);  //Xoa thong tin sach

void searchBook(Book *book, int current);

void sortBook(Book *book, int current);

void checkChar(char *value, int max, char *input);
void checkInt(int *value, char *input);



//file
void saveFile();
void openFile();

char confirmExitOrBack();
