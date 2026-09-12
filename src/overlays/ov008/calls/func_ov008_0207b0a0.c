/* func_ov008_0207b0a0 -- Ov008_IsMissionGroupStale: does the current mission id
 * group need rebuilding?  Never while there is no mission context or its transfer
 * word (+0x4e8) is busy.  Without a tick source, a session id that differs from the
 * one recorded marks the group dirty and answers yes; with one, a group already
 * marked dirty answers yes.  Otherwise yes unless the scene poll reports 4.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct MissionContext {
    u8  pad_0000[0x4a8];
    u32 bHeaderBit0 : 1;      /* 0x4a8: current group header */
    u32 bDirty : 1;
    u32 nHeaderRest : 30;
    u8  pad_04ac[0x4e8 - 0x4ac];
    int nTransferBusy;        /* 0x4e8 */
} MissionContext;

typedef struct Ov006Globals {
    MissionContext *context;
} Ov006Globals;

#define SCENE_POLL_IDLE 4

extern Ov006Globals data_ov008_02090f24;
extern int OS_IsTickAvailable(void);
extern u16 func_01fff988(void);                    /* recorded session id */
extern u16 OS_IsTickAvailable_0x01ff8138(void);    /* current session id */
extern int func_02001030(void);                    /* Game_PollSceneAlive */

int func_ov008_0207b0a0(void)
{
    MissionContext *pCtx = data_ov008_02090f24.context;
    u16 nRecorded;

    if (pCtx == 0 || pCtx->nTransferBusy != 0) {
        return 0;
    }
    if (OS_IsTickAvailable() == 0) {
        nRecorded = func_01fff988();
        if (nRecorded != OS_IsTickAvailable_0x01ff8138()) {
            data_ov008_02090f24.context->bDirty = 1;
            return 1;
        }
    } else if (data_ov008_02090f24.context->bDirty != 0) {
        return 1;
    }
    return func_02001030() != SCENE_POLL_IDLE;
}
