/**********************************************************************

Timur Iakhshigulov. BS20-06. Innopolis University, Innopolis, Russia. the end of project: 20.09.2020

***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**********************************************************************

My linked list is working kind of strange. Nobody know where is the end of it.
So, the append()-function, like others goes through full list to get to the last element.

So every operation with my linked list is working with time of O(n);

I have 2 different lists for Customers and Books, so we have two sets of almost identically functions for both categories (for ex. append_c() and append_b()).
This makes code longer.

Linked list contains all elements and one null element, which is head of list:
	head -> first_elem -> second_elem -> ... -> last_elem -> NULL

***********************************************************************/

int random_useless_variable = 1;	// this variable is not used in the program

struct Customer {		// Customer structure
	char name[50];
	int age;
	float customer_rate;
	struct Customer* next;
};

typedef struct Customer user; // now struct Customer is user

void append_c(user* head, char name[50], int age, float customer_rate) {
	/*
		append_c is creating new Customer and appending it to the end of list.

		:: user* head - pointer to the null element of the customers list
		:: char name[50] - name of Customer
		:: int age - age of Customer (any integer)
		:: float customer_rate - customer's rate (any float)
	*/
	if (head->next == NULL) {
		/*
			If  list is empty, my program does this:
				head -> new_elem;
		*/
		user* new_user = (user*)(malloc(sizeof(user))); // new_nd = new node of linked list
		new_user->next = NULL; // new_elem = last_elem => new_elem -> NULL
		strcpy(new_user->name, name);
		new_user->age = age;
		new_user->customer_rate = customer_rate;
		(head)->next = new_user;
		return;
	}
	/*
			Else, my program does this:
				last_elem -> new_elem;
	*/
	user* now = head->next;
	while (now->next != NULL) {
		now = now->next;	//iterating until last element
	}
	user* new_user = (user*)(malloc(sizeof(user)));	// new_nd = new node of linked list
	new_user->next = NULL;
	strcpy(new_user->name, name);
	new_user->age = age;
	new_user->customer_rate = customer_rate;
	now->next = new_user;		// now = last_elem -> new node
	return;
}

void print_c(user* head) {
	/*
		print_c() prints all elements of list of Customers from first till last

		:: user* head - pointer to the null element of the customers list
	*/
	printf("\n<----------------------->\nCustomers in System:\n\n");	// printing some visual things
	if (head->next == NULL) {
		printf("The library is empty for now. Sorry");					// if library is empty now (head -> NULL = last_elem)
	}
	else {
		user now = *(head->next);										// take and prints first element
		printf("%s, age: %d; rate: %.2f\n", now.name, now.age, now.customer_rate);
		while (now.next != NULL) {
			now = *(now.next);											// take and prints all elements except first
			printf("%s, age: %d; rate: %.2f\n", now.name, now.age, now.customer_rate);
		}
	}
	printf("\n<----------------------->\n\n");	// printing some visual things
}

int remove_c(user* head, char name[50]) {
	/*
		remove_c() is deleting Customer with EXACT name from library. If there is not that name in library it returns to MAIN MENU;

		:: user* head - pointer to the null element of the customers list
		:: char name[50] - name of Customer who should be deleted

		Returns 0 if removing failed, else 1.
	*/

	// this fuction should be called only after the checking, that list is not empty

	user* now = head->next;		// iterating through all customers
	user* prev = head;
	while (strcmp(now->name, name) != 0) {	// tryind to find that we should remove
		if (now->next == NULL) {			// if get to the end of array we just return;
			return 0;
		}
		prev = now;
		now = now->next;
	}
	prev->next = now->next;		// connect previous and next
	free(now);					// make memory free again
	return 1;
}

void update_customer(user* head) {
	/*
		update_customer() - updating (but not necessary) any information about the customer.
			Identifies a the customer using his (or her) name.

		:: head - starting node of the list of customers
	*/
	if (head->next == NULL) {		// if the list is empty
		printf("\nThere are no customers in library. Noone can be edited\n\n");
		return;
	}
	char prev_name[50];
	printf("\nPlease, write the name of the customer, that you want to edit: ");
	scanf("%*c");
	gets(prev_name);
	user* now = head->next;			// iterating through all customers
	while (strcmp(now->name, prev_name) != 0) {		// tryind to find that we should update
		if (now->next == NULL) {					// if get to the end of array we just return;
			printf("\nThis book is not in the library\n");
			return;
		}
		now = now->next;
	}
	char tmp[50];			        //
	auto int age;				  //
	float customer_rate;		 //
	printf("Editing a customer %s:  -- If you want to edit identifier, write it. If not (except customer rate), write a '0' --\nName: ", now->name);
	/*
			If you don't want to edit some information about the customer, you can just type 0, and his information
				will not change.

			Why 0?
			  - because no title or author's name starting with 0
			  - because there is no year with zero number
	*/
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
	now->customer_rate = customer_rate;

	printf("Edited!\n");
}

void remove_customer(user* head) {
	/*
		remove_customer() - remove all information about the customer
			Identifies a the customer using his (or her) name.

		:: head - starting node of the list of customers
	*/
	if (head->next == NULL) {	// checking if list is empty
		printf("\nThere are no customers in the library. Noone can be removed\n\n");
		return;
	}
	char name_to_remove[50];
	printf("\nPlease, write the name of the customer, whose information you want to remove: ");
	scanf("%*c");
	gets(name_to_remove);
	if (remove_c(head, name_to_remove)) {
		printf("\nRemoved!\n");
	}
	else {
		printf("\nThis customer is not in library!\n");
	}
	return;
}

void add_user(user* head) {
	/*
		add_user() - adding new customer, before getting useful info and then call an append_c()

		:: head - starting node of the list of customers
	*/
	char name[50];
	int age;
	float customer_rate;
	printf("\nAdding a customer:\nName: ");
	scanf("%*c");		// for parse \n
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
	/*
		append_b is creating new Book and appending it to the end of list.

		:: struct Book* head - pointer to the null element of the customers list
		:: char title[60] - title of the Book
		:: char author[50] - name of the Author
		:: int year -  (any integer)
		:: float book_rate - customer's rate (any float)
	*/
	if (head->next == NULL) {	// if list is empty, then we should create first element
		struct Book* new_nd = (struct Book*)(malloc(sizeof(struct Book)));
		new_nd->next = NULL;
		strcpy(new_nd->title, title);
		strcpy(new_nd->author, author);
		new_nd->book_rate = book_rate;
		new_nd->year = year;
		(head)->next = new_nd;
		return -1;
	}
	// if list is not empty, then we should create new element after the last element
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
	/*
		print_b() prints all elements of list of Books from first till last

		:: struct Book* head - pointer to the null element of the customers list
	*/
	printf("\n<----------------------->\nBooks in System:\n\n");
	if (head->next == NULL) {	//if list is empty
		printf("The library is empty for now. Sorry");
	}
	else {	// if not, then printing
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
	/*
		remove_b() is deleting Book with EXACT name from library. If there is not that name in library it returns to MAIN MENU;

		:: struct Book* head - pointer to the null element of the books list
		:: char title[60] - name of Customer who should be deleted

		Returns 0 if removing failed, else 1.
	*/

	// this function should be called only after checking that list is not empty

	struct Book* now = head->next;
	struct Book* prev = head;
	while (strcmp(now->title, title) != 0) {		// iterating through all elements
		if (now->next == NULL) {
			return 0;
		}
		prev = now;
		now = now->next;
	}
	prev->next = now->next;							// connecting previous element with new
	free(now);
	return 1;
}

void update_book(struct Book* head) {
	/*
		update_book() - updating (but not necessary) any information about the book.
			Identifies a the book using his (or her) title.

		:: head - starting node of the list of books
	*/
	if (head->next == NULL) {		// if list is empty
		printf("\nThere are no books in library. Nothing to edit\n\n");
		return;
	}
	// else:
	char prev_title[60];
	printf("\nPlease, write the title of the book, that you want to edit: ");
	scanf("%*c");
	gets(prev_title);
	struct Book* now = head->next;		// iterating through all books to find that one
	while (strcmp(now->title, prev_title) != 0) {
		if (now->next == NULL) {
			printf("\nThis book is not in the library\n");
			return;
		}
		now = now->next;
	}
	// local variables

	// <<<<<

	char tmp[60];
	auto year;
	float book_rate;

	// >>>>>

	printf("Editing a book %s:  -- If you want to edit identifier, write it. If not (except book rate), write a '0' --\nTitle: ", now->title);
	// this function is almost full copy of the update_customer() which is fully commented
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
	now->book_rate = book_rate;

	printf("Edited!\n");
}

void remove_book(struct Book* head) {
	/*
		remove_book() - remove all information about the book
			Identifies a the customer using his (or her) name.

		:: head - starting node of the list of customers
	*/
	if (head->next == NULL) {		// if list is empty
		printf("\nThere are no books in library. Nothing to remove\n\n");
		return;
	}
	char title_to_edit[60];
	printf("\nPlease, write the title of the book, that you want to remove: ");
	scanf("%*c");
	gets(title_to_edit);
	if (remove_b(head, title_to_edit)) {
		printf("\nRemoved!\n");
	}
	else {
		printf("\nThis book is not in library!\n");
	}
	return;
}

void add_book(struct Book* head) {
	/*
		almost full copy of add_customer() which is fully commented

		add_book() - adding new book, before getting useful info and then call an append_b()

		:: head - starting node of the list of customers
	*/
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

void output_hello_message() {
	/*
		output_hello_message() printing information about creator, and printing the menu
	*/
	printf("The Linked List Library System by Timur Iakhshigulov t.iakhshigulov@innopolis.university\nInnopolis University, Russia\n2020 year\n\nAny key to continue.\n");
	scanf("%*c");
	printf("Menu:\n    0: Help;\n    1: Show all books in system;\n    2: Add new book;\n    3: Update a book;\n    4: Remove a book;");
	printf("\n    5: Show Customers;\n    6: Add new Customer;\n    7: Update a Customer;\n    8: Update a Customer;\n    9: Exit;\n");

}

void print_help() {
	/*
			print_help() printing the help menu
	*/
	printf("\n    0: Help;\n    1: Show all books in system;\n    2: Add new book;\n    3: Update a book;\n    4: Remove a book;");
	printf("\n    5: Show Customers;\n    6: Add new Customer;\n    7: Update a Customer;\n    8: Update a Customer;\n    9: Exit;\n\n");
	printf("Print number of function to start work.\n\n");
}

void loop() {
	/*
		loop() is main part of the program, that coordinates all the program and allows it to work
	*/
	struct Book null_book = { "", "", 0, 0, NULL };		// initialising the null element of Books-List
	user null_customer = { "", 0, 0, NULL };			// initialising the null element of	Customers-List
	int command = 0;									// initialising the command variable
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
			// This does nothing
			break;
		}
		case 0: {
			print_help();
			break;
		}
		default:
			printf("The System can not work with this command. You should write number from 1 to 9. Type 0 for help");
			break;
		}
	} while (command != 9);
}

void output_goodbye_message() {
	/*
			output_goodbye_message() printing goodbye message
	*/
	printf("\nThank you for using our library system. \n");
}

int main() {
	output_hello_message();

	loop();

	output_goodbye_message();

	return 0;
}