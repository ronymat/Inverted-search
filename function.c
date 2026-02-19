#include "inv.h"

//insert at first is done
int insert_at_first(Slist **head, char *arr)
{
    // Allocate memory for new node
    Slist *new = malloc(sizeof(Slist));
    if (new == NULL)//check if allocated
    {
        return FAILURE;
    }
    // Copy file name into new node
    strcpy(new->filename, arr);
    new->link = NULL;

    // If list is empty
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    else
    {
        // Store current head in temp
        Slist *temp = *head;
        *head = new; // Make new node as head
        new->link = temp; // Link new node to previous head
    }

    return SUCCESS;
}


//remove the duplicate file if present in the backup
int delete_duplicate(Slist **head, char *arr)
{
    // Check if list is empty
    if(*head == NULL)
    {
        return FAILURE;
    }
    // If only one node and it matches
    if((strcmp((*head)->filename, arr) == 0) && (*head)->link == NULL)
    {
        free(*head);          
        *head = NULL;        
        return SUCCESS;
    }
    Slist *temp = *head;      // Pointer to traverse list
    Slist *prev = NULL;       // Pointer to store previous node
    while(temp != NULL)
    {
        // If file name matches
        if(strcmp(temp->filename, arr) == 0)
        {
            // If found at first position
            if(temp == *head)
            {
                *head = temp->link;
                free(temp);
                return SUCCESS;
            }

            // If found in middle or last
            prev->link = temp->link;
            free(temp);
            return SUCCESS;
        }

        prev = temp;
        temp = temp->link;
    }
    return FAILURE;
}
