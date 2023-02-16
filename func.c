#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

Node *merge_sorted_lists(Node *list1, Node *list2) // Функция соединения двух отсортированых списков
{                                                  // в новый список
    if (list1 == NULL) return list2; // Если связный список пустой
    if (list2 == NULL) return list1;

    Node *l1current, *l2current; // Переменные, которые отвечают за значенния первого, второго и нового
    Node *new_head, *newcurrent; // связного списка

    l1current = list1;
    l2current = list2;

    if (l1current->value <= l2current->value) // Блок для определения начала связного списка
    {
        new_head = l1current;
        l1current = l1current->next; // Сдвиг вперед
    }
    else
    {
        new_head = l2current;
        l2current = l2current->next;
    }
    newcurrent = new_head; // Присваиваем значения нового начала переменной newcurrent

    while (l1current != NULL && l2current != NULL) // Блок для определения меньшего значения
    {                                              // в списках
        if (l1current->value <= l2current->value)
        {
            newcurrent->next = l1current;
            newcurrent = l1current;
            l1current = l1current->next; // Сдвиг вперед
        }
        else
        {
            newcurrent->next = l2current;
            newcurrent = l2current;
            l1current = l2current->next;
        }
    }

    if (l1current == NULL) // Если первый список закончился указываем на значения второго
    {
        newcurrent->next = l2current;
    }
    else if (l2current == NULL)
    {
        newcurrent = l1current;
    }
    return new_head;
}

Node *duplicate_list(Node *head)
{
    if (head == NULL) return NULL; // Замкнутая форма, если дошли до конца списка возвращаем NULL

    Node *new_node = calloc(1, sizeof(Node)); // Создание новых нодов
    new_node->value = head->value; // Дублирования значения в переменную new_node

    new_node->next = duplicate_list(head->next); // Рекурсивная форма, дублирования последующего нода

    return new_node;
}

void add_list_recursive(Node *head1, Node *head2)
{
    if (head1 == NULL || head2 == NULL) return; // Замкнутая форма, если дошли до конца списка возвращаем NULL
    head1->value = head1->value + head2->value;
    add_list_recursive(head1->next, head2->next); // Рекурсивная форма, сдвигает ноды вперед
}

Node *add_list(Node *head1, Node *head2)
{
    if (head1 == NULL) return head2;

    Node *current1, *current2;
    current1 = head1;
    current2 = head2;

    if (length(head1) == length(head2))
    {
        while (current1 != NULL)
        {
            current1->value = current1->value + current2->value;
            current1 = current1->next;
            current2 = current2->next;
        }

    }
    else if (length(head1) < length(head2))
    {
        while (current2->next != NULL)
        {
            current1->value = current1->value + current2->value;
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    else
    {
        while (current1->next != NULL)
        {
            current1->value = current1->value + current2->value;
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    return head1;
}

Node *delete_list(Node *node)
{
    if (node != NULL) // Рекурсивно поочередно "удаляем" ноды
    {
        delete_list(node->next);
        free(node);
    }
    return NULL;
}

Node *insert_after(Node *head, int new_value, int after_value) // Функция вставки нода после
{                                                              // определенного числа
    Node *new_node = calloc(1, sizeof(Node)); // Создание нода
    new_node->value = new_value;

    if (head == NULL) return new_node; // Если список пустой возвращаем новый нод
    else
    {
        Node *current = head;
        while (current->next != NULL) // Проверка каждого нода
        {
            if (current->value == after_value)
            {
                new_node->next = current->next;//Новый нод указывает на следующий нод после current->value
                current->next = new_node; // А current нод указывает на новый нод
                return head;
            }
            else current = current->next; // Если не нашли after_value продолжаем сдвиг вперед
        }
        // Если мы дошли до конца списка и не нашли after_value, то делаем вставку в конце списка
        new_node->next = current->next; // new_node указывает на NULL
        current->next = new_node;// А current на новый нод
        return head;
    }
}

void delete_all_duplicates(Node *head)
{
    if (head == NULL) return ;
    if (head->next == NULL) return ;

    Node *current1, *current2, *duplicate; // Инициализация "счетчиков" current1 и current2
    current1 = head;

    while (current1 != NULL && current1->next != NULL) // Внешним циклом проходимся по всем нодам
    {
        current2 = current1; // Присваиваем значения счетчика

        while (current2->next != NULL) // Внутренний цикл используем для сравнения нод между собой
        {
            if (current1->value == current2->next->value) // Если значения внешнего счетчика равно
            {                                             // значению последующего внутреннего счетчика
                duplicate = current2->next;
                current2->next = current2->next->next; // Присваиваем значения последующего нода
                free(duplicate);
            }
            else current2 = current2->next; // Если дубликата нет, сдвигаем "счетчик" вперед
        }

        current1 = current1->next; // Сдвигаем нод вперед
    }
}

void *sort_list (Node *head) // Сортировка пузырьком
{
    if (head == NULL) return NULL;
    if (head->next == NULL) return NULL;

    bool swapped = false; // Переменная swapped отвечает за внешний цикл
    do // Внешний цикл
    {
        swapped = false;
        Node *current = head; // Инициализация "счетчиков" current и prev
        Node *prev = NULL;

        while (current->next != NULL) // Внутренний цикл
        {
            prev = current;
            current = current->next;
            if (current != NULL)
            {
                if (current->value < prev->value) // Стандартный алгоритм обмена значений
                {
                    int tmp = prev->value;
                    prev->value = current->value;
                    current->value = tmp;
                    swapped = true;
                }
            }
        }
    }while (swapped);

}

Node *reverse_list(Node *head)
{
    if (head == NULL) return NULL; // Если список пустой
    if (head->next == NULL) return NULL; // Если в списке один нод

    Node *current = head;
    Node *next_node = head->next;

    current->next = NULL;  // Начало списка должно стать концом, поэтому current->next должен указывать на NULL

    while (next_node != NULL) // Все остальные ноды нужно настроить так, чтобы они указывали на предыдущий нод
    {
        Node *tmp = next_node->next;
        next_node->next = current;
        current = next_node;
        next_node = tmp;
    }
    return current;
}

Node *append_list(Node *head1, Node *head2) // Функция соединения двух списков
{
    if (head1 == NULL) return head2;

    Node *current = head1;
    while (current->next != NULL) current = current->next; // Сдвигаем пока current не будет указывать на last нод
    current->next = head2; // Последний нод указывает на начало второго списка
    return head1;
}

Node *efficient_delete_match(Node *head, int delete_value, int *num_delete)
{
    *num_delete = 0;
    if (head == NULL) return NULL; // Если связный список пустой возвращаем NULL

    Node *current, *temp, *new_head;
    current = head; // Присваиваем переменной current начало списка
    while (current->value == delete_value) // Если первый нод связного списка равен delete_value
    {
        temp = current; // Присваиваем переменной temp значения current для подальшего "удаления"
        current = current->next; // Теперь current указывает на следуйщий нод
        free(temp); // "Удаляем" повторный нод
        *num_delete = *num_delete + 1;
        if (current == NULL) return NULL; // Если дошли до конца и весь связный список равен delete_value
    }

    new_head = current;

    while (current->next != NULL) // Если delete_value в середине списка
    {
        if (current->next->value == delete_value) // Если значения последующего нода равно delete_value
        {
            temp = current->next; // Присваиваем переменной temp значения current->next для подальшего "удаления"
            current->next = current->next->next;
            free(temp); // "Удаляем" повторный нод
            *num_delete = *num_delete + 1;
        }
        else current = current->next; // current указывает на "неудаляемый" нод
    }

    return new_head;
}

Node *delete_all_matches (Node *head, int delete_value, int *num_deleted) // "Энергозатратный" метод
{
    Node *current = head; // Если первый нод нужно удалить, current будет началом
    bool deleted = false;
    *num_deleted = 0;

    do // Пока deleted = 1 выполняем цикл
    {
        current = delete_first_match(current, delete_value, &deleted);
        if (deleted) *num_deleted = *num_deleted + 1; // Если deleted 1 прибавляем один
    }while (deleted);

    return current;

}

Node *delete_first_match(Node *head, int delete_value, bool *was_deleted)
{
    if (head == NULL) // Если связный список пустой возвращаем NULL
    {
        *was_deleted = false;
        return NULL;
    }

    if (head->value == delete_value) // Если начало связного списка нужно удалить
    {
        Node *temp = head->next; // Присваиваем значенния следующего начала списка
        free(head); // "Удаляем" нод
        *was_deleted = true;
        return temp; // Возвращаем начало списка
    }

    Node *current = head->next;
    Node *prev = head;

    while (current != NULL) // Если удаляемый нод в середине связного списка
    {
        if (current->value == delete_value)
        {
            prev->next = current->next; // Указываем на следующий нод
            free(current); // "Удаляем" нод
            *was_deleted = true;
            return head;
        }
        prev = current; // Сдвигаем элементы
        current = current->next;
    }

    *was_deleted = false; // Если ничего не нашли
    return head;

}

void replace_matches(Node *node, int search_value, int replace_value)
{
    if (node != NULL)
    {
       if (node->value == search_value)
           node->value = replace_value;

       replace_matches(node->next, search_value, replace_value);
    }
}

int count_matches(Node *node, int search_value)
{
    if (node == NULL) return 0;
    else if (node->value == search_value) return 1 + count_matches(node->next, search_value);
    else return count_matches(node->next, search_value);
}

bool is_member(Node *node, int search_value)
{
    if (node == NULL) return false;
    else if (node->value == search_value) return true;
    else return is_member(node->next, search_value);
}

int recursive_length(Node *node)
{
    if (node == NULL) return 0;
    else return 1 + recursive_length(node->next);
}

int length(Node *head)
{
    int length = 0;
    Node *current = head;
    while (current != NULL) // Сдвиг текущего нода на один
    {
        length++;
        current = current->next; // Присвоения текущему ноду значения последующего
    }
    return length;
}

Node *delete_at_tail(Node *head)
{
    if (head == NULL) return NULL; // Если связный список пустой возвращаем NULL
    else if (head->next == NULL) // Если в связном списке 1 нод
    {
        free(head); // "УДАЛЯЕМ" нод
        return NULL;
    }
    else
    {
        Node *current = head; // Указатель на начало списка
        Node *prev = NULL; // Указатель на нод предыдущий current

        while (current->next != NULL) // Проходимся по всему списку,
        {
            prev = current;           // присваиваем значения текущего нода
            current = current->next;  // сдвигаем переменну на 1 нод
        }

        prev->next = NULL; // Присваиваем значения конца списка
        free(current); // "УДАЛЯЕМ" нод
        return head;
    }

}

Node *delete_at_head(Node *head)
{
    if (head == NULL) return NULL; // Если связный список пустой возвращаем NULL
    else
    {
        Node *to_return = head->next; // Создаем указатель, которому присваиваем значения следующего нода
        free(head); // "УДАЛЯЕМ" нод в начале списка
        return to_return;
    }
}

Node *insert_at_tail(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node)); // Создаем новый нод
    new_node->value = new_value;

    if (head == NULL) return new_node; // Если связный список пустой, возвращаем значения new_node
    else
    {
        Node *current = head;
        while(current->next != NULL) current = current->next; /* Пока не дойдем до последнего элемента,
                                                                 сдвигаем значения current на один элемент*/
        current->next = new_node; // Присваиваем последнему элементу значения new_node
        return head; // Возвращаем указатель на начало списка
    }
}

Node *insert_at_head(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node)); // Создаем новый нод
    new_node->value = new_value;

    if (head == NULL) return new_node; // Если связный список пустой, возвращаем значения new_node
    else /* Если связный список НЕ пустой,
            присваиваем значения следуещего нода значения head, возвращаем значения new_node*/
    {
        new_node->next = head;
        return new_node;
    }

}

void print_list(Node *head)
{
    Node *current = head;
    int i = 0;
    while (current != NULL)
    {
        printf("Node %d: %d\n", i++, current->value);
        current = current->next;
    }

}
