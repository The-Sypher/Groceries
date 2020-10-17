#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
int indx = -1;
int employee_num;
int member_id = -1;
int s, num, k, m, q, t,i;
char x;
void press_key_to_continue()
{
  printf("\n\nPress any key to continue.....\n");
  scanf("%d",&x);
}
struct INVENTORY
{
  char item_name[50];
  int item_no;
  int item_quantity;
  float item_MRP;
  float item_price;
  struct INVENTORY *next;
}item[53];

struct INVOICE
{
  float subtotal;
  float gst;
  float discount;
  float total;
  int item_number[53];
  int item_q[53];
  char cust_name[50];
} bill;

struct MEMBER
{
  char name[50];
  int id;
  int number_of_donation;
}mem[100];

int mem_count=0;
int mem_index=-1;

void member_updation()
{
  FILE *member;
  member = fopen("members.csv", "w");
  for(i=0;i<mem_count;i++)
  {
    fprintf(member, "%s,%d,%d\n", mem[i].name, mem[i].id, mem[i].number_of_donation);
  }
  fclose(member);
}

void add_member()
{
  mem_index++;
  mem_count++;
  printf("Enter Member's Name: \n");
  fflush(stdin);
  gets(mem[mem_index].name);
  mem[mem_index].id = mem_index+100;
  mem[mem_index].number_of_donation = 0;
  member_id = mem[mem_index].id;
  member_updation();
}

void print_donation(int id)
{
  printf("THE NUMBER OF DONATIONS MADE BY THE MEMBER: %d\n",  mem[id-100].number_of_donation);

}

void member_donate(int id)
{
  mem[id-100].number_of_donation++;
}

void afterBill()
{
  FILE *f;
  f=fopen("sold.csv","r");
  float profit;
  char line[100],*l;
  fgets(line,100,f);
  l=strtok(line,"\n");
  profit=atof(l);
  for(int i=0;i<indx;i++)
    profit+=(item[bill.item_number[i]-101].item_MRP-item[bill.item_number[i]-101].item_price)*bill.item_q[i];
  fclose(f);
  f=fopen("sold.csv","w");
  fprintf(f,"%0.2f",profit);
  fclose(f);
}

void printProfit()
{
  FILE *f;
  f=fopen("sold.csv","r");
  char line[100],*l;
  fgets(line,100,f);
  l=strtok(line,"\n");
  printf("Your profit this month: %s",l);
  fclose(f);
}

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
    n=fopen("sold.csv","w");
    fprintf(n, "0");
    fclose(n);
  }
  else if(a[0]!=b[0])
  {

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
  after_goodjob();
}

void showsales(int id)
{
  
  FILE *emp;
  int temp;
  emp=fopen("employees.csv","r");
  char line[100],*l;
  while(fgets(line,100,emp))
  {
    l = strtok(line,",");
    int emp_id=atoi(l);

    l = strtok(NULL,",");
    int emp_sales = atoi(l);

    l = strtok(NULL,"\n");
    char name[50];
    strcpy(name,l);
    if(emp_id == id)
    {
      printf("%20d%20s%20d\n",emp_id,name,emp_sales);
    }
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
      mem_index++;
    }
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

    for(i=0;i<54;i++)
    {
      fprintf(data , "%s,%d,%d,%0.2f,%0.2f\n", item[i].item_name, item[i].item_no,item[i].item_quantity,item[i].item_MRP, item[i].item_price);
    }
  }
  fclose(data);
}

void update_item_quantity_after_sale()
{

  for(i=0;i<=indx;i++)
  {
    item[bill.item_number[i] - 101].item_quantity = item[bill.item_number[i] - 101].item_quantity - bill.item_q[i];
  }
  indx = -1;
  inventory_updation();
}

void add_item(int id, int quantity)
{
  if(check_if_possible(id,quantity))
  {
    indx++;
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
  char name[50];
  if(member_id == -1)
  {
    printf("Enter Customer Name: ");
    fflush(stdin);
    gets(name);
  }
  else
  {
    strcpy(name,mem[member_id-100].name);
  }
  for(i=0;i<=indx;i++)
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
  system("cls");
  printf("%d", item[bill.item_number[i] - 101].item_no);
      printf("\n________________________________________________________________________________________________________\n");
  printf("                                                Invoice                                                |\n");
  printf("________________________________________________________________________________________________________\n");
  printf("Bill to: %s\n",name);
  printf("|--------------------------------------------------------------------------------------------------------|\n");
  printf("|%20s|%20s|%20s|%20s|%20s|\n",b,a,c,d,e);
  for(i=0;i<=indx;i++)
  {
    printf("|%20d|%20s|%20d|%20.2f|%20.2f|\n", item[bill.item_number[i] - 101].item_no, item[bill.item_number[i] - 101].item_name, bill.item_q[i], item[bill.item_number[i] - 101].item_MRP, item[bill.item_number[i] - 101].item_MRP * bill.item_q[i]);
  }
  printf("|--------------------------------------------------------------------------------------------------------|\n");
  printf("                                                                                                __________\n");
  printf("%86s%20.2f\n",g,bill.subtotal);
  printf("%86s%20.2f\n",h,bill.gst);
  printf("%86s%20.2f\n",f,bill.total);
  printf("                                                                                                __________\n");
}

void print_inventory()
{
  char a[] = "Item Code";
  char b[] = "Item Name";
  char c[] = "Quantity Left";
  printf("%10s%20s%20s\n",a,b,c);

  for(i=0;i<54;i++)
  {
    printf("%10d%20s%20d\n",item[i].item_no,item[i].item_name,item[i].item_quantity);
  }
}

void make_bill()
{
  int flag;
  do
  {
    system("cls");
    printf("Enter (0) To Print Bill\n\n");
    printf("Add Items\n");
    printf("Item number:\n");
    scanf("%d", &m);
    if (m != 0)
    {
      printf("Quantity:\n");
      scanf("%d", &q);
    }
    add_item(m, q);
    system("cls");
  } while (m != 0 && indx < 0);

  print_bill();
  update_item_quantity_after_sale();
  inventory_updation();
  if(member_id != -1)
  {
    printf("Do You Want To Donate Rs.5 to charity?\n1.Yes\2.No\n");
    scanf("%d",&flag);
    if(flag == 1)
    {
      member_donate(member_id);
      member_updation();
    }
    else 
    {
      printf("No Problem...Maybe next time....\n");
    }
  }
  goodjob(employee_num);
  afterBill();
  press_key_to_continue();
}

void call()
{
  if (check(employee_num))
  {
    system("cls");
    printf("\n___________________________________________");
    printf("\n                  Menu");
    printf("\n___________________________________________");
    do
    {
      printf("\n1.New Customer \n2.Check Inventory \n3.Go Back\n4.Exit:\n");
      scanf("%d", &s);
      switch (s)
      {
      case 1:
        system("cls");
        printf("\n__________________________________________");
        printf("\n                  Menu");
        printf("\n__________________________________________");
        printf("\n1.Existing Member \n2.Not a Member \n3.Go Back: ");
        scanf("%d", &k);

        if (k == 1)
        {
          bool flag = false;
          do
          {
            system("cls");
            printf("Enter (0) to Go Back");
            printf(" \nExisting Member\n");
            printf("ID OF MEMBER: ");
            scanf("%d", &member_id);
            if(member_id == 0)
            {
              flag = 1;
              break;
            }
            else if(member_id > mem_count*100 || member_id < 100)
            {
              printf("\nMember not found ):\n");
              Sleep(1500);
            }
            else
            {
              make_bill();
            }
          }while(!flag);
        }
        if (k == 2)
        {
          int z;
          do
          {
            system("cls");
            printf("Enter (0) to Go Back\n");
            printf("Add Member?\n1. Yes\n2. No\n");
            scanf("%d",&z);
          }while(z != 1 && z != 2 && z != 0);
          if(z == 1)
          {
            add_member();
            make_bill();
          }
          else if(z == 2)
          {
            make_bill();
          }
        }
        system("cls");
      break;

      case 2:
        print_inventory();
        press_key_to_continue();
        system("cls");
      break;

      case 3:
        printf("Going to Employee Login....\n");
        employee_num = 7;
        Sleep(2000);
        system("cls");
      break;

      case 4:
        system("cls");
        printf("Have a nice day!!\n");
        Sleep(2000);
        exit(0);
        break;

      default:
        printf("Wrong Input");
        break;
      }
    } while (s != 3 && s != 4);
  }
}

void employee_Login()
{
  do
  {
    printf("Enter (0) to Go Back\n");
    printf("Enter (1) to Exit\n");
    printf("\nEnter Employee Id: ");
    scanf("%d", &employee_num);
    if (check(employee_num) != 1 && employee_num != 0 && employee_num != 1)
    {
      printf("Employee does not exist, Please enter valid id....\n");
      Sleep(2000);
      system("cls");
    }
    else if (employee_num == 1)
    {
      system("cls");
      printf("Have a nice day!!!!");
      Sleep(2000);
      exit(0);
    }
    else if(employee_num != 0)
    {
      call();
    }
  } while (check(employee_num) != 1 && employee_num != 0 && employee_num != 1);
}

void start()
{
  do
  {
    system("cls");
    printf("Welcome\n\n");
    printf("1.Employee Login\n2.Check Profits\n3.Check Employee Sales\n4.Check Inventory\n5.Exit\n");
    scanf("%d",&s);
    switch(s)
    {
      case 1:
        system("cls");
        employee_Login();
      break;

      case 2:
        system("cls");
        printProfit();
        press_key_to_continue();
      break;

      case 3: 
        system("cls");
        char a[] = "Employee Id";
        char b[] = "Employee Name";
        char c[] = "Number of sales by employee";
        printf("%20s%20s%20s\n", a, b, c);
        showsales(100);
        showsales(101);
        showsales(102);
        press_key_to_continue();
      break;

      case 4:
        system("cls");
        print_inventory();
        press_key_to_continue();
      break;

      case 5:
        system("cls");
        printf("Have a nice day!!!!");
        Sleep(1500);
        exit(0);
      break;

      default: 
        printf("\n\nWrong Input\n");
        Sleep(2000);
        system("cls");
      break;
    }
  }while(s != 5);
}

int main()
{
  checkDate();
  inventory_reading();
  member_reading();
  start();
  return 0;
}