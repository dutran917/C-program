#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct word
{
	char *tu;
	int dem;
	int *xh;
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
		(*root) -> xh = (int*)realloc((*root) -> xh,((*root) -> dem)*sizeof(int));
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
				(*root) -> xh = (int*)realloc((*root) -> xh,((*root) -> dem)*sizeof(int));
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
		printf("%-20s: %d - ", root -> tu, root -> dem);
		for (int i = 0; i < root -> dem; ++i)
		{
			printf("%d,", root -> xh[i]);
		}
		printf("\n");
		PrintBST(root->right);
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

struct word* wordprint = NULL;
struct word* stopword = NULL;
int main()
{
	FILE* f1 = fopen("stopw.txt", "r");
	FILE* f2 = fopen("alice30.txt", "r");
	char* s1 =(char*)calloc(100, sizeof(char));

	while(!feof(f1))
	{
		fscanf(f1,"%s",s1);
		push(s1,1,&stopword);
	}
	fclose(f1);
	// PrintBST(stopword);
	int vitri = 0;
	int xuongDong = 0;
	int dong = 1;
	int khoangTrang = 0;
	int dacBiet = 0;
	char c = fgetc(f2);
	while(c != EOF)
	{
		c = tolower(c);
		// if(c == ' ' || c == '.' || c == ',' || c == '(' || c == ')' || c == '\n')
		if(c < 'a' || c > 'z')
		{
			++dacBiet;
			if(c == ' ' || c == '\n')
				++khoangTrang;
			if(c == '\n')
			{
				++xuongDong;
				++dong;
			}
		}else{
			if(dacBiet >= 2)
			{
				s1[vitri - dacBiet] = '\0';
				if(search(stopword, s1) == NULL)
				{
					push(s1, dong - xuongDong, &wordprint);
					xuongDong = 0;
				}
				vitri = 0;
			}else{
				if(khoangTrang == 1)
				{
					s1[vitri - 1] = '\0';
					vitri = 0;
					if(search(stopword, s1) == NULL)
						if(xuongDong != 0)
						{
							push(s1, dong - xuongDong, &wordprint);
							xuongDong = 0;
						}
				}			
			}
			dacBiet = 0;
			khoangTrang = 0;
		}
		s1[vitri++] = tolower(c);
		c = fgetc(f2);
		if(c == EOF)
		{
			s1[vitri - dacBiet] = '\0';
			if(search(stopword, s1) == NULL){
				push(s1, dong - xuongDong, &wordprint);
				// printf("%s\n", s1);
			}
		}
	}
	fclose(f2);
	PrintBST(wordprint);


}
