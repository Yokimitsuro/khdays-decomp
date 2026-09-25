#pragma thumb on
/* func_020229c4 -- enter a scene, MAIN. Unless forced (data_0204bd85) or flag 0x20ef is set, the
 * call is refused (func_020208d0(0)). Otherwise: graphics mode 1/0/1 when +0xe4 asks for it, the
 * scene state becomes 3 (+0xc8, sub-state +0xcc = 2, +0xd8 cleared), a +0xdc scene resets its
 * display (func_ov002_02056fb8(1, 0), func_0200c5fc, layers 4). Unless a reset is pending
 * (data_0204c240 bit 2 while mode bit 1 is set) the state is saved for the way back: the 64-bit
 * tick (+0x0), the random seed (+0x8) and the playing BGM track (+0xc4, then paused). In mode bit 1
 * the sound fades to 0x40; the main screen shows BG0 only; the fade block (+0xac, 0x18 bytes) is
 * reset with its step at 3 in mode bit 1 else 2; mode bit 3 resets the effect layer; and
 * func_02022af4 is queued as the next task. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

typedef struct GameHeap {
    u64 save;                           /* +0x00 */
    unsigned int seed;                  /* +0x08 */
    char pad0c[0xac - 0xc];
    int fade[6];                        /* +0xac */
    int track;                          /* +0xc4 */
    int state;                          /* +0xc8 */
    int subState;                       /* +0xcc */
    int fadeStep;                       /* +0xd0 */
    int fadeTimer;                      /* +0xd4 */
    int stateTimer;                     /* +0xd8 */
    int scene;                          /* +0xdc */
    int object;                         /* +0xe0 */
    int gfxMode;                        /* +0xe4 */
} GameHeap;

extern char *data_0204be08;
extern u8 data_0204bd85;
extern u8 data_0204c240;
extern char data_02042748[16];
extern int func_02023588(int id);
extern void func_020208d0(int a);
extern void func_020056b4(int a, int b, int c);
extern void func_ov002_02056fb8(int nHold, int bLeaving);
extern void func_0200c5fc(void);
extern void func_0200ca50(int layer);
extern void func_0200ca68(int layer);
extern int func_02020a9c(void);
extern u64 func_020031d4(void);
extern unsigned int OS_IsThreadAvailable(void);
extern int func_02034014(int slot);
extern int func_02034048(int slot);
extern void func_02033fec(int slot, int a);
extern void func_02033c24(int volume, int frames);
extern void MI_CpuFill8(void *dest, int data, u32 size);
extern void func_02023c30(int mode);
extern void func_02000f48(int nSlot, const char *pName, void (*pfnTask)(void));
extern void func_02022af4(void);

void func_020229c4(void)
{
    GameHeap *heap = (GameHeap *)(&data_0204be08)[1];

    if (data_0204bd85 == 0 && func_02023588(0x20ef) == 0) {
        func_020208d0(0);
        return;
    }
    if (heap->gfxMode != 0) {
        func_020056b4(1, 0, 1);
    }
    heap->stateTimer = 0;
    heap->state = 3;
    heap->subState = 2;
    if (heap->scene != 0) {
        func_ov002_02056fb8(1, 0);
        func_0200c5fc();
        func_0200ca50(4);
        func_0200ca68(4);
    }
    if ((data_0204c240 & 4) == 0 || (func_02020a9c() & 2) == 0) {
        heap->save = func_020031d4();
        heap->seed = OS_IsThreadAvailable();
        if (func_02034014(0) != 0) {
            heap->track = func_02034048(0);
            func_02033fec(0, 0);
        }
    }
    if ((func_02020a9c() & 2) != 0) {
        func_02033c24(0x40, 10);
    }
    REG_DISPCNT = (REG_DISPCNT & 0xffffe0ff) | 0x100;
    heap->fadeStep = (func_02020a9c() & 2) ? 3 : 2;
    heap->fadeTimer = 0;
    MI_CpuFill8(heap->fade, 0, sizeof(heap->fade));
    heap->fade[1] = 1;
    if ((func_02020a9c() & 8) != 0) {
        func_02023c30(0);
    }
    func_02000f48(1, data_02042748, func_02022af4);
}
