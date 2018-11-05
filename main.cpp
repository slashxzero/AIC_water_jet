//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <cstdio>
#include <cstring>

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
#define TBitmap Graphics::TBitmap
int cmd_no = 0;

TBitmap *org, *hue, *sat, *val, *com;
TBitmap *bin_hue, *bin_sat, *bin_val;

HANDLE hSM_org, hSM_hue, hSM_sat, hSM_val, hSM_com;
HANDLE hSM_bin_hue, hSM_bin_sat, hSM_bin_val;

extern LPCTSTR pSM_org, pSM_hue, pSM_sat, pSM_val, pSM_com;
extern LPCTSTR pSM_bin_hue, pSM_bin_sat, pSM_bin_val;

unsigned int adjust_HSV = 0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    org = new TBitmap();
    hue = new TBitmap();
    sat = new TBitmap();
    val = new TBitmap();
    bin_hue = new TBitmap();
    bin_sat = new TBitmap();
    bin_val = new TBitmap();
    com = new TBitmap();
    
    org->Width  = 512;
    org->Height = 512;
    hue->Width  = 256;
    hue->Height = 256;
    sat->Width  = 256;
    sat->Height = 256;
    val->Width  = 256;
    val->Height = 256;
    bin_hue->Width  = 256;
    bin_hue->Height = 256;
    bin_sat->Width  = 256;
    bin_sat->Height = 256;
    bin_val->Width  = 256;
    bin_val->Height = 256;
    com->Width  = 512;
    com->Height = 512;

    hue->PixelFormat = pf24bit;
    sat->PixelFormat = pf24bit;
    val->PixelFormat = pf24bit;
    bin_hue->PixelFormat = pf24bit;
    bin_sat->PixelFormat = pf24bit;
    bin_val->PixelFormat = pf24bit;
    com->PixelFormat = pf24bit;
    
    //Image_Org->Canvas->Pen->Color   = clBlack;
    //Image_Org->Canvas->Brush->Color = clBlack;
    //Image_Org->Canvas->Rectangle(0, 0, 511, 511);
    Image_Hue->Canvas->Pen->Color   = clBlack;
    Image_Hue->Canvas->Brush->Color = clBlack;
    Image_Hue->Canvas->Rectangle(0, 0, 255, 255);
    Image_Sat->Canvas->Pen->Color   = clBlack;
    Image_Sat->Canvas->Brush->Color = clBlack;
    Image_Sat->Canvas->Rectangle(0, 0, 255, 255);
    Image_Val->Canvas->Pen->Color   = clBlack;
    Image_Val->Canvas->Brush->Color = clBlack;
    Image_Val->Canvas->Rectangle(0, 0, 255, 255);

    Image_Bin_Hue->Canvas->Pen->Color   = clBlack;
    Image_Bin_Hue->Canvas->Brush->Color = clBlack;
    Image_Bin_Hue->Canvas->Rectangle(0, 0, 255, 255);
    Image_Bin_Sat->Canvas->Pen->Color   = clBlack;
    Image_Bin_Sat->Canvas->Brush->Color = clBlack;
    Image_Bin_Sat->Canvas->Rectangle(0, 0, 255, 255);
    Image_Bin_Val->Canvas->Pen->Color   = clBlack;
    Image_Bin_Val->Canvas->Brush->Color = clBlack;
    Image_Bin_Val->Canvas->Rectangle(0, 0, 255, 255);

    Image_Com->Canvas->Pen->Color   = clBlack;
    Image_Com->Canvas->Brush->Color = clBlack;
    Image_Com->Canvas->Rectangle(0, 0, 511, 511);

    //HANDLE hSM_org, hSM_hue, hSM_sat, hSM_val, hSM_com;
    //LPCTSTR pSM_org, pSM_hue, pSM_sat, pSM_val, pSM_com;

    Open_Share_Memory(hSM_org, pSM_org, 512*512*3, "sm_image_org");
    Open_Share_Memory(hSM_hue, pSM_hue, 512*512*3, "sm_image_hue");
    Open_Share_Memory(hSM_sat, pSM_sat, 512*512*3, "sm_image_sat");
    Open_Share_Memory(hSM_val, pSM_val, 512*512*3, "sm_image_val");
    Open_Share_Memory(hSM_bin_hue, pSM_bin_hue, 512*512*3, "sm_image_bin_hue");
    Open_Share_Memory(hSM_bin_sat, pSM_bin_sat, 512*512*3, "sm_image_bin_sat");
    Open_Share_Memory(hSM_bin_val, pSM_bin_val, 512*512*3, "sm_image_bin_val");
    Open_Share_Memory(hSM_com, pSM_com, 512*512*3, "sm_image_com");

    s_image_processing = new cSOCKET_IMAGE_PROCESSING(false);
}
//---------------------------------------------------------------------------
int TForm1::Create_Share_Memory(HANDLE& hdl, LPCTSTR& pSM, int size, const char *sm_name)
{
    char buffer[256];
    //TCHAR szMsg[]=TEXT("Message from first process.");

    hdl = CreateFileMapping(
                   INVALID_HANDLE_VALUE,    // use paging file
                   NULL,                    // default security
                   PAGE_READWRITE,          // read/write access
                   0,                       // maximum object size (high-order DWORD)
                   size,                // maximum object size (low-order DWORD)
                   sm_name);                 // name of mapping object

    if (hdl == NULL)
    {
        sprintf(buffer, "Could not create file mapping object (%d).", GetLastError());
        ShowMessage(buffer);
        return -1;
    }
    pSM = (LPTSTR) MapViewOfFile(hdl,   // handle to map object
                                FILE_MAP_ALL_ACCESS, // read/write permission
                                0,
                                0,
                                size);

    if (pSM == NULL)
    {
        sprintf(buffer, "Could not map view of file (%d).", GetLastError());
        ShowMessage(buffer);
        CloseHandle(hdl);
        hdl = NULL;
        return -1;
    }
    return 0;
}
//---------------------------------------------------------------------------
int TForm1::Open_Share_Memory(HANDLE& hdl, LPCTSTR& pSM, int buff_size, const char *sm_name)
{
    char buffer[256];
    hdl = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,   // read/write access
                FALSE,                 // do not inherit the name
                sm_name);              // name of mapping object

    pSM = (LPTSTR)MapViewOfFile(
                hdl, // handle to map object
                FILE_MAP_ALL_ACCESS,  // read/write permission
                0,
                0,
                buff_size);

    if (pSM == NULL)
    {
        sprintf(buffer, "Could not map view of file (%d).", (int)GetLastError());
        ShowMessage(buffer);
        CloseHandle(hdl);
        return -1;
    }
    //sprintf(buffer, "ptr:%X", pSM);
    //ShowMessage(buffer);
    return 0;
}
//---------------------------------------------------------------------------
void TForm1::Close_Share_Memory(HANDLE& hdl, LPCTSTR& pSM)
{
    UnmapViewOfFile(pSM);
    CloseHandle(hdl);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    if (s_image_processing->Id_image_processing->Connected())
        s_image_processing->Id_image_processing->Disconnect();
    s_image_processing->thread_running = false;
    while (!s_image_processing->thread_terminated)
    {
        Sleep(10);
    }
    s_image_processing->Terminate();
    s_image_processing = NULL;


    delete org;
    delete hue;
    delete sat;
    delete val;
    delete bin_hue;
    delete bin_sat;
    delete bin_val;
    delete com;
    Close_Share_Memory(hSM_org, pSM_org);
    Close_Share_Memory(hSM_hue, pSM_hue);
    Close_Share_Memory(hSM_sat, pSM_sat);
    Close_Share_Memory(hSM_val, pSM_val);
    Close_Share_Memory(hSM_bin_hue, pSM_bin_hue);
    Close_Share_Memory(hSM_bin_sat, pSM_bin_sat);
    Close_Share_Memory(hSM_bin_val, pSM_bin_val);
    Close_Share_Memory(hSM_com, pSM_com);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
    if (!s_image_processing->Id_image_processing->Connected())
        s_image_processing->Id_image_processing->Connect();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
    if (s_image_processing->Id_image_processing->Connected())
    {
        if (OpenDialog1->Execute())
        {
            AnsiString command = "load_image:" + OpenDialog1->FileName;
            s_image_processing->Id_image_processing->Write(command);
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image_HueMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    byte* k = (byte*)((TImage*)Sender)->Picture->Bitmap->ScanLine[Y];
    
    Label13->Caption = X;
    Label15->Caption = Y;

    Label17->Caption = k[X*4];
    Label19->Caption = k[X*4+1];
    Label21->Caption = k[X*4+2];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
    Image_Hue->Canvas->Pen->Color   = clRed;
    Image_Hue->Canvas->Brush->Color = clBlue;
    Image_Hue->Canvas->Rectangle(64, 64, 192, 192);

    Image_Sat->Canvas->Pen->Color   = clBlue;
    Image_Sat->Canvas->Brush->Color = clGreen;
    Image_Sat->Canvas->Rectangle(64, 64, 192, 192);

    Image_Val->Canvas->Pen->Color   = clGreen;
    Image_Val->Canvas->Brush->Color = clRed;
    Image_Val->Canvas->Rectangle(64, 64, 192, 192);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    if (adjust_HSV == 1)
    {
        char buffer[32];
        sprintf(buffer, "set_hsv:%d %d %d %d %d %d %d %d %d",
                CheckBox1->Checked, TrackBar1->Position, TrackBar2->Position,
                CheckBox2->Checked, TrackBar3->Position, TrackBar4->Position,
                CheckBox3->Checked, TrackBar5->Position, TrackBar6->Position);
        AnsiString command = buffer;
        s_image_processing->Id_image_processing->Write(command);
    }

    if (adjust_HSV > 0)
    {
        adjust_HSV--;
    }

    if (cmd_no == 1)
    {
        cmd_no = 0;
        Image_Hue->Canvas->Draw(0, 0, hue);
        Image_Sat->Canvas->Draw(0, 0, sat);
        Image_Val->Canvas->Draw(0, 0, val);
        Image_Bin_Hue->Canvas->Draw(0, 0, bin_hue);
        Image_Bin_Sat->Canvas->Draw(0, 0, bin_sat);
        Image_Bin_Val->Canvas->Draw(0, 0, bin_val);

        Image_Com->Canvas->Draw(0, 0, com);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
    adjust_HSV = 4;
    Label2->Caption = TrackBar1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
    adjust_HSV = 4;
    Label5->Caption = TrackBar3->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
    adjust_HSV = 4;
    Label3->Caption = TrackBar2->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar5Change(TObject *Sender)
{
    adjust_HSV = 4;
    Label8->Caption = TrackBar5->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar4Change(TObject *Sender)
{
    adjust_HSV = 4;
    Label6->Caption = TrackBar4->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar6Change(TObject *Sender)
{
    adjust_HSV = 4;
    Label9->Caption = TrackBar6->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar7Change(TObject *Sender)
{
    //adjust_HSV = 4;
    Label11->Caption = TrackBar7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
    adjust_HSV = 4;    
}
//---------------------------------------------------------------------------

