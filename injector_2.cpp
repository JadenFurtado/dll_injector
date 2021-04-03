//gotta add the file name as part of the command line arguments

//this file injects the DLL into the target process. Displays a message box saying "HACKED" on successful execution

#include <windows.h>
#include<iostream>

int inject_DLL(const char* file_name, int PID);

int main(int argc, char *argv[]){
    int choice,pid;
    int h;    
    do{
        printf("\n1. inject dll");
        printf("\n2. exit");
        printf("\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            printf("\nplease enter the PID");
            scanf("%d",&pid);
            h=inject_DLL(argv[2],pid);
            if(h==1){
                printf("success");
            }
            else{
                printf("failed");
            }
            break;
            case 2:
            printf("\nexiting process");
            break;
        }
    }while(choice!=2);
}

int inject_DLL(const char* file_name, int PID)
{

    HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);               
    char fullDLLPath[_MAX_PATH];                                                     
    GetFullPathName(file_name, _MAX_PATH, fullDLLPath, NULL);

    LPVOID DLLPath_addr = VirtualAllocEx(h_process, NULL, _MAX_PATH,MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);                  
    
    if(WriteProcessMemory(h_process, DLLPath_addr, fullDLLPath,strlen(fullDLLPath), NULL))                                    
    {
        HANDLE rThread=NULL;//just to be shure, we NULL the pointer

        LPVOID LoadLib_addr = (LPVOID *)GetProcAddress(GetModuleHandle(TEXT("main.dll")),"LoadLibraryA");//pointer to dll address
        rThread = CreateRemoteThread(h_process, NULL, 0,(LPTHREAD_START_ROUTINE)LoadLib_addr, DLLPath_addr, 0, NULL);//pointer to thread
        if(rThread!=NULL){
        //    MessageBoxA(0,"hacked","hacked",MB_OK | MB_ICONINFORMATION);
        }
        WaitForSingleObject(rThread, INFINITE);//executes thread
        return 1;
        }
    else{
        return 0;
    }
}