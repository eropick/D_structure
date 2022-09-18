#include "myList.h"

int main() {
	NodeType* head = NULL;
	head = insert_first(head, 100);
	head = insert_first(head, 200);
	head = insert_first(head, 300);
	head = insert_first(head, 400);
	head = insert_first(head, 500);
	head = insert_first(head, 600);
	print_list(head);
	node_free(&head);
	print_list(head);
	return 0;
}