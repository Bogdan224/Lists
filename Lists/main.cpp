#include<iostream>
#include<stdio.h>
/*
Реализовать функции для обработки списка(по варианту) : ​​​
-
-Определить, входит ли список L1 в L2. Вернуть адрес начала вхождения (нулевой адрес в противном случае).
*/
struct Item
{
	int value;
	Item* next;
};

int ListSize(Item* item);

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
	//Неверный ввод позиции
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
	//Неверный ввод позиции
	if (pos <= 0) {
		printf("Enter position > 0\n");
		return *item;
	}
	//Если нужно добавить объект в начало, создаем новый объект и присваем в "next" наш список
	else if (pos == 1) {
		Item* tmp = (Item*)malloc(sizeof(Item));
		tmp->value = value;
		tmp->next = *item;
		return tmp;
	}
	//Неверный ввод позиции
	else if (pos > ListSize(*item)) {
		printf("Enter position > list size\n");
		return *item;
	}
	//Создаем два указателя, в которых хранятся объект, на место которого мы хотим поставить наш объект и предыдущий от него объект
	Item* pred = GetItemByPos(pos - 1, *item);
	Item* next = GetItemByPos(pos, *item);
	//Проверка на null предыдущего объекта
	if (GetItemByPos(pos-1, *item) != NULL) {
		//Выделяем память для нового объекта, предыдущий пересвязываем с новым и к новому добавляем ссылку на следующий
		Item* newItem = (Item*)malloc(sizeof(Item));
		newItem->value = value;
		pred->next = newItem;
		newItem->next = next;
	}
	return *item;
}

Item* Pop(int pos, Item** item) {
	//Неверный ввод позиции
	if (pos <= 0) {
		printf("Enter position > 0\n");
		return *item;
	}
	//Если нужно удалить первый объект, сохраняем указатель на второй объект и удаляем первый 
	else if (pos == 1) {
		Item* tmp = (*item)->next;
		free(*item);
		return tmp;
	}
	//Неверный ввод позиции
	else if (pos > ListSize(*item)) {
		printf("Enter position > list size\n");
		return *item;
	}
	//Создаем два указателя, в которых хранятся предыдущий и следующий объект от выбранного
	Item* pred = GetItemByPos(pos - 1, *item);
	Item* next = GetItemByPos(pos + 1, *item);
	//Проверка на null предыдущего объекта
	if (GetItemByPos(pos - 1, *item) != NULL) {
		//Освобождаем память выбранного объекта и связываем предыдущий со следующим объектом
		free(GetItemByPos(pos, *item));
		pred->next = next;
	}
	return *item;
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

//Найти среднее арифметическое значение элементов списка
float ArithmeticMean(Item* item) {
	int result = 0, size = ListSize(item);

	while (item != NULL) {
		result += item->value;
		item = item->next;
	}

	return result / size;
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

	printf("The Arithmetic mean: %f\n", ArithmeticMean(arr));

	free(arr);
	return 0;
}