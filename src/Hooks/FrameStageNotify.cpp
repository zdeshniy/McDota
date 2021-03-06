#include "Hooks.h"

#include "../Hacks/Zoom.h"
#include "../Settings.h"
#include "../Hooks/HardHooks.h"

typedef void (* FrameStageNotifyFn)( CSource2Client*, ClientFrameStage_t );

//looks like they added stages 7 and 9
/*
static const char* Stage2String( ClientFrameStage_t stage ){
    switch( stage ){
        CASE_STRING( FRAME_UNDEFINED );
        CASE_STRING( FRAME_START );
        CASE_STRING( FRAME_NET_UPDATE_START );
        CASE_STRING( FRAME_NET_UPDATE_POSTDATAUPDATE_START );
        CASE_STRING( FRAME_NET_UPDATE_POSTDATAUPDATE_END );
        CASE_STRING( FRAME_NET_UPDATE_END );
        CASE_STRING( FRAME_RENDER_START );
        CASE_STRING( FRAME_RENDER_END );
        default:
            return std::to_string((int)stage).c_str();
    }
}*/
void Hooks::FrameStageNotify( CSource2Client *thisptr, ClientFrameStage_t stage ) {
    //MC_PRINTF("FSN: %s\n", Stage2String(stage));
    Zoom::FrameStageNotify( thisptr, stage );

    switch( stage ){
        case ClientFrameStage_t::FRAME_START:
            if( mc_log_GC_recv->GetBool() ){
                if( !HardHooks::DispatchPacket.IsInstalled() ){
                    if( !HardHooks::DispatchPacket.Install( (void*)DispatchPacketFnAddr, (void*)HardHooks::MyDispatchPacket )){
                        Util::Log("Failed to Install HardHook - DispatchPacket\nSetting Convar to false\n");
                        mc_log_GC_recv->SetValue(0);
                    } else {
                        Util::Log("Installed HardHook - DispatchPacket\n");
                    }
                }
            } else {
                if( HardHooks::DispatchPacket.IsInstalled() ){
                    if( !HardHooks::DispatchPacket.Remove() ){
                        Util::Log("ERROR Removing HardHook - DispatchPacket\n");
                    } else {
                        Util::Log("Removed HardHook - DispatchPacket\n");
                    }
                }
            }

            if( mc_log_GC_send->GetBool() ){
                if( !HardHooks::BAsyncSendProto.IsInstalled() ){
                    if( !HardHooks::BAsyncSendProto.Install( (void*)BAsyncSendProtoFnAddr, (void*)HardHooks::MyBAsyncSendProto ) ){
                        Util::Log("Failed to Install HardHook - BAsyncSendProto\nSetting Convar  to false\n");
                        mc_log_GC_send->SetValue(0);
                    } else {
                        Util::Log("Installed HardHook - BAsyncSendProto\n");
                    }
                }
            } else {
                if( HardHooks::BAsyncSendProto.IsInstalled() ){
                    if( !HardHooks::BAsyncSendProto.Remove() ){
                        Util::Log("ERROR Removing HardHook - BAsyncSendProto\n");
                    } else {
                        Util::Log("Removed HardHook - BAsyncSendProto\n");
                    }
                }
            }

            break;
        case ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END:
            break;
        default:
            break;
    }
    return clientVMT->GetOriginalMethod<FrameStageNotifyFn>(29)( thisptr, stage );
}