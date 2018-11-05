//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <cstdio>
#include <cstring>
#include "main.h"

using namespace std;
#include <windows.h>

#include "thread_socket_image_processing.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define TBitmap Graphics::TBitmap
extern int cmd_no;
extern TBitmap *org, *hue, *sat, *val, *com;
extern TBitmap *bin_hue, *bin_sat, *bin_val;
LPCTSTR pSM_org, pSM_hue, pSM_sat, pSM_val, pSM_com;
LPCTSTR pSM_bin_hue, pSM_bin_sat, pSM_bin_val;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall cSOCKET_IMAGE_PROCESSING::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall cSOCKET_IMAGE_PROCESSING::cSOCKET_IMAGE_PROCESSING(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    Id_image_processing = new TIdTCPClient(0);
    Id_image_processing->Host = "127.0.0.1";
    Id_image_processing->Port = 9487;

    thread_running = true;
    thread_terminated = false;
}
//---------------------------------------------------------------------------
void __fastcall cSOCKET_IMAGE_PROCESSING::Execute()
{

    AnsiString msg;
    int a = 0;
    while (thread_running)
    {
        a++;
        if (Id_image_processing->Connected())
        {
            try
            {

                msg = Id_image_processing->ReadLn();

                if (msg == "done")
                {
                    for (int i = 0; i < hue->Height; i++)
                    {
                        memcpy(hue->ScanLine[i], pSM_hue+i*256*3, 256*3);
                        memcpy(sat->ScanLine[i], pSM_sat+i*256*3, 256*3);
                        memcpy(val->ScanLine[i], pSM_val+i*256*3, 256*3);
                        memcpy(bin_hue->ScanLine[i], pSM_bin_hue+i*256*3, 256*3);
                        memcpy(bin_sat->ScanLine[i], pSM_bin_sat+i*256*3, 256*3);
                        memcpy(bin_val->ScanLine[i], pSM_bin_val+i*256*3, 256*3);
                    }
                    for (int i = 0; i < 512; i++)
                    {
                        memcpy(com->ScanLine[i], pSM_com+i*512*3, 512*3);
                    }
                    cmd_no = 1;
                }
            }
            catch(...)
            {}
        }
        Sleep(10);
    }
    if (Id_image_processing->Connected()) Id_image_processing->Disconnect();
    Sleep(100);
    delete Id_image_processing;
    
    thread_terminated = true;
}
//---------------------------------------------------------------------------
