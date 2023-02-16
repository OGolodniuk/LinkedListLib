#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"
//
Node *merge_sorted_lists(Node *list1, Node *list2) // Ôóíêöèÿ ñîåäèíåíèÿ äâóõ îòñîðòèðîâàíûõ ñïèñêîâ
{                                                  // â íîâûé ñïèñîê
    if (list1 == NULL) return list2; // Åñëè ñâÿçíûé ñïèñîê ïóñòîé
    if (list2 == NULL) return list1;

    Node *l1current, *l2current; // Ïåðåìåííûå, êîòîðûå îòâå÷àþò çà çíà÷åííèÿ ïåðâîãî, âòîðîãî è íîâîãî
    Node *new_head, *newcurrent; // ñâÿçíîãî ñïèñêà

    l1current = list1;
    l2current = list2;

    if (l1current->value <= l2current->value) // Áëîê äëÿ îïðåäåëåíèÿ íà÷àëà ñâÿçíîãî ñïèñêà
    {
        new_head = l1current;
        l1current = l1current->next; // Ñäâèã âïåðåä
    }
    else
    {
        new_head = l2current;
        l2current = l2current->next;
    }
    newcurrent = new_head; // Ïðèñâàèâàåì çíà÷åíèÿ íîâîãî íà÷àëà ïåðåìåííîé newcurrent

    while (l1current != NULL && l2current != NULL) // Áëîê äëÿ îïðåäåëåíèÿ ìåíüøåãî çíà÷åíèÿ
    {                                              // â ñïèñêàõ
        if (l1current->value <= l2current->value)
        {
            newcurrent->next = l1current;
            newcurrent = l1current;
            l1current = l1current->next; // Ñäâèã âïåðåä
        }
        else
        {
            newcurrent->next = l2current;
            newcurrent = l2current;
            l1current = l2current->next;
        }
    }

    if (l1current == NULL) // Åñëè ïåðâûé ñïèñîê çàêîí÷èëñÿ óêàçûâàåì íà çíà÷åíèÿ âòîðîãî
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
    if (head == NULL) return NULL; // Çàìêíóòàÿ ôîðìà, åñëè äîøëè äî êîíöà ñïèñêà âîçâðàùàåì NULL

    Node *new_node = calloc(1, sizeof(Node)); // Ñîçäàíèå íîâûõ íîäîâ
    new_node->value = head->value; // Äóáëèðîâàíèÿ çíà÷åíèÿ â ïåðåìåííóþ new_node

    new_node->next = duplicate_list(head->next); // Ðåêóðñèâíàÿ ôîðìà, äóáëèðîâàíèÿ ïîñëåäóþùåãî íîäà

    return new_node;
}

void add_list_recursive(Node *head1, Node *head2)
{
    if (head1 == NULL || head2 == NULL) return; // Çàìêíóòàÿ ôîðìà, åñëè äîøëè äî êîíöà ñïèñêà âîçâðàùàåì NULL
    head1->value = head1->value + head2->value;
    add_list_recursive(head1->next, head2->next); // Ðåêóðñèâíàÿ ôîðìà, ñäâèãàåò íîäû âïåðåä
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
    if (node != NULL) // Ðåêóðñèâíî ïîî÷åðåäíî "óäàëÿåì" íîäû
    {
        delete_list(node->next);
        free(node);
    }
    return NULL;
}

Node *insert_after(Node *head, int new_value, int after_value) // Ôóíêöèÿ âñòàâêè íîäà ïîñëå
{                                                              // îïðåäåëåííîãî ÷èñëà
    Node *new_node = calloc(1, sizeof(Node)); // Ñîçäàíèå íîäà
    new_node->value = new_value;

    if (head == NULL) return new_node; // Åñëè ñïèñîê ïóñòîé âîçâðàùàåì íîâûé íîä
    else
    {
        Node *current = head;
        while (current->next != NULL) // Ïðîâåðêà êàæäîãî íîäà
        {
            if (current->value == after_value)
            {
                new_node->next = current->next;//Íîâûé íîä óêàçûâàåò íà ñëåäóþùèé íîä ïîñëå current->value
                current->next = new_node; // À current íîä óêàçûâàåò íà íîâûé íîä
                return head;
            }
            else current = current->next; // Åñëè íå íàøëè after_value ïðîäîëæàåì ñäâèã âïåðåä
        }
        // Åñëè ìû äîøëè äî êîíöà ñïèñêà è íå íàøëè after_value, òî äåëàåì âñòàâêó â êîíöå ñïèñêà
        new_node->next = current->next; // new_node óêàçûâàåò íà NULL
        current->next = new_node;// À current íà íîâûé íîä
        return head;
    }
}

void delete_all_duplicates(Node *head)
{
    if (head == NULL) return ;
    if (head->next == NULL) return ;

    Node *current1, *current2, *duplicate; // Èíèöèàëèçàöèÿ "ñ÷åò÷èêîâ" current1 è current2
    current1 = head;

    while (current1 != NULL && current1->next != NULL) // Âíåøíèì öèêëîì ïðîõîäèìñÿ ïî âñåì íîäàì
    {
        current2 = current1; // Ïðèñâàèâàåì çíà÷åíèÿ ñ÷åò÷èêà

        while (current2->next != NULL) // Âíóòðåííèé öèêë èñïîëüçóåì äëÿ ñðàâíåíèÿ íîä ìåæäó ñîáîé
        {
            if (current1->value == current2->next->value) // Åñëè çíà÷åíèÿ âíåøíåãî ñ÷åò÷èêà ðàâíî
            {                                             // çíà÷åíèþ ïîñëåäóþùåãî âíóòðåííåãî ñ÷åò÷èêà
                duplicate = current2->next;
                current2->next = current2->next->next; // Ïðèñâàèâàåì çíà÷åíèÿ ïîñëåäóþùåãî íîäà
                free(duplicate);
            }
            else current2 = current2->next; // Åñëè äóáëèêàòà íåò, ñäâèãàåì "ñ÷åò÷èê" âïåðåä
        }

        current1 = current1->next; // Ñäâèãàåì íîä âïåðåä
    }
}

void *sort_list (Node *head) // Ñîðòèðîâêà ïóçûðüêîì
{
    if (head == NULL) return NULL;
    if (head->next == NULL) return NULL;

    bool swapped = false; // Ïåðåìåííàÿ swapped îòâå÷àåò çà âíåøíèé öèêë
    do // Âíåøíèé öèêë
    {
        swapped = false;
        Node *current = head; // Èíèöèàëèçàöèÿ "ñ÷åò÷èêîâ" current è prev
        Node *prev = NULL;

        while (current->next != NULL) // Âíóòðåííèé öèêë
        {
            prev = current;
            current = current->next;
            if (current != NULL)
            {
                if (current->value < prev->value) // Ñòàíäàðòíûé àëãîðèòì îáìåíà çíà÷åíèé
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
    if (head == NULL) return NULL; // Åñëè ñïèñîê ïóñòîé
    if (head->next == NULL) return NULL; // Åñëè â ñïèñêå îäèí íîä

    Node *current = head;
    Node *next_node = head->next;

    current->next = NULL;  // Íà÷àëî ñïèñêà äîëæíî ñòàòü êîíöîì, ïîýòîìó current->next äîëæåí óêàçûâàòü íà NULL

    while (next_node != NULL) // Âñå îñòàëüíûå íîäû íóæíî íàñòðîèòü òàê, ÷òîáû îíè óêàçûâàëè íà ïðåäûäóùèé íîä
    {
        Node *tmp = next_node->next;
        next_node->next = current;
        current = next_node;
        next_node = tmp;
    }
    return current;
}

Node *append_list(Node *head1, Node *head2) // Ôóíêöèÿ ñîåäèíåíèÿ äâóõ ñïèñêîâ
{
    if (head1 == NULL) return head2;

    Node *current = head1;
    while (current->next != NULL) current = current->next; // Ñäâèãàåì ïîêà current íå áóäåò óêàçûâàòü íà last íîä
    current->next = head2; // Ïîñëåäíèé íîä óêàçûâàåò íà íà÷àëî âòîðîãî ñïèñêà
    return head1;
}

Node *efficient_delete_match(Node *head, int delete_value, int *num_delete)
{
    *num_delete = 0;
    if (head == NULL) return NULL; // Åñëè ñâÿçíûé ñïèñîê ïóñòîé âîçâðàùàåì NULL

    Node *current, *temp, *new_head;
    current = head; // Ïðèñâàèâàåì ïåðåìåííîé current íà÷àëî ñïèñêà
    while (current->value == delete_value) // Åñëè ïåðâûé íîä ñâÿçíîãî ñïèñêà ðàâåí delete_value
    {
        temp = current; // Ïðèñâàèâàåì ïåðåìåííîé temp çíà÷åíèÿ current äëÿ ïîäàëüøåãî "óäàëåíèÿ"
        current = current->next; // Òåïåðü current óêàçûâàåò íà ñëåäóéùèé íîä
        free(temp); // "Óäàëÿåì" ïîâòîðíûé íîä
        *num_delete = *num_delete + 1;
        if (current == NULL) return NULL; // Åñëè äîøëè äî êîíöà è âåñü ñâÿçíûé ñïèñîê ðàâåí delete_value
    }

    new_head = current;

    while (current->next != NULL) // Åñëè delete_value â ñåðåäèíå ñïèñêà
    {
        if (current->next->value == delete_value) // Åñëè çíà÷åíèÿ ïîñëåäóþùåãî íîäà ðàâíî delete_value
        {
            temp = current->next; // Ïðèñâàèâàåì ïåðåìåííîé temp çíà÷åíèÿ current->next äëÿ ïîäàëüøåãî "óäàëåíèÿ"
            current->next = current->next->next;
            free(temp); // "Óäàëÿåì" ïîâòîðíûé íîä
            *num_delete = *num_delete + 1;
        }
        else current = current->next; // current óêàçûâàåò íà "íåóäàëÿåìûé" íîä
    }

    return new_head;
}

Node *delete_all_matches (Node *head, int delete_value, int *num_deleted) // "Ýíåðãîçàòðàòíûé" ìåòîä
{
    Node *current = head; // Åñëè ïåðâûé íîä íóæíî óäàëèòü, current áóäåò íà÷àëîì
    bool deleted = false;
    *num_deleted = 0;

    do // Ïîêà deleted = 1 âûïîëíÿåì öèêë
    {
        current = delete_first_match(current, delete_value, &deleted);
        if (deleted) *num_deleted = *num_deleted + 1; // Åñëè deleted 1 ïðèáàâëÿåì îäèí
    }while (deleted);

    return current;

}

Node *delete_first_match(Node *head, int delete_value, bool *was_deleted)
{
    if (head == NULL) // Åñëè ñâÿçíûé ñïèñîê ïóñòîé âîçâðàùàåì NULL
    {
        *was_deleted = false;
        return NULL;
    }

    if (head->value == delete_value) // Åñëè íà÷àëî ñâÿçíîãî ñïèñêà íóæíî óäàëèòü
    {
        Node *temp = head->next; // Ïðèñâàèâàåì çíà÷åííèÿ ñëåäóþùåãî íà÷àëà ñïèñêà
        free(head); // "Óäàëÿåì" íîä
        *was_deleted = true;
        return temp; // Âîçâðàùàåì íà÷àëî ñïèñêà
    }

    Node *current = head->next;
    Node *prev = head;

    while (current != NULL) // Åñëè óäàëÿåìûé íîä â ñåðåäèíå ñâÿçíîãî ñïèñêà
    {
        if (current->value == delete_value)
        {
            prev->next = current->next; // Óêàçûâàåì íà ñëåäóþùèé íîä
            free(current); // "Óäàëÿåì" íîä
            *was_deleted = true;
            return head;
        }
        prev = current; // Ñäâèãàåì ýëåìåíòû
        current = current->next;
    }

    *was_deleted = false; // Åñëè íè÷åãî íå íàøëè
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
    while (current != NULL) // Ñäâèã òåêóùåãî íîäà íà îäèí
    {
        length++;
        current = current->next; // Ïðèñâîåíèÿ òåêóùåìó íîäó çíà÷åíèÿ ïîñëåäóþùåãî
    }
    return length;
}

Node *delete_at_tail(Node *head)
{
    if (head == NULL) return NULL; // Åñëè ñâÿçíûé ñïèñîê ïóñòîé âîçâðàùàåì NULL
    else if (head->next == NULL) // Åñëè â ñâÿçíîì ñïèñêå 1 íîä
    {
        free(head); // "ÓÄÀËßÅÌ" íîä
        return NULL;
    }
    else
    {
        Node *current = head; // Óêàçàòåëü íà íà÷àëî ñïèñêà
        Node *prev = NULL; // Óêàçàòåëü íà íîä ïðåäûäóùèé current

        while (current->next != NULL) // Ïðîõîäèìñÿ ïî âñåìó ñïèñêó,
        {
            prev = current;           // ïðèñâàèâàåì çíà÷åíèÿ òåêóùåãî íîäà
            current = current->next;  // ñäâèãàåì ïåðåìåííó íà 1 íîä
        }

        prev->next = NULL; // Ïðèñâàèâàåì çíà÷åíèÿ êîíöà ñïèñêà
        free(current); // "ÓÄÀËßÅÌ" íîä
        return head;
    }

}

Node *delete_at_head(Node *head)
{
    if (head == NULL) return NULL; // Åñëè ñâÿçíûé ñïèñîê ïóñòîé âîçâðàùàåì NULL
    else
    {
        Node *to_return = head->next; // Ñîçäàåì óêàçàòåëü, êîòîðîìó ïðèñâàèâàåì çíà÷åíèÿ ñëåäóþùåãî íîäà
        free(head); // "ÓÄÀËßÅÌ" íîä â íà÷àëå ñïèñêà
        return to_return;
    }
}

Node *insert_at_tail(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node)); // Ñîçäàåì íîâûé íîä
    new_node->value = new_value;

    if (head == NULL) return new_node; // Åñëè ñâÿçíûé ñïèñîê ïóñòîé, âîçâðàùàåì çíà÷åíèÿ new_node
    else
    {
        Node *current = head;
        while(current->next != NULL) current = current->next; /* Ïîêà íå äîéäåì äî ïîñëåäíåãî ýëåìåíòà,
                                                                 ñäâèãàåì çíà÷åíèÿ current íà îäèí ýëåìåíò*/
        current->next = new_node; // Ïðèñâàèâàåì ïîñëåäíåìó ýëåìåíòó çíà÷åíèÿ new_node
        return head; // Âîçâðàùàåì óêàçàòåëü íà íà÷àëî ñïèñêà
    }
}

Node *insert_at_head(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node)); // Ñîçäàåì íîâûé íîä
    new_node->value = new_value;

    if (head == NULL) return new_node; // Åñëè ñâÿçíûé ñïèñîê ïóñòîé, âîçâðàùàåì çíà÷åíèÿ new_node
    else /* Åñëè ñâÿçíûé ñïèñîê ÍÅ ïóñòîé,
            ïðèñâàèâàåì çíà÷åíèÿ ñëåäóåùåãî íîäà çíà÷åíèÿ head, âîçâðàùàåì çíà÷åíèÿ new_node*/
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
