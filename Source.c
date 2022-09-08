/************************************
 * C - Program to manage dictionary *
 * Coded by: Nasir Alden			*
 * Zionet-Ma'ase Bootcamp           *
 * 08/09/2022                       *
 ************************************/

#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <conio.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

// structure of basic node (item) in the dictionary
struct Item {
	int id;
	int key;
	int val;
	struct Item* next;
	struct Item* prev;
};

struct Item* head = NULL;
struct Item* tail = NULL;

// Functions declarations.
// All functions were written after main function.
void freeList();   // Function to free dynamic memory of linked list.
void printDict(); // Function to print the whole dictionary.
struct Item* search(int key);  // Function to search items in dictionary by key.
void add(int key, int val);  // Function to add items to dictionary.
void removeFromDict(int key); // Function to remove item from dictionary by key.


void main()
{
	char op;
	int key, val;

	// Multichoice Main Menu of the program.
	printf("\n***** Zionet Dictionary System *******\n\n");
	printf("Choose an operation to do:\n");
	printf("A) Add item to the dictionary.\n");
	printf("S) Search item by key in the dictionary.\n");
	printf("R) Remove item from dictionary.\n");
	printf("P) Print dictionary.\n");
	printf("E) Exit.\n");
	scanf(" %c",&op);

	while (toupper(op) != 'E')
	{
		switch (toupper(op)) {
		case 'A':
			printf("Insert key and value to add item to dictionary:\n");
			scanf("%d%d", &key, &val);
			add(key, val);
			system("cls");
			break;
		case 'S':
			printf("insert key to search item ?");
			scanf("%d", &key);
			search(key);
			break;

		case 'R':
			printf("insert key to remove item ?");
			scanf("%d", &key);
			removeFromDict(key);
			break;

		case 'P':
			system("cls");
			printDict();
			break;
		
		}
		if (toupper(op) != 'E') { // Show menu again if not Exitied.
			printf("\n***** Zionet Dictionary System *******\n\n");
			printf("Choose an operation to do:\n");
			printf("A) Add item to the dictionary.\n");
			printf("S) Search item by key in the dictionary.\n");
			printf("R) Remove item from dictionary.\n");
			printf("P) Print dictionary.\n");
			printf("E) Exit.\n");
			scanf(" %c", &op);
		}
	}
	printf(" Thanks for using our Dictionary Application. GoodBye!\n");

	freeList();  //Free allocated memory before exit from program !
}


void add(int key, int val) {
	struct Item* currentItem;
	struct Item* prevItem=tail ;
	int  id;

	currentItem = (struct Item*)malloc(sizeof(struct Item));
	

	if (head == NULL)
	{
		currentItem->id = 1;
		head=tail=prevItem=currentItem;
	}
	else
	{
		prevItem->next = currentItem;
		currentItem->id = (prevItem->id) + 1;
	}
	
	currentItem->key = key;
	currentItem->val = val;
	currentItem->next = NULL;
	tail = currentItem;
}


void freeList()
{
	struct Item* currentItem = head;
	struct Item* releaseItem = head;
	while (currentItem != NULL)
	{
		releaseItem = currentItem;
		currentItem = currentItem->next;
		free(releaseItem);
	}
}

void printDict() {
	struct Item* currentItem = head;
	struct Item* printItem = head;
	printf("********* Print List ***********\n");
	printf("\nHead-->");
	while (currentItem != NULL)
	{
		printItem = currentItem;
		printf("(id%d[%d:%d]) -> ", printItem->id, printItem->key, printItem->val);
		currentItem = currentItem->next;
	}
	printf("NULL\n\n");
}


struct Item* search(int key) {
	struct Item* currentItem = head;
	int runIndex = 1;
	int foundIndex = 1;
	printf("********* Find key = %d ***********\n", key);
	while (currentItem != NULL)
	{
		if (currentItem->key == key) {
			foundIndex = runIndex;
			printf("item key %d was found at node number [%d].\n", key, foundIndex);
			printf("Memory Address: %p\n", currentItem);
			printf("it's value is : %d \n", currentItem->val);
			return currentItem;
		}
		currentItem = currentItem->next;
		runIndex++;
	}
	printf("No item was found that has key=%d .\n", key);
	return NULL;
}

void removeFromDict(int key) {
	struct Item* currentItem = head;
	struct Item* ptrToRemove;
	ptrToRemove = search(key);
	while (currentItem->next != NULL) {
		if (currentItem->next == ptrToRemove) {
			if (ptrToRemove->next == NULL) { //if item is tail
				tail = currentItem;
				currentItem->next = NULL;
				free(ptrToRemove);
			}
			else {
				struct Item* nextItem = ptrToRemove->next;
				currentItem->next = ptrToRemove->next;
				nextItem->prev = currentItem;
				free(ptrToRemove);
			}	
			printf("Item was removed !\n");
			return;
		}		
		currentItem = currentItem->next;
	}
	printf("There is no item with key=%d to remove", key);
}





