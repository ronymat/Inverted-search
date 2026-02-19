#include "inv.h"
#include<ctype.h>
#include<strings.h>

int search_db(mnode *arr[],char *str)
{
    int index;
     // Convert first word to lowercase
     char first = tolower(str[0]);
     // Determine hash index based on first character
    if(first>=48 && first<=57)//check if it is number
       {
        index=26;
       }
       else if (first>='a'&&first<='z')//check if lowercase
       {
        index=first-'a';
       }
       else
       index=27;
       mnode *m_temp=arr[index];
       while (m_temp!=NULL)//traverse main node link
       {

            if(strcasecmp(m_temp->word,str)==0)
            {
            // Word found → print details
             printf("Index : %d\n\tWord: %-18s FileCount: %d\n",index,m_temp->word,m_temp->file_count);    
             snode *s_temp = m_temp->sub_link;
             while (s_temp!=NULL)
             {
             printf("\tFile name: %s\t Word count: %-4d \n",s_temp->file,s_temp->word_count);
             s_temp=s_temp->s_link;//update sub node to travel
             }
             return SUCCESS;  
            }
             m_temp=m_temp->main_link;//update main temp
        }   
        printf("Data search is not found in db!!!\n");
       } 
