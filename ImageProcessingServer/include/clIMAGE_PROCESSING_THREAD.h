#ifndef CLIMAGE_PROCESSING_THREAD_H
#define CLIMAGE_PROCESSING_THREAD_H

//======================================================
#include <winsock2.h>
#include <thread>
#include <iostream>
#include <Windows.h>
//======================================================
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;
//======================================================
#define THREAD_TERMINATED  -1
#define THREAD_IDLE         0
#define THREAD_RUNNING      1
//============================================================
class clIMAGE_PROCESSING_THREAD
{
    public:
        int thread_no;
        SOCKET socket;
        int status;  //-1:terminate, 0:sleep, 1:running,
        thread th;
        Mat *image;

        const int size_org = 512*512*3;
        const int size_hue = 512*512*3;
        const int size_sat = 512*512*3;
        const int size_val = 512*512*3;
        const int size_bin_hue = 512*512*3;
        const int size_bin_sat = 512*512*3;
        const int size_bin_val = 512*512*3;
        const int size_com = 512*512*3;
        HANDLE hSM_org, hSM_hue, hSM_sat, hSM_val, hSM_com;
        HANDLE hSM_bin_hue, hSM_bin_sat, hSM_bin_val;
        LPCTSTR pSM_org, pSM_hue, pSM_sat, pSM_val, pSM_com;
        LPCTSTR pSM_bin_hue, pSM_bin_sat, pSM_bin_val;

        bool inH, inS, inV;
        unsigned short minH, maxH, minS, maxS, minV, maxV;
        double target_area;

        clIMAGE_PROCESSING_THREAD();
        ~clIMAGE_PROCESSING_THREAD();

        int Create_Share_Memory(HANDLE& hdl, LPCTSTR& pSM, int buff_size, const char *SM_name);
        void Close_Share_Memory(HANDLE& hdl, LPCTSTR& pSM);
        //void Copy_Image_To_Share_Memory(Mat src, LPCTSTR pSM);

        int Find_Contour(void);
        //char Find_Target(int *X, int*Y, double *angle, double *width, double *height, unsigned char threshold);

    protected:

    private:
};
//============================================================
#endif // CLIMAGE_PROCESSING_THREAD_H
