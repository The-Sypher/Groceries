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

void after_goodjob()
{
  remove("employees.csv");
  rename("temp.csv","employees.csv");
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
  /*FILE *emp,*temp;
  int ti;
  emp=fopen("employees.csv","r");
  temp=fopen("temp.csv","w");
  char line[100],newline[100]="",*t;
  while(fgets(line,100,emp))
  {
    t=strtok(line,",");
    ti=atoi(t);                         Do not delete this or uncomment this
    if(ti!=id)                          This is intentionally left this way
    {                                   By parnav
      strcat(newline,t);
      strcat(newline,",");
      t=strtok(NULL,",");
      ti=1+atoi(t);t=0;
      sprintf(t,"%d",ti);
      strcat(newline,t);
      strcat(newline,",");
      strcat(newline,strtok(NULL,"\n"));
      strcat(newline,"\n");
      fprintf(temp,newline);
    }
    else
    {
      fprintf(temp,"%shmm\n",line);
    }
  }*/
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
    item[bill.item_number[i] - 101].item_quantity = item[bill.item_number[i] - 101].item_quantity - bill.item_quantity[i];
  }
  inventory_updation();
}

void print()
{
  printf("Test");
}
/*Samarth when building the main after calling the printing of bill call goodjob(id) make an id variable in main and input it inthe start of the program*/
int main()
{
  return 0;
}
