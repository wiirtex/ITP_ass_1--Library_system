#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Customer {
	char name[50];
	int age;
	float customer_rate;
	struct Customer* next;
};

typedef struct Customer user;

void append_c(user* head, char name[50], int age, float customer_rate) {

	if (head->next == NULL) {
		user* new_nd = (user*)(malloc(sizeof(user)));
		new_nd->next = NULL;
		strcpy(new_nd->name, name);
		new_nd->age = age;
		new_nd->customer_rate = customer_rate;
		(head)->next = new_nd;
		return;
	}
	user* now = head->next;
	while (now->next != NULL) {
		now = now->next;
	}
	user* new_nd = (user*)(malloc(sizeof(user)));
	new_nd->next = NULL;
	strcpy(new_nd->name, name);
	new_nd->age = age;
	new_nd->customer_rate = customer_rate;
	now->next = new_nd;
	return;
}

void print_c(user* head) {
	printf("\n<----------------------->\nCustomers in System:\n\n");
	if (head->next == NULL) {
		printf("The library is empty for now. Sorry");
	}
	else {
		user now = *(head->next);
		printf("%s, age: %d; rate: %.2f\n", now.name, now.age, now.customer_rate);
		while (now.next != NULL) {
			now = *(now.next);
			printf("%s, age: %d; rate: %.2f\n", now.name, now.age, now.customer_rate);
		}
	}
	printf("\n<----------------------->\n\n");
}

void remove_c(user* head, char name[50]) {
	if (head->next == NULL) {
		return;
	}
	user* now = head->next;
	user* prev = head;
	while (strcmp(now->name, name) != 0) {
		if (now->next == NULL) {
			return;
		}
		prev = now;
		now = now->next;
	}
	prev->next = now->next;
	free(now);
	return;
}

void update_customer(user* head) {
	if (head->next == NULL) {
		printf("\nThere are no customers in library. Nothing to edit\n\n");
		return;
	}
	char prev_name[50];
	printf("\nPlease, write the name of the customer, that you want to edit: ");
	scanf("%*c");
	gets(prev_name);
	user* now = head->next;
	while (strcmp(now->name, prev_name) != 0) {
		if (now->next == NULL) {
			printf("\nThis book is not in the library\n");
			return;
		}
		now = now->next;
	}
	char tmp[50];
	char author[50];
	int age;
	float customer_rate;
	printf("Editing a customer %s:  -- If you want to edit identifier, write it. If not, write a '0' --\nName: ", now->name);
	//scanf("%*c");
	gets(tmp);
	if (tmp[0] != '0') {
		strcpy(now->name, tmp);
	}
	printf("Age: ");
	scanf("%d", &age);
	if (age != 0) {
		now->age = age;
	}
	printf("Customer rate: ");
	scanf("%f", &customer_rate);
	if (customer_rate > 1e-5) {
		now->customer_rate = customer_rate;
	}

	printf("Edited!\n");
}

void remove_customer(user* head) {
	if (head->next == NULL) {
		printf("\nThere are no customers in the library. Noone can be removed\n\n");
		return;
	}
	char name_to_remove[50];
	printf("\nPlease, write the name of the customer, whose information you want to remove: ");
	scanf("%*c");
	gets(name_to_remove);
	remove_c(head, name_to_remove);
	printf("\nRemoved!\n");
	return;
}

void add_user(user* head) {
	char name[50];
	int age;
	float customer_rate;
	printf("\nAdding a customer:\nName: ");
	scanf("%*c");
	gets(&name);
	printf("Age: ");
	scanf("%d", &age);
	printf("Customer rate: ");
	scanf("%f", &customer_rate);
	append_c(head, name, age, customer_rate);
}

struct Book {
	char title[60];
	char author[50];
	int year;
	float book_rate;
	struct Book* next;
};

int append_b(struct Book* head, char title[60], char author[50], int year, float book_rate) {

	if (head->next == NULL) {
		struct Book* new_nd = (struct Book*)(malloc(sizeof(struct Book)));
		new_nd->next = NULL;
		strcpy(new_nd->title, title);
		strcpy(new_nd->author, author);
		new_nd->book_rate = book_rate;
		new_nd->year = year;
		(head)->next = new_nd;
		return -1;
	}
	struct Book* now = head->next;
	while (now->next != NULL) {
		now = now->next;
	}
	struct Book* new_nd = (struct Book*)(malloc(sizeof(struct Book)));
	new_nd->next = NULL;
	strcpy(new_nd->title, title);
	strcpy(new_nd->author, author);
	new_nd->book_rate = book_rate;
	new_nd->year = year;
	now->next = new_nd;
	return 0;
}

void print_b(struct Book* head) {
	printf("\n<----------------------->\nBooks in System:\n\n");
	if (head->next == NULL) {
		printf("The library is empty for now. Sorry");
	}
	else {
		struct Book now = *(head->next);
		printf("%s, %s, %d year; rate: %.2f\n", now.author, now.title, now.year, now.book_rate);
		while (now.next != NULL) {
			now = *(now.next);
			printf("%s, %s, %d year; rate: %.2f\n", now.author, now.title, now.year, now.book_rate);
		}
	}
	printf("\n<----------------------->\n\n");
}

int remove_b(struct Book* head, char title[60]) {
	if (head->next == NULL) {
		return -1;
	}
	struct Book* now = head->next;
	struct Book* prev = head;
	while (strcmp(now->title, title) != 0) {
		if (now->next == NULL) {
			return;
		}
		prev = now;
		now = now->next;
	}
	prev->next = now->next;
	free(now);
	return 0;
}

void update_book(struct Book* head) {
	if (head->next == NULL) {
		printf("\nThere are no books in library. Nothing to edit\n\n");
		return;
	}
	char prev_title[60];
	printf("\nPlease, write the title of the book, that you want to edit: ");
	scanf("%*c");
	gets(prev_title);
	struct Book* now = head->next;
	while (strcmp(now->title, prev_title) != 0) {
		if (now->next == NULL) {
			printf("\nThis book is not in the library\n");
			return;
		}
		now = now->next;
	}
	char tmp[60];
	char title[60];
	char author[50];
	int year;
	float book_rate;
	printf("Editing a book %s:  -- If you want to edit identifier, write it. If not, write a '0' --\nTitle: ", now->title);
	//scanf("%*c");
	gets(tmp);
	if (tmp[0] != '0') {
		strcpy(now->title, tmp);
	}
	printf("Author: ");
	gets(tmp);
	if (tmp[0] != '0') {
		strcpy(now->author, tmp);
	}
	printf("Year: ");
	scanf("%d", &year);
	if (year != 0) {
		now->year = year;
	}
	printf("Book rate: ");
	scanf("%f", &book_rate);
	if (book_rate > 1e-5) {
		now->book_rate = book_rate;
	}

	printf("Edited!\n");
}

void remove_book(struct Book* head) {
	if (head->next == NULL) {
		printf("\nThere are no books in library. Nothing to edit\n\n");
		return;
	
	}
	char title_to_edit[60];
	printf("\nPlease, write the title of the book, that you want to edit: ");
	scanf("%*c");
	gets(title_to_edit);
	remove_b(head, title_to_edit);
	printf("\nRemoved!\n");
	return;
}

void add_book(struct Book* head) {
	char title[60];
	char author[50];
	int year;
	float book_rate;
	printf("\nAdding a book:\nTitle: ");
	scanf("%*c");
	gets(title);
	printf("Author: ");
	gets(author);
	printf("Year: ");
	scanf("%d", &year);
	printf("Book rate: ");
	scanf("%f", &book_rate);
	append_b(head, title, author, year, book_rate);
}

int main() {
	printf("The Linked List Library System by Timur Iakhshigulov t.iakhshigulov@innopolis.university\nInnopolis University, Russia\n2020 year\n\nAny key to continue.\n");
	scanf("%*c");
	printf("Menu:\n    0: Help;\n    1: Show all books in system;\n    2: Add new book;\n    3: Update a book;\n    4: Remove a book;");
	printf("\n    5: Show Customers;\n    6: Add new Customer;\n    7: Update a Customer;\n    8: Update a Customer;\n    9: Exit;\n");
	struct Book null_book = { "", "", 0, 0, NULL };
	user null_customer = { "", 0, 0, NULL };
	int command = 0;
	do {
		printf("\nPlease, write a new command. 0 for help\n");
		printf("command: ");
		scanf("%d", &command);
		switch (command) {
		case 1: {
			print_b(&null_book);
			break;
		}
		case 2: {
			add_book(&null_book);
			break;
		}
		case 3: {
			update_book(&null_book);
			break;
		}
		case 4: {
			remove_book(&null_book);
			break;
		}
		case 5: {
			print_c(&null_customer);
			break;
		}
		case 6: {
			add_user(&null_customer);
			break;
		}
		case 7: {
			update_customer(&null_customer);
			break;
		}
		case 8: {
			remove_customer(&null_customer);
			break;
		}
		case 9: {
			break;
		}
		case 0: {
			printf("    0: Help;\n    1: Show all books in system;\n    2: Add new book;\n    3: Update a book;\n    4: Remove a book;");
			printf("\n    5: Show Customers;\n    6: Add new Customer;\n    7: Update a Customer;\n    8: Update a Customer;\n    9: Exit;\n\n");
			printf("Print number of function to start work.\n\n");
			break;
		}
		default:
			printf("The System can not work with this command. You should write number from 1 to 9. Type 0 for help");
			break;
		}
	} while (command != 9);
	printf("Thank you for using our library system. \n");
	return 0;
}