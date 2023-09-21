//Jeremy Odor
//C21302913

#define _CRT_SECURE_NO_WARNINGS 1

#define bool int
#define false 0
#define true (!false)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>



#define MAX_Books 5
/*
void loadData() {
	FILE* file = fopen("book.dat", "rb");
	if (file == NULL) {
		printf("Book database not found.\n");
		return;
	}

	// Read the book data from the file and add it to the linked list
	struct book book_data;
	while (fread(&book_data, sizeof(struct book), 1, file) == 1) {
		struct LinearNode* new_node = (struct LinearNode*)malloc(sizeof(struct LinearNode));
		new_node->element = (struct book*)malloc(sizeof(struct book));
		memcpy(new_node->element, &book_data, sizeof(struct book));
		new_node->next = NULL;

		if (front == NULL) {
			front = new_node;
			last = new_node;
		}
		else {
			last->next = new_node;
			last = new_node;
		}
	}

	fclose(file);
	printf("Book database loaded from file.\n");
}

void saveData() {
	FILE* file = fopen("book.dat", "wb");
	if (file == NULL) {
		printf("Error saving book database to file.\n");
		return;
	}

	// Write the book data from the linked list to the file
	struct LinearNode* current = front;
	while (current != NULL) {
		fwrite(current->element, sizeof(struct book), 1, file);
		current = current->next;
	}

	fclose(file);
	printf("Book database saved to file.\n");
}

*/



struct LinearNode* front = NULL; //front of the list

struct LinearNode* last = NULL; //pointer to last node in the list - not used in this code

struct book {
	char identifier[9];   // book identifier (8 digit number + null terminator)
	char name[50];       // book name (up to 100 characters)
	char author[50];      // book author (up to 50 characters)
	int year;             // year of publication (cannot be older than 2017)
	bool is_loaned;       // whether the book is currently loaned out or not
	char customer_name[100];// customer name if the book is loaned out, otherwise empty string
	int num_loans;        // number of times the book has been loaned out
};

struct LinearNode {
	struct book* element;
	struct LinearNode* next;
	

	 
};


void addBook();
void borrowBook();
void returnBook();
void deleteBook();
void viewAllBooks();
void viewSpecificBook();
void viewMostAndLeastPopularBooks();
void searchByAuthor();

int main()
{
	
	int menuOption;
	printf("Library Menu\n\n");
	printf("1. Add a new book to library\n");
	printf("2. Borrow a Book\n");
	printf("3. Return a Book\n"); 
	printf("4. Delete a Book from the Library\n");
	printf("5. View All Books\n");
	printf("6.View a Specific Book\n");
	printf("7.Display Most Popular and Least Popular Books\n");
	printf("8.Search by Author\n");
	printf("9. Exit System\n\n");

	printf("Which option would you like to proceed with?: ");
	scanf("%d", &menuOption);

	if (menuOption == 1) {
		addBook();
	}
	else if (menuOption == 2) {
		borrowBook();
	}
	else if (menuOption == 3) {
		returnBook();
	}
	else if (menuOption == 4) {
		deleteBook();
	}
	else if (menuOption == 5) {
		viewAllBooks();
	}
	else if (menuOption == 6) {
		viewSpecificBook();
	}
	else if (menuOption == 7) {
		viewMostAndLeastPopularBooks();
	}
	else if (menuOption == 8) {
		searchByAuthor();
	}
	else if (menuOption == 9) {
		printf("Exiting program...\n");
		return 0;
	}
    else {
		system("cls");
		printf("Invalid option selected\n");

		// Wait for 2 seconds
		Sleep(2000);
		// Clear the console screen
		system("cls");
		// Return to the main menu
		main();
	}




	getchar();
    getchar();

}

 void addBook()
{
	 system("cls");
	 int count = 0;
	 
	 struct LinearNode* current = front;
	 while (current != NULL)
	 {
		 count++;
		 current = current->next;
	 }
	 if (count == MAX_Books)
	 {
		 printf("Maximum number of books have been reached");
		 // Wait for 2 seconds
		 Sleep(2000);
		 // Clear the console screen
		 system("cls");
		 // Return to the main menu
		 main();
	 }

	 struct book new_book;

	 int valid_input = 0;
	 do {
		 printf("Enter book identifier (8 digit number in the form xxxx-xxxx): ");
		 scanf("%s", new_book.identifier);
		 valid_input = 1;
		 for (int i = 0; i < strlen(new_book.identifier); i++) {
			 if (!isdigit(new_book.identifier[i])) {
				 printf("Error: Invalid input. Book identifier must be a number.\n");
				 valid_input = 0;
				 break;
			 }
		 }
		 if (strlen(new_book.identifier) != 8) {
			 printf("Error: Invalid input. Book identifier must be exactly 8 digits.\n");
			 valid_input = 0;
		 }
	 } while (!valid_input);

	 // Check if identifier is unique
	 current = front;
	 
	while (current != NULL) {
			 if (strcmp(current->element->identifier, new_book.identifier) == 0) {

			 printf("Error: Book with identifier %s already exists\n", new_book.identifier);
			 // Wait for 2 seconds
			 Sleep(2000);
			 // Clear the console screen
			 system("cls");
			 // Return to the main menu
			 main();
		 }
		 current = current->next;
	 }
	 

	 printf("Enter book name: ");
	 scanf(" %[^\n]", new_book.name);

	 printf("Enter book author: ");
	 scanf(" %[^\n]", new_book.author);

	 printf("Enter year of publication (cannot be older than 2017): ");
	 scanf("%d", &new_book.year);

	 do {
		 printf("Enter year of publication (cannot be older than 2017): ");
		 if (scanf("%d", &new_book.year) != 1) {
			 printf("Error: Invalid input. Please enter a valid year.\n");
			 while (getchar() != '\n'); // clear the input buffer
			 continue;
		 }

		 if (new_book.year < 2017) {
			 printf("Error: Year of publication cannot be older than 2017\n");
		 }
	 } while (new_book.year < 2017);
	 ;



	 new_book.is_loaned = false;
	 strcpy(new_book.customer_name, "");
	 new_book.num_loans = 0;

	 // Create a new node for the book and add it to the linked list
	 struct LinearNode* new_node = (struct LinearNode*)malloc(sizeof(struct LinearNode));
	 new_node->element = (struct book*)malloc(sizeof(struct book));
	 *(new_node->element) = new_book;
	 new_node->next = NULL;

	 

	 if (front == NULL) {
		 front = new_node;
	 }
	 else {
		 struct LinearNode* current = front;
		 while (current->next != NULL) {
			 current = current->next;
		 }
		 current->next = new_node;
	 }
	 


	 printf("Book added successfully\n");

	 // Wait for 2 seconds
	 Sleep(2000);
	 // Clear the console screen
	 system("cls");
	 // Return to the main menu
	 main();



}


 void borrowBook()
 {
	 system("cls");
	 char identifier[9];
	 printf("Enter book identifier: ");
	 scanf("%s", identifier);

	 // Find the book with the given identifier
	 struct LinearNode* current = front;
	 while (current != NULL) {
		 if (strcmp(current->element->identifier, identifier) == 0) {
			 // Book found, check if it's loaned or not
			 if (current->element->is_loaned) {
				 printf("Error: Book with identifier %s is already loaned\n", identifier);
				 // Wait for 2 seconds
				 Sleep(2000);
				 // Clear the console screen
				 system("cls");
				 // Return to the main menu
				 main();
			 }
			 else {
				 // Book is available, update loan status and customer name
				 printf("Enter your name: ");
				 scanf("%s", current->element->customer_name);
				 current->element->num_loans++;
				 printf("Book %s borrowed successfully\n", identifier);
				 current->element->is_loaned = true;
				 // Wait for 2 seconds
				 Sleep(2000);
				 // Clear the console screen
				 system("cls");
				 // Return to the main menu
				 main();

			 }
			 
		 }
		 current = current->next;
	 }
	 


	 // Book not found
	 printf("Error: Book with identifier %s not found\n", identifier);
	 // Wait for 2 seconds
	 Sleep(2000);
	 // Clear the console screen
	 system("cls");
	 // Return to the main menu
	 main();
 }




 void returnBook()
 {
	 system("cls");
	 char identifier[9];
	 printf("Enter book identifier: ");
	 scanf("%s", identifier);

	 char customerName[100];
	 printf("Enter your name: ");
	 scanf("%s", customerName);

	 // Find the book with the given identifier
	 struct LinearNode* current = front;
	 while (current != NULL) {
		 if (strcmp(current->element->identifier, identifier) == 0) {
			 // Book found, check if it's loaned and if it's loaned to the customer
			 if (current->element->is_loaned && strcmp(current->element->customer_name, customerName) == 0) {
				 // Book is loaned to the customer, update loan status and customer name
				 current->element->is_loaned = false;
				 strcpy(current->element->customer_name, "");
				 printf("Book %s returned successfully by %s\n", identifier, customerName);

				 // Wait for 2 seconds
				 Sleep(2000);
				 // Clear the console screen
				 system("cls");
				 // Return to the main menu
				 main();
			 }
			 else if (!current->element->is_loaned) {
				 // Book is not loaned
				 printf("Error: Book with identifier %s is not loaned\n", identifier);

				 // Wait for 2 seconds
				 Sleep(2000);
				 // Clear the console screen
				 system("cls");
				 // Return to the main menu
				 main();
			 }
			 else {
				 // Book is loaned but not to this customer
				 printf("Error: Book with identifier %s is not loaned to %s\n", identifier, customerName);

				 // Wait for 2 seconds
				 Sleep(2000);
				 // Clear the console screen
				 system("cls");
				 // Return to the main menu
				 main();
			 }
		 }
		 current = current->next;
	 }
	 


	 // Book not found
	 printf("Error: Book with identifier %s not found\n", identifier);

	 // Wait for 2 seconds
	 Sleep(2000);
	 // Clear the console screen
	 system("cls");
	 // Return to the main menu
	 main();
 }


 void deleteBook()
 {
	 system("cls");
	 char identifier[9];
	 printf("Enter book identifier: ");
	 scanf("%s", identifier);

	 // Find the book with the given identifier
	 struct LinearNode* current = front;
	 struct LinearNode* previous = NULL;
	 while (current != NULL) {
		 if (strcmp(current->element->identifier, identifier) == 0) {
			 // Book found, check if it's old enough to be deleted
			 if (current->element->year < 2010) {
				 // Book is old enough to be deleted, remove it from the list
				 if (previous == NULL) {
					 // Book is at the front of the list
					 front = current->next;
				 }
				 else {
					 // Book is in the middle or at the end of the list
					 previous->next = current->next;
				 }
				 //De-Allocate memory of the book
				 free(current);
				 printf("Book with identifier %s deleted successfully\n", identifier);

				 // Wait for 2 seconds
				 Sleep(2000);
				 // Clear the console screen
				 system("cls");
				 // Return to the main menu
				 main();
			 }
			 else {
				 printf("Error: Book with identifier %s is too recent to be deleted\n", identifier);

				 // Wait for 2 seconds
				 Sleep(2000);
				 // Clear the console screen
				 system("cls");
				 // Return to the main menu
				 main();
			 }
			 
		 }
		 previous = current;
		 current = current->next;
	 }
	 


	 // Book not found
	 printf("Error: Book with identifier %s not found\n", identifier);

	 // Wait for 2 seconds
	 Sleep(2000);
	 // Clear the console screen
	 system("cls");
	 // Return to the main menu
	 main();
 }




 void viewAllBooks() {
	 system("cls");
	 if (front == NULL) {
		 printf("No books in library\n");
		 // Wait for 2 seconds
		 Sleep(2000);
		 // Clear the console screen
		 system("cls");
		 // Return to the main menu
		 main();
	 }

	 struct LinearNode* current = front;
	 while (current != NULL) {

		 printf("Displaying All Books.........\n");
		 Sleep(2000);

		 printf("Identifier: %s\n", current->element->identifier);
		 printf("Name: %s\n", current->element->name);
		 printf("Author: %s\n", current->element->author);
		 printf("Year of Publication: %d\n\n", current->element->year);
		 current = current->next;
	 }

	 // Wait for 5 seconds
	 Sleep(5000);
	 // Clear the console screen
	 system("cls");
	 // Return to the main menu
	 main();
 }


 void viewSpecificBook() {
	 system("cls");

	 if (front == NULL) {
		 printf("No books in library\n");
		 // Wait for 2 seconds
		 Sleep(2000);
		 // Clear the console screen
		 system("cls");
		 // Return to the main menu
		 main();
	 }

	 char identifier[9];
	 printf("Enter the book identifier: ");
	 scanf("%s", identifier); 

	 struct LinearNode* current = front;
	 while (current != NULL) {
		 if (strcmp(current->element->identifier, identifier) == 0) {
			 // Book found, display its details
			 printf("Identifier: %s\n", current->element->identifier);
			 printf("Name: %s\n", current->element->name);
			 printf("Author: %s\n", current->element->author);
			 printf("Year of Publication: %d\n", current->element->year);
			 // Wait for 5 seconds
			 Sleep(5000);
			 // Clear the console screen
			 system("cls");
			 // Return to the main menu
			 main();
		 }
		 current = current->next;
	 }

	 // Book not found
	 printf("Book with identifier %s not found\n", identifier);
	 // Wait for 2 seconds
	 Sleep(2000);
	 // Clear the console screen
	 system("cls");
	 // Return to the main menu
	 main();
 }



 void viewMostAndLeastPopularBooks() {
	 system("cls");

	 
	 if (front == NULL) {
		 
		 printf("No books in library\n");
		 // Wait for 2 seconds
		 Sleep(2000);
		 // Clear the console screen
		 system("cls");
		 // Return to the main menu
		 main();
	 }
	 struct LinearNode* current = front;
	 struct book* most_popular = current->element;
	 struct book* least_popular = current->element;

	 while (current != NULL) {
		 if (current->element->num_loans > most_popular->num_loans) {
			 most_popular = current->element;
		 }
		 if (current->element->num_loans < least_popular->num_loans) {
			 least_popular = current->element;
		 }
		 current = current->next;
	 }

	 printf("Most popular book:\n");
	 printf("Identifier: %s\n", most_popular->identifier);
	 printf("Name: %s\n", most_popular->name);
	 printf("Author: %s\n", most_popular->author);
	 printf("Year of publication: %d\n", most_popular->year);
	 printf("Number of times loaned: %d\n", most_popular->num_loans);

	 printf("\nLeast popular book:\n");
	 printf("Identifier: %s\n", least_popular->identifier);
	 printf("Name: %s\n", least_popular->name);
	 printf("Author: %s\n", least_popular->author);
	 printf("Year of publication: %d\n", least_popular->year);
	 printf("Number of times loaned: %d\n", least_popular->num_loans);

	 // Wait for 5 seconds
	 Sleep(5000);
	 // Clear the console screen
	 system("cls");
	 // Return to the main menu
	 main();
 }






 void searchByAuthor() {

	 system("cls");

	 if (front == NULL) {

		 printf("No books in library\n");
		 // Wait for 2 seconds
		 Sleep(2000);
		 // Clear the console screen
		 system("cls");
		 // Return to the main menu
		 main();
	 }

	 char author[50];
	 

	 printf("Enter the name of the author: ");
	 scanf("%s", author);
	

	

	 printf("\nBooks written by %s:\n", author);
	 struct LinearNode* current = front;

	 while (current != NULL) {
		 if (strcmp(current->element->author, author) == 0) {
			 printf("%s (ID: %s, Year: %d)\n", current->element->name, current->element->identifier, current->element->year);
			 
			 // Wait for 5 seconds
			 Sleep(5000);
			 // Clear the console screen
			 system("cls");
			 // Return to the main menu
			 main();
		 }
		 current = current->next;
	 }

	 	printf("No books found written by %s.\n", author);
		 // Wait for 2 seconds
		 Sleep(2000);
		 // Clear the console screen
		 system("cls");
		 // Return to the main menu
		 main();
	 
 }


