#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include"record.h"
#include<time.h>

void choice();
void viewdata();
int insert(data *);
void search();
void admin();
void delemploy();


int main(){
	char usrname[20], paswrd[20], usrname1[20], paswrd1[20];
	FILE *fp;
	int i = 0;	
	printf("\n\n");  
	system("clear");
	printf("\n\n\n\n");	
	printf("\t\t\t\t\t\tWelcome to Employee Data Management System\n\n");
	for(i = 0; i < 143; i++){
		printf("*");
	}
	printf("\n\n\n");
	printf("\t\t\t\t\tPlease Login to Continue\n\n");
	printf("\t\t\t\t\tUsername : ");
	scanf("%s", usrname);
	printf("\t\t\t\t\tPassword : ");
	scanf("%s", paswrd);
	fp = fopen("paswrd.txt", "r");
	if(fp == NULL)
		printf("Something wents wrong.\n\t... Please try after some time.");
	else{
		fscanf(fp, "%s", usrname1);
		fscanf(fp, "%s", paswrd1);
		if(strcmp(usrname,usrname1) == 0 && strcmp(paswrd,paswrd1) == 0){
			system("clear");
			printf("\n\nLogged In...");
			choice();
		}
		else{
			system("clear");
			printf("Either username or password is wrong.\n");
			fclose(fp);
		}
	}
	return 0;
}


void choice(){
	int ch;
	struct data *node;
	while(1){
		printf("\n\n\t\t\t\t\t\t Please select your choice \n\n");
		printf("\t\t\t\t\t\t 1.Insert data\n\t\t\t\t\t\t 2.View data\n\t\t\t\t\t\t 3.Search data\n\t\t\t\t\t\t 4.Administrator window\n\t\t\t\t\t\t 5.Exit");
		printf("\n\n\t\t\t\t\tYour choice is : ");
		scanf("%d", &ch);
		switch(ch){
			case 1 :
				node = (struct data *)malloc(sizeof(data));
				insert(node);
				break;
				
			case 2 :
				viewdata();
				break;
				
			case 3 :
				search();
				break;
			case 4 :
				admin();
				break;
			case 5 :
				exit(0);
				break;
			default :
				printf("\t\t\t\t\t\tPlease enter valid choice\n");
				break;
		}
	}	
}

int insert(data *tmp){
	FILE *fp;
	fp = fopen("data.txt", "a+");
	system("clear");
	if(fp == NULL){
		printf("error in opening file ");
	}
	else{
		printf("\nEnter the Data: \n\nId\tName\tSalary\tMob.No\n");
		scanf("%d%s%d%d", &tmp->id, tmp->name, &tmp->salary, &tmp->mob);
		fprintf(fp, "%d\t%s\t%d\t%d\n", tmp->id, tmp->name, tmp->salary, tmp->mob);
		printf("... Record Inserted\n");
	}
	fclose(fp);
}

void viewdata(){
	FILE *fp;
	int id;	
	char name[16];
	int salary;
	int mob;
	system("clear");
	fp = fopen("data.txt", "r");
	if(fp == NULL){
		printf("file not exist\n");
	}
	else{
		system("clear");
		printf("Id\tName\tSalary\tMob.No\n");
		while(!feof(fp)){
			fscanf(fp, "%d\t%s\t%d\t%d\n", &id, name, &salary, &mob);
			printf("%d\t%s\t%d\t%d\n", id, name, salary, mob);
		}
	}
	fclose(fp);
}

void search(){

}

// Administration task

void admin(){
	time_t curr;
	FILE *fp, *fp1;
	char t[20];
	int i;
	int flag;
	system("clear");
	//printf("\n\t\t\t\tWarning : You are in administrator zone \n\t\t\t\t Log of your activities might be saved\n\n");
	fp = fopen("log.txt", "a+");
	if(fp == NULL)
		printf("log failed.\n");
	curr = time(&curr);
	strcpy(t, ctime(&curr));
	fprintf(fp, "Root user logged in on : %s", t);
	fclose(fp);
	//system("clear");
	while(1){
		curr = time(&curr);
		strcpy(t, ctime(&curr));
		printf("\n\t\t\t\t\t You are in the Administrative Zone \n");
		printf("\t\t\t\t( Warning : The Log of Your Activities might be saved.) \n\t\t\t\t\t");
		printf("Logged in as ROOT on  %s ", t);
		printf("Please Select Your Option:\n");
		printf("\t\t\t\t\t1. Delete Employee Data\n\t\t\t\t\t2. Employee Daily Record\n\t\t\t\t\t3. Display Log\n\t\t\t\t\t4. Change Password \n\t\t\t\t\t5. Go to Trash\n\t\t\t\t\t6. Switch to Main Menu \n\t\t\t\t\t");
	printf("Your choice is : ");		
	scanf("%d",&i);
		switch(i){
			case 1:  
				delemploy();
				system("clear");
				flag = 1;
				break;
			default:
				printf("\t\t\t\t\tPlease enter valid choice.\n");
				break;
		}
		
	}
}

void delemploy(){
	FILE *fp, *fp1, *log, *trash;
	int id, l, i, k;
	time_t curr;
	char t[20];
	int d1, d2, d3;
	l = i = 0;
	fp = fopen("data.txt", "r");
	trash = fopen("trash.txt", "a+");
	printf("Enter the ID of the record to be deleted : ");
	scanf("%d", &id);
	while(!feof(fp)){
		fscanf(fp, "%d\t%s\t%d\t%d", &d1, t, &d2, &d3);
		l++;
		if(id == d1){
			printf("Record is found and will be deleted shortly ");
			fprintf(trash, "%d\t%s\t%d\t%d", d1, t, d2, d3);
			fclose(trash);
			i = 1;
			break;
		}
	}
	fclose(fp);
	if(i == 0)
		printf("No Data found with the ID %d\n\n", id);
	fp1 = fopen("tmp.txt", "w");
	fp = fopen("data.txt", "r");
	k = 0;
	while(!feof(fp)){
		fscanf(fp, "%d\t%s\t%d\t%d\n",&d1, t, &d2, &d3);
		k++;
		if(k == l){
		}	
		else{
			fprintf(fp1, "%d\t%s\t%d\t%d\n", d1, t, d2, d3);
		}
	}
	fclose(fp);
	fclose(fp1);
	fp1 = fopen("tmp.txt", "r");
	fp = fopen("data.txt", "w");
	while(!feof(fp1)){
		fscanf(fp1, "%d\t%s\t%d\t%d\n",&d1, t, &d2, &d3);
		fprintf(fp, "%d\t%s\t%d\t%d\n", d1, t, d2, d3);
	}
	//fclose(fp);
	//fclose(fp1);
	curr = time(&curr);
	strcpy(t, ctime(&curr));
	log = fopen("log.txt", "a+");
	if(log == NULL)
		printf("Log failed.\n\n");
	//fprintf(log, " %s -> DELETED RECORD OF ID : %d SUCCESSFULLY\n\n", t, id);
	fclose(log);
	fclose(fp);
	fclose(fp1);
	printf("\n\n Do You want to Continue...(Y/N) ");
	scanf("%s", t);
	if(strcmp(t, "Y"))
		exit(0);
	else
		return;
		
}
		


