#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;
extern int greater;
extern int smaller;
extern int equal;

// void copy_list(Dlist *src, Dlist **dest_head, Dlist **dest_tail);
int compare(Dlist *head1, Dlist *head2);
int read_and_validate(int argc, char *argv[]);
int is_num(char *str);  
int convert_string_to_list(const char *str, Dlist **head);
void print_list(Dlist *head);
void print_number(Dlist *head);
int addition(Dlist **head1, Dlist **head2, Dlist **result,
              Dlist **tail1,Dlist **tail2, Dlist **rtail);
int insert_first(Dlist **head, Dlist **tail, int data);
int subtraction(Dlist **head1, Dlist **head2, Dlist **result,
                Dlist **tail1, Dlist **tail2, Dlist **rtail);
int multiplication(Dlist **head1, Dlist **head2,Dlist **result,
                        Dlist **tail1,Dlist **tail2,Dlist **rtail);
int division(Dlist **head1, Dlist **head2,Dlist **result,
                        Dlist **tail1,Dlist **tail2,Dlist **rtail);

int dl_delete_list(Dlist **head, Dlist **tail);
#endif