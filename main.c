/*
NAME:RONY MATHEW
DATE:19/02/2026
PROJECT NAME :INVERTED SEARCH
 */

#include "inv.h"

int main(int argc,char *argv[])
{
  printf("================================================\n");
  printf("                INVERTED SEARCH       ");
  printf("\n================================================\n");
  
  Slist *head=NULL;
  int choice;              // Stores user  choice
  int create_flag = 0;     // mark if database is created
  int update_flag = 0;     // mark if database is updated from backup

  mnode *hash_table[SIZE]={NULL};
  //call argument validation
  if(arg_validation(argc,argv,&head)==FAILURE)
  {
    printf("Error: incorrect number of arguments are passed\nMinimum 1 file should be needed\n");
    return FAILURE;
  }
  //run loop infinite times
  while (1)
  {
    printf("\n===========   SELECT AN OPTION  =============\n");
    printf("\n1.Create Database\n2.Display Database\n3.Search Database\n4.Save Database\n5.Update database\n6.Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
         case 1:
              //create database
              if (create_flag == 1)
              {
                  printf("Database already created. Cannot create again.\n");
                  break;
              }
              // Create inverted index database 
              if (create_db(head, hash_table) == FAILURE)
              {
                  printf("Error: Failed to create database\n");
                  break;
              }

              printf("Database created successfully\n");
              create_flag = 1;
              break;
        case 2:
               //display database
                printf("\n===========  DATABASE CONTENTS  =============\n");
                display_db(hash_table);
               break;
        case 3:
               //search database
                printf("\n=============  SEARCH CONTENTS  =============\n\n");
                char str[50];
               printf("Enter the String to be searched in database\n");
               scanf("%s",str);
                if(search_db(hash_table,str)==FAILURE)
                {
                     printf("Error: Word not found in Database!!!\n");
                     return FAILURE;
                }
               break;
        case 4:
                printf("\n=============  SAVE DATABASE  ==============\n\n");
                save_db(hash_table,&head);
               break;
        case 5:
        printf("\n============  UPDATE DATABASE  =============\n\n");
        // Allow update only if database is not already created or updated
          if (create_flag == 0 && update_flag == 0)
          {
              char filename[50];
              printf("Enter backup file name: ");// Ask user for backup file name
              scanf("%s", filename);
               // Rebuild hash table from backup file
              if (update_db(hash_table, filename) == FAILURE)
              {
                  printf("Update database failed...!\n");
                  break;
              }
              
              update_flag = 1; // Mark that update has been performed
              FILE *fp = fopen(filename, "r");// Open the backup file again to extract stored file list
              if (fp == NULL)
              {
                  printf("Unable to open backup file\n");
                  break;
              }

              char buffer[200];
              fgets(buffer, sizeof(buffer), fp);   // Skip header line
              fgets(buffer, sizeof(buffer), fp);   // Read file list line

              char *token = strtok(buffer, ";\n");// Tokenize the file list line using ';'
              // Remove each updated file from the linked to prevents duplication if CREATE is called later
              while(token != NULL)
              {
                  delete_duplicate(&head, token);   // remove updated files from list
                  token = strtok(NULL, ";\n");
              }
              fclose(fp);
              printf("Database updated successfully\n");
              break;
          }
          else
          {
              printf("Database already Updated...!\n");
              break;
          }

        case 6:
               printf("\n=============     EXITING     ==============\n\n");
               return 0;
               break;

        }
  }
  
}