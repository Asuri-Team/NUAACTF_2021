#include <stdio.h>
#include <string.h>
#include <emscripten/emscripten.h>

int g_magic = 0;
int g_table[30] = {0};
int main(int argc, char ** argv) {
  // just enter this function
  // g_magic = 0x66;
  g_magic = 0x66 - 0x36;
  char input_test[] = {0x8,0x12,0x5,0x4,0x1,0x17,0x6,0x1a,0x39,0x5c,0xe,0x2c,0x19,0x58,0x5b,0x24,0x38,0x46,0xd,0x2a,0x21,0x44,0x2,0x31,0x10,0x18,0x5d,0x0};
  for(int i = 0; i < sizeof(input_test)/sizeof(input_test[0]); i++)
  {
    g_table[i] = input_test[i];
  }
}

// void decode()
// {
//   char input_test[] = {0x8,0x12,0x5,0x4,0x1,0x17,0x6,0x1a,0x39,0x5c,0xe,0x2c,0x19,0x58,0x5b,0x24,0x38,0x46,0xd,0x2a,0x21,0x44,0x2,0x31,0x10,0x18,0x5d,0x0};
//   for(int i = 0; i < sizeof(input_test)/sizeof(char); i++)
//   // for(int i = 0; i < strlen(flag); i++)
//   {
//     // printf("0x%x,", flag[i] ^ g_magic ^ i);
//     printf("%c", input_test[i] ^ g_magic ^ i);
//   }
// }

#ifdef __cplusplus
extern "C" {
#endif

int calculate(int num) {
   num += 0x36;
   return num;
}

int EMSCRIPTEN_KEEPALIVE entry(char *input) {
  int magic = calculate(g_magic);
  printf("test:%s\n",input);
  for(int i = 0; i < strlen(input); i++)
  {
    // nuaactf{W3bAs33MN1y_S7r@ng!}
    // printf("0x%x,", flag[i] ^ g_magic ^ i);
    // printf("%c,", input_test[i] ^ g_magic ^ i);
    if(g_table[i] != (input[i] ^ magic ^ i))
    {
      puts("failed!");
      return 0;
    }
  }
  puts("success!");
  return 1;
}



#ifdef __cplusplus
}
#endif