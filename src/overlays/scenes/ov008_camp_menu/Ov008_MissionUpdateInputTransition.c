#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
typedef struct {
    u32 mode;
    u32 keycode;
    u32 rawKeys;
    u16 packedKeys;
} MissionDisplayConfig;

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)

extern void Ov105_WH_SetReceiver(void *callback);
extern void ReleaseServiceInstance(void);
extern void Session_StoreSetup(void *config);
extern void EnsureServiceInstance(void);
extern unsigned short WH_GetCurrentAid(void);
extern void Ov008_MissionPushDisplayConfig(void);
extern void StoreGlobalPtrArray4At0c(int slot, void *callback);
extern void Ov008_MissionApplyEntryUpdate(void);

void Ov008_MissionUpdateInputTransition(void) {
    MissionDisplayConfig exit_config;
    MissionDisplayConfig key_config;
    MissionKeyBlock *key_block;

    MISSION_CONTEXT->transitionRequested = 0;
    if (MISSION_CONTEXT->localMode == 0) {
        Ov105_WH_SetReceiver(0);
    }
    ReleaseServiceInstance();

    if (MISSION_CONTEXT->localMode != 0) {
        exit_config.mode = 1;
        exit_config.keycode = 1;
        Session_StoreSetup(&exit_config);
        EnsureServiceInstance();
    } else {
        if (WH_GetCurrentAid() == 0) {
            Ov008_MissionPushDisplayConfig();
        } else {
            key_block = &MISSION_CONTEXT->message.keys;
            Ov008_MissionPushDisplayConfig();
            key_config.mode = 3;
            key_config.rawKeys = key_block->rawKeys;
            key_config.packedKeys = key_block->packedKeys;
            Session_StoreSetup(&key_config);
        }
        EnsureServiceInstance();
        StoreGlobalPtrArray4At0c(0xd, Ov008_MissionApplyEntryUpdate);
    }

    MISSION_CONTEXT->entryUpdateMask = 1;
}
