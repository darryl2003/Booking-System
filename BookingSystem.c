/* Name: Darryl Djohan Student ID: 20414727*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct visitData
{
char *SrNo;
char *ticketNo;
char *Name;
char *ID;
}data;

typedef struct ticket 
{
data *visitor;
struct ticket *nextPtr;
}node;

//function prototypes
void add(node** begin, int num);
void searchname(node **begin);
void searchticket(node **begin);
void searchID(node**begin);
void deletename(node**begin);
void deleteticket(node**begin);
void deleteID(node**begin);
void display(node **begin);
void deallocate(node** begin);
void ticket_txt (node **begin, int totalvisitor);
void output_txt(char *string);

//main program
int main()
{    
    node *begin = NULL; //for the linked list

    int choice;         //choice is for choosing the action 
    char cont = 'Y';    //for looping purpose
    char exitloop = 'Y';    //cont is for looping purpose while its value is 'y' or 'Y' 
    int num = 0, maxvisitor = 40;   //num is for the srno of the visitor, max visitor is 40
    int totalvisitor; //for printing the total visitor in ticket.txt

    printf("THEME PARK BOOKING SYSTEM\n");
    
    while (exitloop == 'Y'||exitloop == 'y'|| num < 40)    //for looping the code while the user want to continue
    {                               //so it wont be more than 40 visitors information
        add(&begin,num);    //adding the visitor info
        printf("-------------------------------------------\n");
        printf("Do you want to continue adding (Y/N):");  //ask user whether want to stop or want to continue
        scanf("%c",&exitloop);  //the input for that
        getchar();
        num++; //increment
        while (exitloop != 'y' && exitloop != 'Y' && exitloop != 'n' && exitloop != 'N')    //while the input is invalid, ask again
        {
            printf("-------------------------------------------\n");
            printf("Please input the right choice\n");
            printf("Do you want to continue adding (Y/N):");
            scanf("%c",&exitloop);
            getchar();
        }
        
        if(exitloop == 'N' || exitloop == 'n')  //if the user want to stop adding visitor's information
        {
            printf("ADDING VISITOR ENDED\n");
            break;
        }
        if(num == 39)
        {
            printf("MAX CAPACITY REACHED\n");   //because after this cannot input anymore
        }
    }
    totalvisitor = num; //update the total visitor
    while (cont == 'Y' || cont == 'y')  //while the user want to continue it will always loop
    {
        printf("-------------------------------------------\n");
        printf("Please choose what action will be done\n");        //ask the user to choose the action
        printf("-------------------------------------------\n");
        printf("1. ADD the visitor's information\n");
        printf("2. SEARCH based on NAME of a visitor's information\n");
        printf("3. SEARCH based on TICKET NUMBER of a visitor's information\n");
        printf("4. SEARCH based on ID of a visitor's information\n");
        printf("5. DELETE based on NAME of a visitor's information\n");
        printf("6. DELETE based on TICKET NUMBER of a visitor's information\n");
        printf("7. DELETE based on ID of a visitor's information\n");
        printf("8. DISPLAY the visitor information\n");
        printf("9. EXIT\n");
        printf("-------------------------------------------\n");
        printf("Choose the action(1-9):");
        scanf(" %d",&choice);
        getchar();              //getchar is to make sure fgets working after using the scanf
        if (choice<1 || choice>9)   //if input invalid, ask again
        {
            printf("-------------------------------------------\n");
            printf("Please choose the valid action(1-9):");
            scanf(" %d",&choice);
            getchar();  
        }
        printf("-------------------------------------------\n");

        switch(choice)
        {
            case 1:
            if (totalvisitor == 40)  //means full already
            {
                printf("Max capacity reached\n");
                break; //out from case 1
            }                       
            add(&begin,num);    //adding the visitor info
            printf("-------------------------------------------\n");
            printf("ADDING VISITOR ENDED\n");
            totalvisitor++; //update the total visitor
            break;

            case 2:
            printf("SEARCH NAME is chosen\n");
            searchname(&begin); //call search by name function
            break;

            case 3:
            printf("SEARCH TICKET is chosen\n");
            searchticket(&begin);    //call search by ticket number function
            break;

            case 4:
            printf("SEARCH ID is chosen\n");
            searchID(&begin);                       //call search by ID function
            break;

            case 5:
            printf("DELETE NAME is chosen\n");
            deletename(&begin);               //call delete by name function
            totalvisitor--;
            break;

            case 6:
            printf("DELETE TICKET is chosen\n"); //call delete by ticketNo function
            deleteticket(&begin);
            totalvisitor--; //keep track of the total visitor
            break;

            case 7:
            printf("DELETE ID is chosen\n");
            deleteID(&begin);     //call delete by ID function
            totalvisitor--;
            break;

            case 8:
            printf("DISPLAY is chosen\n");  
            display(&begin);    //call display function
            break;

            case 9:    //exit directly
            break;
        }
        printf("-------------------------------------------\n");
        printf("Do you want continue adding/searching/deleting?\n");
        printf("Press Y to continue, N to stop:");
        scanf(" %c",&cont);          //ask to repeat or end the program
        getchar();
    }
    printf("-------------------------------------------\n");
    ticket_txt(&begin,totalvisitor); //call function to generate ticket.txt
    deallocate(&begin); //deallocate the malloc
    printf("PROGRAM ENDED\n");
}

void add(node **begin, int num)
{   
    node *new_data = malloc(sizeof(node));  //create the memory allocation for a new node

    if (new_data == NULL) //means that the user already finished inputing
    {
        exit(1); //if its NULL then return from the function
    }
    new_data -> nextPtr = NULL;
    //for changing the pointer destination so it points at a valid address 
    if (*begin==NULL)   //when starting if it is NULL then make a new node
    {
       *begin = new_data;                //instead of NULL, we wanna put something that is valid for the pointer to point
    }
    else
    {
        node *current_node = *begin;
        while(current_node -> nextPtr != NULL)
        {
            current_node = current_node -> nextPtr;     //iterate through the linked list until the pointer points at null
        }
        current_node -> nextPtr = new_data; //make the node it points 
    }
    
    char nationality; //to determine whether the input ID is Passport or IC
    char tempID[20]; //a temporary array for ID input
    char tempname[30]; //for temporary name before it converts to decimals
                    
    new_data->visitor = malloc(sizeof(new_data));           //make memory for later input
    new_data->visitor->SrNo = (char*)malloc(sizeof(char*));       
    new_data->visitor->ticketNo = (char*)malloc(30*sizeof(char*));
    new_data->visitor->Name = (char*)malloc(30*sizeof(char*));
    new_data->visitor->ID = (char*)malloc(10*sizeof(char*));

    printf("-------------------------------------------\n");
    printf("Inputting visitor's information:\n");
    //for the Name
    printf("Enter the visitor's name:");
    fgets(new_data->visitor->Name,30*sizeof(char*),stdin);    //get the visitor's name, 30 because the max is 30 characters
    strtok(new_data->visitor->Name,"\n");     //delete the \n that is appended when entering the value using fgets
    //for the ID
    printf("-------------------------------------------\n");
    printf("Press I if the visitor is international visitor\n");
    printf("Press L if the visitor is local visitor\n");
    printf("Enter I/L:");
    scanf("%c",&nationality);                                   //ask the user whether is international or local
    getchar();
    printf("-------------------------------------------\n");
    
    while(nationality != 'i' && nationality != 'I' && nationality != 'l' && nationality != 'L') //ask to input again if the input is invalid
    {
        printf("Please input the right choice\n");
        printf("Press I if the visitor is international visitor\n");
        printf("Press L if the visitor is local visitor\n");
        printf("Enter I/L:");
        scanf("%c",&nationality);
        getchar();
        printf("-------------------------------------------\n");
    }
    if (nationality == 'i' || nationality == 'I')   //if international
    {
        strcpy(new_data->visitor->ID,"PASS");     //copy the word PASS
        printf("Please enter your Passport Number:");
        fgets(tempID,20*sizeof(char*),stdin);          //ask to input the passport number,20 because it is the max character
        strtok(tempID,"\n");        //clear the new line made by fgets
        strcat(new_data->visitor->ID, tempID); //combine the PASS and the id input 
    }
    else   //if local
    {
        strcpy(new_data->visitor->ID,"IC");     //copy the word IC
        printf("Please enter your IC Number:");
        fgets(tempID,20*sizeof(char*),stdin);          //ask to input the passport number,20 because it is the max character
        strtok(tempID,"\n");        //clear the new line made by fgets
        strcat(new_data->visitor->ID, tempID); //combine the IC and the id input 
    }
    //for the SrNo
    snprintf(new_data->visitor->SrNo,4,"%02d",num+1); //because we want the Sr to be 01 instead of 1 

    //for the ticket number
    new_data->visitor->ticketNo[0]='\0'; //to clear everything before
    
    if(strlen(new_data->visitor->Name)<6)        //if the name is less than 6, append space before the name
    {
        for(int j = 0; j < 6-strlen(new_data->visitor->Name); j++) //for the spaces at the left side
        {
            snprintf(tempname,4,"%d",' ');          
            strcat( new_data->visitor->ticketNo, tempname);
        }
        for(int k = 0 ; k <strlen(new_data->visitor->Name) ; k++)  
        {
            snprintf(tempname,4,"%d",new_data->visitor->Name[k]); ; //then take the rest from the visitor.name
            strcat( new_data->visitor->ticketNo, tempname);
        }
    }
    else 
    {
        for(int h = 0; h<6 ; h++)   //else only take 6 letters of the name
        {
            snprintf(tempname,4,"%d",new_data->visitor->Name[h]);
            strcat(new_data->visitor->ticketNo, tempname);
        }
    }
    strcat(new_data->visitor->ticketNo,new_data->visitor->SrNo) ; //add the SrNo to the ticket num

    //to change the spaces in the name into underscore
    for(int i=0 ; new_data->visitor->Name[i]!= '\0'; i++) 
    {
        if(new_data->visitor->Name[i] == ' ')
        {
            new_data->visitor->Name[i] = '_'; //change space to underscore
        }
    }
    printf("The information of the visitor %s is recorded\n",new_data->visitor->Name); 
    output_txt("The information of the visitor "); //print in output.txt
    output_txt(new_data->visitor->Name);
    output_txt(" "); //add space
    output_txt("is recorded\n\n");
}

void deallocate(node **begin)   //to deallocate the linked list
{
    node *current_node = *begin;
    while (current_node != NULL)    //will exit when it points to NULL
    {   
        node *auxiliary = current_node;     //another pointer which points to the node we wanna free
        current_node = current_node -> nextPtr;     //iterate through the linked list
        free(auxiliary);    //deallocate it
    }
    *begin = NULL ; //make the begin empty
}

void searchname(node **begin)
{
    char temp[30]; // Temporary variable to hold the search input
    char temp2[30]; //temporary variable to hold the name from the linked list
    int found = 0; // Flag to indicate whether the visitor was found
    node *current_node = *begin; // Current node in the linked list
    printf("Enter the Name to search:");    //ask user to input the search key
    fgets(temp, 20, stdin);
    strtok(temp,"\n"); 

   //changing the input value to suit the search value
    for(int i=0 ; temp[i]!= '\0'; i++)  
    {
        if(temp[i] == ' ')
        {
            temp[i] = '_'; //change space to underscore
        }
        temp[i]= tolower(temp[i]);  //change all the letter into lowerspace
    }
   
    printf("-------------------------------------------\n");
    printf("The following record of the visitor is recorded:\n");   //print the information searched
    output_txt("The following record of the visitor is recorded:\n\n"); //print in the output_txt
    while (current_node != NULL)
    {   
        //changing the value of temp2 according to the name data in the linked list
        strcpy(temp2,current_node->visitor->Name);
        for(int j=0; current_node->visitor->Name[j]!='\0';j++)
        {
        temp2[j]= tolower(temp2[j]);  //change all the letter into lowerspace
        }
        // Search for the visitor name in the linked list
        if (strcmp(temp2,temp) == 0)
        {
            printf("%s %s %s %s\n",current_node->visitor->SrNo,current_node->visitor->ticketNo,current_node->visitor->Name,current_node->visitor->ID);
            output_txt(current_node->visitor->SrNo); // the visitor's info
            output_txt(" "); //spaces
            output_txt(current_node->visitor->ticketNo);
            output_txt(" ");
            output_txt(current_node->visitor->Name);
            output_txt(" ");
            output_txt(current_node->visitor->ID);
            output_txt("\n");
            found = 1;
        }
        current_node = current_node->nextPtr;
    }
    
    if (found==0) // If the visitor was not found
    {
        printf("Visitor not found.\n");
        output_txt("Visitor not found.\n");
    }
    output_txt("\n");
}

void searchticket(node **begin)
{
    char temp[20]; // Temporary variable to hold the search input
    int found = 0; // Flag to indicate whether the visitor was found
    node *current_node = *begin; // Current node in the linked list
    printf("Enter the TicketNo to search:");    //ask user to input the search key
    fgets(temp, 20, stdin);
    strtok(temp,"\n"); 
    printf("-------------------------------------------\n");
    while (current_node != NULL)
    {   
        // Search for the visitor with the ticketNo
        if (strcmp(current_node->visitor->ticketNo,temp) == 0)
        {
            printf("The following record of the visitor is recorded:\n");   //print the information searched
            output_txt("The following record of the visitor is recorded:\n\n"); //print in the output_txt
            printf("%s %s %s %s\n",current_node->visitor->SrNo,current_node->visitor->ticketNo,current_node->visitor->Name,current_node->visitor->ID);
            output_txt(current_node->visitor->SrNo); // the visitor's info
            output_txt(" "); //spaces
            output_txt(current_node->visitor->ticketNo);
            output_txt(" ");
            output_txt(current_node->visitor->Name);
            output_txt(" ");
            output_txt(current_node->visitor->ID);
            output_txt("\n");
            found = 1;
        }
        current_node = current_node->nextPtr;
    }
    
    if (found==0) // If the visitor was not found
    {
        printf("Visitor not found.\n");
        output_txt("Visitor not found.\n");
    }
    output_txt("\n");
}

void searchID(node **begin)
{
    char temp[20]; // the changed user input
    char input[20]; //the user input
    char nationality; //search international or national visitor
    int found = 0;  //flag to indicate whether the visitor was found
    node *current_node = *begin; // Current node in the linked list
    //ask user interntional or national
    printf("Press I for international\n");
    printf("Press L for local\n");
    printf("-------------------------------------------\n");
    printf("Press I/L:");
    scanf("%c",&nationality);
    getchar();
    //verify the answer is true
    while(nationality != 'I' && nationality != 'i'&& nationality != 'L'&& nationality != 'l')
    {
        printf("Please input the right option!\n");
        printf("Press I/L:");
        scanf("%c",&nationality);
        getchar();
    }
    printf("-------------------------------------------\n");
    printf("Enter the ID to search (only the number):");    //ask user to input the search key
    fgets(input, 20, stdin);
    strtok(input,"\n"); 
    printf("-------------------------------------------\n");
    //append PASS or IC infront of the input
    if(nationality == 'I' || nationality =='i')
    {
        strcpy(temp,"PASS");     //copy the word PASS
        strcat(temp, input); //copy the user input afterward
    }
    else //it is either 'L' or 'l'
    {
        strcpy(temp,"IC");     //copy the word IC
        strcat(temp, input); //copy the user input afterward
    }
    //comparison
    while (current_node != NULL)
    {   
        // Search for the visitor with the ID
        if (strcmp(current_node->visitor->ID,temp) == 0)
        {
            printf("The following record of the visitor is recorded:\n");   //print the information searched
            output_txt("The following record of the visitor is recorded:\n\n"); //print in the output_txt
            printf("%s %s %s %s\n",current_node->visitor->SrNo,current_node->visitor->ticketNo,current_node->visitor->Name,current_node->visitor->ID);
            output_txt(current_node->visitor->SrNo); // the visitor's info
            output_txt(" "); //spaces
            output_txt(current_node->visitor->ticketNo);
            output_txt(" ");
            output_txt(current_node->visitor->Name);
            output_txt(" ");
            output_txt(current_node->visitor->ID);
            output_txt("\n");
            found = 1;
        }
        current_node = current_node->nextPtr;
    }
    
    if (found==0) // If the visitor was not found
    {
        printf("Visitor not found.\n");
        output_txt("Visitor not found.\n");
    }
    output_txt("\n");
}

void deletename(node **begin)
{
    char *temp=malloc(30*sizeof(char*)); // Temporary variable to hold the search input
    char temp2[30]; //temporary variable to hold the name from the linked list
    int counter = 0; //for how many data found
    node *current_node = *begin; // Current node in the linked list
    //node *delete_multiple = *begin; //for deleting multiple
    printf("Enter the Name to delete:");    //ask user to input the search key
    fgets(temp, 30*sizeof(char), stdin);
    strtok(temp,"\n"); 

   //changing the input value to suit the search value
    for(int i=0 ; temp[i]!= '\0'; i++)  
    {
        if(temp[i] == ' ')
        {
            temp[i] = '_'; //change space to underscore
        }
        temp[i]= tolower(temp[i]);  //change all the letter into lowerspace
    }
   
     //special case: if want to remove the first node
    if(strcmp(current_node->visitor->Name,temp) == 0) //if the first node is the one we wanna delete
    {
        node *remove = current_node;    //remove is the current node now
        *begin = current_node->nextPtr;   //move begin to the next node
        free(remove);   //delete the current node
        counter++;
    }
    while (current_node != NULL)
    {   
        //changing the value of temp2 according to the name data in the linked list
        strcpy(temp2,current_node->nextPtr->visitor->Name);
        for(int j=0; current_node->nextPtr->visitor->Name[j]!='\0';j++)
        {
        temp2[j]= tolower(temp2[j]);  //change all the letter into lowerspace
        }
        // Search for the visitor name in the linked list
        if (strcmp(temp2,temp) == 0)
        {
            counter++;//increment the counter
        }
        current_node = current_node->nextPtr;
    }
    
    if (counter ==0) // If the visitor was not found
    {
        printf("Visitor not found.\n");
        output_txt("Visitor not found.\n\n"); //print in output.txt
    }

    if(counter ==1) // If only one visitor was found
    {
        node *current_node = *begin; // Current node in the linked list
        while (current_node != NULL)
        {   
            //changing the value of temp2 according to the name data in the linked list
            strcpy(temp2,current_node->visitor->Name);
            for(int k=0; current_node->visitor->Name[k]!='\0';k++)
            {
            temp2[k]= tolower(temp2[k]);  //change all the letter into lowerspace
            }
            // Search for the visitor name in the linked list
            if (strcmp(temp2,temp) == 0)
            {
                node *remove = current_node->nextPtr; //store the pointer of the node we wanna delete
                current_node -> nextPtr = current_node -> nextPtr -> nextPtr; //make the pointer points to the next node skipping the node we wanna delete
                free(remove);   //clear the memory allocation of the node 
                printf("The visitor:%s 's information is deleted\n",current_node->visitor->Name);
                output_txt("The visitor:"); //print in output.txt
                output_txt(current_node->visitor->Name);
                output_txt(" ");
                output_txt("'s information is deleted\n\n");
            }
            current_node = current_node->nextPtr;
        }
    }

    if (counter >= 2)   //if more than 2 found, search by id
    {
        printf("Redirecting to Delete by ID\n");
        output_txt("Redirecting to Delete by ID\n\n"); //print in output.txt
        deleteID(begin);
    }
}

void deleteticket(node **begin)
{
    //search the information and then delete it
    char temp[20]; // Temporary variable to hold the search input
    int found = 0; // Flag to indicate whether the visitor was found
    node *current_node = *begin; // Current node in the linked list
    printf("Enter the TicketNo to delete:");    //ask user to input the search key
    fgets(temp, 20, stdin);
    strtok(temp,"\n"); 
    printf("-------------------------------------------\n");
    //special case: if want to remove the first node
    if(strcmp(current_node->visitor->ticketNo,temp) == 0) //if the first node is the one we wanna delete
    {
        node *remove = current_node;    //remove is the current node now
        *begin = current_node->nextPtr;   //move begin to the next node
        free(remove);   //delete the current node
        found = 1;
    }
    else
    {
        while(current_node != NULL)
        {   
            // Search for the visitor with the ticketNo
            if (strcmp(current_node->nextPtr->visitor->ticketNo,temp) == 0)   //if the next value is the one that we want to delete
            {
                node *remove = current_node->nextPtr; //store the pointer of the node we wanna delete
                current_node -> nextPtr = current_node -> nextPtr -> nextPtr; //make the pointer points to the next node skipping the node we wanna delete
                free(remove);   //clear the memory allocation of the node 
                found = 1;
            }
            current_node = current_node->nextPtr;   //go to the next node
        }
    }
    if (found==0) // If the visitor was not found
    {
        printf("Visitor not found.\n");
        output_txt("Visitor not found.\n\n"); //print in output.txt
    }
    if (found ==1) //if the visitor is deleted
    {
        printf("The visitor with ticketNo:%s 's information is deleted\n",temp);
        output_txt("The visitor with ticketNo:"); //print in output.txt
        output_txt(temp);
        output_txt(" ");
        output_txt("'s information is deleted\n\n");
    }
}

void deleteID(node **begin)
{
    char temp[20]; // the changed user input
    char input[20]; //the user input
    char nationality; //search international or national visitor
    int found = 0;  //flag to indicate whether the visitor was found
    node *current_node = *begin; // Current node in the linked list
    //ask user interntional or national
    printf("Press I for international\n");
    printf("Press L for local\n");
    printf("-------------------------------------------\n");
    printf("Press I/L:");
    scanf("%c",&nationality);
    getchar();
    //verify the answer is true
    while(nationality != 'I' && nationality != 'i'&& nationality != 'L'&& nationality != 'l')
    {
        printf("Please input the right option!\n");
        printf("Press I/L:");
        scanf("%c",&nationality);
        getchar();
    }
    printf("-------------------------------------------\n");
    printf("Enter the ID to delete (only the number):");    //ask user to input the search key
    fgets(input, 20, stdin);
    strtok(input,"\n"); 
    printf("-------------------------------------------\n");
    //append PASS or IC infront of the input
    if(nationality == 'I' || nationality =='i')
    {
        strcpy(temp,"PASS");     //copy the word PASS
        strcat(temp, input); //copy the user input afterward
    }
    else //it is either 'L' or 'l'
    {
        strcpy(temp,"IC");     //copy the word IC
        strcat(temp, input); //copy the user input afterward
    }
     //special case: if want to remove the first node
    if(strcmp(current_node->visitor->ID,temp) == 0) //if the first node is the one we wanna delete
    {
        node *remove = current_node;    //remove is the current node now
        *begin = current_node->nextPtr;   //move begin to the next node
        free(remove);   //delete the current node
        found = 1;
    }
    //comparison
    while(current_node != NULL)
        {   
            // Search for the visitor with the ID
            if (strcmp(current_node->nextPtr->visitor->ID,temp) == 0)   //if the next value is the one that we want to delete
            {
                node *remove = current_node->nextPtr; //store the pointer of the node we wanna delete
                current_node -> nextPtr = current_node -> nextPtr -> nextPtr; //make the pointer points to the next node skipping the node we wanna delete
                free(remove);   //clear the memory allocation of the node 
                found = 1;
            }
            current_node = current_node->nextPtr;   //go to the next node
        }
    
    if (found==0) // If the visitor was not found
    {
        printf("Visitor not found.\n");
        output_txt("Visitor not found.\n\n"); //print in output.txt
    }
    if (found ==1) //if the visitor is deleted
    {
        printf("The visitor with ID:%s 's information is deleted\n",temp);
        output_txt("The visitor with ID:"); //print in output.txt
        output_txt(temp);
        output_txt(" ");
        output_txt("'s information is deleted\n\n");
    }
}

void display(node **begin)
{
    node *current_node = *begin; // Current node in the linked list
    printf("-------------------------------------------\n");
    while (current_node != NULL)    //iterate through the nodes
    {   
        printf("%s %s %s %s\n",current_node->visitor->SrNo,current_node->visitor->ticketNo,current_node->visitor->Name,current_node->visitor->ID); //print the information
        output_txt(current_node->visitor->SrNo); // the visitor's info
        output_txt(" "); //spaces
        output_txt(current_node->visitor->ticketNo);
        output_txt(" ");
        output_txt(current_node->visitor->Name);
        output_txt(" ");
        output_txt(current_node->visitor->ID);
        output_txt("\n");
        current_node = current_node->nextPtr;  //go to next node
    }
    output_txt("\n");
}

void ticket_txt (node **begin, int totalvisitor)
{
    //generate the ticket.txt 
    FILE *file = fopen("Tickets.txt","w"); //create the txt 
    if(file==NULL)
    {
        printf("Cannot Open/Create the file\n");
    }
    node *current_node = *begin; // Current node in the linked list
    char total[3]; //for the total visitor
    //print in ticket.txt the total visitors number
    fputs("Total visitors:",file);
    sprintf(total, "%d", totalvisitor);
    fputs(total,file);
    fputs("\n",file);
    //print all visitor's information
    while (current_node != NULL)
    {
        fprintf(file,"%s %s %s %s\n",current_node->visitor->SrNo,current_node->visitor->ticketNo,current_node->visitor->Name,current_node->visitor->ID);
        current_node = current_node->nextPtr;   //go to the next node
    }
    fclose(file);
}

void output_txt(char *string)
{
    FILE *file;
    file = fopen("Output.txt","a+");    //append the output.txt
    //if the file cant be opened
    if(file==NULL)
    {
        printf("Cannot Open/Create the file\n");
    }
    //if opened then print the string inside the file
    fprintf(file,"%s",string);
    fclose(file);  //close the file
}