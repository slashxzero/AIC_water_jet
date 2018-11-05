//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
#include "thread_socket_image_processing.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTrackBar *TrackBar1;
        TLabel *Label1;
        TLabel *Label2;
        TTrackBar *TrackBar2;
        TLabel *Label3;
        TCheckBox *CheckBox1;
        TTrackBar *TrackBar3;
        TLabel *Label4;
        TLabel *Label5;
        TTrackBar *TrackBar4;
        TLabel *Label6;
        TCheckBox *CheckBox2;
        TTrackBar *TrackBar5;
        TLabel *Label7;
        TLabel *Label8;
        TTrackBar *TrackBar6;
        TLabel *Label9;
        TCheckBox *CheckBox3;
    TImage *Image_Com;
    TImage *Image_Hue;
        TButton *Button1;
    TImage *Image_Sat;
    TImage *Image_Val;
    TImage *Image_Bin_Val;
    TButton *Button2;
    TButton *Button3;
    TIdTCPClient *IdTCPClient1;
    TButton *Button4;
    TButton *Button5;
    TButton *Button6;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TButton *Button7;
    TTimer *Timer1;
    TImage *Image_Bin_Hue;
    TImage *Image_Bin_Sat;
    TLabel *Label10;
    TTrackBar *TrackBar7;
    TLabel *Label11;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Image_HueMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall TrackBar1Change(TObject *Sender);
    void __fastcall TrackBar3Change(TObject *Sender);
    void __fastcall TrackBar2Change(TObject *Sender);
    void __fastcall TrackBar5Change(TObject *Sender);
    void __fastcall TrackBar4Change(TObject *Sender);
    void __fastcall TrackBar6Change(TObject *Sender);
    void __fastcall TrackBar7Change(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    cSOCKET_IMAGE_PROCESSING *s_image_processing;

    //TBitmap *org, *hue, *sat, *val, *com;
    //HANDLE hSM_org, hSM_hue, hSM_sat, hSM_val, hSM_com;
    //char *pSM_org, *pSM_hue, *pSM_sat, *pSM_val, *pSM_com;

     __fastcall TForm1(TComponent* Owner);
    int Create_Share_Memory(HANDLE& hdl, LPCTSTR& pSM, int buff_size, const char *sm_name);
    int Open_Share_Memory(HANDLE& hdl, LPCTSTR& pSM, int buff_size, const char *sm_name);
    void Close_Share_Memory(HANDLE& hdl, LPCTSTR& pSM);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
