#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
struct INVENTORY
{
  char item_name[50];
  int item_no;
  int item_quantity;
  float item_MRP;
  float item_price;
  struct INVENTORY *next;
}item[53];
//if 5 apple item_number [0]=appple code
//              item quantity of [0]=5
//    item [item_number[0]-101].item_mrp
struct MEMBER
{
  char name[50];
  int id;
  int number_of_donation;
}mem[100];
int mem_count;
//hellllo
struct INVOICE
{
  float subtotal;
  float gst;
  float discount;
  float total;
  int item_number[53];
  int item_quantity[53];
  char cust_name[];
}bill;

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
  FILE *emp,*temp;
  int i=0,ti;
  emp=fopen("employees.csv","r");
  temp=fopen("temp.csv","w");
  char line[100],newline[100],*t;
  while(fgets(line,100,emp))
  {
    t=strtok(line,",");
    if((int)t!=id)
      fprintf(temp,"%s\n",line);
    else
    {
      strcat(newline,t);
      t=strtok(NULL,",");
      ti=1+atoi(t);
      sprintf(t,"%d",ti);
      strcat(newline,t);
      strcpy(newline,strtok(NULL,"\n"));
      strcpy(newline,"\n");
      fprintf(emp,newline);
    }
    i++;
  }
}
void update_inventory()
{
  int i;
  for(i=0;i<54;i++)
  {
    item[i].item_quantity = item[i].item_quantity - bill.item_quantity[i];
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
void print()
{
  printf("Test");
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


  return 0;
}
