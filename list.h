#include <stdbool.h>
typedef struct node{
    int value;
    struct node *next;
}Node;

void print_list(Node *head);
Node *insert_at_head(Node *head, int new_value);
Node *insert_at_tail(Node *head, int new_value);
Node *delete_at_head(Node *head);
Node *delete_at_tail(Node *head);
int length(Node *head);
int recursive_length(Node *node);
int count_matches(Node *node, int search_value);
bool is_member(Node *node, int search_value);
void replace_matches(Node *node, int search_value, int replace_value);
Node *delete_first_match(Node *head, int delete_value, bool *was_deleted);
Node *delete_all_matches(Node *head, int delete_value, int *num_deleted);
Node *efficient_delete_match(Node *head, int delete_value, int *num_delete);
Node *append_list(Node *head1, Node *head2);
Node *reverse_list(Node *head);
void *sort_list(Node *head);
void delete_all_duplicates(Node *head);
Node *insert_after(Node *head, int new_value, int after_value);
Node *delete_list(Node *node);
Node *add_list(Node *head1, Node *head2);
void add_list_recursive(Node *head1, Node *head2);
Node *duplicate_list(Node *head);
Node *merge_sorted_lists(Node *list1, Node *list2);
