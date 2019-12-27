#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>
#include "tree.h"
/* Drier program to test above function*/
int main() 
{ 
struct Node *root = NULL,*head=NULL; 
FILE *f = fopen("/home/mehroz/repo/cLang/movies.txt", "r");
char line[1024],title[1024],link[1024],imdbid[1024],year[1024];
int dataLength=40, yearsAndMovies[dataLength][2];
int i=0,j=0;
for (;i<dataLength;i++){
    for (j=0;j<2;j++){
        yearsAndMovies[i][j]=0;
    }
}
while (fgets(line, 1024, f))
{
    strcpy(title,strtok(line, ","));
    strcpy(year,strtok(NULL, ","));
    strcpy(imdbid,strtok(NULL, ","));
    strcpy(link,strtok(NULL, ","));
    if(strcmp("Title",title)==0){
         continue;
    }
    for(i=0;i<dataLength;i++){
        if(yearsAndMovies[i][0]==atoi(year)){
           yearsAndMovies[i][1]++;
           break;
        }else
         if(yearsAndMovies[i][0]==0){
           yearsAndMovies[i][0]=atoi(year);
           yearsAndMovies[i][1]++;
           break;
        }
    }
    root = insert(root, title,year,imdbid,link); 
}
int choice;
do{
    printf("\n>>>Welcome to Movie Analysis at IMDB<<<\n--Menu--\n");
    printf("1. Display the full index of movies\n2. Display the movies where their title contains a specific keyword\n3. Display the year with maximum number of movies\n4. Exit");
    printf("\nOption: ");
    scanf("%d",&choice);
    int index=0;
    char str[1024];
    switch (choice)
    {
    case 1/* constant-expression */:
        printf("Movie index\n-------\n");

        inOrder(root); 
        break;
    case 2/* constant-expression */:
        printf("\nEnter Keyword: ");
        scanf("%s",str);
        matchNode(root,str);
        break;
    case 3/* constant-expression */:
        
        for(i=1;i<dataLength;i++){
            if(yearsAndMovies[index][1]<yearsAndMovies[i][1]){
                index=i;
            }
         } 
         printf("\nYear with most movies is: %d\n\n",yearsAndMovies[index][0]);
        break;
    }   
}
while(choice!=4);
return 0; 
} 
