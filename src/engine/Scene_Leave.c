#pragma thumb on
/* Scene_Leave -- leave the current scene, MAIN. The main screen falls back to BG0 only; in mode
 * bit 3 the effect layer is reset (SetGameMode(2)). Unless a reset is pending (data_0204c240 bit
 * 2 while mode bit 1 is set), the saved state of the game heap is restored: OS_SetTick with
 * +0x0/+0x4, the VBlank count from +0x8, sound stopped, and, when no
 * +0xe0 object holds it, stream 0 restarted from the playback position saved at +0xc4. In mode bit 1 the sound fades out (InvokeSubStructAndStampByte(0x7f, 10)). A +0xdc
 * scene drops its +0xe0 object; the scene state (+0xc8) becomes 5 and Gfx_RestoreAfterPause is queued as
 * the next task. */

#include "nitro/types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

typedef struct GameHeap {
    int saveA;                          /* +0x00 */
    int saveB;                          /* +0x04 */
    unsigned int vblankCount;           /* +0x08 */
    char pad0c[0xc4 - 0xc];
    int streamPos;                      /* +0xc4: stream 0 position saved on pausing, -1 = none */
    int state;                          /* +0xc8 */
    char padcc[0xdc - 0xcc];
    int scene;                          /* +0xdc */
    int object;                         /* +0xe0 */
} GameHeap;

extern char *data_0204be08;
extern u8 data_0204c240;
extern char gPauseRefreshName[16];
extern int LoadGlobalU16At0(void);
extern void SetGameMode(int mode);
extern void OS_SetTick(int a, int b);
extern void VBlank_SetCount(unsigned int count);
extern void SNDi_BroadcastChannelOp(int op);
extern int SoundMgr_StartStream(int slot, int pos);
extern void InvokeSubStructAndStampByte(int volume, int frames);
extern int Touch_StartAutoSampling(void);
extern void Ov002_HoldPanelScreen(int a, int object);
extern void RegisterNamedTask(int nSlot, const char *pName, void (*pfnTask)(void));
extern void Gfx_RestoreAfterPause(void);

void Scene_Leave(void)
{
    GameHeap *heap = (GameHeap *)(&data_0204be08)[1];

    REG_DISPCNT = (REG_DISPCNT & 0xffffe0ff) | 0x100;
    if ((LoadGlobalU16At0() & 8) != 0) {
        SetGameMode(2);
    }
    if ((data_0204c240 & 4) == 0 || (LoadGlobalU16At0() & 2) == 0) {
        OS_SetTick(heap->saveA, heap->saveB);
        VBlank_SetCount(heap->vblankCount);
        SNDi_BroadcastChannelOp(0);
        if (heap->object == 0 && heap->streamPos != -1) {
            SoundMgr_StartStream(0, heap->streamPos);
        }
        heap->streamPos = -1;
    }
    if ((LoadGlobalU16At0() & 2) != 0) {
        InvokeSubStructAndStampByte(0x7f, 10);
    }
    if (heap->scene != 0) {
        Touch_StartAutoSampling();
        Ov002_HoldPanelScreen(0, heap->object);
        heap->object = 0;
    }
    heap->state = 5;
    RegisterNamedTask(1, gPauseRefreshName, Gfx_RestoreAfterPause);
}
