#include<iostream>
#include<stdio.h>


/*
Реализовать функции для обработки списка(по варианту) : ​​​
-Найти среднее арифметическое значение элементов списка
-Определить, входит ли список L1 в L2. Вернуть адрес начала вхождения (нулевой адрес в противном случае).
*/
struct Item
{
	int value;
	Item* next;
};

void Push_back(int value, Item** item) {

	if (*item == NULL) {
		*item = (Item*)malloc(sizeof(Item));
		(*item)->value = value;
		(*item)->next = NULL;
		return;
	}
	else {
		Push_back(value, &(*item)->next);
	}
}

Item* GetItemByPos(int pos, Item* item) {
	if (pos <= 0) {
		printf("Enter position > 0\n");
		return NULL;
	}
	for (int i = 0; i < pos - 1; i++)
	{
		if (item != NULL) {
			item = item->next;
		}
		else
		{
			printf("The position value is more than the count of items!\n");
			return NULL;
		}
	}
	return item;
}

int GetValueByPos(int pos, Item* item) {
	if (pos <= 0) {
		printf("Enter position > 0\n");
		return INT16_MIN;
	}
	for (int i = 0; i < pos - 1; i++)
	{
		if (item != NULL) {
			item = item->next;
		}
		else
		{
			printf("The position value is more than the count of items!\n");
			return INT16_MIN;
		}
	}
	return item->value;
}

Item* Push(int value, int pos, Item** item) {
	if (pos <= 0) {
		printf("Enter position > 0\n");
		return *item;
	}
	if (pos == 1) {
		Item* tmp = (Item*)malloc(sizeof(Item));
		tmp->value = value;
		tmp->next = *item;
		return tmp;
	}
	Item* pred = GetItemByPos(pos - 1, *item);
	Item* next = GetItemByPos(pos, *item);
	if (GetItemByPos(pos-1, *item) != NULL) {
		Item* newItem = (Item*)malloc(sizeof(Item));
		newItem->value = value;
		pred->next = newItem;
		newItem->next = next;
		return *item;
	}
	else
	{
		return *item;
	}
}

Item* Pop(int pos, Item** item) {
	if (pos <= 0) {
		printf("Enter position > 0\n");
		return *item;
	}
	if (pos == 1) {
		Item* tmp = (*item)->next;
		free(*item);
		return tmp;
	}
	Item* pred = GetItemByPos(pos - 1, *item);
	Item* next = GetItemByPos(pos + 1, *item);
	if (GetItemByPos(pos - 1, *item) != NULL) {
		free(GetItemByPos(pos, *item));
		pred->next = next;
		return *item;
	}
	else
	{
		return *item;
	}
}

int ListSize(Item* item) {
	int cnt = 0;
	while (item != NULL) {
		cnt++;
		item = item->next;
	}
	return cnt;
}

void PrintList(Item* item) {
	printf("List of items:\n");
	while (item != NULL) {
		printf("%d ", item->value);
		item = item->next;
	}
	printf("\n");
}

int main() {
	Item* arr = (Item*)malloc(sizeof(Item));
	arr->value = 0;
	arr->next = NULL;

	Push_back(1, &arr);
	Push_back(2, &arr);
	Push_back(4, &arr);

	arr = Push(3, 4, &arr);
	PrintList(arr);
	printf("%d\n", ListSize(arr));

	arr = Pop(3,&arr);
	PrintList(arr);
	printf("%d\n", ListSize(arr));
	return 0;
}