#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void menu()
{
    puts("1.get a chunk");
    puts("2.free a chunk");
    puts("3.show the chunk");
    puts("4.exit");
    printf("> ");
}
int main()
{
    FILE * fp;
    char *chunk1 = malloc(0x30);
    if(chunk1 == NULL){
        printf("malloc error");
        exit(0);
    }
    fp = fopen("./flag", "r");
    if(fp == NULL){
        printf("open error");
        exit(0);
    }
    fread(chunk1, 1, 0x30, fp);
    free(chunk1);
    chunk1 = NULL;
    puts("Now I freeed the flag. So you have no choice to get it hahahah!");
    while(1){
        int choice;
        menu();
        scanf("%d", &choice);
        if(choice == 1){
            int size;
            printf("please input size: ");
            scanf("%d", &size);
            if(size <0 || size > 0x100) {
                 printf("size worong!\n");
                 continue;
            }
            chunk1 = malloc(size);
            if(chunk1 == NULL) {
                printf("malloc error");
                exit(0);
            }
        }
        if(choice == 2) {
            if(chunk1 == NULL) {
                puts("you have no chunk");
                continue;
            }
            free(chunk1);
            chunk1 = NULL;
        }
        else if(choice == 3) {
            if(chunk1 == NULL) {
                puts("you have no chunk");
                continue;
            }
            fwrite(chunk1, 1, 0x30, stdout); 
        }
        else if(choice == 4) {
            exit(0);
        }
        else{
            puts("Invalid choice");
        }
    }
    return 0;
}