//---------------------------------------------------------------------------

#ifndef thread_socket_image_processingH
#define thread_socket_image_processingH
//---------------------------------------------------------------------------
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Classes.hpp>
//---------------------------------------------------------------------------
class cSOCKET_IMAGE_PROCESSING : public TThread
{            
private:
protected:
    void __fastcall Execute();
public:
    TIdTCPClient *Id_image_processing;
    bool thread_running;
    bool thread_terminated;
    __fastcall cSOCKET_IMAGE_PROCESSING(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
