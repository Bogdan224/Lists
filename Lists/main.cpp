#include<stdio.h>
#include<iostream>
#define _CRT_SECURE_NO_WARNINGS

struct Item
{
	int value;
	Item* next;
};

int ListSize(Item* item);

//Добавляет объект в конец списка
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

//Возращает указатель на объект в заданной позиции
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

//Возращает значение объекта в заданной позиции(минимальное значение при неверных данных)
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

//Добавляет в список объект в позицию pos и возвращает отредактированный список
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
	else if (pos > ListSize(*item)+1) {
		printf("Enter position < list size\n");
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

//Удаляет из список объект с позицией pos и возвращает отредактированный список
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
		printf("Enter position < list size\n");
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

//Возвращает кол-во элементов в списке
int ListSize(Item* item) {
	int cnt = 0;
	while (item != NULL) {
		cnt++;
		item = item->next;
	}
	return cnt;
}

//Выводит все значения в списке
void PrintList(Item* item) {
	if (item == NULL) {
		printf("List is empty!\n");
		return;
	}
	printf("List of items:\n");
	while (item != NULL) {
		printf("%d ", item->value);
		item = item->next;
	}
	printf("\n");
}

//Находит и возвращает среднее арифметическое значение элементов списка
float ArithmeticMean(Item* item) {
	float result = 0, size = ListSize(item);

	while (item != NULL) {
		result += item->value;
		item = item->next;
	}

	return result / size;
}

//Определяет, входит ли список item1 в item2. Возвращает адрес начала вхождения (нулевой адрес в противном случае)
Item* Contains(Item* item1, Item* item2) {
	bool isContains = true;
	if (item1 == NULL || item2 == NULL) {
		return NULL;
	}
	//Создаем указатели для промежуточного хранения адреса, с которого должны начинаться следующие итерации главного цикла
	Item* head1 = item1;
	Item* head2 = item2;
	//проходим по item2, чтобы найти точку входа с одинаковыми значениями
	while (item2 != NULL) {
		if (item2->value == item1->value) {
			//item1 возвращаем в самое начало, а для head2 задаем адрес, в котором мы были до входа во вложенный цикл, чтобы потом вернуться к этому значению
			item1 = head1;
			head2 = item2;
			while (item1 != NULL) {
				//Если условие ни разу не выполняется, значит item1 входит в item2, иначе ищем следующую точку входа
				if (item1->value != item2->value) {
					isContains = false;
					break;
				}
				item1 = item1->next;
				item2 = item2->next;
			}
			item2 = head2;
			//Если условие ни разу не выполнелось, поэтому возвращаем полученное значение
			if (isContains) {
				return item2;
			}
		}
		item2 = item2->next;
	}
	//item1 не содержит item2
	return NULL;
}


int main() {
	Item* arr = NULL;
	int length, val, pos;
	printf("Enter count of values -> ");
	scanf_s("%d", &length);
	
	for (int i = 0; i < length; i++)
	{
		printf("%d) ", i+1);
		scanf_s("%d", &val);
		Push_back(val, &arr);
	}
	
	printf("Enter value -> ");
	scanf_s("%d", &val);
	printf("Enter position in list -> ");
	scanf_s("%d", &pos);
	arr = Push(val, pos, &arr);

	PrintList(arr);
	printf("The List size: %d\n", ListSize(arr));

	/*arr = Pop(3,&arr);
	PrintList(arr);
	printf("%d\n", ListSize(arr));*/

	printf("The Arithmetic mean: %f\n", ArithmeticMean(arr));

	Item* arr1 = NULL;
	printf("Enter count of values -> ");
	scanf_s("%d", &length);

	for (int i = 0; i < length; i++)
	{
		printf("%d) ", i+1);
		scanf_s("%d", &val);
		Push_back(val, &arr1);
	}
  	Item* L1 = Contains(arr1,arr);

	PrintList(L1);
	return 0;
}