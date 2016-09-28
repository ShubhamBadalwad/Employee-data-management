#include<stdio.h>
#include<stdlib.h>
#include"record.h"
#include<time.h>

void choice();
void viewdata();
int insert(data *);
void search();
void admin();

void choice() {
	int ch;
	struct data *node;
	while(1) {
		printf("\t\t\t Please select your choice \n\n\n");
		printf("\t\t\t 1.View data\n\t\t\t 2.Insert data\n\t\t\t 3.Search data\n\t\t\t 4.Administrator window\n\t\t\t 5.Exit");
		printf("Your choice is : ");
		scanf("%d", &ch);
		switch(ch) {
			case 1 :
				viewdata();
				break;
			case 2 :
				node = (struct data *)malloc(sizeof(data));
				insert(node);
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
		}
	}	
}

void viewdata() {
	FILE *fp;
	int id;	
	char name[32];
	char post[32];
	float salary;
	double mob;
	fp = fopen("data.txt", "r");
	if(fp == NULL) {
		printf("file not exist\n");
	else {
		printf("/tId/tName/tPost/tSalary/tMob.No\n\");
		while(fp) {
			fscanf(fp, "%d%s%s%f%lf", &id, name, post, &salary, &mob);
			printf("%d%s%s%f%lf", id, name, post, salary, mob);





















}

