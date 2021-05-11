## writeup
这个题目是一个比较有趣的题目，这个题目可以使用各种不同的做法

### 静态审计
题目几乎没有去掉符号，所以可以直接审计。首先可以看到，整个程序读入的字符串长度为28:
```c
  __isoc99_scanf("%28s", v4);
```
然后读入的字符串，会和`maze_enc`一起传入`walk`函数。walk函数的第一个参数会调用dec函数，对`maze_enc`解密。这个函数大致为:
```c
__int64 __fastcall dec(__int64 a1, unsigned int a2)
{
  char v2; // bl
  __int64 result; // rax
  signed int i; // [rsp+1Ch] [rbp-14h]

  printf("maze size:%d\n", a2);
  srand(0);
  for ( i = 0; ; ++i )
  {
    result = (unsigned int)i;
    if ( i >= (int)a2 )
      break;
    v2 = *(_BYTE *)(i + a1);
    *(_BYTE *)(i + a1) = (rand() % 256) ^ v2;
  }
  return result;
```
可以看到，这边用了一个经典的tricky：假rand。这边由于初始化的时间种子为0，所以这边的rand生成的数字序列实际上是不变的。所以可以直接抄一份代码，然后对`maze_enc`中的数据进行解密，于是能得到迷宫:
```
"##################"
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
"##################"
```
解密完之后，会进入一个循环:
```c
for ( i = 0; i <= 28; ++i )
  {
    v2 = *(unsigned __int8 *)(i + a2);
    if ( v2 == 'w' )
    {
      --v4;
    }
    else if ( *(unsigned __int8 *)(i + a2) <= 0x77u )
    {
      if ( v2 == 's' )
      {
        ++v4;
      }
      else if ( *(unsigned __int8 *)(i + a2) <= 0x73u )
      {
        if ( v2 == 'a' )
        {
          --v5;
        }
        else if ( v2 == 'd' )
        {
          ++v5;
        }
      }
    }
    if ( *(_BYTE *)(18 * v4 + v5 + a1) == '#' )
    {
      printf("the steps is %d\n", (unsigned int)i);
      puts("Boom!!!");
      return 0LL;
    }
  }
  if ( *(_BYTE *)(18 * v4 + v5 + a1) == 'x' )
  {
    puts("success");
    result = 1LL;
  }
  else
  {
    puts("failed...");
    result = 0LL;
  }
```
可以看到，这边代码需要在29步之内走到x的点上。从提示上看，应该是从o处出发，而循环中的逻辑，可以很容易想到是`wsad`表示上下左右。于是输入`ddddssddssddssssssssddddddss`即可得到答案

### 动态调试
对于想要跳过解密的部分，可以直接使用gdb进行调试。一个技巧是直接在dec之前下断点，就能直接找到导出的字符串，之后使用ida即可找到flag