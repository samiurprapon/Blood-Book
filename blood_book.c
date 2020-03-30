/**
 * Program name         :   Blood Book
 * Program Developer    :   Samiur Rahman Prapon, Jibon Krishna Saha
 * Revision History     :   17/04/2017
**/

// headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>

// function prototype
void add_contact();
void edit_contact();
void list_contact();
void delete_contact();

void search_contacts();
void search_blood();

void menu();
void confimation();
void menu_exit();

// structure
struct contact
{
    char phone[25];
    char name[40];
    char add[100];
    char email[30];
    char blood[10];
};

struct contact list;

// global variables
char query[40], name[40], blood[40];

// global file pointers
FILE *fp, *ft;

// global indexers
int i, n, ch, l, found;

void main()
{
    menu();
    scanf("%d", &ch);

    switch (ch)
    {
    case 0:
        menu_exit();
        break;

    case 1:
        // Add new contacts
        add_contact();
        break;

    case 2:
        // list of all contacts
        list_contact();
        break;

    case 3:
        // search contacts
        search_contacts();
        break;

    case 4:
        // edit contacts
        edit_contact();
        break;

    case 5:
        // delete contacts
        delete_contact();
        break;

    case 6:
        // search blood
        search_blood();
        break;

    default:
        printf("Invalid choice");
        break;
    }

    confimation();
}

void menu()
{
    system("cls"); /* ************Main menu ***********************  */

    printf("\n\t\t **** Welcome to Blood Book ****");
    printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List of all Contacts\n\t\t[3] Search contact for Blood Group\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[6] Find Blood Group\n\t\t[0] Exit\n\t\t=====================\n\t\t");
    printf("Enter the choice: ");
}

void add_contact()
{
    system("cls");
    fp = fopen("contacts.bin", "ab");

    for (;;)
    {
        fflush(stdin);
        printf("To exit enter blank space in the name input\nName (Use identical):");
        gets(list.name);

        if (stricmp(list.name, "") == 0 || stricmp(list.name, " ") == 0)
        {
            break;
        }

        fflush(stdin);

        // get phone number
        printf("Phone:");
        gets(list.phone);
        fflush(stdin);

        // get address
        printf("address:");
        gets(list.add);
        fflush(stdin);

        // get blood Group
        printf("Blood Group:");
        gets(list.blood);
        fflush(stdin);

        // get email address
        printf("email address:");
        gets(list.email);
        printf("\n");

        //write in file
        fwrite(&list, sizeof(list), 1, fp);
    }

    fclose(fp);
}

void menu_exit()
{
    printf("\n\n\t\tAre you sure you want to exit?");
}

void list_contact()
{
    system("cls");
    printf("\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n\n\n");

    for (i = 97; i <= 122; i++)
    {
        fp = fopen("contacts.bin", "rb");
        fflush(stdin);
        found = 0;

        while (fread(&list, sizeof(list), 1, fp) == 1)
        {
            if (list.name[0] == i || list.name[0] == i - 32)
            {
                printf("\nName\t: %s\nPhone\t: %s\nAddress\t: %s\nEmail\t: %s\nBlood Group  : %s\n", list.name, list.phone, list.add, list.email, list.blood);
                found++;
            }
        }

        if (found != 0)
        {
            printf("=========================================================== [%c]-(%d)\n\n", i - 32, found);
            getch();
        }

        fclose(fp);
    }
}

void search_contacts()
{
    system("cls");

    do
    {
        found = 0;
        printf("\n\n\t..::CONTACT SEARCH\n\t===========================\n\t..::Name of contact to search: ");

        fflush(stdin);
        gets(query);
        l = strlen(query);

        fp = fopen("contacts.bin", "rb");
        system("cls");
        printf("\n\n..::Search result for '%s' \n===================================================\n", query);

        while (fread(&list, sizeof(list), 1, fp) == 1)
        {
            for (i = 0; i <= l; i++)
            {
                name[i] = list.name[i];
            }

            name[l] = '\0';

            if (stricmp(name, query) == 0)
            {
                printf("\nName\t: %s\nPhone\t: %s\nAddress\t: %s\nEmail\t: %s\nBlood Group\t: %s\n", list.name, list.phone, list.add, list.email, list.blood);
                found++;

                if (found % 4 == 0)
                {
                    printf("..::Press any key to continue...");
                    getch();
                }
            }
        }

        if (found == 0)
        {
            printf("\n..::No match found!");
        }
        else
        {
            printf("\n..::%d match(s) found!", found);
        }

        fclose(fp);
        printf("\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t");
        scanf("%d", &ch);
        system("cls");

        if (ch == 0)
        {
            main();
        }
    } while (ch == 1);
}

void edit_contact()
{
    system("cls");

    fp = fopen("contacts.bin", "rb");
    ft = fopen("temp.bin", "wb");

    fflush(stdin);

    printf("..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:");

    gets(name);

    while (fread(&list, sizeof(list), 1, fp) == 1)
    {
        if (stricmp(name, list.name) != 0)
            fwrite(&list, sizeof(list), 1, ft);
    }

    fflush(stdin);
    printf("\n\n..::Editing '%s'\n\n", name);
    printf("..::Name(Use identical): ");
    gets(list.name);

    fflush(stdin);
    printf("..::Phone: ");
    gets(list.phone);

    fflush(stdin);
    printf("..::address: ");
    gets(list.add);

    fflush(stdin);
    printf("..::Blood Group:  ");
    gets(list.blood);

    fflush(stdin);
    printf("..::email address: ");
    gets(list.email);

    printf("\n");

    fwrite(&list, sizeof(list), 1, ft);

    fclose(fp);
    fclose(ft);

    remove("contacts.bin");
    rename("temp.bin", "contacts.bin");
}

void delete_contact()
{
    system("cls");

    fflush(stdin);
    printf("\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete:");
    gets(name);

    fp = fopen("contacts.bin", "rb");
    ft = fopen("temp.bin", "wb");

    while (fread(&list, sizeof(list), 1, fp) != 0)
    {
        if (stricmp(name, list.name) != 0)
        {
            fwrite(&list, sizeof(list), 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);

    remove("contacts.bin");
    rename("temp.bin", "contacts.bin");
}

void search_blood()
{
    system("cls");

    do
    {
        found = 0;

        printf("\n\n\t..::Blood SEARCH\n\t===========================\n\t..::Blood Group of contact to search: ");

        fflush(stdin);

        gets(query);
        l = strlen(query);

        fp = fopen("contacts.bin", "rb");
        system("cls");
        printf("\n\n..::Search result for '%s' \n===================================================\n", query);

        while (fread(&list, sizeof(list), 1, fp) == 1)
        {
            for (i = 0; i <= l; i++)
            {
                blood[i] = list.blood[i];
            }

            blood[l] = '\0';

            if (stricmp(blood, query) == 0)
            {
                printf("\n..::Name\t: %s\n..::Phone\t: %s\n..::Address\t: %s\n..::Email\t: %s\n..::Blood Group\t: %s\n", list.name, list.phone, list.add, list.email, list.blood);
                found++;
                if (found % 4 == 0)
                {
                    printf("..::Press any key to continue...");

                    getch();
                }
            }
        }

        if (found == 0)
        {
            printf("\n..::No match found!");
        }
        else
        {
            printf("\n..::%d match(s) found!", found);
        }

        fclose(fp);
        printf("\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t");
        scanf("%d", &ch);
        if (ch == 0)
        {
            main();
        }
    } while (ch == 1);
}

void confimation()
{
    if (ch != 0)
    {
        printf("\n\n\n..::Enter the Choice: \n\n\t[1] Main Menu\t\t[0] Exit\n");

        scanf("%d", &ch);
    }
    else
    {
        printf("\n\t\t[0] YES\t\t[1] NO\n\t\t");
        scanf("%d", &ch);
    }

    switch (ch)
    {

    case 1:
        main();
        break;
    case 0:
        printf("\n\t\t..::Thank you for Using Blood Book\n\n");
        break;

    default:
        printf("Invalid choice");
        break;
    }
}
