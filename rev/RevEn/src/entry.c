#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PAGE_SIZE 4096

typedef unsigned char uchar;
typedef uchar(*operand)(uchar, uchar);
typedef void(*decrypt)(uchar*);


uchar mazes[] = "##################"
"#o              ##"
"# ### ### ##### ##"
"#   #   #     # ##"
"# ##### ### ### ##"
"#     #   #   # ##"
"# # ##### # ### ##"
"# #     # #   # ##"
"# # ### # # ### ##"
"# #   # # #   # ##"
"# # ### # # # # ##"
"# #   # # # # # ##"
"# # # ### ########"
"# # #   #       ##"
"# # ##### ##### ##"
"# #     #     #x##"
"##################";
// uchar steps[] = "ddddssddssddssssssssddddddss";
// nuaactf{ddddssddssddssssssssddddddss}

uchar maze_enc[] = {68,229,74,80,114,220,105,207,10,238,153,136,209,216,192,101,95,225,
119,151,59,200,199,173,86,122,14,67,19,191,233,186,70,18,46,148,
18,120,128,121,6,125,38,52,123,201,125,247,136,145,238,230,184,151,
119,49,46,162,87,97,1,29,255,167,80,201,30,129,98,193,223,68,
29,33,93,180,201,255,72,182,172,27,127,10,207,147,24,219,17,140,
31,116,204,56,251,124,33,58,222,99,216,218,138,26,216,9,242,197,
38,28,95,180,86,251,157,66,170,217,127,155,139,186,44,181,146,200,
210,147,38,207,215,32,201,129,25,197,233,43,235,240,107,103,71,158,
60,3,61,136,63,88,71,229,55,83,121,229,125,104,90,67,24,83,
71,4,50,190,41,252,137,244,143,210,56,48,143,27,16,237,192,115,
107,103,54,124,152,76,1,57,153,187,94,213,40,193,57,60,92,0,
219,9,219,132,59,51,150,234,109,200,187,18,27,192,90,109,30,23,
159,127,109,87,217,235,79,38,143,166,2,8,137,57,118,129,157,83,
150,83,24,36,127,243,22,180,144,143,194,208,196,190,111,18,54,106,
222,162,109,137,43,83,247,145,169,9,119,107,185,41,159,245,45,59,
139,100,143,123,211,174,108,247,14,187,41,98,197,38,231,75,140,238,
128,167,92,14,142,247,85,100,253,17,63,207,105,231,19,213,3,0,
133,0,0,0,0,0,0,0,0,0,0,0,0,0,100,100,100,100};


void dec(uchar* maze, int size){
	printf("maze size:%d\n",size);
    srand(0);
    for(int i = 0; i < size;i++)
    {
        maze[i] = maze[i] ^ (rand()%0x100);
        // printf("%d,",maze[i]);
    }
    // for(int i = 0 ; i < 18; i++)
	// {
	// 	for(int j = 0; j <18; j++)
	// 	{
	// 		printf("%c",maze[i*18 + j]);
	// 	}
	// 	puts("");
	// }
}

void draw_map(uchar* maze, int x, int y)
{
	maze[x+18*y] = 'o';
	for(int i = 0 ; i < 18; i++)
	{
		for(int j = 0; j <18; j++)
		{
			printf("%c",maze[i*18 + j]);
		}
		puts("");
	}
}

int walk(uchar tmp_mazes[], uchar input[])
{
	int y = 1;
	int x = 1;
    dec(tmp_mazes, 307);
	for (int i = 0; i < 29; i++)
	{
		// input[i] ^= hint[i];
		switch (input[i])
		{
		case'a':
		{
			x -= 1;
			break;
		}
		case'd':
		{
			x += 1;
			break;
		}
		case'w':
		{
			y -= 1;
			break;
		}
		case's':
		{
			y += 1;
			break;
		}
		default:
			break;
		}
		if (tmp_mazes[x + 18*y] == '#')
		{
            // printf("the steps is %d\n",i);
			puts("Boom!!!");
			return 0;
		}
		// printf("%c",input[i]);
		// draw_map(tmp_mazes,x,y);
	}
    if(tmp_mazes[x+ 18*y] == 'x')
    {
        puts("success");
		printf("you get flag nuaactf{%s}\n",input);
        return 1;
    }
    else
    {
        puts("failed...");
        return 0;
    }
}
//flag{welcome_2_A2m_WoRLD!}
int main()
{
	// dec(mazes,sizeof(mazes));
	puts("Welcome the nuaactf ~");
	puts("Let's try to go out from \"o\".Please input steps:");
	char steps[29] = {0};
	scanf("%28s", steps);
    walk(maze_enc, steps);
	// unsigned char input[14] = { 0 };
	// puts("Check next section");
	// int line = 6;
	// decrypt dec_table[] = { dec1, dec2 };
	// for (int i = 0; i < 6; i++)
	// {
	// 	dec_table[i%2](maze[i]);
	// }
	// // try to walk out
	// if (walk(maze, &input[0]))
	// {
	// 	puts("you find the whole flag!");
	// }
	// else
	// {
	// 	puts("what a pity!");
	// }
	return 0;
}
