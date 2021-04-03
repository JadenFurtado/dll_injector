# dll_injector
**A dll injector I developed in C++.**
# Introudction:
A basic DLL injector in C++. It currently works in Windows 10 and I guess it should work for other versions of windows too.
I am still working on it and I will be pushing changes as and when I work on it.

# About the files:
There are two files. Main.cpp and injector_2.cpp. I have compiled both these files into exe as you can see. 
Main.cpp is a test programme. Injector injects the DLL. The DLL's file name is taken as a cmd line argument.

## How does it work?
It uses the CreateRemoteThread() function from the Windows API, to create a handle to a process by taking in the process ID. 
[Link to CreateRemoteThreat() of Microsoft Docs ]: https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethread
# Syntax for using the inject exe:

**inject <dll_filename.dll>**
