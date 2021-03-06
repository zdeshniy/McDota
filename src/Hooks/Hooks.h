#pragma once
#include "../SDK/SDK.h"
#include "../Interfaces.h" // all hooks can use interfaces

#include <mutex>

namespace Hooks
{
    // CDotaCamera
    float GetFogEnd( CDotaCamera *thisptr, float unk );
    float GetFoWAmount( CDotaCamera *thisptr );
    float GetZFar( CDotaCamera *thisptr, float unk );
    // client
    void FrameStageNotify( CSource2Client* thisptr, ClientFrameStage_t stage );
    // clientMode
    bool CreateMove( IClientMode* thisptr, CUserCmd *cmd, QAngle &angle, Vector &pos );
    void LevelInit( IClientMode* thisptr, const char *newmap );
    // cnetworksystem
    INetChannel* CreateNetChannel( CNetworkSystem * thisptr, int, void *, const char *, unsigned int, unsigned int );
    // gameEventManager
    bool FireEventClientSide( CGameEventManager *thisptr, CGameEvent *event );
    // gameEventSystem
    void PostEventAbstract( CGameEventSystem *thisptr, int splitScreenSlot, bool unk, int int2, unsigned const char *bytes, CNetworkSerializerPB* eventHandle,  google::protobuf::Message *msg, unsigned long dong, NetChannelBufType_t buftype );
    // inputInternal
    void SetKeyCodeState( IInputInternal* thisptr, ButtonCode_t code, bool bPressed );
    // INetChannel
    void PostReceivedNetMessage( INetChannel *thisptr, NetMessageHandle_t * messageHandle, google::protobuf::Message* msg, NetChannelBufType_t const* type);
    bool SendNetMessage( INetChannel *thisptr, NetMessageHandle_t * messageHandle, google::protobuf::Message* msg, NetChannelBufType_t type );
    // ParticleSystemMgr
    CParticleCollection* CreateParticleCollection( CParticleSystemMgr *thisptr, CWeakHandle_InfoForResourceTypeIParticleSystemDefinition *info, void *unk, IParticleSystemQuery *query, bool bUnk, float fUnk, int iUnk );
    void DeleteParticleCollection( CParticleSystemMgr *thisptr, CParticleCollection *collectionToDelete );
    // panel
    void PaintTraverse( IVPanel* thisptr, IVGuiPaintSurface* surface, VPANEL panel, bool force_repaint, bool allow_force );
    // panorama
    int RunScript( panorama::UIEngine* thisptr, panorama::IUIPanel *panel, const char* str1, const char* str2, int int1, int int2, bool bool1 );
    // CDotaPlayer
    void PrepareUnitOrders( CDotaPlayer *thisptr, DotaUnitOrder_t order, int targetIndex, Vector movePosition, int abilityIndex,PlayerOrderIssuer_t orderIssuer,
                           CDotaBaseNPC* entity, bool queue, bool showEffects );
    // CSoundOpSystem
    void StartSoundEvent( CSoundOpSystem *thisptr, const char *name, int entIndex, short unk, void const *something, int unk2 );
    void StartSoundEvent2( CSoundOpSystem *thisptr, unsigned int unk, int entIndex, sound_voice_layer_t voiceLayer, short unk2, const char *name, void const * something, int unk3, SoundEventGuid_t guid);
}

namespace SetKeyCodeState
{
    inline bool shouldListen = false;
    inline ButtonCode_t* keyOutput = nullptr;
}

namespace PaintTraverse
{
    bool InitFonts();
}

namespace CreateMove
{
    inline Vector lastMouse3D;
}

namespace CreateParticleCollection
{
    inline std::vector<CParticleCollection*> particlesTracked;
    inline std::mutex particleRemoveGuard;
}