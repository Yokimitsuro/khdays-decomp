typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov011AnimEntry {
    u8 nTargets : 4;
    u8 nOpcode : 4;
    u8 pad_01[3];
    u16 wDuration;
    u8 pad_06[2];
    u8 nMode : 4;
    u8 reserved84 : 4;
    u8 pad_09[3];
    int nResource;
} Ov011AnimEntry;

typedef struct Ov011Pane {
    void *pGfx;
    u8 pad_00004[0x10928 - 0x04];
    u16 wStartA;
    u16 wEndA;
    u16 wStartB;
    u16 wEndB;
    u8 pad_10930;
    u8 nOpcode;
    u8 pad_10932[0x10940 - 0x10932];
} Ov011Pane;

typedef struct Ov011Scene {
    u8 pad_00000[4];
    int nMode;
    u8 pad_00008[0x14 - 0x08];
    Ov011Pane aPane[2];
    u8 pad_21294[0x23abd - 0x21294];
    u8 nPane : 1;
    u8 reserved23abd1 : 7;
    u8 pad_23abe[2];
    u32 flags;
    u8 pad_23ac4[4];
    u16 wEntryIndex;
    u16 wEntryCount;
    Ov011AnimEntry *pEntries;
    u8 pad_23ad0[0x28508 - 0x23ad0];
    u8 slotManager;
    u8 pad_28509[0x2cf40 - 0x28509];
    int nSlot;
    u8 pad_2cf44[0x2cf50 - 0x2cf44];
    u16 wWindowStart;
    u16 wDeadline;
} Ov011Scene;

typedef struct Ov011Globals {
    u32 nTimer;
    Ov011Scene *pScene;
} Ov011Globals;

typedef struct Ov011CheckState {
    u32 nTimer;
    u8 *pScene;
} Ov011CheckState;

/* khdays: shared-bss */
Ov011Globals data_ov011_0205e960 = {0};
#define OV011_TIMER data_ov011_0205e960.nTimer
#define OV011_SCENE data_ov011_0205e960.pScene

extern void func_ov011_0205d508(void *pGfx, int nPane, int nResource,
                                const Ov011AnimEntry *pEntry);
extern int func_020326a8(void *pManager, int nSlot);
extern void func_02033fb4(int nTable, int nValue);
extern void *func_02033fec(int nTable, int nValue);
extern void func_02032710(void *pManager, int nSlot, int bVisible);

void func_ov011_0205b340(u8 *nScene, u32 nNow)
{
    Ov011AnimEntry *pEntry;
    u16 nDeadline;
    u16 nDuration;
    int nPane;
    u32 nEntryIndex;

    while ((nScene = (u8 *)OV011_SCENE,
            nNow = *(volatile u32 *)&data_ov011_0205e960,
            nNow >= *(u16 *)(nScene + 0x2cf52)) &&
           (nEntryIndex = *(u16 *)(nScene + 0x23ac8)) <
               *(u16 *)(nScene + 0x23aca)) {
        pEntry = &(*(Ov011AnimEntry **)((u8 *)nScene + 0x23acc))[
            nEntryIndex];
        switch (pEntry->nOpcode) {
        case 0:
            if (pEntry->nTargets & 1) {
                nDuration = pEntry->wDuration;
                *(u16 *)((u8 *)nScene + 0x10940) = nNow;
                ((u16 *)((u8 *)nScene + 0x10940))[1] =
                    OV011_TIMER + nDuration;
            }
            if (pEntry->nTargets & 2) {
                nDuration = pEntry->wDuration;
                nNow = OV011_TIMER;
                nScene = (u8 *)OV011_SCENE;
                *(u16 *)((u8 *)nScene + 0x21280) = nNow;
                ((u16 *)((u8 *)nScene + 0x21280))[1] =
                    OV011_TIMER + nDuration;
            }
            break;

        case 1:
            if (pEntry->nTargets & 1) {
                nDuration = pEntry->wDuration;
                *(u16 *)((u8 *)nScene + 0x1093c) = nNow;
                ((u16 *)((u8 *)nScene + 0x1093c))[1] =
                    OV011_TIMER + nDuration;
            }
            if (pEntry->nTargets & 2) {
                nDuration = pEntry->wDuration;
                nNow = OV011_TIMER;
                nScene = (u8 *)OV011_SCENE;
                *(u16 *)((u8 *)nScene + 0x2127c) = nNow;
                ((u16 *)((u8 *)nScene + 0x2127c))[1] =
                    OV011_TIMER + nDuration;
            }
            break;

        case 2:
            if (pEntry->nTargets & 1) {
                nDuration = pEntry->wDuration;
                *(u16 *)((u8 *)nScene + 0x1093c) = nNow;
                ((u16 *)((u8 *)nScene + 0x1093c))[1] =
                    OV011_TIMER + nDuration;
            }
            if (pEntry->nTargets & 2) {
                nDuration = pEntry->wDuration;
                nNow = OV011_TIMER;
                nScene = (u8 *)OV011_SCENE;
                *(u16 *)((u8 *)nScene + 0x2127c) = nNow;
                ((u16 *)((u8 *)nScene + 0x2127c))[1] =
                    OV011_TIMER + nDuration;
            }
            break;

        case 3:
        {
            u16 *pTiming;
            nDuration = pEntry->wDuration;
            nScene = (u8 *)*(Ov011Scene * volatile *)
                ((u8 *)&data_ov011_0205e960 + 4);
            nPane = ((Ov011Scene *)nScene)->nPane ^ 1;
            pTiming = (u16 *)((u8 *)nScene + 0x1093c
                              + nPane * 0x10940);
            pTiming[0] = nNow;
            pTiming[1] = OV011_TIMER + nDuration;
            break;
        }

        case 4:
        {
            u16 *pTiming;
            if (pEntry->nMode == 1)
                OV011_SCENE->nPane = OV011_SCENE->nPane ^ 1;
            nDuration = pEntry->wDuration;
            nNow = ((Ov011Globals *)&data_ov011_0205e960)->nTimer;
            nScene = (u8 *)((Ov011Globals *)&data_ov011_0205e960)->pScene;
            nPane = ((Ov011Scene *)nScene)->nPane;
            pTiming = (u16 *)((u8 *)nScene + 0x1093c
                              + nPane * 0x10940);
            pTiming[0] = nNow;
            pTiming[1] = OV011_TIMER + nDuration;
            break;
        }

        case 5:
            nDuration = pEntry->wDuration;
            *(u16 *)((u8 *)nScene + 0x2cf50) = nNow;
            ((u16 *)((u8 *)nScene + 0x2cf50))[1] =
                OV011_TIMER + nDuration;
            break;

        case 6:
        case 7:
            if (OV011_SCENE->nMode == 0)
                OV011_SCENE->nPane = OV011_SCENE->nPane ^ 1;
            if (pEntry->nTargets & 1) {
                func_ov011_0205d508(OV011_SCENE->aPane[0].pGfx,
                                    OV011_SCENE->nPane ^ 1,
                                    pEntry->nResource,
                                    pEntry->nOpcode == 7 ? pEntry : 0);
            }
            if (pEntry->nTargets & 2) {
                func_ov011_0205d508(OV011_SCENE->aPane[1].pGfx,
                                    (OV011_SCENE->nPane ^ 1) + 2,
                                    pEntry->nResource,
                                    pEntry->nOpcode == 7 ? pEntry : 0);
            }
            break;

        case 10:
            OV011_SCENE->flags |= 2;
            func_020326a8(&OV011_SCENE->slotManager,
                          OV011_SCENE->nSlot);
            OV011_SCENE->wEntryIndex++;
            return;

        case 8:
            if (pEntry->nMode == 0)
                func_02033fb4(0, 2);
            else
                func_02033fec(0, pEntry->wDuration);
            break;

        case 9:
            nScene = (u8 *)*(Ov011Scene * volatile *)
                ((u8 *)&data_ov011_0205e960 + 4);
            func_02032710(&((Ov011Scene *)nScene)->slotManager,
                          ((Ov011Scene *)nScene)->nSlot, 1);
            break;
        }

        switch (pEntry->nOpcode) {
        case 1:
        case 2:
            if (pEntry->nTargets & 1)
                OV011_SCENE->aPane[0].nOpcode = pEntry->nOpcode;
            if (pEntry->nTargets & 2)
                OV011_SCENE->aPane[1].nOpcode = pEntry->nOpcode;
            break;
        case 3:
        case 4:
            OV011_SCENE->aPane[0].nOpcode = pEntry->nOpcode;
            OV011_SCENE->aPane[1].nOpcode = pEntry->nOpcode;
            break;
        }
        OV011_SCENE->wEntryIndex++;
    }
}
