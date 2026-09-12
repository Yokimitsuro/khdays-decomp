/* func_ov008_0207a058 -- Ov008_MissionLobbyInit: create the mission context in
 * the current root heap (0x500 bytes, zeroed), latch whether the transfer flag
 * 0x200d is set, and pick the first lobby state.  A non-zero argument goes
 * straight to the state at 0207aac8.  Otherwise, unless a transfer is pending
 * or a session already exists and is active, five 0x100-byte buffers (the
 * header and four slots at +8, +0x10, +0x18, +0x20) are allocated and the game
 * is put in state 0 -> state 0207a1c4; else the context is marked busy, state 1
 * is set, gate 0xd gets its handler -> state 0207a424.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define CONTEXT_SIZE 0x500
#define BUFFER_SIZE  0x100
#define BUFFER_ALIGN 0x20
#define SLOT_COUNT   4
#define FLAG_TRANSFER 0x200d
#define GATE_LOBBY 0xd

typedef struct Ov008SlotBuffer {
    void *pBuffer;
    int   nPad;
} Ov008SlotBuffer;

typedef struct CardXferOwner {
    void *pHeader;            /* 0x000 */
    u8    pad_004[4];
    Ov008SlotBuffer aSlot[SLOT_COUNT]; /* 0x008 */
    u8    pad_028[0x49c - 0x28];
    int   nBusy;              /* 0x49c */
    u8    pad_4a0[0x4e8 - 0x4a0];
    int   nTransferBusy;      /* 0x4e8 */
} CardXferOwner;

typedef void *(*Ov008StateFn)(void);

extern CardXferOwner *data_ov008_02090f24;
extern CardXferOwner *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern int  func_02023588(int nFlag);                         /* GameState_IsFlagSet */
extern int  func_02030640(void);                              /* Session_Exists */
extern int  func_02030670(void);                              /* Session_IsActive */
extern void func_02023c14(int nState);                        /* StoreToGlobalPtr4Field28 */
extern void func_02030cf8(int nGate, void *pHandler);          /* StoreGlobalPtrArray4At0c */
extern void *NNS_FndAllocFromDefaultExpHeapEx(int nSize, int nAlign);
extern void func_02001054(void);
extern void *func_ov008_0207aac8(void);
extern void *func_ov008_0207a254(void);
extern void *func_ov008_0207a424(void);
extern void *func_ov008_0207a1c4(void);

void *func_ov008_0207a058(int bSkip)
{
    int i;

    data_ov008_02090f24 = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov008_02090f24, 0, CONTEXT_SIZE);
    data_ov008_02090f24->nTransferBusy = func_02023588(FLAG_TRANSFER) != 0;
    if (bSkip != 0) {
        return (void *)func_ov008_0207aac8;
    }
    if (data_ov008_02090f24->nTransferBusy != 0 || (func_02030640() != 0 && func_02030670() != 0)) {
        data_ov008_02090f24->nBusy = 1;
        func_02023c14(1);
        func_02030cf8(GATE_LOBBY, (void *)func_ov008_0207a254);
        return (void *)func_ov008_0207a424;
    }
    data_ov008_02090f24->pHeader = NNS_FndAllocFromDefaultExpHeapEx(BUFFER_SIZE, BUFFER_ALIGN);
    for (i = 0; i < SLOT_COUNT; i++) {
        data_ov008_02090f24->aSlot[i].pBuffer = NNS_FndAllocFromDefaultExpHeapEx(BUFFER_SIZE, BUFFER_ALIGN);
    }
    func_02001054();
    func_02023c14(0);
    return (void *)func_ov008_0207a1c4;
}
