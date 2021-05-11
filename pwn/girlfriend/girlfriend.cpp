#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;

int condition = 0;

void init()
{
    setvbuf(stdin, 0LL, 2, 0LL);
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stderr, 0LL, 2, 0LL);
}
int read_int() {
	char buf[10];
	read(0, buf, 9);
	buf[9] = 0;
	return atoi(buf);
}

class Girlfriend
{
	public:
		int age;
		double height;
		string name;
		string hobby;
		string gift;
		void show_information();
		void set_information(int input_age,double input_height, string input_name);
		void set_hobby();
		void give_gift();
};
void Girlfriend::set_information(int input_age,double input_height, string input_name)
{
	age = input_age;
	height = input_height;
	name = input_name;
}
void Girlfriend::show_information()
{
	cout<<"|--------the information of your girlfriend------|"<<endl;
	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "height: " << height << endl;
}
void Girlfriend::set_hobby()
{
	cout << "What's her hobby?" << endl;
	cin >> hobby;
	condition++;
}
void Girlfriend::give_gift()
{
	cout << "What gift do you want to buy?" << endl;
	cin >> gift;
	condition++;
}
void heart()
{
	cout << "Unbelivable! You get it!!!" << endl;
	system("/bin/sh");
}
void confess()
{
	char letter[40];
	if(condition < 2) {
		cout << "you can't do that" << endl;
		return;
	}
	cout<<"What do you want to say to your girl?" << endl;
	cin>>letter;
	cout <<"you while never get her heart" <<endl;
}
void doWhat()
{
	cout <<"-----------------------------------" <<endl;
	cout<<"1.show the girl's information" << endl;
	cout<<"2.knows her hobby" <<endl;
	cout<<"3.give her gift" <<endl;
	cout<<"4.confess" << endl;
	cout<<"> " << endl;
}
int main()
{
	Girlfriend girlfriend;
	int input_age, chioce;
	double input_height;
	string input_name;

	cout << "Please input a girl's name: ";
	cin >> input_name;
	cout << "Please input the girl's age: ";
	cin >> input_age;
	cout << "Please input the girl's height: ";
	cin >> input_height;
	girlfriend.set_information(input_age, input_height, input_name);
	while(1){
		doWhat();
		chioce = read_int();
		switch(chioce) {
			case 1:
				girlfriend.show_information();
				break;
			case 2:
				girlfriend.set_hobby();
				break;
			case 3:
				girlfriend.give_gift();
				break;
			case 4:
				confess();
				break;
		}
	}
	return 0;
}