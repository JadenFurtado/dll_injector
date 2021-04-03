#include<iostream>
#include<windows.h>

void SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

int main(){
    const LPCSTR sometext="This is it";
    int choice;
    do{
        printf("\njust a simple programme in c++");   
        printf("\n1. display alert box");
        printf("\n2. display process id");
        printf("\n3. exit");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            SomeFunction(sometext);
            break;
            case 2:
            printf("%d",::getpid());
            break;
            case 3:
            printf("exiting the loop");
            break;
        }
    }while(choice!=3);
    return 0;
}