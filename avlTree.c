#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>
struct Node 
{ 
	char title[1024];
	char imdbid[1024];
	char year[1024];
	char link[1024];
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 

// A utility function to get maximum of two integers 
int max(int a, int b); 

// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

struct Node* newNode(char* title,char* year,char* imdbid,char* link) 
{ 
	struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
    strcpy(node->title,title);
    strcpy(node->year,year);
    strcpy(node->imdbid,imdbid);
    strcpy(node->link,link);
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; 
	return(node); 
} 

struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	x->right = y; 
	y->left = T2; 

	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	return x; 
} 

struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 
	y->left = x; 
	x->right = T2; 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	return y; 
} 

int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

struct Node* insert(struct Node* node, char* title,char* year,char* imdbid,char* link) 
{ 
	if (node == NULL) 
		return(newNode(title,year,imdbid,link)); 
    int cmp =strcmp(title,node->title);
	if (cmp < 0) 
		node->left = insert(node->left, title,year,imdbid,link); 
	else if (cmp>0) 
		node->right = insert(node->right, title,year,imdbid,link); 
	else  
		return node; 

	node->height = 1 + max(height(node->left), 
						height(node->right)); 


	int balance = getBalance(node); 



	if (balance > 1 && strcmp(title, node->left->title)<0) 
		return rightRotate(node); 

	if (balance < -1 && strcmp(title, node->right->title)>0) 
		return leftRotate(node); 

	if (balance > 1 && strcmp(title, node->left->title)>0) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 
	if (balance < -1 && strcmp(title, node->right->title)<0) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 
	return node; 
} 
printStruct(struct Node *n){
    printf("title: %s, year: %s,imdbid: %s,link: %s\n",n->title,n->year,n->imdbid,n->link);
}
void matchNode(struct Node *root,char *str){
    if(root != NULL) 
        { 
            matchNode(root->left,str); 
            if(strstr(root->title,str)){
                printStruct(root); 
            }
            matchNode(root->right,str); 
        } 
}
void inOrder(struct Node *root) 
{ 
	if(root != NULL) 
	{ 
		inOrder(root->left); 
		printf("%s \n", root->title); 
		inOrder(root->right); 
	} 
} 
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
