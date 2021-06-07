#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/***************************************** types *************************************************************

struct student type :
contain
* 1) 3 arrays of ( name - ID - age ) to make it easy making line edit on them.
this is better than take digits and convert them inside code
* 2) 3 uint8 sizes SCANS during the run time of (name -ID - age)

*************************************************************************************************************/


typedef unsigned char u_int_8;
typedef unsigned short u_int_16;

struct student
{
    u_int_8 student_name[20];
    u_int_8 array_size_name;
    u_int_8 ID[4];
    u_int_8 age[3];
    u_int_8 array_size_id;
    u_int_8 array_size_age;



};

/*********************************************************************************************************************************
***********************                    Main VARIABLES                     *******************************************
* 1) number_of_student   : total number of students
* 2) index               : shared variable between functions to detect the current index.
                           it has -1 as an inti value to detect errors.
* 3) ptr_class_table     : pointer to array of structs to passed from the main functions to the service functions.
* 4) id_searching[4]     : fixed array to take the id to search for it.
* 5) name_to_compare[20] : fixed array to take the name to search for it.
********************************************************************************************************************************/


struct student class_student_table[10];
struct student *ptr_class_table=&class_student_table[0];

u_int_8 number_of_student=0;
static u_int_8 index=-1;
u_int_8 id_searching[4];
u_int_8 name_to_compare[20]= {0};
/*********************************************************************************************************************************
                                                line editor FUNCTION variables
* 1) ptr_line_edit_struct_address : to refer the address of the current student struct
* 2) ptr_line_edit_array_address  : to refer the address of the current array which want to be editing on the student struct

***********************************************************************************************************************************/

struct student *ptr_line_edit_struct_address;
u_int_8 *ptr_line_edit_array_address;

u_int_8 array_of_edit_line[10];
u_int_8 size_of_aray_of_line;
u_int_8 current_position_line_edit=0;

u_int_8 start_position_x=5;
u_int_8 start_position_y=1;

/*********************************************************************************************************************************
***************************** MAIN FUNCTIONS DECLERATION ***************************

* 1) ADD_Studet_Element     : add student ( name - ID - age ) .. call "scan_array" function
* 2) Remove_Studet_Element  : remove student ( name - ID - age )..call "View_All_Studets" function
* 3) Edit_Studet_Element    : edit student , call "searching_name" "searching_ID" "View_Studet_Element" FUNCTIONS
* 4) View_Studet_Element    : Print 1 student at time.call " print_block"
                             it call "Edit_line" function,if and only if it called by Edit_Studet_Element
* 5) View_All_Studets       : print all students.


*********************************************************************************************************************************/


void ADD_Studet_Element(void);
void Remove_Studet_Element(void);
void Edit_Studet_Element(void);
void View_Studet_Element(u_int_8 choose_line);
void View_All_Studets(void);


/***************************** SERVICE FUNCTIONS DECLERATION ***************************/



void print_block(void);

void gotoxy( int column, int line );
void textattr(int i);

u_int_8 scan_array(u_int_8 *name,u_int_8 select_ind);
u_int_8 searching_ID(u_int_8 *id);
u_int_8 searching_name(u_int_8 *name);


void Edit_line(void);
void insert_char(u_int_8 place,u_int_8 *size,u_int_8 *ptr);
void backspace_char(u_int_8 place,u_int_8 *size,u_int_8 *ptr);
void delete_after(u_int_8 place,u_int_8 *size,u_int_8 *ptr);
void replace_char(u_int_8 ch,u_int_8 position,u_int_8 *ptr);

/*************************************************************************************/
/****************************** MAIN **************************************************/

int main()
{

    menu_list();


    return 0;
}

/*********************************************************************************************************************
                              SERVICE FUNCTIONS IMPLEMENTETION
*********************************************************************************************************************/

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);

}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}
/********************************************* ADD FUNCTION ************************************************/

void ADD_Studet_Element(void)
{
    printf("\n\n");
    printf(" Add the student details : student number : %d\n\n",number_of_student+1);
    printf("enter the name of student :");
    ptr_class_table[number_of_student].array_size_name=scan_array(ptr_class_table[number_of_student].student_name,1);

    printf("enter the ID of student :");
    ptr_class_table[number_of_student].array_size_id=scan_array(ptr_class_table[number_of_student].ID,2);



    printf("enter the age of student :");
    ptr_class_table[number_of_student].array_size_age=scan_array(ptr_class_table[number_of_student].age,3);



    number_of_student++;
}
/**************************remove***************************/
void Remove_Studet_Element(void)
{
    u_int_8 removed_index,i=0;

    system("cls");
    View_All_Studets();
    printf("\n\n*********************\nplease enter the numer of student you want to remove\n****************************\n");
    fflush(stdin);
    scanf("%c",&removed_index);
    removed_index = removed_index-'0';
    for(i=removed_index-1; i<number_of_student; i++)
    {
        ptr_class_table[i]=ptr_class_table[i+1];
    }
    number_of_student--;

    system("cls");
    View_All_Studets();
}
/********************* edit function ****************************/

void Edit_Studet_Element(void)
{
    u_int_8 choose=1;
    u_int_8 checking=1;
    index=0;
    u_int_8 edit_choose=0;
    u_int_8 count_same_names=0;

    printf("do you want to search by:\n name enter 1 \n by id enter 2:");
    fflush(stdin);
    scanf("%c",&choose);


    if(choose=='1')
    {
        printf("\n\n please enter the name you want to search for : ");

        scanf("%s",&name_to_compare);
        checking=searching_name(&name_to_compare);


    }
    else if (choose=='2')
    {
        printf("\n\n please enter the id you want to search for : ");
        scanf("%s",&id_searching);
        checking=searching_ID(id_searching);
    }


    if(checking==1)
    {

        ptr_line_edit_struct_address = ptr_class_table+index;
        printf("choose number to edit by :\n 1-name \n 2-ID \n 3-age\n");
        scanf("%d",&edit_choose);
        View_Studet_Element(edit_choose);

    }

    else if(checking==0)
    {

        printf("\n there is no student with this information \n");
    }

    edit_choose=0;
    index=-1;
}
/******************** view functions ****************************/
void View_Studet_Element(u_int_8 choose_line)
{
    print_block();

    if(choose_line==0)
    {
        start_position_y=1;

    }
    else if (choose_line==1)
    {
        start_position_y=1;

        ptr_line_edit_array_address= ptr_line_edit_struct_address->student_name;
        size_of_aray_of_line=ptr_line_edit_struct_address->array_size_name;
        Edit_line();
    }
    else if(choose_line==2)
    {
        start_position_y=2;
        ptr_line_edit_array_address= ptr_line_edit_struct_address->ID;
        size_of_aray_of_line=ptr_line_edit_struct_address->array_size_id;

        Edit_line();
    }
    else if(choose_line==3)
    {
        start_position_y=3;

        ptr_line_edit_array_address= ptr_line_edit_struct_address->age;
        size_of_aray_of_line=ptr_line_edit_struct_address->array_size_age;

        Edit_line();
    }


}


void View_All_Studets(void)
{
    u_int_8 students;
    for(students=0; students<number_of_student; students++)
    {
        printf("\n\n");
        printf("student details : student number : %d \n\n",students+1);
        printf("the name of student : %s",ptr_class_table[students].student_name);
        printf("\n");
        printf("the ID of student : %s \n",ptr_class_table[students].ID);
        printf("the age of student : %s\n",ptr_class_table[students].age);


    }



}
/*****************************************************************/
/******searching********************/
u_int_8 searching_ID(u_int_8 *id)
{
    u_int_8 i=0,j=0,flag=1;
    for(i=0; i<=number_of_student; i++)
    {

        flag = ((id[0]^(ptr_class_table[i].ID[0])) || (id[1]^(ptr_class_table[i].ID[1]) ) || (id[2]^(ptr_class_table[i].ID[2]) ) || (id[3]^(ptr_class_table[i].ID[3]) ));

        if(flag==0)
        {
            index = i;
            return 1;
        }

    }

    return 0;

}
u_int_8 searching_name(u_int_8 *name)
{

    u_int_8 i=0,x=0,j=0,flag=0;

    for(i=0; (i<number_of_student ); i++)
    {

        for(x=0; name[x]!='\0'; x++)
        {


            if(ptr_class_table[i].student_name[x]!=name[x])
            {
                j=1;
            }


        }
        if(j==0)
        {
            index=i;

            return 1;
        }
    }

    return 0;

}
/******************************************************************/

void print_block(void)
{
    system("cls");
    printf("student no : %d\n",index+1);
    printf("name:%s",ptr_class_table[index].student_name);
    printf("\n");
    printf("ID  :%s",ptr_class_table[index].ID);
    printf("\n");
    printf("age :%s",ptr_class_table[index].age);
    printf("\n");
}


/*********************************************************************************************************************************
//                                        line editor functions

*the main function called
*   Edit_line       : take void and return void. edit line by using a pointer refer to the array which wanted to be eiditing.
* line editor uses 5 functions :
* 1) scan_array     :  to scan array from user and return uint8 the size of it.
* 2) insert_char    :  to insert char in the next place of the cursor position on the array and update it ,return void.
* 3) backspace_char :  to delete char from the prev place of the cursor and update the array,return void.
* 4) delete_after   :  to delete char in the next place of the cursor position on the array and update it ,return void.
* 5) replace_char   :  to replace a char and update the array , return void.
/********************************************************************************************************************************/


u_int_8 scan_array(u_int_8 *name,u_int_8 select_ind)
{
    static u_int_8 i;

    fflush(stdin);
    scanf("%c",name);


    for(i=1; name[i-1]!='\n'; i++)
    {
        scanf("%c",(name+i));
        if(select_ind==2 && i==4)
        {
            name[3]='\0';
            return 3;
        }
        else if(select_ind==3 && i==4)
        {
            name[2]='\0';
            return 2;
        }
    }
    name[i-1]='\0';
    i--;

    return i;

}

void insert_char(u_int_8 place,u_int_8 *size,u_int_8 *ptr)
{

    u_int_8 replaced_char = getch();

    int i= *size;

    if(replaced_char!=13)
    {

        for(; i>current_position_line_edit+1; i--)
        {

            ptr[i]=ptr[i-1];
        }
        ptr[i]=replaced_char;
        (*size)++;
        ptr[(*size)]='\0';
    }
    print_block();
    gotoxy(current_position_line_edit+start_position_x,start_position_y);
}

void backspace_char(u_int_8 place,u_int_8 *size,u_int_8 *ptr)
{
    u_int_8 s=(*size);

    int i= place-1;

    if(place==0);

    else
    {
        for(; i<s; i++)
        {

            ptr[i]=ptr[i+1];
        }
        current_position_line_edit--;
        s--;
        ptr[s]='\0';
    }
    print_block();
    gotoxy(current_position_line_edit+start_position_x,start_position_y);
}

void delete_after(u_int_8 position,u_int_8 *size,u_int_8 *ptr)
{

    int i= position+1;

    if(position==((*size)-1+start_position_x));

    else
    {
        for(; i<(*size); i++)
        {

            ptr[i]=ptr[i+1];
        }

        (*size)--;
        ptr[(*size)]='\0';
    }
    print_block();
    gotoxy(current_position_line_edit+start_position_x,start_position_y);

}

void replace_char(u_int_8 ch,u_int_8 position_x,u_int_8 *ptr)
{
    ptr[position_x]=ch;
    print_block();
    gotoxy(position_x+start_position_x,start_position_y);
}
/******************************* edit line ******************************************/
void Edit_line(void)
{
    u_int_8 ch='+',x=start_position_x;

    gotoxy(start_position_x,start_position_y);


    while(ch!=13)
    {

        ch=getch();


        if(ch==224)
        {
            ch=getch();



            switch(ch)
            {
            case 75:  //left
                if(x>start_position_x)
                {
                    --x;
                    --current_position_line_edit;
                    gotoxy((current_position_line_edit+start_position_x),start_position_y);
                }
                break;

            case 77: //right
                if(x<(size_of_aray_of_line+start_position_x))
                {
                    ++current_position_line_edit;
                    ++x;
                    gotoxy((current_position_line_edit+start_position_x),start_position_y);
                }
                break;
            case 82:  //insert
            {
                insert_char(current_position_line_edit,&size_of_aray_of_line,ptr_line_edit_array_address);
            }
            break;
            case 83:  //insert
            {
                delete_after(current_position_line_edit,&size_of_aray_of_line,ptr_line_edit_array_address);
            }
            break;
            }

        }
        else if(ch==8)
        {
            backspace_char(current_position_line_edit,&size_of_aray_of_line,ptr_line_edit_array_address);

        }
        else if((ch>='A'&& ch<='Z')||(ch>='a'&& ch<='z')||(ch>='0'&& ch<='9'))
        {

            replace_char(ch,current_position_line_edit,ptr_line_edit_array_address);

        }


        gotoxy(current_position_line_edit+start_position_x,start_position_y);

    }

}
/*********************************** menu function **********************************/

void menu_list(void)
{
    char flag=0,ch,y=0;


    while(flag==0)
    {

        system("cls");
        textattr(7<<4);
        printf("ADD \n");
        textattr(8);
        printf("REMOVE \n");
        textattr(8);
        printf("EDIT \n");
        textattr(8);
        printf("view student \n");
        textattr(8);
        printf("view all students \n");
        textattr(8);
        printf("END ");

        textattr(8);
        gotoxy(0,0);
        y=0;

        ch=getch();

        while(ch!=13)
        {
            ch=getch();
            switch(ch)
            {
            case 72:  //up
                if(y>0)
                    y--;
                else if(y==0)
                    y=5;
                gotoxy(0,y);
                break;

            case 80: //down
                if(y<5)
                    y++;
                else if(y==5)
                    y=0;
                gotoxy(0,y);
                break;

            }
            system("cls");
            if(y==0)
            {

                textattr(7<<4);
                printf("ADD \n");
                textattr(8);
                printf("REMOVE \n");
                textattr(8);
                printf("EDIT \n");
                textattr(8);
                printf("view student \n");
                textattr(8);
                printf("view all students \n");
                textattr(8);
                printf("END ");

                textattr(8);
            }
            else if(y==1)
            {

                textattr(8);
                printf("ADD \n");
                textattr(7<<4);
                printf("REMOVE \n");
                textattr(8);
                printf("EDIT \n");
                textattr(8);
                printf("view student \n");
                textattr(8);
                printf("view all students \n");
                textattr(8);
                printf("END ");

                textattr(8);
            }

            else if(y==2)
            {

                textattr(8);
                printf("ADD \n");
                textattr(8);
                printf("REMOVE \n");
                textattr(7<<4);
                printf("EDIT \n");
                textattr(8);
                printf("view student \n");
                textattr(8);
                printf("view all students \n");
                textattr(8);
                printf("END ");

                textattr(8);
            }
            else if(y==3)
            {

                textattr(8);
                printf("ADD \n");
                textattr(8);
                printf("REMOVE \n");
                textattr(8);
                printf("EDIT \n");
                textattr(7<<4);
                printf("view student \n");
                textattr(8);
                printf("view all students \n");
                textattr(8);
                printf("END ");

                textattr(8);
            }
            else if(y==4)
            {

                textattr(8);
                printf("ADD \n");
                textattr(8);
                printf("REMOVE \n");
                textattr(8);
                printf("EDIT \n");
                textattr(8);
                printf("view student \n");
                textattr(7<<4);
                printf("view all students \n");
                textattr(8);
                printf("END ");

                textattr(8);
            }
            else if(y==5)
            {
                textattr(8);
                printf("ADD \n");
                textattr(8);
                printf("REMOVE \n");
                textattr(8);
                printf("EDIT \n");
                textattr(8);
                printf("view student \n");
                textattr(8);
                printf("view all students \n");
                textattr(7<<4);
                printf("END ");

                textattr(8);
            }
            gotoxy(0,y);
        }

        ch='+';

        system("cls");
        textattr(8);
        gotoxy(0,0);

        if(y==0)
        {

            printf("hello, you are in the add choose \n*************************\n press enter to go back to the start menu\n\n");
            ADD_Studet_Element();
            while(ch!=13)
            {
                ch=getch();
            }
        }
        else if(y==1)
        {

            printf("you are in the remove choose \n*************************\n press enter to go back to the start menu\n\n");
            Remove_Studet_Element();
            while(ch!=13)
            {
                ch=getch();
            }
        }
        else if(y==2)
        {

            printf("you are in the edit choose \n*************************\n press enter to go back to the start menu\n\n");
            Edit_Studet_Element();
            while(ch!=13)
            {
                ch=getch();
            }
        }
        else if(y==3)
        {
            u_int_8 ind=0;
            printf("you are in the view one student \n*************************\n press enter to go back to the start menu\n\n");
            printf("enter the student number from 1 to %d :",number_of_student);
            scanf("%d",&ind);
            index=ind-1;
            View_Studet_Element(0);
            while(ch!=13)
            {
                ch=getch();
            }
        }
        else if(y==4)
        {

            printf("you are in the view all students choose \n*************************\n press enter to go back to the start menu\n\n");
            View_All_Studets();
            while(ch!=13)
            {
                ch=getch();
            }
        }
        else if (y==5)
        {

            system("cls");

            while(ch!=13)
            {
                ch=getch();
            }
            flag=1;
        }


    }
}
