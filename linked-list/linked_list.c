#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    int size;
    struct node *next;
}
node;

node* init(int data, node* next);
void clear(node* head);
int size(node* head);
bool is_empty(node* head);
void add(node* head, int data);
void add_first(node** head, int data);
int peek_first(node* head);
int peek_last(node* head);
int remove_first(node** head);
int remove_last(node* head);
int rm_at(node* head, int index);
bool rm(node* head, int data);
int index_of(node* head, int data);
bool contains(node* head, int data);

int main(void)
{
    /*
    printf("hello world\n");
    node* head = init(5, NULL);
    printf("Node data: %d\n", head->data);
    printf("Node size: %d\n", size(head));
    printf("Node next: %s\n", head->next);
    printf("is empty: %d\n", is_empty(head));
    printf("peek first: %d\n", peek_first(head));
    printf("peek last: %d\n", peek_last(head));

    add(head, 6);
    add(head, 12);
    add(head, 51);
    add(head, 85);
    add_first(&head, 62);
    add_first(&head, 513);
    for (node* trav = head; trav != NULL; trav = trav->next)
    {
        printf("trav data: %d\n", trav->data);
    }
    printf("remove_first: %d\n", remove_first(&head));
    printf("remove_last: %d\n", remove_last(head));
    printf("remove_at 2: %d\n", rm_at(head, 2));
    printf("remove 51: %d\n", rm(head, 51));
    printf("remove 3: %d\n", rm(head, 3));
    for (node* trav = head; trav != NULL; trav = trav->next)
    {
        printf("trav data: %d\n", trav->data);
    }

    printf("index of 12: %d\n", index_of(head, 12));
    printf("index of 3: %d\n", index_of(head, 3));

    printf("contains 12: %d\n", contains(head, 12));
    printf("contains 3: %d\n", contains(head, 3));
    clear(head);

    */
}

/* Create a new linked list with given (int)data */
node* init(int data, node* next)
{
    // allocate memory for node
    node* node = malloc(sizeof(*node));

    // initialize node
    node->data = data;
    node->next = next;
    node->size = 1;
    
    return node;
}

/* Free all of the memory that linked list using */
void clear(node* head)
{
    for (node* trav = head; trav != NULL;)
    {
        // create a temp pointer for later remove the node
        node* temp = trav;
        trav = trav->next;

        free(temp);
    }
}

/* Return size of the linked list */
int size(node* head)
{
    return head->size;
}

/* Return 0 or 1 whether linked list is empty or not */
bool is_empty(node* head)
{
    return size(head) == 0;
}

/* Add new node and of the linked list */
void add(node* head, int data)
{
    // create a temp node
    node* temp = init(data, NULL);

    // go to last node of the linked list
    node* trav = head;
    while (trav->next != NULL)
    {
        trav = trav->next;
    }
    trav->next = temp;
    
    // increment the size
    head->size++;
}

void add_first(node** head, int data)
{
    // create new temp node that pointing at head
    node* temp = init(data, *head);

    // transfer current size of the head to the temp node
    temp->size = (*head)->size;

    // change head pointer to temp (make temp new head of the linked list)
    *head = temp;
}

/* Return first element of the linked list */
int peek_first(node* head)
{
    return head->data;
}

/* Return last element of the linked list */
int peek_last(node* head)
{
    // create temp node
    node* trav = head;

    // get to the end of the linked list
    while (trav->next != NULL)
    {
        trav = trav->next;
    }

    // return last element data
    return trav->data;
}

/* Remove first element of the linked list */
int remove_first(node** head)
{
    // create temp node for head for later free it
    node* temp = *head;

    // get data of the element that gonna be removed
    int data = temp->data;

    // make second element head of the linked list
    *head = (*head)->next;

    // free old head
    free(temp);

    return data;
}

/* Remove last element of the linked list */
int remove_last(node* head)
{
    // create temp node
    node* trav = head;

    // get to the second to last element in the linked list
    while (trav->next->next != NULL)
    {
        trav = trav->next;
    }

    // get last element data
    int data = trav->next->data;

    // free last element
    free(trav->next);
    // make second to last element next NULL
    trav->next = NULL;

    return data;
}

/* Remove the node at the given index */
int rm_at(node* head, int index)
{
    // if it is the first element use remove_first function
    if (index == 0)
    {
        return remove_first(&head);
    }

    node* trav = head;
    for (int i=0; i < index-1; i++)
    {
        trav = trav->next;
    }

    // get data of the node that gonna be removed
    int data = trav->next->data;

    // check for last node
    if (trav->next->next == NULL)
    {
        return remove_last(head);
    }

    // get next node of the current node
    node* temp = trav->next->next;

    // free the removed node
    free(trav->next);

    trav->next = temp;

    return data;
}

/* Remove the node with the given data*/
bool rm(node* head, int data)
{
    int index = 0;
    for (node* trav = head; trav != NULL; trav = trav->next)
    {
        // if given data equals the current node's data then remove it
        if (trav->data == data)
        {
            rm_at(head, index);
            return true;
        }

        // else increment the index
        index++;
    }

    // if number is not in the linked list
    return false;
}

/* Return index of the given data */
int index_of(node* head, int data)
{
    int i = 0;
    for (node* trav = head; trav != NULL; trav = trav->next)
    {
        // check all of the nodes data
        if (trav->data == data)
        {
            return i;
        }

        // increment i every iteration
        i++;
    }

    // if number not found return -1
    return -1;
}

/* Return true or false depends on the condition */
bool contains(node* head, int data)
{
    return index_of(head, data) != -1;
}
