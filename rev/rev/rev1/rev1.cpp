// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;
//flag{qwer_asd_12345}
char key[6] = "asuri";

int before_main()
{
	key[0] = 'n';
	key[1] = 'u';
	key[2] = 'a';
	key[3] = 'a';
	return 0;
}

typedef int func();

#pragma data_seg(".CRT$XIU")
//static func * before[] = { before_main };  
func * before = before_main;

#pragma data_seg() 


int main()
{
	char flag[0x20];
	char x[] = "\x8\x19\x0\x6\x15\x4\x16\x4\x1c\x2a\x0\x12\xa\x2a\x50\x53\x5d\x41\x54\x1c";

	cout << "Please input the key:" << endl;
	scanf("%20s", flag);
	for (int i = 0; i < 20; i++) {
		flag[i] = flag[i] ^ key[i % 4];
		if (x[i] != flag[i]) {
			cout << "Error" << endl;
			return 0;
		}
	}

	cout << "You got it!" << endl;
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
