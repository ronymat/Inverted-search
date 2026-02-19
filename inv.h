#ifndef INV_H
#define INV_H
//header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//macros used for return
#define SUCCESS 0
#define FAILURE 1
#define SIZE 28

//structure definition
typedef struct node
{
    char filename[100];
    struct node *link;   
}Slist;
//struct for sub node
typedef struct subnode
{
char file[50];
int word_count;
struct subnode *s_link;
}snode;
//structure for mnain node
typedef struct mainnode
{
  char word[50]; 
  int file_count; 
  struct mainnode *main_link;
  struct subnode *sub_link;
}mnode;
//list of functions used

int arg_validation(int argc,char *argv[],Slist **head);
int file_tolist(char *fname,Slist **head);
int create_db(Slist *head,mnode *hash_table[]);
int display_db(mnode *hash_table[]);
int search_db(mnode *hash_table[],char *str);
int save_db(mnode *hash_table[],Slist **head);
int update_db(mnode *hash_table[],char *filename);
int insert_at_first(Slist **head, char *arr);
int delete_duplicate(Slist **head, char *arr);
#endif