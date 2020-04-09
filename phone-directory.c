//Selman Burak Karagöl
//Telephone Guide With Linked List

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//typedef provide to change name of the struct
struct HumanBeing
{
	char firstname[40];
	char lastname[40];
	int telephone;

	struct HumanBeing *next;
	struct HumanBeing *prev;
} typedef human;

void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock())
		;
}

//basic function prototypes bellow this command line
void sort();
human *add(human *, human *);
void update();
human *search(human *, int);
human *delete (human *, human *);
void show(human *);
human *createBox(human *, human *);
void Menu(human *);
void upgrade(human *, human *);
//Secondary Functions are Bellow This Line. This Functions are used only inside of other fuctions.
int ShortString(human *first, human *second);
void relocateBox(int shortName, human *box1, human *box2, int choose);
int counter(int, human *, char name[40]);

void Menu(human *root)
{
	system("CLS");
	int choose;

	human *iter = root;

	while (1 == 1)
	{

		printf("\n--Menu--\n");
		printf("0-Exit\n");
		printf("1-Show All Guide\n");
		printf("2-Add New Person\n");
		printf("3-Delete From Guide\n");
		printf("4-Update Person\n");
		printf("5-Search\n");
		printf("6-Sort\n");
		printf("\nPls select process : ");
		flushall;
		scanf("%d", &choose);

		if (choose == 0)
		{
			exit(0);
		}
		else if (choose == 1)
		{
			system("CLS");
			show(root);
		}
		else if (choose == 2)
		{
			system("CLS");
			human *willAdd = createBox(NULL, root);
			root = add(root, willAdd);
			show(root);
		}
		else if (choose == 3)
		{
			system("CLS");
			human *willDelete = search(root, 1);
			if (willDelete == NULL)
			{
				printf("Your Search didn't Match With any Person");
				Menu(root);
			}
			root = delete (willDelete, root);
			system("CLS");
			show(root);
		}
		else if (choose == 4)
		{
			system("CLS");
			human *willUpdate = search(root, 2);
			if (willUpdate == NULL)
			{
				printf("Your Search didn't Match With any Person");
				Menu(root);
			}
			update(willUpdate, root);
			system("CLS");
		}
		else if (choose == 5)
		{
			system("CLS");
			human *results = search(root, 0);
			system("CLS");
			show(results);
		}
		else if (choose == 6)
		{
			system("CLS");
			sort(root);
			show(root);
		}
		else
		{
			system("CLS");
			printf("Unvalid Choose");
			continue;
		}
	}
}

int main()
{
	human *root = NULL;

	Menu(root);
}

human *createBox(human *loadedBox, human *root) //this function gona be take the informations before add new human to Guide
{
	human *box = (human *)malloc(sizeof(human));

	if (loadedBox == NULL)
	{
		printf("\nFirstname : ");
		scanf("%s", box->firstname);
		printf("\nLastname : ");
		scanf("%s", box->lastname);
		printf("\nTelephone Number(Unique) : ");
		scanf("%d", &box->telephone);
		while (root != NULL)
		{
			if (root->telephone == box->telephone)
			{
				printf("\nTelephone Number Must Be Unique,This Thelephone Number is Already Exist.\n");
				delay(2000);
				Menu(root);
			}
			root = root->next;
		}
	}
	else
	{
		strcpy(box->firstname, loadedBox->firstname);
		strcpy(box->lastname, loadedBox->lastname);
		box->telephone = loadedBox->telephone;
	}

	box->prev = NULL;
	box->next = NULL;

	return box;
}

human *add(human *r, human *willAdd) //this functions add for only last of link list
{
	human *iter = r;

	if (r == NULL) //if root is NULL we can understand this is the empty link list.And Return new root with WillAdd.
	{
		willAdd->next = NULL;
		willAdd->prev = NULL;
		return willAdd;
	}
	while (iter->next != NULL)
	{
		iter = iter->next;
	}
	willAdd->next = iter->next;
	willAdd->prev = iter;
	iter->next = willAdd;
	return r;
}

human *delete (human *willDelete, human *r)
{
	human *iter = r;
	human *temp;

	if (r == NULL) //guide is empty
	{
		printf("Nobody on Guide");
		return r;
	}
	if (r == willDelete) //try to delete first box on guide
	{
		temp = r;
		iter = iter->next; //this line loosing the root*********************************
		if (iter != NULL)
		{
			iter->prev = temp->prev;
		}
		free(temp);
		return iter;
	}
	while (iter->next != NULL && iter->next != willDelete)
	{
		iter = iter->next;
	}
	temp = iter->next;
	iter->next = iter->next->next;
	if (temp->next != NULL) //This line control try to delete last box on the link list.When try to delete last, we should not control null->next->prev.
	{
		temp->next->prev = iter; //this line close the program ************************
	}
	free(temp);
	return r;
}

human *search(human *r, int from)
{
	int choice;
	char name[40];
	char surname[40];
	int telephone;
	human *onlyforShow;

	human *iter = r;

	if (r == NULL)
	{
		printf("Guide is Empty");
		return r;
	}

	human *results = NULL;
	human *newBox;

	printf("\n 1-Search for First Name");
	printf("\n 2-Search for Last Name");
	printf("\n 3-Search for Telephone Number");
	printf("\nYour Choose : ");
	scanf("%d", &choice);

	if (choice == 1)
	{
		printf("\nSearch Name : ");
		scanf("%s", name);
	}
	else if (choice == 2)
	{
		printf("\nSearch Last Name : ");
		scanf("%s", surname);
	}
	else if (choice == 3)
	{
		printf("\nSearch Telephone Number : ");
		scanf("%d", &telephone);
	}
	else
	{
		printf("\nWrong Choice");
		return r;
	}
	int count = 0;
	int control;
	while (iter != NULL)
	{
		if (choice == 1)
		{
			if (!strcmp(iter->firstname, name))
			{
				if (from >= 1)
				{
					onlyforShow = createBox(iter, NULL);
					show(onlyforShow);
					count = counter(choice, iter, name);
					if (from == 1)
						printf("1-Delete\n");
					if (from == 2)
						printf("1-Update\n");
					printf("2-Do Nothing\n");
					if (count > 1)
					{
						count = 0;
						printf("3-See Other Same Name\n");
					}
					printf("Your Choose : ");
					scanf("%d", &control);
					if (control == 1)
						return iter;
					else if (control == 2)
						Menu(r);
					else if (control == 3)
					{
						iter = iter->next;
						continue;
					}
					else
						continue;
				}
				newBox = createBox(iter, NULL);
				results = add(results, newBox);
			}
		}
		else if (choice == 2)
		{
			if (!strcmp(iter->lastname, surname))
			{
				if (from >= 1)
				{
					onlyforShow = createBox(iter, NULL);
					show(onlyforShow);
					count = counter(choice, iter, surname);

					if (from == 1)
						printf("1-Delete\n");
					if (from == 2)
						printf("1-Update\n");
					printf("2-Do Nothing\n");
					if (count > 1)
					{
						count = 0;
						printf("3-See Other Same Name\n");
					}
					printf("Your Choose : ");
					scanf("%d", &control);
					if (control == 1)
						return iter;
					else if (control == 2)
						Menu(r);
					else if (control == 3)
					{
						iter = iter->next;
						continue;
					}
					else
						continue;
				}
				newBox = createBox(iter, NULL);
				results = add(results, newBox);
			}
		}
		else if (choice == 3)
		{
			if (iter->telephone == telephone)
			{
				if (from == 1)
				{
					if (from == 1)
						printf("1-Delete\n");
					if (from == 2)
						printf("1-Update\n");
					printf("2-Do Nothing");
					printf("Your Choose : ");
					scanf("%d", &control);
					if (control == 1)
						return iter;
					else
						Menu(r);
				}
				newBox = createBox(iter, NULL);
				results = add(results, newBox);
			}
		}
		else
		{
			printf("Unvalid Choose");
		}
		iter = iter->next;
	}
	show(results);
	return results;
}

void show(human *willShow)
{
	if (willShow == NULL)
	{
		printf("\nNobody on Guide\n\n");
	}
	while (willShow != NULL)
	{
		printf("\n First Name : %s", willShow->firstname);
		printf("\n Last Name : %s", willShow->lastname);
		printf("\n Telephone Number : %d", willShow->telephone);
		printf("\n\n");

		willShow = willShow->next;
	}
}

int ShortString(human *first, human *second)
{
	int a, b;
	a = strlen(first->firstname);
	b = strlen(second->firstname);
	if (a > b)
		return b;
	else
		return a;
}

void relocateBox(int shortName, human *box1, human *box2, int choose)
{
	char tempname[40];
	char tempsurname[40];
	int temp;
	int i;

	if (choose == 1)
		for (i = 0; i <= shortName; i++)
		{
			if (box1->firstname[i] < box2->firstname[i])
			{
				break;
			}
			else if (box1->firstname[i] > box2->firstname[i])
			{
				strcpy(tempname, box2->firstname);
				strcpy(tempsurname, box2->lastname);
				temp = box2->telephone;

				strcpy(box2->firstname, box1->firstname);
				strcpy(box2->lastname, box1->lastname);
				box2->telephone = box1->telephone;

				strcpy(box1->firstname, tempname);
				strcpy(box1->lastname, tempsurname);
				box1->telephone = temp;

				break;
			}
			else
			{
				continue;
			}
		}
	else
	{
		if (box1->telephone > box2->telephone)
		{

			strcpy(tempname, box2->firstname);
			strcpy(tempsurname, box2->lastname);
			temp = box2->telephone;

			strcpy(box2->firstname, box1->firstname);
			strcpy(box2->lastname, box1->lastname);
			box2->telephone = box1->telephone;

			strcpy(box1->firstname, tempname);
			strcpy(box1->lastname, tempsurname);
			box1->telephone = temp;
		}
	}
}

void sort(human *willSort)
{
	human *iter, *iterator;
	int choose, shortName;
	printf("1-Sort by Name\n");
	printf("2-Sort by Telephone\n");
	printf("Your Choose :");
	scanf("%d", &choose);
	for (iter = willSort; iter != NULL; iter = iter->next)
	{
		for (iterator = iter; iterator != NULL; iterator = iterator->next)
		{
			if (choose == 1)
			{
				shortName = ShortString(iter, iterator);
				relocateBox(shortName, iter, iterator, choose);
			}
			else if (choose == 2)
			{
				relocateBox(0, iter, iterator, choose);
			}
			else
			{
				printf("Unvalid Choose");
				break;
			}
		}
	}
}

int counter(int choice, human *iter, char name[40])
{
	int count = 0;
	while (iter != NULL)
	{
		if (choice == 1)
		{
			if (!strcmp(iter->firstname, name))
			{
				count += 1;
			}
		}
		if (choice == 2)
		{
			if (!strcmp(iter->lastname, name))
			{
				count += 1;
			}
		}
		iter = iter->next;
	}
	return count;
}

void update(human *willUpdate, human *root)
{
	int choice;
	while (1 == 1)
	{
		printf("\n1-Update Name");
		printf("\n2-Update Surname");
		printf("\n3-Update Telephone");
		printf("\nYour Choose : ");
		scanf("%d", &choice);

		if (choice == 0)
		{
			Menu(root);
		}
		else if (choice == 1)
		{
			printf("\nNew Name : ");
			scanf("%s", willUpdate->firstname);
			break;
		}
		else if (choice == 2)
		{
			printf("\nNew Surname : ");
			scanf("%s", willUpdate->lastname);
			break;
		}
		else if (choice == 3)
		{
			printf("\nNew Telephone : ");
			scanf("%d", &willUpdate->telephone);
			break;
		}
		else
		{
			printf("Unvalid Choose...");
		}
	}
}
