#define WITH_MUTEX

#include "include\clIMAGE_PROCESSING_THREAD.h"
#include <ws2tcpip.h>

#include <unistd.h>
#include <iostream>
#include <string>
#include <mutex>
#include <cstdio>
#include <assert.h>

#include <cstdlib>
#include <Windows.h>
#include <process.h>

using namespace std;
cv::RNG rng(12345);

#define MAX_THREADS 1
std::mutex mtx;
//======================================================
extern void receive_command(clIMAGE_PROCESSING_THREAD* my_thread, string msg);
//======================================================
int action_thread(clIMAGE_PROCESSING_THREAD* my_thread)
{
    char receive_buffer[1048576]; // 1MB buffer

    while (true)
    {
        if (my_thread->status == THREAD_TERMINATED)
        {
            //closesocket(my_thread->socket);
            break;
        }
        else if (my_thread->status == THREAD_IDLE)
        {
            this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        else if (my_thread->status == THREAD_RUNNING)
        {
            int bytes_read;

            //memset(receive_buffer, 0, sizeof(receive_buffer));
            while ((bytes_read = recv(my_thread->socket, receive_buffer, sizeof(receive_buffer), 0)) > 0)
            {
                if (bytes_read > 0)
                {
                    #ifdef WITH_MUTEX
                    lock_guard<mutex> mLock(mtx);
                    #endif
                    string msg(receive_buffer, bytes_read);
                    receive_command(my_thread, msg);
                }
            }
            #ifdef WITH_MUTEX
            lock_guard<mutex> mLock(mtx);
            #endif
            cout << "id " << my_thread->thread_no << " go idle." << endl;
            closesocket(my_thread->socket);
            //WSACleanup();
            my_thread->socket = INVALID_SOCKET;
            my_thread->status = THREAD_IDLE;
        }
    }
    return 0;
}

//======================================================
int main()
{
    int result;
    clIMAGE_PROCESSING_THREAD threads[MAX_THREADS];

    //Initial thread pool
    for (int i = 0; i < MAX_THREADS; i++)
    {
        threads[i].thread_no = i;
        threads[i].th = thread(action_thread, &threads[i]);
        //threads[i].pSystem = pSystem;
        cout << "Thread " << threads[i].thread_no << " created." << endl;
    }

    //Initial winsock
    WSAData wsaData;
    //WORD version = MAKEWORD(2, 2); // 版本
    result = WSAStartup(MAKEWORD(2,2), &wsaData); // 成功回傳 0
    if (result != 0)
    {
        // 初始化Winsock 失敗
    }

    SOCKET sListen = INVALID_SOCKET;
    sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sListen == INVALID_SOCKET)
    {
        // 建立失敗
    }

    SOCKADDR_IN addr;
    memset (&addr, 0, sizeof (addr)) ; // 清空,將資料設為 0
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 設定 IP,後面解釋 inet_addr()
    addr.sin_addr.s_addr = INADDR_ANY; // 若設定 INADDR_ANY 表示任何 IP
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9487); // 設定 port,後面解釋 htons()

    result = bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    assert(result != SOCKET_ERROR);

    result = listen(sListen, SOMAXCONN);
    assert(result != SOCKET_ERROR);

    //Accept and incoming connection
    cout << "Waiting for incoming connections..." << endl;
    //c = sizeof(struct sockaddr_in);

    SOCKET sConnect;
    struct sockaddr_in clientAddr; // client 端位址資訊
    int clientAddrLen = sizeof(clientAddr);
    //sConnect = accept(sListen, (SOCKADDR*)&clientAddr, &clientAddrLen);

    // sConnect = accept(sListen, NULL, NULL);
    while(sConnect = accept(sListen, (SOCKADDR*)&clientAddr, &clientAddrLen))
    {
        int thread_no;

        cout << "Get connect from " << inet_ntoa(clientAddr.sin_addr) << ":" << clientAddr.sin_port << endl;

        for (thread_no = 0; thread_no < MAX_THREADS; thread_no++)
        {
            if (threads[thread_no].status == THREAD_IDLE)
            {
                threads[thread_no].status = THREAD_RUNNING;
                threads[thread_no].socket = sConnect;
                cout << "Thread " << threads[thread_no].thread_no << " start." << endl;
                break;
            }
        }

        if (thread_no >= MAX_THREADS)
        {
            cout << "All threads are busy..." << endl;
        }
    }
    WSACleanup();
    for (int i = 0; i < MAX_THREADS; i++)
    {
        cout << "thread " << threads[i].thread_no << " terminated." << endl;
        threads[i].th.join();
    }

    return 0;
}
//======================================================

