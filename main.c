#include <stdio.h>
#include "main.h"

int main(int argc,char *argv[])
{
    int ret = read_and_validate(argc, argv);
    if (ret == FAILURE)
    {
        printf("\033[1;31mERROR: Invalid arguments\033[0m\n");
        return FAILURE;
    }

    Dlist *head1 = NULL;
    Dlist *head2 = NULL;
    Dlist *result = NULL;
    Dlist *tail1 = NULL;
    Dlist *tail2 = NULL;
    Dlist *rtail = NULL;

    int sign1 = 1;
    int sign2 = 1;

    if (argv[1][0] == '-')
        sign1 = -1;

    if (argv[3][0] == '-')
        sign2 = -1;

    /* Convert numbers into linked list */
    convert_string_to_list(argv[1], &head1);
    convert_string_to_list(argv[3], &head2);

    printf("\n\033[1;35m===============================================================\033[0m\n");
    printf("\033[1;35m                 BIG INTEGER CALCULATOR\033[0m\n");
    printf("\033[1;35m===============================================================\033[0m\n");

    printf("\n\033[1;36mFIRST OPERAND : \033[0m");
    print_list(head1);

    printf("\033[1;36mSECOND OPERAND: \033[0m");
    print_list(head2);

    printf("\033[1;33mOPERATOR      : %c\033[0m\n", argv[2][0]);

    printf("\033[1;37m---------------------------------------------------------------\033[0m\n");

    printf("\033[1;32mRESULT        : \033[0m");

    char ch = argv[2][0];

    tail1 = head1;
    while (tail1 && tail1->next != NULL)
        tail1 = tail1->next;

    tail2 = head2;
    while (tail2 && tail2->next != NULL)
        tail2 = tail2->next;

    switch (ch)
    {
        case '+':
        {
            if (sign1 == sign2)
            {
                addition(&head1, &head2, &result, &tail1, &tail2, &rtail);

                if (sign1 == -1 && result != NULL)
                    result->data *= -1;

                print_number(result);
            }
            else
            {
                int cmp = compare(head1, head2);

                if (cmp == 0)
                {
                    insert_first(&result, &rtail, 0);
                    print_number(result);
                }
                else if (cmp > 0)
                {
                    subtraction(&head1, &head2, &result, &tail1, &tail2, &rtail);

                    if (sign1 == -1 && result != NULL)
                        result->data *= -1;

                    print_number(result);
                }
                else
                {
                    subtraction(&head2, &head1, &result, &tail2, &tail1, &rtail);

                    if (sign2 == -1 && result != NULL)
                        result->data *= -1;

                    print_number(result);
                }
            }

            printf("\n\033[1;37m---------------------------------------------------------------\033[0m\n");
            printf("\033[1;32mAddition completed successfully\033[0m\n");
        }
        break;

        case '-':
        {
            if (sign1 != sign2)
            {
                addition(&head1, &head2, &result, &tail1, &tail2, &rtail);

                if (sign1 == -1 && result != NULL)
                    result->data *= -1;
            }
            else
            {
                int cmp = compare(head1, head2);

                if (cmp == 0)
                {
                    insert_first(&result, &rtail, 0);
                }
                else if (cmp > 0)
                {
                    subtraction(&head1, &head2, &result, &tail1, &tail2, &rtail);

                    if (sign1 == -1 && result != NULL)
                        result->data *= -1;
                }
                else
                {
                    subtraction(&head2, &head1, &result, &tail2, &tail1, &rtail);

                    if (sign1 == 1 && result != NULL)
                        result->data *= -1;
                }
            }

            print_number(result);

            printf("\n\033[1;37m---------------------------------------------------------------\033[0m\n");
            printf("\033[1;32mSubtraction completed successfully\033[0m\n");
        }
        break;

        case '*':
        {
            multiplication(&head1, &head2, &result, &tail1, &tail2, &rtail);

            if (sign1 != sign2 && result != NULL)
                result->data *= -1;

            print_number(result);

            printf("\n\033[1;37m---------------------------------------------------------------\033[0m\n");
            printf("\033[1;32mMultiplication completed successfully\033[0m\n");
        }
        break;

        case '/':
        {
            if (division(&head1, &head2, &tail1, &tail2, &result, &rtail) == FAILURE)
            {
                printf("\033[1;31mDivision failed\033[0m\n");
            }
            else
            {
                if (sign1 != sign2 && result != NULL)
                    result->data *= -1;

                print_number(result);

                printf("\n\033[1;37m---------------------------------------------------------------\033[0m\n");
                printf("\033[1;32mDivision completed successfully\033[0m\n");
            }
        }
        break;

        default:
            printf("\033[1;31mInvalid operator\033[0m\n");
    }

    printf("\033[1;35m===============================================================\033[0m\n");

    return SUCCESS;
}