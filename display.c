#include "inv.h"
#include<ctype.h>

int display_db(mnode *arr[])
{
  int i=0;
  int check=0;
  for(i=0;i<SIZE;i++)//run loop for 28 times
  {
    if(arr[i]!=NULL)//if table is not empty
    {
        check=1;
        mnode *m_temp=arr[i];
        while (m_temp!=NULL)//run main node and print index word and filecount
        {
           printf("Index : %d\n\tWord: %-18s FileCount: %d\n",i,m_temp->word,m_temp->file_count);

           snode *s_temp=m_temp->sub_link;
           while (s_temp!=NULL)//run sub node and print filename and count
           {
            printf("\tFile name: %s\t Word count: %-4d \n",s_temp->file,s_temp->word_count);
            s_temp=s_temp->s_link;//update sub node to travel
           }
           printf("\n"); 
           m_temp=m_temp->main_link;//update main node to traverse
        }
    }
  }
  if(check)//used to check if database is empty or not
  {
   return SUCCESS;
  }
  else
  {
    printf("Data base is empty!!!\n");
    return FAILURE;
  }
}
