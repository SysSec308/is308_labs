#include<stdio.h>
#include<string.h>

void rot13(char *s){

    int len;
    len = strlen(s);

    for(int i = 0; i < (len - 1); i++){
        if((s[i] >='a' && s[i] <'n')||(s[i]>='A' && s[i]<'N')){
            s[i]+=13;
        }else if((s[i]>='n' && s[i] <='z')||(s[i]>='N' && s[i] <='Z')){
            s[i]-=13;
        } else if((s[i] >= 48 && s[i] <=52)){
            s[i]+=4;
        } else if((s[i] >= 53 && s[i] <=57)){
            s[i]-=4;
        }    
    }
}

int main()
{
    char flag[] = "the quick brown fox jumps over the lazy dog\n";
    char input[50];
    
    printf("Enter passcode: ");
    fgets(input, 50, stdin);
    rot13(input);
    
    if(!strcmp(input, flag))
        printf("Big Cong!!!\n");
    else
        printf("Try again...\n");
    
    return 0;
}
