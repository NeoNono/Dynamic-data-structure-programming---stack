#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct
{
    char surname[20];
    char cathegory[20];
    char product[20];
    char manufacturer[20];
    int qty;
    int price;
} data;


typedef struct Stack      //�������� ����
{
    data newB;
    struct Stack *next;
} OBJ;


int  amount(OBJ*top);
void print(OBJ*top);
void push(OBJ**top,data newB);
void del_(OBJ**top, char s_name[] );
void print_type_product(OBJ* top);
void print_zamov_cath(OBJ* top);
//void print_manufacturer(OBJ*top);
void push_to_mas(int am, OBJ mas[],OBJ *top);
void sort(int am,OBJ mas[],int a);
void redactor(OBJ* top);
void lower_price(OBJ*top);
void tovarX_to_tovarY(OBJ* top);
void povtor(OBJ**top);
void output_file(OBJ**top,data newB);
void input_in_file(OBJ*top,int amo);

int main ()
{

    OBJ *top = NULL;
    data newB;
    int a;
    int amount_;
    int b = 0;
    int proverka;
    system("chcp 1251 && cls");

    while(1)
    {
        printf("\nMenu:\n\n");           
        printf("1.Add a product\n");
        printf("2.Show all information about product\n");
        printf("3.Delete information about product\n");
        printf("4.Change information about product\n");
        printf("5.Show the information about product sorted by price\n");
        printf("6.Change selected manufactirer's product X to product Y\n");
        printf("7.Show the list of customers on a selected group of products\n");
        printf("8.Show products with a price less that specified\n");
        printf("9.Show the list of customers on selected product\n");
        printf("10.Add products to file\n");
        printf("11.Add to stack and show products from the file on the screen\n");
        printf("12.Exit the program\n");
        printf("\nWhich option would you like to choose?\n");

        while( scanf("%d",&a) != 1 )
        {
            printf("Enter a number!\n");
            _flushall();
        }

        switch(a)                                   //����� ������ �� ������� ����
        {
        case 1:
            getchar();
            printf("Enter the surname of customer: ");
            gets(newB.surname);
            printf("Enter the category of product: ");
            gets(newB.cathegory);
            printf("Enter the name of product: ");
            gets(newB.product);
            printf("Enter the name of manufacturer: ");
            gets(newB.manufacturer);

            printf("ʳAmount ");
            while( scanf("%d",&newB.qty) != 1 || newB.qty <= 0 )
            {
                printf("Enter a number!\n");
                _flushall();
            }

            printf("ֳPrice: ");
            while( scanf("%d",&newB.price) != 1 || newB.price <= 0 )
            {
                printf("Enter a number!\n");
                _flushall();
            }


            push(&top,newB);
            povtor(&top);
            break;

        case 2:
            print(top);
            break;

        case 3:
            printf("Enter the name of produc you would like to delete: ");
            char p_name[50];
            getchar();
            gets(p_name);

            int YorN;
            printf("Are you sure you want to delete information about this product?\n 1 - Yes\n 2 - No\nYour choice: ");
            while( scanf("%d",&YorN) != 1 || YorN < 1 || YorN > 2 )
            {
                printf("Enter the number that satisfies the condition!\n");
                _flushall();
            }


            if(YorN == 1)
                del_(&top, p_name );
            else printf("Deletion cancelled!\n");

            break;
       case 4:
           redactor(top);
            break;

        case 5:
{


            amount_ = amount(top);
            OBJ* mas = (OBJ*)malloc(amount_*(sizeof(OBJ)));
            push_to_mas(amount_,mas,top);
            sort(amount_,mas,a);
            break;
}

        case 6:
              tovarX_to_tovarY(top);
               break;
        case 7:
            print_zamov_cath(top);
             break;
    case 8:
           lower_price(top);
            break;

        case 9:
            print_type_product(top);
             break;



        case 10:
            ;
            int YorN1;

            printf("Would you like to add this product to file? All previous data in file will bt deleted.\n 1 - �Yes\n 2 - No\nYour choice: ");

            while( scanf("%d",&YorN1) != 1 || YorN1 < 1 || YorN1 > 2 )
            {
                printf("Enter the number that satisfies the condition!\n");
                _flushall();
            }
            if( YorN1 == 1 )
            {
                amount_ = amount(top);
                input_in_file(top,amount_);
            }
            else printf("Data is not added to the file\n");
            break;
        case 11:
            ;
            int YorN2;

            printf("Would you like to add product from file?\n 1 - Yes\n 2 - No\nYour choice: ");

            while( scanf("%d",&YorN2) != 1 || YorN2 < 1 || YorN2 > 2 )
            {
                printf("Enter the number that satisfies the condition!\n");
                _flushall();
            }

            if( YorN2 == 1 )
            {
                if(b == 0)
                {
                    output_file(&top,newB);
                    print(top);
                    b++;
                }
                else printf("You have already read information about product from file!");
            }
            else printf("Data is not added from the file!\n");
            break;
        case 12:
            exit(1);
            break;
        }
    }
    return 0;
}
//-----------------------------------------------------------------------------------------//
void push(OBJ**top,data newB)                       // CASE 1
{
    OBJ *q;

    q = (OBJ *)malloc(sizeof(OBJ));
    q -> newB = newB;

    if(top==NULL)
    {
        *top = q;
    }
    else
    {
        q->next = *top;
        *top = q;
    }
}

void povtor(OBJ**top)    //CASE 1
{

    OBJ* q = *top;
    OBJ* m = q->next;

    while( m )
    {
        if( strcmp( q->newB.product, m->newB.product ) == 0 )
        {
            *top = q->next;
            free(q);
            printf("This product already exists. You can't add it.\n");
        }
        m = m->next;
    }
}

void print(OBJ*top)                             // CASE 2
{

    OBJ *q = top;

    printf(" ______________________________________________________________________________________________________________\n");
    printf("|   Customer's Surname     |  Category        |  Product name |    Manufacturer  |   Amountֳ   | Price          |\n");
    printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");

    while (q)
    {
        printf("|%26s|%18s|%15s|%18s|%12d|%16d|\n",q->newB.surname,q->newB.cathegory,q->newB.product,q->newB.manufacturer,q->newB.qty,q->newB.price);
        printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
        q = q->next;
    }

}

void push_to_mas(int am, OBJ mas[],OBJ *top)
{
    OBJ *q = top;
    for(int i = 0; i < am; i++)
    {
        mas[i].newB = q->newB;
        q = q->next;
    }
}

void del_(OBJ**top, char p_name[] )         //CASE 3 
{

    OBJ *q = *top;
    OBJ *prev = NULL;
    int i = 0;

    while( q != NULL )
    {
        if(strcmp(q->newB.product,p_name)==0)
        {
            if( q == *top )
            {
                *top = q->next;
                free(q);
            }
            else
            {
                prev->next = q->next;
                free(q);
            }
            i++;
        }
        prev = q;
        q = q->next;
    }
    if(i == 0) printf("\nThis product does not exist!\n");
    printf("Deleted successfully!");

}

int amount(OBJ*top)  //CASE 5
{

    OBJ *q = top;

    int i = 0;

    while (q)
    {
        i++;
        q = q->next;
    }
    return i;
}



void redactor(OBJ* top){   //CASE 4
    OBJ * q = top;
    char other_name[20];

    char surname1[20];
    char cathegory1[20];
    char manufacturer1[20];
    int qty1;
    int price1;

    printf("Which product's details would you like to change?\n");
    getchar();
    gets(other_name);

    while(q){
        if( strcmp(q->newB.product,other_name) == 0 ){
            printf("Enter customer's name: ");
            gets(surname1);
             printf("Enter product category: ");
            gets(cathegory1);
             printf("Enter the manufacturer: ");
            gets(manufacturer1);


            printf("ʳAmount: ");
            while( scanf("%d",&qty1) != 1 || qty1 <= 0 ){
                printf("Enter the number!\n");
                _flushall();
            }
             printf("ֳPrice: ");
            while( scanf("%d",&price1) != 1 || price1 <= 0 ){
                printf("Enter the number!\n");
                _flushall();
            }


            strcpy(q->newB.surname,surname1);
             strcpy(q->newB.cathegory,cathegory1);
              strcpy(q->newB.manufacturer,manufacturer1);
            q->newB.qty = qty1;
            q->newB.price = price1;
        }
        q = q->next;
    }
}


void sort(int am,OBJ mas[],int a)   //-----CASE 5
{

    OBJ temp;

    if(a == 5)
    {
        for(int i = 0; i < am; i++)
        {
            for(int j = 0; j < am; j++)
            {
                if( mas[i].newB.price < mas[j].newB.price)
                {
                    temp.newB = mas[i].newB;
                    mas[i].newB = mas[j].newB;
                    mas[j].newB = temp.newB;
                }
            }
        }

    printf(" ______________________________________________________________________________________________________________\n");
    printf("|   Customer's Surname     |  Category        |  Product name |    Manufacturer  |   Amountֳ   | Price          |\n");
    printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");

        for(int i = 0; i < am; i++)
        {
            printf("|%26s|%18s|%15s|%18s|%12d|%16d|\n",mas[i].newB.surname,mas[i].newB.cathegory,mas[i].newB.product,mas[i].newB.manufacturer,mas[i].newB.qty,mas[i].newB.price);
            printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
        }
    }

}

void tovarX_to_tovarY(OBJ* top){       //CASE 6    
    OBJ * q = top;
    char vyrobnyk[20];
     int i = 0;
    char tovar[20];


    printf("?\n");
    getchar();
    gets(vyrobnyk);

    while(q){
        if( strcmp(q->newB.manufacturer,vyrobnyk) == 0 ){
            printf("Enter new name of the product: ");
            gets(tovar);

            strcpy(q->newB.product,tovar);
           i=1;

        }
        q = q->next;
    }



    q = top;

    if( i == 1 )
    {
    printf(" ______________________________________________________________________________________________________________\n");
    printf("|   Customer's Surname     |  Category        |  Product name |    Manufacturer  |   Amountֳ   | Price          |\n");
    printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");

        while(q)
        {
            if( strcmp(q->newB.manufacturer,vyrobnyk) == 0 ){
            printf("|%26s|%18s|%15s|%18s|%12d|%16d|\n",q->newB.surname,q->newB.cathegory,q->newB.product,q->newB.manufacturer,q->newB.qty,q->newB.price);
        printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
            }
        q = q->next;
    }
     printf("No manufacturer with such name");
}
}

void print_zamov_cath(OBJ*top){  //CASE 7  

    OBJ *q = top;
    int i = 0;
    char cath[20];

    printf("Choose the name of product to show the customers:\n ");
    getchar();
    gets(cath);

    while(q){
        if(strcmp(cath,q->newB.cathegory) == 0)
        i=1;
        q = q->next;
    }

    q = top;

    if( i == 1 ){
    printf(" ______________________________________________________________________________________________________________\n");
    printf("|   Customer's Surname     |  Category        |  Product name |    Manufacturer  |   Amountֳ   | Price          |\n");
    printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
        while(q){
                if(strcmp(cath,q->newB.cathegory) == 0){
            printf("|%26s|%18s|%15s|%18s|%12d|%16d|\n",q->newB.surname,q->newB.cathegory,q->newB.product,q->newB.manufacturer,q->newB.qty,q->newB.price);
        printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
                }
        q = q->next;
        }
    }
    else printf("No customers with such category\n");
}

void lower_price(OBJ*top){  //-------CASE 8

 OBJ *q = top;
 int lowprice;

    printf("Enter the price to show the products: ");
    scanf("%d", &lowprice);

    while(q != NULL)
    {

         if (lowprice>q->newB.price)
       {
    printf(" ______________________________________________________________________________________________________________\n");
    printf("|   Customer's Surname     |  Category        |  Product name |    Manufacturer  |   Amountֳ   | Price          |\n");
    printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
    printf("|%26s|%18s|%15s|%18s|%12d|%16d|\n",q->newB.surname,q->newB.cathegory,q->newB.product,q->newB.manufacturer,q->newB.qty,q->newB.price);
    printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
       }
        q = q->next;
    }
    printf("No product with such price\n");
}
void print_type_product(OBJ*top)    // CASE 9
{

    OBJ *q = top;
    int i = 0;
    char type_product[20];

    printf("Enter the name of product by which you want to output customers: \n");
    getchar();
    gets(type_product);

    while(q)
    {
        if(strcmp(type_product,q->newB.product) == 0)
            i=1;
        q = q->next;
    }

    q = top;

    if( i == 1 )
    {
    printf(" ______________________________________________________________________________________________________________\n");
    printf("|   Customer's Surname     |  Category        |  Product name |    Manufacturer  |   Amountֳ   | Price          |\n");
    printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
        while(q)
        {
            if(strcmp(type_product,q->newB.product) == 0){
            printf("|%26s|%18s|%15s|%18s|%12d|%16d|\n",q->newB.surname,q->newB.cathegory,q->newB.product,q->newB.manufacturer,q->newB.qty,q->newB.price);
        printf("|__________________________|__________________|_______________|__________________|____________|________________|\n");
            }
        q = q->next;
        }
    }
    else printf("No clients with such product");
}

void input_in_file(OBJ*top,int amo)   //---CASE10
{

    OBJ *q = top;
    FILE* f = fopen("file.txt","w");

    if(f == NULL)
    {
        printf("Error! Impossible to open the file\n");
        exit(1);
    }

    for(int i = 0; i<amo; i++)
    {
        fprintf(f,"%s %s %s %s %d %d ",q->newB.surname,q->newB.cathegory,q->newB.product,q->newB.manufacturer,q->newB.qty,q->newB.price);
        q = q->next;
    }
    printf("Successfully written to file!\n");
    fclose(f);
}

void output_file(OBJ**top,data newB){  //----- CASE 11

    OBJ* q;

    FILE* f = fopen("file.txt","r");

    if(f == NULL){
        printf("Error! Impossible to open the file\n");
        exit(1);
    }

    while(!feof(f)){
        q = (data *)malloc(sizeof(OBJ));
        fscanf(f,"%s %s %s %s %d %d ",&newB.surname,&newB.cathegory,&newB.product,&newB.manufacturer,&newB.qty,&newB.price);
        q->newB = newB;
        if(top==NULL){
            *top = q;
        }
        else{
            q->next = *top;
            *top = q;
        }
        OBJ* m = *top;
        OBJ* a = m->next;
        while( a ){
        if( strcmp( m->newB.product , m->newB.product ) == 0 ){
            *top = m->next;
            free(m);
        }
        a = a->next;
    }
    }
    fclose(f);
}




