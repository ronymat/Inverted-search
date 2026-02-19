#include "inv.h"

int update_db(mnode *hash_table[], char *filename)
{
    // Open backup file in read mode
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Unable to open backup file\n");
        return FAILURE;
    }

    char buffer[500];        // Buffer to store each line from file
    int index;               // To store hash index
    int file_count;          // To store number of files for a word
    int word_count;          // To store word count inside each file

    //Validate Backup Header 
    // Read first line (should contain backup key)
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        fclose(fp);
        return FAILURE;
    }

    // Compare header key to verify valid backup file
    if (strncmp(buffer, "INVERTED BACKUP!", 16) != 0)
    {
        printf("Invalid backup file\n");
        fclose(fp);
        return FAILURE;
    }

    // Skip File List Line, Second line contains file list  We skip it  
    fgets(buffer, sizeof(buffer), fp);

    char *token;   // Pointer used for tokenization

    // Read Database Data ,remaining lines one by one
    // read remaining lines one by one
    while (fgets(buffer, sizeof(buffer), fp))
    {
        token = strtok(buffer,"#;\n");
        //when tocken is null skip
        if (token == NULL)
        continue;
        index = atoi(token);// Convert index string to integer
        token = strtok(NULL, "#;\n");
        //when tocken is null skip
        if (token == NULL)
        continue;

        // create new main node
        mnode *new_main = malloc(sizeof(mnode));
        if(new_main == NULL)
        {
            fclose(fp);
            return FAILURE;
        }
        
        strcpy(new_main->word, token);   // copy word
        new_main->main_link = NULL;
        new_main->sub_link = NULL;
        
        // insert main node into hash table
        if(hash_table[index] == NULL)
        {
            hash_table[index] = new_main;// If index is empty, insert directly
        }
        else
        {
            // Traverse to last node in that list
            mnode *temp = hash_table[index];
            while(temp->main_link != NULL)
            {
                temp = temp->main_link;
            }
            temp->main_link = new_main;
        }

        // get file count
        token = strtok(NULL, "#;\n");
        if (token == NULL)//when tocken is null skip
        continue;
        file_count = atoi(token);
        new_main->file_count = file_count;
        
        snode *f_temp = NULL;//usd to link sub node

        // create file nodes
        for(int i = 0; i < file_count; i++)
        {
            token = strtok(NULL, "#;\n");
            if (token == NULL)
            break;
            snode *new_file = malloc(sizeof(snode));
            if (new_file == NULL)
            {
                fclose(fp);
                return FAILURE;
            }
            strcpy(new_file->file, token);   // copy file name
            
            token = strtok(NULL, "#;\n");
            if (token == NULL)
            break;
            word_count = atoi(token);
            new_file->word_count = word_count;
            new_file->s_link = NULL;

            // link file nodes
            if(f_temp == NULL)
            {
                new_main->sub_link = new_file;
            }
            else
            {
                f_temp->s_link = new_file;
            }
            f_temp = new_file;
        }
    }

    fclose(fp);   // close file

    printf("Database updated successfully from %s\n", filename);

    return SUCCESS;
}