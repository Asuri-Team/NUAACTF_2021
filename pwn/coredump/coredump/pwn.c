// gcc -o pwn pwn.c -no-pie && strip -s pwn
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#define MAX 7

typedef struct {
	char * name;
	int num;
}Item;

Item items[MAX];

void init() {
	setvbuf(stdout, 0, 2, 0);
	setvbuf(stdin, 0, 1, 0);
	setvbuf(stderr, 0, 1, 0);
	alarm(0);
}

void menu() {
	printf("Please confirm your order.\n");
	printf("1. Add item.\n");
	printf("2. Delete item.\n");
	printf("3. Display the order.\n");
	printf("4. Edit item.\n");
	printf("5. Exit.\n");

	printf("Your choice:\n");
}

int read_int() {
	char buf[10];
	read(0, buf, 9);
	buf[9] = 0;
	return atoi(buf);
}

void add_items() {
	int i = 0;
	while(items[i].num) {
		i++;
	}
	if(i >= MAX) {
		printf("Too many items!\n");
		return;
	}
	printf("What is the name of the added item?\n");
	items[i].name = malloc(0x20);
	read(0, items[i].name, 0x20);
	printf("What is the quantity of items?\n");
	items[i].num = read_int();
	printf("Successful increase.\n");
}

void delete_items() {
	int index;
	printf("What is the index of the deleted item?\n");
	index = read_int();
	if(index >= 0 && index < MAX) {
		free(items[index].name);
	}
	else {
		printf("Delete failed.\n");
		return;
	}
	if(items[index].num) {
		items[index].name = 0;
	}
	printf("Deleted successfully.\n");
}

void show_order() {
	int i = 0;
	while(i < MAX) {
		if(items[i].name)
			printf("name:%s, num:%d.\n", items[i].name, items[i].num);
		i++;
	}
}
void edit_item()
{
	int index;

	printf("What is the index of the edit item?\n");
	index = read_int();
	if(index >= 0 && index < MAX)
	{
		printf("What is the name of the edit item?\n");
		read(0, items[index].name, 0x20);
	}
	else {
		printf("Edit failed.\n");
		return;
	}
	printf("edit successfully.\n");
	return;

}

int main(int argc, char const *argv[],char const *env[])
{
	init();
	int a;
	printf("Welcome to my store!\n");
	while(1) {
		menu();
		a = read_int();
		switch(a) {
			case 1:
				add_items();
				break;
			case 2:
				delete_items();
				break;
			case 3:
				show_order();
				break;
			case 4:
				edit_item();
				break;
			case 5:
				exit(0);
			default:
				printf("Wrong choice!!!\n");
		}
	}
	return 0;
}
