#include<windows.h>
#include<iostream>
#define BUFSIZE 4096

int SetDebugPrivileges(void) { 
	
    TOKEN_PRIVILEGES priv = {0};
	HANDLE hToken = NULL; 

	if( OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) ) {
		
        	priv.PrivilegeCount           = 1;
			priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			if( LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &priv.Privileges[0].Luid ) ) {
				if(AdjustTokenPrivileges( hToken, FALSE, &priv, 0, NULL, NULL ) == 0) {
					printf("AdjustTokenPrivilege Error! [%u]\n",GetLastError());
				} 
			}	

			CloseHandle( hToken );
		
        } 
		return GetLastError();
}

//the attach_to_process returns handle to target process. I guess it works.
//it attaches to the target process
HANDLE attach_to_process(DWORD procID){
    HANDLE hTargetProcess =NULL;
    hTargetProcess = OpenProcess( PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, procID );
    return hTargetProcess;
 }

int inject_dll(){
    int pid;
    DWORD retval=0;
    TCHAR dllPath[1]=TEXT("main.dll");
    LPCSTR file_name="main.dll";

    BOOL   success; 
    TCHAR  buffer[BUFSIZE]=TEXT(""); 
    TCHAR  buf[BUFSIZE]=TEXT(""); 
    TCHAR** lppPart={NULL};

    printf("\nplease enter the process ID");
    scanf("%d",&pid);
    DWORD procID=(DWORD) pid;
    HANDLE h=attach_to_process(procID);
     retval = GetFullPathName(dllPath[0],
                 BUFSIZE,
                 buffer,
                 lppPart);
    
    if (retval == 0) 
    {
        // Handle an error condition.
        printf ("GetFullPathName failed (%d)\n", GetLastError());
        return 0;
    }
    else 
    {
        _tprintf(TEXT("The full path name is:  %s\n"), buffer);
        if (lppPart != NULL && *lppPart != 0)
        {
            _tprintf(TEXT("The final component in the path name is:  %s\n"), *lppPart);
        }
        return 1;
    }
}

int main(){
    int choice;
    do{
        printf("\n1. attempt injection");
        printf("\n2. exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            if(inject_dll()){
                printf("\nsuccess\n");
            }
            else{
                printf("\nthere was some error");
                printf ("\nGetFullPathName failed (%d)\n", GetLastError());
            }
            break;
            case 2:
            break;
        }
    }while(choice!=2);
    return 0;
}

//gotta allocate space for the dll in the target process assuming that the handle is valid