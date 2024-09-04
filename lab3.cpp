#include "lab3.h"
#include <windows.h> 
#include <iostream> 
#include <stdio.h>

DWORD IDThread;
#define THREADCOUNT 12
#define MAX_SEM_COUNT 1
HANDLE Threads[THREADCOUNT];
HANDLE Semaphore_H, Semaphore_G, Semaphore_K, Semaphore_C, Semaphore_M, mutex;

unsigned int lab3_thread_graph_id() 
{
    return 5;
}

const char* lab3_unsynchronized_threads()
{
    return "bceg";
}

const char* lab3_sequential_threads()
{
    return "ghk";
}

DWORD WINAPI ThreadProc_b(LPVOID lpParam);
DWORD WINAPI ThreadProc_c(LPVOID lpParam);
DWORD WINAPI ThreadProc_d(LPVOID lpParam);
DWORD WINAPI ThreadProc_e(LPVOID lpParam);
DWORD WINAPI ThreadProc_f(LPVOID lpParam);
DWORD WINAPI ThreadProc_g(LPVOID lpParam);
DWORD WINAPI ThreadProc_h(LPVOID lpParam);
DWORD WINAPI ThreadProc_k(LPVOID lpParam);
DWORD WINAPI ThreadProc_m(LPVOID lpParam);
DWORD WINAPI ThreadProc_i(LPVOID lpParam);
DWORD WINAPI ThreadProc_n(LPVOID lpParam);


DWORD WINAPI ThreadProc_a(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "a" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }  
    return 0;
}



DWORD WINAPI ThreadProc_c(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    WaitForSingleObject(Threads[0], INFINITE);


    Threads[2] = CreateThread(NULL, 0, ThreadProc_b, NULL, 0, &IDThread);
    if (Threads[2] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    Threads[3] = CreateThread(NULL, 0, ThreadProc_e, NULL, 0, &IDThread);
    if (Threads[3] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    Threads[4] = CreateThread(NULL, 0, ThreadProc_g, NULL, 0, &IDThread);
    if (Threads[4] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    ReleaseSemaphore(Semaphore_G, 1, NULL);
    WaitForSingleObject(Semaphore_C, INFINITE);


    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    WaitForSingleObject(Threads[5], INFINITE);
    WaitForSingleObject(Threads[6], INFINITE);
    ReleaseSemaphore(Semaphore_G, 1, NULL);


    WaitForSingleObject(Threads[4], INFINITE);
    return 0;
}


DWORD WINAPI ThreadProc_b(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "b" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI ThreadProc_e(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "e" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI ThreadProc_g(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    WaitForSingleObject(Threads[2], INFINITE);
    WaitForSingleObject(Threads[3], INFINITE);
    WaitForSingleObject(Semaphore_G, INFINITE);
    ReleaseSemaphore(Semaphore_C, 1, NULL);


    Threads[5] = CreateThread(NULL, 0, ThreadProc_f, NULL, 0, &IDThread);
    if (Threads[5] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    Threads[6] = CreateThread(NULL, 0, ThreadProc_d, NULL, 0, &IDThread);
    if (Threads[6] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }


    Threads[7] = CreateThread(NULL, 0, ThreadProc_h, NULL, 0, &IDThread);
    if (Threads[7] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    Threads[8] = CreateThread(NULL, 0, ThreadProc_k, NULL, 0, &IDThread);
    if (Threads[8] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(Semaphore_G, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(mutex);
        computation();
        ReleaseSemaphore(Semaphore_H, 1, NULL);
    }

    WaitForSingleObject(Threads[8], INFINITE);
    return 0;
}


DWORD WINAPI ThreadProc_d(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "d" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI ThreadProc_f(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "f" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI ThreadProc_h(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(Semaphore_H, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "h" << std::flush;
        ReleaseMutex(mutex);
        computation();
        ReleaseSemaphore(Semaphore_K, 1, NULL);
    }
    return 0;
}


DWORD WINAPI ThreadProc_k(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(Semaphore_K, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "k" << std::flush;
        ReleaseMutex(mutex);
        computation();
        ReleaseSemaphore(Semaphore_G, 1, NULL);
    }


    Threads[9] = CreateThread(NULL, 0, ThreadProc_i, NULL, 0, &IDThread);
    if (Threads[9] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    Threads[10] = CreateThread(NULL, 0, ThreadProc_m, NULL, 0, &IDThread);
    if (Threads[10] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "k" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    WaitForSingleObject(Threads[9], INFINITE);
    ReleaseSemaphore(Semaphore_M, 1, NULL);


    WaitForSingleObject(Threads[10], INFINITE);
    return 0;
}


DWORD WINAPI ThreadProc_i(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "i" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI ThreadProc_m(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "m" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    WaitForSingleObject(Semaphore_M, INFINITE);


    Threads[11] = CreateThread(NULL, 0, ThreadProc_n, NULL, 0, &IDThread);
    if (Threads[11] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "m" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    WaitForSingleObject(Threads[11], INFINITE);
    return 0;
}


DWORD WINAPI ThreadProc_n(LPVOID lpParam)
{
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "n" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}





int lab3_init()
{
    Semaphore_C = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);  
    if (Semaphore_C == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    } 

    Semaphore_H = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    if (Semaphore_H == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    Semaphore_G = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    if (Semaphore_G == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    Semaphore_M = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    if (Semaphore_M == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    Semaphore_K = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    if (Semaphore_K == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    mutex = CreateMutex(NULL, false, NULL);
    if (mutex == NULL)
    {
        printf("Create mutex error: %d\n", GetLastError());
        return 1;
    }

    Threads[0] = CreateThread(NULL, 0, ThreadProc_a, NULL, 0, &IDThread);
    if (Threads[0] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    Threads[1] = CreateThread(NULL, 0, ThreadProc_c, NULL, 0, &IDThread);
    if (Threads[1] == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(Threads[1], INFINITE);
    

    //ÓÒ‚Ó·ÓÊ‰ÂÌËÂ Ô‡ÏˇÚË
    CloseHandle(Threads[0]);
    CloseHandle(Threads[1]);
    CloseHandle(Threads[2]);
    CloseHandle(Threads[3]);
    CloseHandle(Threads[4]);
    CloseHandle(Threads[5]);
    CloseHandle(Threads[6]);
    CloseHandle(Threads[7]);
    CloseHandle(Threads[8]);
    CloseHandle(Threads[9]);
    CloseHandle(Threads[10]);
    CloseHandle(Threads[11]);
    CloseHandle(Semaphore_M);
    CloseHandle(Semaphore_K);
    CloseHandle(Semaphore_H);
    CloseHandle(Semaphore_C);
    CloseHandle(Semaphore_G);
    CloseHandle(mutex);
    
    return 0;
}
