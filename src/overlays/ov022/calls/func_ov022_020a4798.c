#pragma thumb on

/* Ov022_RequestVoiceIds -- ask the resource layer for an actor's three voices.
 *
 * The caller's own id goes in first and is requested at once. The second comes
 * from the actor's own handler, the third from its kind: normally through a
 * table of constants, but while the fourth bit of the global mode byte is set
 * the local player takes it from a table of twenty words copied onto the frame
 * instead. A packed parameter can move that third id on by one. Every id that
 * came out valid is requested.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct Actor;

typedef short (*GetVoiceIdFn)(struct Actor *pActor);

struct Actor {
    u8 pad0000[8];
    u8 nOwner;                   /* 0x0008 */
    u8 nId;                      /* 0x0009 */
    u8 pad000a[2];
    int nModelId;                /* 0x000c */
    u8 pad0010[0x66c];
    GetVoiceIdFn pfnGetVoiceId;  /* 0x067c */
    u8 pad0680[0x124];
    short nVoiceId;              /* 0x07a4 */
    short nHandlerId;            /* 0x07a6 */
    short nKindId;               /* 0x07a8 */
    short nVoiceArg;             /* 0x07aa */
    int nField7ac;               /* 0x07ac */
};

struct KindIdTable {
    int aIds[20];
};

extern u8 data_0204c240;
extern struct KindIdTable data_ov022_020b2724;

extern void func_0203355c(short nId);
extern int func_02030788(void);
extern unsigned int func_020358f4(int nSlot, int nParam);

#define MODE_TABLE_DRIVEN 4
#define VOICE_PARAM 0x58

void func_ov022_020a4798(struct Actor *pActor, short nId, u16 nArg2)
{
    struct KindIdTable tbl;

    pActor->nVoiceId = nId;
    pActor->nVoiceArg = nArg2;
    pActor->nHandlerId = -1;
    pActor->nKindId = -1;
    pActor->nField7ac = 0;
    func_0203355c(nId);
    pActor->nHandlerId = pActor->pfnGetVoiceId(pActor);
    if (pActor->nHandlerId >= 0) {
        func_0203355c(pActor->nHandlerId);
    }
    if ((data_0204c240 & MODE_TABLE_DRIVEN) != 0) {
        if (func_02030788() == pActor->nOwner) {
            tbl = data_ov022_020b2724;
            pActor->nKindId = (short)tbl.aIds[pActor->nModelId];
        }
    } else {
        switch (pActor->nModelId) {
        case 0:
            pActor->nKindId = 0xd8;
            break;
        case 0xe:
            pActor->nKindId = 0xe8;
            break;
        case 0x13:
            pActor->nKindId = 0xda;
            break;
        case 1:
            pActor->nKindId = 0xdc;
            break;
        case 2:
            pActor->nKindId = 0xde;
            break;
        case 4:
            pActor->nKindId = 0xe2;
            break;
        case 3:
            pActor->nKindId = 0xe0;
            break;
        case 6:
            pActor->nKindId = 0xe4;
            break;
        case 9:
            pActor->nKindId = 0xe6;
            break;
        }
    }
    if (pActor->nKindId >= 0
        && func_020358f4(pActor->nId, VOICE_PARAM) >= 1) {
        pActor->nKindId = pActor->nKindId + 1;
    }
    if (pActor->nKindId >= 0) {
        func_0203355c(pActor->nKindId);
    }
}
