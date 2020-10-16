#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
int indx = -1;
int mem_index;
struct INVENTORY
{
  char item_name[50];
  int item_no;
  int item_quantity;
  float item_MRP;
  float item_price;
  struct INVENTORY *next;
}item[53];

struct MEMBER
{
  char name[50];
  int id;
  int number_of_donation;
}mem[100];
int mem_count;

struct INVOICE
{
  float subtotal;
  float gst;
  float discount;
  float total;
  int item_number[53];
  int item_q[53];
  char cust_name[50];
}bill;

void after_goodjob()
{
  remove("employees.csv");
  rename("temp.csv","employees.csv");
}

void checkDate()
{
  FILE *f;
  f=fopen("date.txt","r");
  int a[3],b[3];
  SYSTEMTIME t;
  GetLocalTime(&t);
  a[0]=t.wDay;
  a[1]=t.wMonth;
  a[2]=t.wYear;
  char l[15];
  fgets(l,15,f);
  b[0]=atoi(strtok(l,"/"));
  b[1]=atoi(strtok(NULL,"/"));
  b[2]=atoi(strtok(NULL,"\n"));
  fgets(l,2,f);
  int flag=atoi(strtok(l,"\n"));
  if(a[0]==b[0]&&flag==1)
  {
    printf("1");
    FILE *emp,*newfile;
    int ti;
    emp=fopen("employees.csv","r");
    newfile=fopen("temp.csv","w");
    char line[100],newline[100],*temp;
    memset(newline,0,sizeof(newline));
    while(fgets(line,100,emp))
    {
      temp=strtok(line,",");
      strcat(newline,temp);
      strcat(newline,",");
      temp=strtok(NULL,",");
      ti=0;
      sprintf(temp,"%d",ti);
      strcat(newline,temp);
      strcat(newline,",");
      strcat(newline,strtok(NULL,"\n"));
      strcat(newline,"\n");
      fprintf(newfile,newline);
      memset(newline,0,sizeof(newline));
    }
    fclose(emp);
    fclose(newfile);
    fclose(f);
    FILE *n;
    n=fopen("date.txt","w");
    fprintf(n,"%d/%d/%d\n0",b[0],b[1],b[2]);
    fclose(n);
    after_goodjob();
  }
  else if(a[0]!=b[0])
  {
    printf("2");
    fclose(f);
    FILE *n;
    n=fopen("date.txt","w");
    fprintf(n,"%d/%d/%d\n1",b[0],b[1],b[2]);
    fclose(n);
  }
}

int check(int id)
{
  FILE *emp;
  int flag=-1,temp;
  emp=fopen("employees.csv","r");
  char line[100];
  while(fgets(line,100,emp))
  {
    temp=atoi(strtok(line,","));
    if(temp==id)
    {
      flag=1;break;
    }
  }
  return flag;
}

void goodjob(int id)
{
  FILE *emp,*newfile;
  int ti;
  emp=fopen("employees.csv","r");
  newfile=fopen("temp.csv","w");
  char line[100],newline[100],*temp;
  memset(newline,0,sizeof(newline));
  while(fgets(line,100,emp))
  {
    temp=strtok(line,",");
    ti=atoi(temp);
    if(ti!=id)
    {
      strcat(newline,temp);
      strcat(newline,",");
      temp=strtok(NULL,",");
      strcat(newline,temp);
      strcat(newline,",");
      strcat(newline,strtok(NULL,"\n"));
      strcat(newline,"\n");
      fprintf(newfile,newline);
      memset(newline,0,sizeof(newline));
    }
    else
    {
      strcat(newline,temp);
      strcat(newline,",");
      temp=strtok(NULL,",");
      ti=1+atoi(temp);
      sprintf(temp,"%d",ti);
      strcat(newline,temp);
      strcat(newline,",");
      strcat(newline,strtok(NULL,"\n"));
      strcat(newline,"\n");
      fprintf(newfile,newline);
      memset(newline,0,sizeof(newline));
    }
  }
  fclose(emp);
  fclose(newfile);
}

void showsales(int id)
{
  FILE *emp;
  int temp;
  emp=fopen("employees.csv","r");
  char line[100];
  while(fgets(line,100,emp))
  {
    temp=atoi(strtok(line,","));
    if(temp==id)
    {
      printf("Number of sales made by this person:%d",atoi(strtok(line,",")));
      break;
    }
  }
}

void update_inventory()
{
  int i;
  for(i=0;i<54;i++)
  {
    item[i].item_quantity = item[i].item_quantity - bill.item_q[i];
  }
}

bool check_if_possible(int item_number, int quantity)
{
  if(item[item_number-101].item_quantity >=  quantity)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void member_reading()
{
  FILE *member;
  char line[100];
  char *field;
  int i = 0;
  mem_count = 0;
  member = fopen("members.csv", "r");
  if (!member)
  {
    printf("Error opening file\n");
  }
  else
  {
    while (fgets(line, 200, member))
    {
      field = strtok(line, ",");
      strcpy(mem[i].name, field);

      field = strtok(NULL, ",");
      mem[i].id = atoi(field);

      field = strtok(NULL, "\n");
      mem[i].number_of_donation = atoi(field);

      mem_count++;
    }
  }
}

void member_updation()
{
  FILE *member;
  member = fopen("members.csv", "w");
  int i = 0;
  while (i < mem_count)
  {
    fprintf(member, "%s,%d,%d", mem[i].name, mem[i].id, mem[i].number_of_donation);
  }
}

void inventory_reading()
{
  FILE *data;
  char line[100];
  char *field;
  int i = 0;

  data = fopen("inventory.csv", "r");
  if(data == NULL)
  {
      printf("Error opening file\n");
  }
  else
  {
    while(fgets(line,100,data) != NULL)
    {
      field = strtok(line,",");
      strcpy(item[i].item_name,field);

      field = strtok(NULL,",");
      item[i].item_no = atoi(field);

      field = strtok(NULL,",");
      item[i].item_quantity = atoi(field);

      field = strtok(NULL,",");
      item[i].item_MRP = atof(field);

      field = strtok(NULL,"\n");
      item[i].item_price = atof(field);
      i++;
    }
    fclose(data);
  }
}

void inventory_updation()
{
  FILE *data;
  data = fopen("inventory.csv", "w");

  if(!data)
  {
    printf("Error while updating file\n");
  }
  else
  {
    int i=0;
    for(i=0;i<54;i++)
    {
      fprintf(data , "%s,%d,%d,%0.2f,%0.2f\n", item[i].item_name, item[i].item_no,item[i].item_quantity,item[i].item_MRP, item[i].item_price);
    }
  }
}

void update_item_quantity_after_sale()
{
  int i;
  for(i=0;i<54;i++)
  {
    item[bill.item_number[i] - 101].item_quantity = item[bill.item_number[i] - 101].item_quantity - bill.item_q[i];
  }
  inventory_updation();
}

void add_item(int id, int quantity)
{
  if(check_if_possible(id,quantity))
  {
    indx++;
    printf("ITEM ADDED!!\n");
    bill.item_q[indx]=quantity;
    bill.item_number[indx]=id;
  }
  else
  {
    printf("Not enough items available!!\n");
  }
}

void print_bill()
{
    int i;
    for(i=0;i<indx;i++)
    {
        bill.subtotal += item[bill.item_number[i]-101].item_MRP*bill.item_q[i];
    }
    bill.gst=bill.subtotal*0.18;
    bill.total=bill.subtotal+bill.gst;

    char a[]="Item Name";
    char b[]="Item Number";
    char c[]="Quantity";
    char d[]="Rate";
    char e[]="Amount";
    char f[]="Total";
    char g[]="Subtotal";
    char h[]="GST";
    printf("|________________________________________________________________________________________________________|\n");
    printf("|**************************************************Invoice***********************************************|\n\n");
    printf("|%20s|%20s|%20s|%20s|%20s|\n",b,a,c,d,e);
    for(i=0;i<indx;i++)
    {
      printf("|%20d|%20s|%20d|%20.2f|%20.2f|\n", item[bill.item_number[i] - 101].item_no, item[bill.item_number[i] - 101].item_name, bill.item_q[i], item[bill.item_number[i] - 101].item_MRP, item[bill.item_number[i] - 101].item_MRP * bill.item_q[i]);
    }
    printf("|---------------------------------------------------------------------------------------------------------\n");
    printf("                                                                                                __________\n");
    printf("%86s%20.2f\n",g,bill.subtotal);
    printf("%86s%20.2f\n",h,bill.gst);
    printf("%86s%20.2f\n",f,bill.total);
    printf("                                                                                                __________\n");
}

void print_inventory()
{

}

/*Samarth when building the main after calling the printing of bill call goodjob(id) make an id variable in main and input it inthe start of the program*/
int main()
{
  // employee login
  //          new customer
  //              member,or not(if not add?)
  //              add items to the bill .line 84.
  //              create bill(discount , gst)
  //check sales
  //2nd screen

  //change by Parnav keep the following line the first line of main
  checkDate();

  int s, num, k, m, q, t;
  char x;
  printf("\t\t\t\t#########  Welcome Human  ##########\n");

  printf("\n\nEnter Employee Id:");
  scanf("%d", &num);
  if (num == 007)
  {
    system("cls");
    printf("\n___________________________________________");
    printf("\n******************Menu*********************");
    printf("\n___________________________________________\n ");
    do
    {

      printf("\nMenu:\n1.New Customer \n2.Check Inventory \n3.Go Back\n4.Exit:\n");
      scanf("%d", &s);
      switch (s)
      {
        case 1:
          inventory_reading();
          system("cls");
          printf("\n__________________________________________");
          printf("\n****************Menu***************");
          printf("\n____________________________________________\n ");
          printf("\n1.Existing Member \n2.Add Member \n3.Go Back: ");
          scanf("%d", &k);
          if (k == 1)
          {
            printf(" \nExisting Member\n");
            printf("ID OF MEMBER: ");
            scanf("%d",&mem_index);
            do
            {
              printf("Enter 0 To Print Bill\n");
              printf("Add Items\n");
              printf("Item number:");
              scanf("%d", &m);
              if(m != 0)
              {
                printf("Quantity:");
                scanf("%d", &q);
              }
              add_item(m, q);
              system("cls");
            } while (m != 0);
            print_bill();
            printf("Press any key to continue.....\n");
            scanf("%s",&x);
          }
          if (k == 2)
          {
            printf("\n***Add Member***\n");
            printf("ENTER THE NAME OF MEMBER: ");
            fflush(stdin);
            scanf("%s", &mem[mem_index].name);
            printf("ENTER THE id OF MEMBER: ");
            fflush(stdin);
            scanf("%s", &mem[mem_index].id);
            mem[mem_index].number_of_donation = 0;
          }
          system("cls");
        break;

        case 2:
          print_inventory();
        break;

        case 3:
        break;

        case 4:
          exit(0);
        break;

        default:
          printf("Wrong Input");
        break;
      }
    } while (s != 3 && s!=4);
  }
  else
  {
    printf("INVALID ID ");
  }
  return 0;
}
