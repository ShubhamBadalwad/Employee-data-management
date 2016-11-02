
/*****************************************************************************
 * Copyright (C) ShubhamBadalwad badalwadsg15.it@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include<stdio.h>
#include<menu.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include"record.h"
#include<time.h>
#include<ncurses.h>

int choice();
void viewdata();
int insert(data *);
void search();
int admin();
int delemploy();
void viewlog();
void viewtrash();
void changepaswrd();


int main(){
	char usrname[20], paswrd[20], usrname1[20], paswrd1[20];
	initscr();
	raw();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	cbreak();
	keypad(stdscr, TRUE);	
	FILE *fp;
	int i = 0;	
	attron(A_BOLD | A_STANDOUT);
	attron(COLOR_PAIR(1));
	mvprintw(3, (COLS - 64) / 2, "Welcome to Employee Data Management System");
	attroff(A_BOLD | A_STANDOUT);	
	move(5, 1);
	mvprintw(6, (COLS - 50) / 2, "Please Login to Continue");
	mvprintw(7, (COLS - 50) / 2, "Username : ");
	getstr(usrname);
	mvprintw(8, (COLS - 50) / 2, "Password : ");
	noecho();
	attroff(COLOR_PAIR(1));
	scanw("%s", paswrd);
	echo();
	fp = fopen("paswrd.txt", "r");
	if(fp == NULL)
		mvprintw(10, (COLS - 50) / 2, "Something went wrong.... Please try after some time.");
	else{
		fscanf(fp, "%s", usrname1);
		fscanf(fp, "%s", paswrd1);
		if(strcmp(usrname,usrname1) == 0 && strcmp(paswrd,paswrd1) == 0){
			clear();
			mvprintw(1, 6, "Logged In...");
			int k = choice();
			if(k == 0)
				return 0;
		}
		else{
			clear();
			mvprintw(6, 20, "Either username or password is wrong.");
			fclose(fp);
		}
	}
	refresh();
	getch();
	endwin();
	return 0;
}

int choice(){
	int ch;	
	char  *arr[5] = {"Insert data", "View data", "Search data", "Administrator Window", "Exit"};
	int i;
	ITEM *my_items[6];
	MENU *my_menu;
	struct data *node;
	clear();
	attron(COLOR_PAIR(1));
	for(i = 0;i < 5;i++)
		my_items[i] = new_item(arr[i], arr[i]);
	my_items[i] = NULL;
	my_menu  = new_menu(my_items);
	menu_opts_off(my_menu, O_SHOWDESC);
	set_menu_win(my_menu, stdscr);
	set_menu_sub(my_menu, derwin(stdscr, 7, 22, 2, 1) );
	post_menu(my_menu);
	refresh();
	while(1){
		int h;
		switch(ch = getch()){
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case 10:
				if(current_item(my_menu) == my_items[0]){
					node = (struct data *)malloc(sizeof(data));
					insert(node);
				}
				else if(current_item(my_menu) == my_items[1])
					viewdata();
				else if(current_item(my_menu) == my_items[2])
					search();
				else if(current_item(my_menu) == my_items[3])
					h = admin();
				else if(current_item(my_menu) == my_items[4]){
					endwin();
					exit(0);
				}
				break;
		}
	}
	attroff(COLOR_PAIR(1));
	free_menu(my_menu);
	
}
/* Function for insertion of record */

int insert(data *tmp){
	FILE *fp;
	fp = fopen("data.txt", "a+");
	clear();
	if(fp == NULL){
		mvprintw(1, 3, "error in opening file ");
	}
	else{
		mvprintw(8, (COLS - 36) / 2, "Enter the Data: Id \tName \tSalary \tMob.No");
		move(9, (COLS - 4) / 2	);
		scanw("%d%s%d%ld", &tmp->id, tmp->name, &tmp->salary, &tmp->mob);
		fprintf(fp, "%d\t%s\t%d\t%ld\n", tmp->id, tmp->name, tmp->salary, tmp->mob);
		mvprintw(14, (COLS + 40) / 2, "... Record Inserted");
	}
	fclose(fp);
}

void viewdata(){
	FILE *fp;
	int id;	
	char name[16];
	int salary;
	long int mob;
	int i = 2;
	clear();
	fp = fopen("data.txt", "r");
	if(fp == NULL){
		printw("file not exist");
	}
	else{
		clear();
		mvprintw(1, (COLS - 70) / 2, "Id\t\tName\tSalary\tMob.No");
		while(!feof(fp)){
			fscanf(fp, "%d\t%s\t%d\t%ld\n", &id, name, &salary, &mob);
			mvprintw(i, (COLS - 70) / 2, "%d\t%s\t%d\t%ld", id, name, salary, mob);
			i++;
		}
	}
	fclose(fp);
}
/* Function for searching operation */

void search(){
	FILE *fp, *fp1;
	int id, id1, salary;
	long int mob;
	char ch, name[20], name1[20]; 
	int flag = 0;
	clear();
	fp = fopen("data.txt", "r");
	fp1 = fopen("data.txt", "r");
	move(2, 48);
	printw("How do you want to search the record ?");
	mvprintw(4, (COLS - 20) / 2, "1. By ID");
	mvprintw(5, (COLS - 20) / 2, "2. By NAME");
	move(6, (COLS - 20) / 2);	
	ch = getch();
	switch(ch){
		case '1':
			mvprintw(7, (COLS - 20) / 2, "Enter the ID : ");
			scanw("%d", &id);
			while(!feof(fp)){
				fscanf(fp, "%d\t%s\t%d\t%ld", &id1, name, &salary, &mob);
				if(id == id1){
					flag = 1;					
					fp1 = fp;
					mvprintw(10, 40, "The Record of the given ID is:\t  %d\t%s\t%d\t%ld", id, name, salary, mob);
				}

			}
			if(flag == 0)
				mvprintw(8, 40, "No Record found with the given Id.");
			fclose(fp);
			break;
		case '2' :
			mvprintw(7, (COLS - 20) / 2, "Enter the Name : ");
			scanw("%s", name);
			while(!feof(fp)){
				fscanf(fp, "%d\t%s\t%d\t%ld", &id, name1, &salary, &mob);
				if(strcmp(name, name1) == 0){
					flag = 1;
					fp1 = fp;
					mvprintw(10, 40, "The Record of the given Name is  %d\t%s\t%d\t%ld ", id, name, salary, mob);
				}
			}
			if(flag == 0)
				mvprintw(8, 40, "No Record found with the given Name.");
			fclose(fp);
			break;
		default :
			mvprintw(8, 40, "Please Enter valid choice");
			break;
	}

}

/* Administrative task */

int admin(){
	time_t curr;
	int j;
	FILE *fp, *fp1;
	char t[20];
	clear();
	char  *arr[7] = {"Delete Employee data", "Employee daily record", "Display Log", "Change password", "Go to trash", "Switch to main menu", "Exit"};
	ITEM *my_items[8];
	MENU *my_menu;
	for(j = 0;j < 7;j++)
		my_items[j] = new_item(arr[j], arr[j]);
	my_items[j] = NULL;
	my_menu  = new_menu(my_items);
	menu_opts_off(my_menu, O_SHOWDESC);
	set_menu_win(my_menu, stdscr);
	set_menu_sub(my_menu, derwin(stdscr, 7, 22, 2, 1) );
	post_menu(my_menu);
	int i;
	int flag;
	//clear();
	fp = fopen("log.txt", "a+");
	if(fp == NULL)
		mvprintw(1, 3, "log failed.");
	curr = time(&curr);
	strcpy(t, ctime(&curr));
	fprintf(fp, "Root user logged in on : %s", t);
	fclose(fp);
	move(1, 14);
	while(1){
		curr = time(&curr);
		strcpy(t, ctime(&curr));
		attroff(COLOR_PAIR(1));
		init_pair(2, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		mvprintw(1, 54, "You are in the Administrative Zone ");
		mvprintw(2, 45, "( Warning : The Log of Your Activities might be saved.)");
		mvprintw(3, 50, "Logged in as ROOT on  %s ", t);
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		move(5, 1);
		int check;
		switch(i = getch()){
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case 10:
				if(current_item(my_menu) == my_items[0]){
					check = delemploy();
					clear();	
				}
				else if(current_item(my_menu) == my_items[1]){
				}	
				else if(current_item(my_menu) == my_items[2]){					
					viewlog();
				}	
				else if(current_item(my_menu) == my_items[3])
					changepaswrd();
				else if(current_item(my_menu) == my_items[4]){
					viewtrash();
				}
				else if(current_item(my_menu) == my_items[5])
					i = choice();
				else if(current_item(my_menu) == my_items[6]){
					endwin();
					exit(0);
				}
				break;
							
		}
			
	}
}
/* Function for deletion of record */

int delemploy(){
	FILE *fp, *fp1, *log, *trash;
	int l, i, k, id;
	time_t curr;
	clear();
	char t[16];
	char ch[4];
	int d1, d2;
	long int d3;
	l = i = 0;
	fp = fopen("data.txt", "r");
	trash = fopen("trash.txt", "a+");
	mvprintw(10, 40, "Enter the ID of the record to be deleted : ");
	scanw("%d", &id);
	while(!feof(fp)){
		fscanf(fp, "%d\t%s\t%d\t%ld", &d1, t, &d2, &d3);
		l++;
		if(id == d1){
			mvprintw(14,50,"Record is found and will be delete shortly...");
				fprintf(trash, "%d\t%s\t%d\t%ld\n", d1, t, d2, d3);
				fclose(trash);
				i = 1;
				break;
		}
	}
	fclose(fp);
	if(i == 0){
		mvprintw(12, 50,"No Data found with the ID %d\n\n", id);
	}
	fp1 = fopen("tmp.txt", "w");
	fp = fopen("data.txt", "r");
	k = 0;
	while(!feof(fp)){
		fscanf(fp, "%d\t%s\t%d\t%ld\n", &d1, t, &d2, &d3);
		k++;
		if(k == l){
		}	
		else{
			fprintf(fp1, "%d\t%s\t%d\t%ld\n", d1, t, d2, d3);
		}
	}
	fclose(fp);
	fclose(fp1);
	fp1 = fopen("tmp.txt", "r");
	fp = fopen("data.txt", "w");
	while(!feof(fp1)){
		fscanf(fp1, "%d\t%s\t%d\t%ld\n", &d1, t, &d2, &d3);
		fprintf(fp, "%d\t%s\t%d\t%ld\n", d1, t, d2, d3);
	}
	curr = time(&curr);
	strcpy(t, ctime(&curr));
	log = fopen("log.txt", "a+");
	if(log == NULL)
		printf("Log failed.\n\n");
	fprintf(log, " %s -> Deleted Record of ID : %d Successfully\n\n", t, id);
	fclose(log);
	fclose(fp);
	fclose(fp1);
	mvprintw(16, 60," Do You want to Continue...(y/n)?");
	scanw("%s", &ch[0]);
	if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
		i = admin();
	else{
		endwin();		
		exit(0);
	}
		
}
/* Function to view log of activities */
		
void viewlog(){
	FILE *fp;
	char ch;
	clear();
	int i = 5;
	move(5, 44);
	fp = fopen("log.txt", "r");
	if(fp == NULL)
		printw("Unable to open log please try after some time.");
	else{
		while((ch = fgetc(fp)) != EOF){
			if(ch == '\n'){
				move(i, 44);
				i++;
				continue;
			}
			printw("%c",ch);
			
		}
		
	}
	fclose(fp);
}	
/* Function to view trash */
	
void viewtrash(){
	FILE *fp;
	char ch;
	int i = 5;
	clear();
	move(10, 50);
	fp = fopen("trash.txt", "r");
	if(fp == NULL)
		printw("Unable to open trash please try after some time.");
	else{
		while((ch = fgetc(fp)) != EOF){
			if(ch == '\n'){
				move(i, 50);
				i++;
				continue;
			}
			printw("%c",ch);
			
		}
		
	}
	fclose(fp);
}
/* Function to change the password */

void changepaswrd(){
	FILE *fp, *fp1;
	char paswrd[16], paswrd1[16], id[16];
	char ti[32];
	time_t ct;
	clear();
	fp = fopen("paswrd.txt", "r");	
	fscanf(fp, "%s %s", id, paswrd);
	fclose(fp);
	mvprintw(10, 50, "Enter the new password : ");
	scanw("%s", paswrd1);
	fp1 = fopen("paswrd.txt", "w");
	fprintf(fp1, "%s %s", id, paswrd1);
	fclose(fp1);
	fp = fopen("log.txt", "a+");
	ct = time(&ct);
	strcpy(ti, ctime(&ct));
	fprintf(fp, "Password changed successfully at time %s \n", ti);
	mvprintw(12, 56, "Password changed successfully. ");
	fclose(fp);
	
}
/* Function for daily records */

















