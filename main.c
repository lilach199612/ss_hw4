#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

//change the Capital letter to small letter
char DownCase(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c - 'A' + 'a';
	}
	return c;
}
//init a new node
node* newNode(char c)
{
    node* root=NULL;
	root=(node*)malloc(sizeof(node));
    if(root)
    {
        root->letter=c;
	    root->countChiledren=0;
	    root->countNode=0;
        root->countPrint=0;
        for(int i=0;i<LETTERS;i++)
        {
            root->children[i]=NULL;
        }
    }
	return root;
}
//add all the words from the input to the tree
void add(node* root ,char c)
{
	node *temp=root;
    int t=1;
    int index=0;
    while(c!=' '&&c!='\t'&&c!='\n'&&t) //continue until its the end of the word or the file
    {
    	c=DownCase(c); //if its a Capital letter, change to small letter
    	if(c>='a'&&c<='z')//check if it is a letter
    	{
        	index=(int)(c-'a');
       		if(!temp->children[index]) //if there is no node, create 
    		{
    			temp->children[index]=newNode(c);
    		}
       		temp->children[index]->countChiledren++;
       		temp=temp->children[index];
    	}
    	if(scanf("%c",&c)==EOF) //if it is the end of the file
    		t=0;
    }
    temp->countNode++;
    temp->countChiledren--;
}
//The function free all the memory in the end of the program
void release(node** root)
{
   if(*root!=NULL) //if the node is null
    {
        for(int i=0;i<LETTERS;i++) //release all his children
        {
            release(&((*root)->children[i]));
        }
        free(*root);
        return;
    }
}
//The function print all the word in Lexicographic order
long unsigned int print(node** root )
{
    if((*root)!=NULL) //if the node is null
    {
        long unsigned int countWord=(*root)->countNode+(*root)->countChiledren;
        long unsigned int countPrint=(*root)->countPrint;
        if(countWord>countPrint) //check if all the words printed
        {
            long unsigned int countNode=(*root)->countNode;
            if(countNode>countPrint) //if this word was printed
            {
                char letter=(*root)->letter;
                (*root)->countPrint=countPrint+countNode;
                printf("%c %lu\n",letter,countNode);
                return countNode;
            }
            for(int i=0;i<LETTERS;i++) //if the childrens printed
            {
                if((*root)->children[i]!=NULL&&(*root)->children[i]->countPrint<(*root)->children[i]->countNode + (*root)->children[i]->countChiledren)
                {
                    printf("%c",(*root)->letter);
                    long unsigned int countI=print(&((*root)->children[i]));
                    (*root)->countPrint=countPrint+countI;
                    return countI;
                }
            }   
        }
    }
    return 0;
}
//The function print all the word in a reverse Lexicographic order
long unsigned int printR(node** root )
{
    if((*root)!=NULL) //if the node is null
    {
        long unsigned int countWord=(*root)->countNode+(*root)->countChiledren;
        long unsigned int countPrint=(*root)->countPrint;
        if(countWord>countPrint)//check if all the words printed
        {
            for(int i=LETTERS;i>=0;i--)//check if all the children printed
            {
                if((*root)->children[i]!=NULL&&(*root)->children[i]->countPrint<(*root)->children[i]->countNode + (*root)->children[i]->countChiledren)
                {
                    printf("%c",(*root)->letter);
                    long unsigned int countI=printR(&((*root)->children[i]));
                    (*root)->countPrint=countPrint+countI;
                    return countI;
                }
            } 
            //if there is a word in the node print it
            long unsigned int countNode=(*root)->countNode;
            char letter=(*root)->letter;
            (*root)->countPrint=countPrint+countNode;
            printf("%c %lu\n",letter,countNode);
            return countNode;
        }
    }
    return 0;
}

int main(int argc,char* argv[])
{
		bool printRev=false;
		if((argc==2)&&strcmp(argv[1],"r")==0)
			printRev=true;
	    node* head=newNode('\0');
	    char c;
	    while(scanf("%c",&c)!=EOF) //add all the word from the input to the tree
	    {
	    	add(head,c);
	    }
	    if(printRev) //print all the word in a reverse Lexicographic order
	    {
            for(int i=LETTERS-1;i>=0;i--)
	         {
                 if(head->children[i]!=NULL)
                 {
                     long unsigned int countPrint=head->children[i]->countPrint;
                     long unsigned int countWord=head->children[i]->countNode + head->children[i]->countChiledren;
                     while(countPrint<countWord)
                     {
                        countPrint=countPrint+printR(&(head->children[i]));
                        head->children[i]->countPrint=countPrint;
                     }
                 }
             }
	     }
	     else //print all the word in a reverse Lexicographic order
	     {
            for(int i=0;i<LETTERS;i++)
	         {
                 if(head->children[i]!=NULL)
                 {
                     long unsigned int countPrint=head->children[i]->countPrint;
                     long unsigned int countWord=head->children[i]->countNode + head->children[i]->countChiledren;
                     while(countPrint<countWord)
                     {
                        countPrint=countPrint+print(&(head->children[i]));
                        head->children[i]->countPrint=countPrint;
                     }
                 }
             }
	     }
        release(&head);
}
