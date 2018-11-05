#include <cmath>
#include "clIMAGE_PROCESSING_THREAD.h"

//static HANDLE hSM_org, hSM_hue, hSM_sat, hSM_val, hSM_com;
//static LPTSTR pSM_org, pSM_hue, pSM_sat, pSM_val, pSM_com;
//============================================================
clIMAGE_PROCESSING_THREAD::clIMAGE_PROCESSING_THREAD()
{
    socket = INVALID_SOCKET;
    status = THREAD_IDLE;

    Size image_size(512, 512);
    image = new Mat(image_size, CV_8UC3);

    inH = true, inS = true, inV = true;
    minH = 0, maxH = 255, minS = 0, maxS = 255, minV = 0, maxV = 50;
    target_area   = 0;

    Create_Share_Memory(hSM_org, pSM_org, size_org, "sm_image_org");
    Create_Share_Memory(hSM_hue, pSM_hue, size_hue, "sm_image_hue");
    Create_Share_Memory(hSM_sat, pSM_sat, size_sat, "sm_image_sat");
    Create_Share_Memory(hSM_val, pSM_val, size_val, "sm_image_val");
    Create_Share_Memory(hSM_com, pSM_com, size_com, "sm_image_com");

    Create_Share_Memory(hSM_bin_hue, pSM_bin_hue, size_bin_hue, "sm_image_bin_hue");
    Create_Share_Memory(hSM_bin_sat, pSM_bin_sat, size_bin_sat, "sm_image_bin_sat");
    Create_Share_Memory(hSM_bin_val, pSM_bin_val, size_bin_val, "sm_image_bin_val");

    /*
    char buffer[256];
    sprintf(buffer, "pSM_org:%X size:%d", pSM_org, size_org);
    cout << buffer << endl;
    sprintf(buffer, "pSM_hue:%X size:%d", pSM_hue, size_hue);
    cout << buffer << endl;
    sprintf(buffer, "pSM_sat:%X size:%d", pSM_sat, size_sat);
    cout << buffer << endl;
    sprintf(buffer, "pSM_val:%X size:%d", pSM_val, size_val);
    cout << buffer << endl;
    sprintf(buffer, "pSM_com:%X size:%d", pSM_com, size_com);
    cout << buffer << endl;
    */
}
//============================================================
clIMAGE_PROCESSING_THREAD::~clIMAGE_PROCESSING_THREAD()
{
    Close_Share_Memory(hSM_org, pSM_org);
    Close_Share_Memory(hSM_hue, pSM_hue);
    Close_Share_Memory(hSM_sat, pSM_sat);
    Close_Share_Memory(hSM_val, pSM_val);
    Close_Share_Memory(hSM_com, pSM_com);

    Close_Share_Memory(hSM_bin_hue, pSM_bin_hue);
    Close_Share_Memory(hSM_bin_sat, pSM_bin_sat);
    Close_Share_Memory(hSM_bin_val, pSM_bin_val);

    socket = INVALID_SOCKET;
    status = THREAD_IDLE;
    delete image;
    image = NULL;
}
//============================================================
int clIMAGE_PROCESSING_THREAD::Create_Share_Memory(HANDLE& hdl, LPCTSTR& pSM, int buff_size, const char *SM_name)
{
    char buffer[256];

    hdl = CreateFileMapping(
              INVALID_HANDLE_VALUE,    // use paging file
              NULL,                    // default security
              PAGE_READWRITE,          // read/write access
              0,                       // maximum object size (high-order DWORD)
              buff_size,                // maximum object size (low-order DWORD)
              SM_name);                 // name of mapping object

    if (hdl == NULL)
    {
        sprintf(buffer, "Could not create file mapping object (%d).", (int)GetLastError());
        cout << buffer << endl;
        return -1;
    }
    pSM = (LPTSTR)MapViewOfFile(hdl,   // handle to map object
                                FILE_MAP_ALL_ACCESS, // read/write permission
                                0,
                                0,
                                buff_size);

    if (pSM == NULL)
    {
        sprintf(buffer, "Could not map view of file (%d).\n", (int)GetLastError());
        CloseHandle(hdl);
        cout << buffer << endl;
        hdl = NULL;
        return -1;
    }
    else
    {
        sprintf(buffer, "pSM:%X", pSM);
        cout << buffer << endl;
    }
    //CopyMemory((PVOID)pSM, szMsg, strlen(szMsg) * sizeof(TCHAR));
    return 0;
}
//---------------------------------------------------------------------------
void clIMAGE_PROCESSING_THREAD::Close_Share_Memory(HANDLE& hdl, LPCTSTR& pSM)
{
    UnmapViewOfFile(pSM);
    pSM = NULL;
    CloseHandle(hdl);
    hdl = NULL;
}
//============================================================
int clIMAGE_PROCESSING_THREAD::Find_Contour(void)
{
    char buffer[256];
    Mat org = image->clone();

    cvtColor(org, org, COLOR_BGR2HSV, 3);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    ///Set HSV range
    Mat chan[3];
    split(org, chan);

    Mat bin_H, bin_S, bin_V;

    if (inH)
    {
        bin_H = (this->minH <= chan[0]) & (chan[0] <= this->maxH);  // note: single '|'
    }
    else
    {
        bin_H = (chan[0] < this->minH) | (chan[0] > this->maxH);  // note: single '|'
    }

    if (inS)
    {
        bin_S = (this->minS <= chan[1]) & (chan[1] <= this->maxS);  // note: single '|'
    }
    else
    {
        bin_S = (chan[1] < this->minS) | (chan[1] > this->maxS);  // note: single '|'
    }

    if (inV)
    {
        bin_V = (this->minV <= chan[2]) & (chan[2] <= this->maxV);  // note: single '|'
    }
    else
    {
        bin_V = (chan[2] < this->minV) | (chan[2] > this->maxV);  // note: single '|'
    }

    Mat combine = bin_H | bin_S | bin_V;  // where all conditions were met

    imwrite("C:\\temp\\2.1.H.jpg", bin_H);
    imwrite("C:\\temp\\2.2.S.jpg", bin_S);
    imwrite("C:\\temp\\2.3.V.jpg", bin_V);
    imwrite("C:\\temp\\3.0.combine.jpg", combine);

    resize(chan[0], chan[0], Size(256, 256));
    resize(chan[1], chan[1], Size(256, 256));
    resize(chan[2], chan[2], Size(256, 256));
    cvtColor(chan[0], chan[0], COLOR_GRAY2BGR);
    cvtColor(chan[1], chan[1], COLOR_GRAY2BGR);
    cvtColor(chan[2], chan[2], COLOR_GRAY2BGR);

    resize(bin_H, bin_H, Size(256, 256));
    resize(bin_S, bin_S, Size(256, 256));
    resize(bin_V, bin_V, Size(256, 256));
    cvtColor(bin_H, bin_H, COLOR_GRAY2BGR);
    cvtColor(bin_S, bin_S, COLOR_GRAY2BGR);
    cvtColor(bin_V, bin_V, COLOR_GRAY2BGR);

    Mat temp;
    cvtColor(combine, temp, COLOR_GRAY2BGR);

    cout << "Start copy memory." << endl;
    CopyMemory((PVOID)pSM_hue, (PVOID)chan[0].data, chan[0].rows*chan[0].cols*chan[0].channels());
    CopyMemory((PVOID)pSM_sat, (PVOID)chan[1].data, chan[1].rows*chan[1].cols*chan[1].channels());
    CopyMemory((PVOID)pSM_val, (PVOID)chan[2].data, chan[2].rows*chan[2].cols*chan[2].channels());

    CopyMemory((PVOID)pSM_bin_hue, (PVOID)bin_H.data, bin_H.rows*bin_H.cols*bin_H.channels());
    CopyMemory((PVOID)pSM_bin_sat, (PVOID)bin_S.data, bin_S.rows*bin_S.cols*bin_S.channels());
    CopyMemory((PVOID)pSM_bin_val, (PVOID)bin_V.data, bin_V.rows*bin_V.cols*bin_V.channels());

    CopyMemory((PVOID)pSM_com, (PVOID)temp.data, temp.rows*temp.cols*temp.channels());
    cout << "Copy memory finished." << endl;

    ///erode
    Mat erodeStruct = getStructuringElement(MORPH_CROSS, Size(3,3));
    morphologyEx(combine, combine, MORPH_CLOSE, erodeStruct, Point(-1, -1), 3);

    /// Find contours
    findContours(combine, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    int num_of_contours = contours.size();

    for( int i = 0; i < num_of_contours; i++ )
    {

    }

    sprintf(buffer, "done\n");
    send(socket, buffer, strlen(buffer), 0);
    return num_of_contours;
}
//============================================================
