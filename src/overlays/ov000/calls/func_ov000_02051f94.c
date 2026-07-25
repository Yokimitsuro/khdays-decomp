/* Teardown for the ov000 title/menu/Load scene: releases every buffer the scene
 * allocated, blanks the four sub-screen background layers and drops the context
 * pointer, so the next scene starts from a clean slate.
 *
 * Order matters and is the ROM's: mask the display's BG enable bits first (so nothing
 * is scanned out of memory that is about to be freed), then release the var table, the
 * three node lists, the two scene-owned buffer sets and the three selection-object
 * pools; then free the three per-slot buffers and the page buffer from the default
 * heap; then clear the four BG screen maps; then hand the three resource ids back.
 * Publishing NULL to the context global last is what makes the scene unreachable.
 */

typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov000DestroyContext {
    u8 pad_0000[0x4c];
    u8 aSelectionObject[1];
} Ov000DestroyContext;

typedef struct Ov000SceneContext {
    u8 pad_0000[0x4aec];
    void *apSlotBuffer[3];
    u8 pad_4af8[0x4b04 - 0x4af8];
    void *pPageBuffer;
    u8 pad_4b08[0x4cb4 - 0x4b08];
    u8 aVarTable[1];
} Ov000SceneContext;

extern Ov000SceneContext *data_ov000_0205ac24;

extern void func_ov000_02056960(u8 *table);
extern void func_0202ffbc(u8 *list);
extern void func_ov000_020568c8(Ov000SceneContext *ctx);
extern void func_ov000_0205651c(Ov000SceneContext *ctx);
extern void func_ov000_02055ad8(u8 *obj);
extern void func_ov000_02055b0c(u8 *obj);
extern void func_ov000_02055750(u8 *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void func_020235bc(int id);

static volatile u32 *const REG_DISPCNT = (volatile u32 *)0x04000000;

void func_ov000_02051f94(void)
{
    Ov000SceneContext *ctx = data_ov000_0205ac24;
    u8 i;

    *REG_DISPCNT &= ~0xe000;

    func_ov000_02056960((u8 *)data_ov000_0205ac24 + 0x4cb4);
    func_0202ffbc((u8 *)data_ov000_0205ac24 + 0x4cfc);
    func_0202ffbc((u8 *)data_ov000_0205ac24 + 0x4cc0);
    func_0202ffbc((u8 *)data_ov000_0205ac24 + 0x4d38);

    func_ov000_020568c8(ctx);
    func_ov000_0205651c(ctx);
    func_ov000_02055ad8(((Ov000DestroyContext *)ctx)->aSelectionObject);
    func_ov000_02055b0c(((Ov000DestroyContext *)ctx)->aSelectionObject);
    func_ov000_02055750(((Ov000DestroyContext *)ctx)->aSelectionObject);

    for (i = 0; i < 3; i++) {
        if (data_ov000_0205ac24->apSlotBuffer[i] != 0) {
            NNSi_FndFreeFromDefaultHeap(data_ov000_0205ac24->apSlotBuffer[i]);
            data_ov000_0205ac24->apSlotBuffer[i] = 0;
        }
    }
    if (data_ov000_0205ac24->pPageBuffer != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov000_0205ac24->pPageBuffer);
        data_ov000_0205ac24->pPageBuffer = 0;
    }

    MIi_CpuClearFast(0, G2S_GetBG0ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);

    func_020235bc(0x200a);
    func_020235bc(0x200c);
    func_020235bc(0x200d);

    data_ov000_0205ac24 = 0;
}
