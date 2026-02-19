#include "inv.h"

int save_db(mnode *arr[],Slist **head)
{
    char backup[50];
    printf("Enter the name of backup file :");
    scanf("%s",backup);
    //validate the file and extension
    int len=strlen(backup);
    if(len<=4 || strcmp(backup+len-4,".txt")!=0)//check extension and length
    {
     return FAILURE;
    }
    //open the file in write mode
    FILE *fp=fopen(backup,"w");
    if(fp==NULL)
    {
        printf("Error: Unable to create backup file\n");
        return FAILURE;
    }
    //coppy backup key to file
    fprintf(fp,"INVERTED BACKUP!\n");
    //copy the file list to backup file
    Slist *head_temp=*head;
    if (head_temp!=NULL)
    {
        while (head_temp->link!=NULL)//coppy filename to backup file until secondlast file
        {
            fprintf(fp,"%s;",head_temp->filename);
            head_temp=head_temp->link;
        }
     fprintf(fp,"%s\n",head_temp->filename);//copy the last file name
    }
    else
    {
         fprintf(fp,"NO FILES PRESENT\n");
    }

    //copy hashtable data 
    for(int i=0;i<SIZE;i++)
    {
        mnode *temp=arr[i];
        while (temp!=NULL)
        {
           fprintf(fp,"#");//used to give # to seperate each word
        //copy main node
           fprintf(fp,"%d;%s;%d",i,temp->word,temp->file_count);

           //copy sub nodes
           snode *subtemp=temp->sub_link;
           while (subtemp!=NULL)
           {
           fprintf(fp,";%s;%d",subtemp->file,subtemp->word_count);//copy subnode data to file
           subtemp=subtemp->s_link;//update subnode temp
           }
           fprintf(fp,"#\n");
           temp=temp->main_link;//update temp
        }   
    }
    fclose(fp);
    printf("\nDatabase backup created successfully....\n");
}