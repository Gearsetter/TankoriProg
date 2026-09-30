#include <stdio.h>

int main() {
    printf("Hello World!\n");
    char terminate;
    while(1){
        if(scanf("%c", &terminate)){
            break;
        }
    }
    return 0;
}