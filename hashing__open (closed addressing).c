#include<stdio.h>
#include<stdlib.h>
#define size 5

struct node{
	int data;
	struct node* next;	
};

struct node *hashTable[size] = {NULL};

struct node* createNode(int element)
{
	struct node *nn;
	nn = (struct node*)malloc(sizeof(struct node));
	nn->data = element;
	nn->next = NULL;
	return nn;
}

void insert(int element)
{
	struct node *nn;
	nn = createNode(element);
	int hashValue;
	hashValue = nn->data % size;
	if(hashTable[hashValue] == NULL)
	{
		hashTable[hashValue] = nn;
	}
	else
	{
		struct node *ptr = hashTable[hashValue];
		while(ptr->next != NULL)
		{
			ptr = ptr->next;   
		}
		ptr->next = nn;        //----> inserts at the end of the bucket
		
		/*
			nn->next = hashTable[hashValue];       //--->inserts at begining of the bucket
			hashTable[hashValue]=nn;
		*/
	}
}

void del(int key)
{
	int hash_key;
	hash_key = key % size;
	struct node *temp = hashTable[hash_key] , *ptr;
	if(temp == NULL)
	{
		printf("%d is not found in the Hashtable\n",key);	
	}
	else if(temp->data == key)
	{
		hashTable[hash_key] = temp->next;
		free(temp); 	
	}
	else
	{
		int flag = 0;
		while(temp->data != key)
		{
			ptr = temp;
			temp = temp->next;
			if(temp == NULL)
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			printf("%d is not found in the HashTable\n",key);
		}
		else
		{
			ptr->next = temp->next;
			free(temp);
		}
	}	
}

void search(int key)
{
	int hash_key = key % size;
	struct node *temp = hashTable[hash_key];
	if(temp == NULL)
	{
		printf("NOT FOUND\n\n");
	}
	else
	{
		int loc = 1, c=0;
		while(temp->data != key)
		{
			loc++;
			temp = temp->next;
			if(temp == NULL)
			{
				c=1;
				break;
			}
		}
		if(c == 1)
		{
			printf("%d is not Found", key);
		}
		else
		{
			printf("%d is FOUND at INDEX=%d at location--%d\n\n", key, hash_key, loc);
		}
	}
}

void display()
{
	int i=0;
	printf("\n HASH TABLE :\n");
	while(i<size)
	{
		printf("%d---> ",i);
		struct node *ptr = hashTable[i];
		while(ptr != NULL)
		{
			printf("%d\t", ptr->data);
			ptr=ptr->next;	
		} 
		printf("NULL\n");
		i++;
	}
	printf("\n");
}

void main()
{
	printf("\t\tOPEN HASHING\n\n");
	while(1)
	{
		printf("1.Insert\n");
		printf("2.Display\n");
		printf("3.Search\n");
		printf("4.Delete\n");
		printf("5.Quit\n\n");
		
		int choice;
		printf("Select your choice:");
		scanf("%d",&choice);
		int data, element, key;
		
		switch(choice)
		{
			case 1:
				printf("\nEnter element to added:");
				scanf("%d",&data);
				insert(data);
				break;
			case 2:
				display();
				break;
			case 3:
				printf("\nEnter element to search:");
				scanf("%d",&element);
				search(element);
				break;
			case 4:
				printf("\nEnter element to delete:");
				scanf("%d",&key);
				del(key);
				break;
			case 5:
				exit(0);
				break;
			default:
				printf("\nSelect correct choice\n");
				break;
		}
		
	}
}
