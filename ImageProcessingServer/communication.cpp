#include <cstdio>
#include <iostream>
#include <string>
#include <exception>

using namespace std;
#include "include\clIMAGE_PROCESSING_THREAD.h"
//======================================================
void receive_command(clIMAGE_PROCESSING_THREAD* my_thread, string msg);
extern bool image_raw_data_ready;
//======================================================
void receive_command(clIMAGE_PROCESSING_THREAD* my_thread, string msg)
{
    //char buffer[256];
    string delimiter = ":";  //帶參數的命令用 ':' 把命令和參數隔開
    int delimiter_pos = msg.find(delimiter);  //find out the position of ':'
    string cmd1 = msg.substr(0, delimiter_pos);
    string cmd2;
    if (delimiter_pos != -1) cmd2 = msg.substr(delimiter_pos+1);

    if (cmd1 == string("set_hsv"))
    {
        int HSV[9];
        istringstream iss(cmd2);
        cout << "hsv:" << cmd2 << endl;

        try
        {
            for (int i = 0; i < 9; i++)
            {
                iss >> HSV[i];
            }

            my_thread->inH  = HSV[0];
            my_thread->minH = HSV[1];
            my_thread->maxH = HSV[2];

            my_thread->inS  = HSV[3];
            my_thread->minS = HSV[4];
            my_thread->maxS = HSV[5];

            my_thread->inV  = HSV[6];
            my_thread->minV = HSV[7];
            my_thread->maxV = HSV[8];

            my_thread->Find_Contour();
        }
        catch (...)
        {
        }
    }
    else if (cmd1 == string("load_image"))
    {
        try
        {
            Mat temp = imread(cmd2);
            resize(temp, *my_thread->image, my_thread->image->size());
            cout << "load image:" << cmd2 << endl;
            my_thread->Find_Contour();
        }
        catch (...)
        {
        }
    }
    else
    {
        #ifdef WITH_MUTEX
        lock_guard<mutex> mLock(mtx);
        #endif
        cout << "id " << my_thread->thread_no << ", get unknow message :" << msg << endl;

        int r = send(my_thread->socket, msg.c_str(), msg.length(), 0);
        if (r == SOCKET_ERROR)
        {
            cout << "send failed:" << WSAGetLastError() << endl;
            closesocket(my_thread->socket);
            WSACleanup();
            return;
        }
    }
}
//======================================================
