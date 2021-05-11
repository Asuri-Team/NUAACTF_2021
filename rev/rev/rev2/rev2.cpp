//mips-linux-gnu-g++ check.cpp -o check -static && mips-linux-gnu-strip check
//build/bin/clang++ check.cpp -o demo -mllvm -sub -mllvm -fla && strip demo
//flag{60ca0a178b747d018889b52fbqwehuqi}
#include<iostream>
#include<string>
#include<stdio.h>

using namespace std;

static const string base64_chars = "abcdefghijklmnopqrstuvwxyz!@#$%^&*()ABCDEFGHIJKLMNOPQRSTUVWXYZ+/";

string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];
  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      // char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      // char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      // char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      // char_array_4[3] = char_array_3[2] & 0x3f;
      char_array_4[0] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[1] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[2] = char_array_3[2] & 0x3f;
      char_array_4[3] = (char_array_3[0] & 0xfc) >> 2;
      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }
  if (i) {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';
      char_array_4[0] = char_array_3[2] & 0x3f;
      // char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      // char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      // char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = (char_array_3[0] & 0xfc) >> 2;
      // char_array_4[3] = char_array_3[2] & 0x3f;
    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];
    while((i++ < 3))
      ret += '=';
  }
  return ret;
}

void encrypt(unsigned int * v, unsigned int * k) {  
    unsigned int v0 = v[0], v1 = v[1], sum = 0, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 32; i++) {
        sum += delta;  
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);  
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);  
    }
    v[0] = v0; v[1] = v1;  
}

class CheckM{
  private:
    string str1;
    string str2;
    string temp1;
    string temp2;
  public:
    string check1() {
      this->temp1 = "";
      this->temp2 = "";
      for(int i = 0;i < str1.size() && i < str2.size();i++) {
        temp1 += (str1[i] & 0xf) | (str2[i] & 0xf0);
        temp2 += (str2[i] & 0xf) | (str1[i] & 0xf0);
      }
      return temp1 + temp2;
    }

    CheckM(string str1, string str2) {
      this->str1 = str1;
      this->str2 = str2;
    }
};

int main() {
  string flag = "";
  cout << "input the flag(flag{*}):";
  cin >> flag;
  if (flag.substr(0, 5) != "flag{") {
    printf("Error flag 1\n");
    return 0;
  } else if (flag[37] != '}') {
    printf("Error flag 2\n");
    return 0;
  }  else if (flag.size() != 38) {
    printf("Error flag 3\n");
    return 0;
  }
  string str1 = flag.substr(5, 16);
  string str2 = flag.substr(21, 16);
  CheckM a(str1, str2);
  string check1 = a.check1();
  unsigned int v[2] = {0 , 233}, k[4] = {66, 55, 44, 33};
  for(int i = 0;i < check1.size();i++) {
    v[0] = check1[i];
    encrypt(v, k);
    check1[i] = v[0];
  }
  // cout << base64_encode((const unsigned char*)check1.c_str(), check1.size());
  if(base64_encode((const unsigned char*)check1.c_str(), check1.size()) == "O/PZtMirvlh%^XOwDAcis+!#z*#RESToobroKgKka#g=") {
    printf("Congratulations,you found it!!!\n");
  } else {
    printf("Error flag 4\n");
    return 0;
  }
  return 0;
}
