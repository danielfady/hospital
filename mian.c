/*
Project: Hospital management system
Authors: Daniel Fady -- Fady Ashraf
version:1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int room_number, patient_id;
    bool is_empty;

} st_Rooms;
typedef struct
{
    char *username, *password;
    int privilege; // 1-doctor 2-patient
} st_User;
typedef struct
{
    int patient_id;
    char *name, *status; // normal or severe case
} st_Patient;

st_User user[8] = {
    // username,password,privilege
    {"shady", "1111", 1},
    {"daniel", "2222", 1},
    {"saleh", "abcabc", 2},
    {"tolba", "a1a1a1", 2},
    {"ramy", "121212", 2}};
st_Rooms room[4] = {
    // room number,patient id,is
    {194, 1000, false},
    {235, 0, true},
    {316, 1001, false},
    {462, 0, true},
};
st_Patient patient[5] = {
    // patient id, name, status
    {1000, "saleh", "normal"},
    {1001, "tolba", "severe"},
    {1002, "ramy", "severe"}};
int p; // variable to check privillege in switch case

void login()
{
    for (int i = 0; i < 8; i++) // Loop to print the usernames and passwords at begining
    {
        if(user[i].username==0)
        break;
        printf("%s: %s\n", user[i].username, user[i].password);
    }
    printf("\n");
    int x = 0, found = 0;
    printf("Login:\n******\n");
    do
    {
        char name[50], pass[50];
        printf("enter your username:\n");
        scanf("%s", name);
        printf("enter your password:\n");
        scanf("%s", pass);
        for (int i = 0; i < 10; i++)
        {
            if (user[i].privilege != 0) // To check only the occupied places in the users array
            {
                if (strcmp(user[i].username, name) == 0 && strcmp(user[i].password, pass) == 0) // login conditions
                {
                    if (user[i].privilege == 1) // Login as doctor
                    {
                        printf("Welcome doctor %s", &name);
                        found = 1;
                        p = user[i].privilege; // to use in the switch cases
                        i = 10;                // to not to operate in for loop again
                    }
                    else // Login as patient
                    {
                        printf("Weclome patient %s", &name);
                        found = 1;
                        p = user[i].privilege;
                        i = 10;
                    }
                }
            }
        }
        if (found == 1) // to exit the loop
        {
            break;
        }
        if (found == 0)
        {
            printf("Invalid data, please try again\n");
            x++;
        }
        if (x == 3) // User has 3 trials only
        {
            printf("System failure, try again later.\n");
            exit(0);
        }

    } while (x < 3);
}
void remove_reservation()
{
    int n, x = 0;
    printf("Enter the room number\n");
    char input[10];
    scanf("%s", input);
    for (int i = 0; input[i] != '\0'; i++) // for loop to make sure input is digits only and has no characters
    {
        if (!isdigit(input[i]))
        {
            printf("Error: invalid input\n");
            return;
        }
    }
    n = atoi(input);            // convert string to integer
    for (int i = 0; i < 4; i++) // Loop on the rooms array
    {
        x = 0;
        if (room[i].room_number == n)
        {
            if (room[i].is_empty == false) // If room is full reserv. is removed so as the patient id in it
            {
                room[i].is_empty = true;
                room[i].patient_id = 0;
                printf("RESERVATION REMOVED SUCCESSFULLY\n");
                i = 5;
            }
            if (room[i].is_empty == true)
            {
                printf("THIS ROOM IS ALREADY EMPTY\n");
                i = 5;
            }
        }
        else
        {
            x = 1;
        }
    }
    if (x == 1)
        printf("Room not found\n");
};
void check_rooms()
{
    int x = 0;
    printf("*********************\n");
    for (int i = 0; i < 4; i++)
    {
        if (room[i].is_empty == true)
        {
            x++;
            printf("%d- Room %d is empty\n", x, room[i].room_number);
        }
    }
    printf("*********************\n");
    if (x == 0)
        printf("Sorry, no rooms available now, try again later\n");
    printf("There are %d rooms available\n", x);
};
void update_patient_data()
{
    int id, x, found, y = 0;
    char option;
    printf("Please enter patient id\n");
    char input[10];
    scanf("%s", input);
    for (int i = 0; input[i] != '\0'; i++) // make sure the input is only integers
    {
        if (!isdigit(input[i]))
        {
            printf("Error: invalid input\n");
            y = 2;
            break;
        }
    }
    id = atoi(input);
    if (y == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            found = 0;
            if (patient[i].patient_id == id)
            {
                found = 1;
                printf("This patient status is %s\n", patient[i].status);
                printf("Do you want too update this statue? y/n: ");
                scanf("%s", &option);
                if (option == 'y' || option == 'Y')
                {
                    printf("choose the new status 1-normal 2-severe: ");
                    char input[10];
                    scanf("%s", input);
                    for (int i = 0; input[i] != '\0'; i++)
                    {
                        if (!isdigit(input[i]))
                        {
                            printf("Error: invalid input\n");
                            return;
                        }
                    }
                    x = atoi(input);
                    if (x == 1)
                    {
                        patient[i].status = "Normal";
                        printf("DONE");
                        i = 5;
                    }
                    else if (x == 2)
                    {
                        patient[i].status = "Severe";
                        printf("DONE");
                        i = 5;
                    }
                    else
                    {
                        printf("Invalid input\n");
                        i = 5;
                    }
                }
                else if (option == 'n' || option == 'N')
                {
                    printf("Okay\n");
                    i = 5;
                }
                else
                {
                    printf("Invalid input\n");
                    i = 5;
                    found = 1;
                }
            }
        }
        if (found == 0)
            printf("No such patient in the system.\n");
    }
};
void new() // Function to add new user wheather doctor or patient
{
    int x, z = 0, v = 0, found = 0;
    char name[50], pass[50];
    for (int i = 0; i < 8; i++) // Loop to search for empty places in the array
    {
        if (user[i].privilege == 0)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        printf("Enter 1 for new doctor or 2 for new patient: ");
        char input[5];
        scanf("%s", input);
        for (int i = 0; input[i] != '\0'; i++)
        {
            if (!isdigit(input[i]))
            {
                printf("Error: invalid input\n");
                return;
            }
        }
        x = atoi(input);
        if (x == 1 || x == 2)
        {
            printf("Enter username: ");
            scanf("%s", &name);
            if (isdigit(*name)) // Condition to make sure name is characters
            {
                printf("Error: username cannot contain numbers\n");
                return;
            }
            printf("Enter password: ");
            scanf("%s", &pass);
            int i, j;
            for (i = 0; i < 8; i++) // loop to find the first empty place in users array
            {
                if (user[i].privilege == 0)
                {
                    z = i;
                    i = 9;
                    if (x == 2)
                    {
                        for (j = 0; j < 5; j++) // loop to find the first empty place in patients array
                        {
                            if (patient[j].patient_id == 0)
                            {
                                v = j;
                                j = 6;
                            }
                        }
                    }
                }
            }
            if (z < 10)
            {

                if (x == 1)
                {
                    user[z].username = malloc(strlen(name) + 1); // Allocate memory for the username
                    strcpy(user[z].username, name);              // Copy the username into the allocated memory
                    user[z].password = malloc(strlen(pass) + 1); // Allocate memory for the password
                    strcpy(user[z].password, pass);
                    user[z].privilege = 1;
                    printf("Doctor added successfully\n");
                }
                if (x == 2)
                {
                    int status;
                    printf("status: enter 1 for severe or 2 for normal: ");
                    char input[5];
                    scanf("%s", input);
                    for (int i = 0; input[i] != '\0'; i++)
                    {
                        if (!isdigit(input[i]))
                        {
                            printf("Error: invalid input\n");
                            return;
                        }
                    }
                    status = atoi(input);
                    if (status == 1 || status == 2)
                    {
                        user[z].username = malloc(strlen(name) + 1); // Allocate memory for the username
                        strcpy(user[z].username, name);              // Copy the username into the allocated memory
                        user[z].password = malloc(strlen(pass) + 1); // Allocate memory for the password
                        strcpy(user[z].password, pass);
                        // put patient in patient array
                        user[z].privilege = 2;
                        patient[v].patient_id = patient[v - 1].patient_id + 1;
                        patient[v].name = malloc(strlen(name) + 1); // Allocate memory for the username
                        strcpy(patient[v].name, name);              // Copy the username into the allocated memory
                        if (status == 1)
                        {
                            patient[v].status = "severe";
                            printf("Patient added successfully\n");
                        }
                        else if (status == 2)
                        {
                            patient[v].status = "normal";
                            printf("Patient added successfully\n");
                        }
                    }
                    else
                    {
                        printf("Invalid input\n");
                    }
                }
            }
        }
        else
            printf("Invalid input\n");
    }
    else
        printf("No available space\n");
};

int main()
{
    printf("\n\n*********************************************Welcome to our hospital system*********************************************\n");
    printf("**Please login to continue**\n\n");
    login();
    do
    {
        int c;
        printf("\nPlease choose an option:\n*************************\n");
        printf("1-Remove reservation\n2-Check rooms\n3-Update patient data\n4-Add new user\n5-logout\n6-Exit program\n");
        char input[10];
        scanf("%s", input);
        for (int i = 0; input[i] != '\0'; i++)
        {
            if (!isdigit(input[i]))
            {
                printf("Input can't be a character\n");
                break;
            }
        }
        c = atoi(input);
        switch (c)
        {
        case 1:
        {
            remove_reservation();
            break;
        }
        case 2:
        {
            check_rooms();
            break;
        }
        case 3:
        {
            if (p == 1)
                update_patient_data();
            else
                printf("You are not authorized to edit this data\n");
            break;
        }
        case 4:
        {
            if (p == 1)
                new ();
            else
                printf("You are not authorized to edit this data\n");
            break;
        }
        case 5:
        {
            printf("Logging out\n");
            login();
            break;
        }
        case 6:
        {
            printf("\n\nExiting program\n\n");
            return 0;
        }
        default:
        {
            printf("Invalid choise please try again\n");
        }
        }
    } while (1); //infinite loop
}