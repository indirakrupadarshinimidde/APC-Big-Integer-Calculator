#include "main.h"
#include<string.h>
#include "ctype.h"


int greater = 0;
int smaller = 0;
int equal = 0;

int is_num(char *str)
{
    int i=0;
    if(str[i] == '\0')
    {
        return 0;
    }
    if( str[i] == '+' || str[i] =='-')
    {
        i++;
    }
    while(str[i])
    {
        if(!isdigit(str[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}


 int compare(Dlist *head1, Dlist *head2)
 {
    greater=smaller=equal=0;
    int first=0;
    int second=0;
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while(temp1)
    {
        first++;
        temp1= temp1->next;
    }
    while(temp2)
    {
        second++;
        temp2= temp2->next;
    }
    if(first > second)
    {
       greater = 1;
        return 1;
    }
    else if(first < second)
    {
        smaller = 1;
        return -1;
    }
    
    temp1 = head1;
    temp2 = head2;

    while(temp1 && temp2)
    {
        if(temp1->data > temp2->data)
        {
          greater = 1;
            return 1;
        }
        else if( temp1->data < temp2->data)
        {
            smaller = 1;
            return -1;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    equal = 1;
    return 0;
 }
int read_and_validate(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("Invalid input\n");
        return FAILURE;
    }

    if(strlen(argv[2]) != 1 || (argv[2][0] != '+' &&
                               argv[2][0] != '-' &&
                               argv[2][0] != '*' &&
                               argv[2][0] != '/'))
    {
        printf("Invalid operator\n");
        return FAILURE;
    }

    if(!is_num(argv[1]) || !is_num(argv[3]))
    {
        printf("Invalid operand\n");
        return FAILURE;
    }

    return SUCCESS;
}

int convert_string_to_list(const char *str, Dlist **head)
 {
    int i = 0;

    if (str[i] == '+' || str[i] == '-')
        i++;

    while (str[i] != '\0')
    {
        Dlist *new = malloc(sizeof(Dlist));
        if (new == NULL)
            return FAILURE;

        new->data = str[i] - '0';
        new->prev = NULL;
        new->next = NULL;

        if (*head == NULL)
        {
            *head = new;
        }
        else
        {
            Dlist *temp = *head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = new;
            new->prev = temp;
        }

        i++;
    }
   
    return SUCCESS;
}
void print_number(Dlist *head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}
void print_list(Dlist *head)
{
    if(head == NULL)
    {
        printf("list is empty");
        return;
    }

    printf("head-> ");

    while(head)
    {
        printf("%d", head->data);

        head = head->next;

        if(head)
            printf(" <- -> ");
    }

    printf(" <-Tail\n");
}
//insert before function
 int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*head)->prev = new;
        *head = new;
    }

    return SUCCESS;
}
int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail)->next = new;
        *tail = new;
    }

    return SUCCESS;
}

// function: addition 
int addition(Dlist **head1, Dlist **head2, Dlist **result,
              Dlist **tail1,Dlist **tail2, Dlist **rtail)
{
    int carry=0;
    int res;
    Dlist *tail1_temp = *tail1;
    Dlist *tail2_temp = *tail2;

   while(tail1_temp != NULL || tail2_temp != NULL || carry != 0)
   {
      res = carry; 
        if(tail1_temp != NULL)
        {
            res += tail1_temp->data;      
            tail1_temp = tail1_temp->prev; 
        }

        if(tail2_temp != NULL)
        {
            res += tail2_temp->data;       
            tail2_temp = tail2_temp->prev;
        }
     carry = res /10;
     res = res % 10;

     
     insert_first(result,rtail,res);
     
   }
   return SUCCESS;
}
  // subtraction
  int subtraction(Dlist **head1, Dlist **head2, Dlist **result,
                  Dlist **tail1, Dlist **tail2, Dlist **rtail)
     {
        *result = NULL;
         *rtail = NULL;
       Dlist *temp1 = *tail1;
       Dlist *temp2 = *tail2;
       int borrow = 0;
       int res;
       Dlist *larger = *head1;
       Dlist *smaller = *head2;
       int len1 = 0;
       int len2 = 0;
        
       Dlist *temp;
       temp = *head1;
       
       while(temp)
       {
        len1++;
        temp = temp->next;
       }
        
       temp = *head2;
       while(temp)
       {
        len2++;// mottham enni digits vunnayo cheppaniki
        temp = temp->next;// next digit vunna index ki teeskeltundhi
       }
    //    now compare which one is largest number
      if(len1 < len2)
      {
        larger = *head2;//assigning the head 2 value into larger
        smaller = *head1;//lly head1 to smaller
        temp1 = *tail2;
        temp2 = *tail1;
      }
      else if(len1 == len2)
      {
        temp = *head1;
        Dlist *tem2 = *head2;
        while(temp && tem2)//if both r true
        {
            if(temp->data < tem2->data)
            {
            larger = *head2;
            smaller = *head1;
            temp1 = *tail2;
            temp2 = *tail1;
            break;
            }
        else if(temp->data > tem2->data)
        {
            break;
        }
        temp = temp->next;
        tem2 = tem2->next;
      }
      }
      while(temp1)
      {
        res = temp1->data - borrow;
        if(temp2)
        {
            res = res - temp2->data;
            temp2 = temp2->prev;
        }
        if(res < 0)
        {
            res = res +10;
            borrow = 1;
        }
        else
        borrow = 0; 
    insert_first(result, rtail, res);
    temp1 = temp1->prev;
      }
      return SUCCESS;
    }
    //Multiplication
   int multiplication(Dlist **head1, Dlist **head2, Dlist **result,
                   Dlist **tail1, Dlist **tail2, Dlist **rtail)
{
    Dlist *temp2 = *tail2;
    int count = 0;
  
    while (temp2 != NULL)
    {
        Dlist *temp1 = *tail1;
        Dlist *res1 = NULL;  //head of linkedlist to store rslt   
        Dlist *restail1 = NULL; //tail for result 
        int carry = 0;

        
    // carry = 0 tarvatha 
  for (int i = 0; i < count; i++)
        {
            insert_first(&res1, &restail1, 0);
        }
        while (temp1 != NULL || carry != 0)
        {
            int val1; 
            if (temp1 != NULL) 
            {
              val1 = temp1->data;
            }
          else
           {
                val1 = 0;
           }  
            
            int product = (val1 * temp2->data) + carry;
            insert_first(&res1, &restail1, product % 10);
            carry = product / 10;

            if (temp1 != NULL) 
               temp1 = temp1->prev;
        }

      
        if (*result == NULL)
        {
            
            *result = res1;
            *rtail = restail1;
        }
        else
        {
            Dlist *res_sum = NULL;
            Dlist *res_sum_tail = NULL;
            
            addition(result, &res1, &res_sum, rtail, &restail1, &res_sum_tail);
            
            
            *result = res_sum;
            *rtail = res_sum_tail;
        }

        count++;
        temp2 = temp2->prev;
    }
      return SUCCESS;
}


int division(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2,
             Dlist **result, Dlist **rtail)
{
    *result = NULL;
    *rtail = NULL;
    
    if ((*head2) && (*head2)->data == 0 && (*head2)->next == NULL) 
    {
        printf("Division by zero\n");
        return FAILURE;
    }
    
    long long num1 = 0, num2 = 0;
    
    Dlist *temp1 = *head1;
    while (temp1) 
    {
        num1 = num1 * 10 + temp1->data;
        temp1 = temp1->next;
    }
   
    Dlist *temp2 = *head2;
    while (temp2)
     {
        num2 = num2 * 10 + temp2->data;
        temp2 = temp2->next;
    }
    
    // Divide
    long long quotient = num1 / num2;
    
    // Convert result back to list
    if (quotient == 0) 
    {
        Dlist *zero = malloc(sizeof(Dlist));
        zero->data = 0;
        zero->prev = zero->next = NULL;
        *result = *rtail = zero;
    }
     else 
    {
        while (quotient > 0)
         {
            insert_first(result, rtail, quotient % 10);
            quotient /= 10;
        }
    }
    
    return SUCCESS;
}

int compare_lists(Dlist *head1, Dlist *head2)
{
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;
    int len1 = 0, len2 = 0;

    while(temp1)
    { 
        len1++; 
        temp1 = temp1->next; 
    }
    while(temp2)
    { 
        len2++; 
        temp2 = temp2->next; 
    }

    if(len1 > len2) 
        return 1;
    if(len1 < len2) 
        return -1;

    temp1 = head1;
    temp2 = head2;

    while(temp1 && temp2)
    {
        if(temp1->data > temp2->data) 
            return 1;
        if(temp1->data < temp2->data) 
            return -1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0; // equal
}

int dl_delete_list(Dlist **head, Dlist **tail)
{
    if (*head == NULL)
        return FAILURE;
    Dlist *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
    return SUCCESS;
}