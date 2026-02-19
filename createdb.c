#include "inv.h"
#include<ctype.h>
#include<strings.h>
int create_db(Slist *head,mnode *arr[])
{
  Slist *temp=head;
  char name[50];
  while (temp!=NULL)//move till last file 
  {
    FILE *fp=fopen(temp->filename,"r");//open the file to read thw contents also check it is present or not
    if(fp==NULL)
    {
        return FAILURE;
    }
    while (fscanf(fp,"%s",name)==1)//read string until null space
    {
        int index;
        char first=tolower(name[0]);
       if(first>=48 && first<=57)//check if it is number
       {
        index=26;
       }
       else if (first>='a'&& first<='z')//check if lowercase
       {
        index=first-'a';
       }
       else
       index=27;

       mnode *tmp=arr[index];//copy the head of mainlist to temp
       // Traverse main node list to find matching word
       while (tmp) 
       {
        if(strcasecmp(tmp->word, name) == 0)
        {
            break;
        }
        tmp=tmp->main_link;
       }
       //check if node contail main node or note
       if(tmp)
        {
          snode *s=tmp->sub_link;
          snode *s_prev=NULL;
          // Search if this file already exists in subnode list
          while(s && strcmp(s->file,temp->filename)!=0)
          {
            s_prev=s;
            s=s->s_link;
          }
           // If file already exists increment word count
          if(s)
          {
           s->word_count++; 
          }
          // If file not found create new subnode
          else
          {
            //create new sub node if file is not same
            snode *new_sub=malloc(sizeof(snode));
            if(new_sub==NULL)
            {
              return FAILURE;
            }
            strcpy(new_sub->file,temp->filename);
            new_sub->word_count=1;
            new_sub->s_link=NULL;
            //if sub list is empty
            if(s_prev==NULL)
            {
              tmp->sub_link=new_sub;
            }else//if not empty
            {
              s_prev->s_link=new_sub;
            }
            //increment file count
            tmp->file_count++;
          }
        }
       else
         {
          //create new main node
          mnode *new_main=malloc(sizeof(mnode));
          if(new_main==NULL)
          {
            return FAILURE;
          }
          strcpy(new_main->word,name);//copy word to new node
          new_main->file_count=1;
          //create subnode
          snode *new_sub=malloc(sizeof(snode));
          if(new_sub==NULL)
          {
            return FAILURE;
          }
          strcpy(new_sub->file,temp->filename);//copy filename to sub node
          new_sub->word_count=1;
          new_sub->s_link=NULL;

          new_main->sub_link=new_sub;//addsub node link to main node

          //do insert before
          new_main->main_link=arr[index];
          arr[index]=new_main; 
        }
        
    }
    fclose(fp);
    temp=temp->link;//update temp
  }
  return SUCCESS;
}
