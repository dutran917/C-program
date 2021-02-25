#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct word
{
	char *tu;
	int dem;
	int xh[100];
	struct word* left;
	struct word* right;
}word;

void push(char* str,int a,struct word **root)
{
	if(*root == NULL)
	{
		*root = (struct word*)calloc(1,sizeof(struct word));
		(*root) -> tu = (char*)calloc(strlen(str), sizeof(char));
		strcpy((*root)->tu,str);
		(*root) -> dem = 1;
		(*root) -> xh[0] = a;
	}
	else
	{
		if(strcmp((*root)->tu,str) > 0)
		{
			push(str,a,&((*root)->left));
		}
		else
		{
			if(strcmp((*root)->tu,str) < 0)
			{
				push(str,a,&((*root)->right));
			}else{
				++((*root) -> dem);
				(*root) -> xh[(*root)->dem - 1] = a;
			}
		}
	}
}
void PrintBST(word* root)
{
	if (root != NULL)
	{
		PrintBST(root->left);
		printf("%-20s: %d,", root -> tu, root -> dem);
		for (int i = 0; i < root -> dem; ++i)
		{
			printf("%d,", root -> xh[i]);
		}
		printf("\n");
		PrintBST(root->right);
	}
}


int count =0;
void find(word* root,char *s)
{	
	if(root != NULL && count != 1)
	{	
		//printf("%-20s\n", (root->Word).tu);
		if(strcmp((root->tu ), s) == 0)
		{
			count =1;
		}
		if(strcmp((root->tu),s) < 0)
			find(root->right,s);
		if(strcmp((root->tu),s) > 0)
			find(root->left,s);
	}
}

word* search(word* root,char* s)
{
	if(root == NULL)
	{
		return NULL;
	}
	else
	{
		if(strcmp(s,root->tu) == 0)
			return root;
		else if(strcmp(s , root->tu) < 0)
			return search(root->left,s);
		else if(strcmp(s,root->tu) > 0)
			return search(root->right,s);
	}
} 
/*int checkwork(char *s1,char *s2);
{

}*/
struct word* wordprint = NULL;
struct word* stopword = NULL;
int main()
{
	FILE* f1 = fopen("stopw.txt", "r");
	FILE* f2 = fopen("vanban.txt", "r");
	char c=fgetc(f1);
	int row=1;
	int space=0;
	int stop=0;
	int breakLine=0;
	int i=0;
	char* s1 =(char*)calloc(100, sizeof(char));

	while(c != EOF)
	{
		c = tolower(c);
		if(c > 'z' || c < 'a')
		{
			++stop;
			if(c == ' ' || c == '\n')
				++space;
			if(c == '\n')
			{
				breakLine = 1;
				++row;
			}
		}else{
			if(stop >= 2)
			{
				s1[i - stop] = '\0';
				if(breakLine == 1)
				{
					breakLine = 0;
					push(s1,row-1,&stopword);
				}
				else
					push(s1,row,&stopword );
				// printf("%s\n", s1);
				i = 0;
			}else{
				if(space == 1)
				{
					s1[i - 1] = '\0';
					i = 0;
					if(breakLine == 1)
					{
						breakLine = 0;
						push(s1,row-1,&stopword);
					}
					else
						push(s1,row,&stopword );
					// printf("%s\n", s1);
				}			
			}
			stop = 0;
			space = 0;
		}
		s1[i++] = tolower(c);
		c = fgetc(f1);
		if(c == EOF)
		{
			s1[i - stop] = '\0';
			push(s1,row,&stopword);
			// printf("%s\n", s1);
		}
	}
	fclose(f1);

	// PrintBST(stopword);
	breakLine = 0;
	row = 1;
	space = 0;
	stop = 0;
	c = fgetc(f2);
	while(c != EOF)
	{
		c = tolower(c);
		// if(c == ' ' || c == '.' || c == ',' || c == '(' || c == ')' || c == '\n')
		if(c < 'a' || c > 'z')
		{
			++stop;
			if(c == ' ' || c == '\n')
				++space;
			if(c == '\n')
			{
				++breakLine;
				++row;
			}
		}else{
			if(stop >= 2)
			{
				s1[i - stop] = '\0';
				if(search(stopword, s1) == NULL)
					if(breakLine != 0)
					{
						push(s1, row - breakLine, &wordprint);
						breakLine = 0;
						// printf("%s\n", s1);
					}else{
						// printf("%s\n", s1);
						push(s1, row - breakLine, &wordprint);
					}
				i = 0;
			}else{
				if(space == 1)
				{
					s1[i - 1] = '\0';
					i = 0;
					if(search(stopword, s1) == NULL)
						if(breakLine != 0)
						{
							// printf("%s\n", s1);
							push(s1, row - breakLine, &wordprint);
							breakLine = 0;
						}else{
							// printf("%s\n", s1);
							push(s1, row - breakLine, &wordprint);
						}
				}			
			}
			stop = 0;
			space = 0;
		}
		s1[i++] = tolower(c);
		c = fgetc(f2);
		if(c == EOF)
		{
			s1[i - stop] = '\0';
			if(search(stopword, s1) == NULL){
				push(s1, row - breakLine, &wordprint);
				// printf("%s\n", s1);
			}
		}
	}
	fclose(f2);
	PrintBST(wordprint);


}