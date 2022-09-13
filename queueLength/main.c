/*
Author: Billy Gene Ridgeway
Date: Sept. 12th. 2022
Purpose: To learn how to calculate the length of a list.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This what is going to be in the queue.
typedef struct listitem {
	struct listitem *next;			// Pointer to the next item.
	struct listitem *prev;			// Pointer to the previous item.
	int data;						// Some integer data.
} LISTITEM;

// This is the queue 'header'.
typedef struct {
	struct listitem *first;			// Pointer to the 1st. item.
	struct listitem *last;			// Pointer to the last item.
} LISTHDR;

LISTHDR head;						// Our queue.

									// This puts an item in at the end of a queue.
void enqueue(LISTHDR *queue, LISTITEM *item) {
	LISTITEM *temp;

	temp = queue->last;				// Get the 'last' item in the queue and keep hold of it.
	queue->last = item;				// Put the item in the queue at the end.
	item->prev = temp;				// Link back to old 'last' item.
	item->next = (LISTITEM*)queue;	// Set the forward link of the new item.
	temp->next = item;				// Finally set the forward link of the old 'last' item to the new one.
}

// This removes an item from the front of a queue and returns the item or NULL if there are no more items.
LISTITEM *dequeue(LISTHDR *queue) {
	LISTITEM *temp;

	temp = queue->first;				// Get the 'first' item in the queue.
	if (temp == (LISTITEM*)queue) {		// If the head of the queue points to itself ...
		temp = NULL;					// ... then the queue is empty.	
	} else {
		queue->first = temp->next;		// Set the queue header to point to the 'second' item.
		queue->first->prev = (LISTITEM*)queue;
	}
	return temp;
}

// Returns the number of items in a queue.
int queue_length(LISTHDR *queue) {
	LISTITEM *temp;
	int length;

	temp = queue->first;			// Get the 'first' item.
	length = 0;						// Initialize the length.
	do {
		// Check for an empty queue or if we've gone through the whole queue.
		if (temp == (LISTITEM*)queue) {
			temp = NULL;			// This will break out of the do ... while loop.
			break;
		}
		temp = temp->next;			// Get the next item in the queue.
		length = length + 1;
	} while (temp != NULL);

	return length;
}


int main() {
	LISTITEM *temp;

	// First, make an empty queue.
	// Which is a queue where the header points to itself and there are no items in it.
	head.first = (LISTITEM*)&head;
	head.last = (LISTITEM*)&head;

	printf("\nAt start, the length of the queue is %d\n\n", queue_length(&head));
	for (int i = 0; i < 3; i++) {			// Populate the queue.
		temp = malloc(sizeof(LISTITEM)); 	// Allocate some memory for the new queue item.
		temp->data = i;						// Set the item's data to the loop count so that we can see where it is in the queue.
		enqueue(&head, temp);				// Put it in the queue.
	}
	printf("After initialization, the length of the queue is %d\n\n", queue_length(&head));

	// See what we've got left.
	do {							// Keep going until the queue is empty.
		printf("The length of the queue is now %d\n", queue_length(&head));
		temp = dequeue(&head);		// If the queue is empty we will get NULL returned.
		if (temp != NULL) {
			printf("Dequeued item. Data is %d\n\n", temp->data);
			free(temp);				// Call 'free' to clean up.
		}
	} while (temp != NULL);

	return 0;
}
