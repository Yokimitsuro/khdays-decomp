#pragma thumb on
/* func_02023018 -- leave the current scene, MAIN. The main screen falls back to BG0 only; in mode
 * bit 3 the effect layer is reset (func_02023c30(2)). Unless a reset is pending (data_0204c240 bit
 * 2 while mode bit 1 is set), the saved state of the game heap is restored: func_02003284 with
 * +0x0/+0x4, the random seed from +0x8, sound stopped, and the +0xc4 track released when no
 * +0xe0 object holds it. In mode bit 1 the sound fades out (func_02033c24(0x7f, 10)). A +0xdc
 * scene drops its +0xe0 object; the scene state (+0xc8) becomes 5 and func_02023100 is queued as
 * the next task. */
typedef unsigned char u8;
typedef unsigned int u32;

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

typedef struct GameHeap {
    int saveA;                          /* +0x00 */
    int saveB;                          /* +0x04 */
    unsigned int seed;                  /* +0x08 */
    char pad0c[0xc4 - 0xc];
    int track;                          /* +0xc4 */
    int state;                          /* +0xc8 */
    char padcc[0xdc - 0xcc];
    int scene;                          /* +0xdc */
    int object;                         /* +0xe0 */
} GameHeap;

extern char *data_0204be08;
extern u8 data_0204c240;
extern char data_02042748[16];
extern int func_02020a9c(void);
extern void func_02023c30(int mode);
extern void func_02003284(int a, int b);
extern void srand(unsigned int seed);
extern void SNDi_BroadcastChannelOp(int op);
extern void func_0203409c(int a);
extern void func_02033c24(int volume, int frames);
extern int func_02024d68(void);
extern void func_ov002_02056fb8(int a, int object);
extern void func_02000f48(int nSlot, const char *pName, void (*pfnTask)(void));
extern void func_02023100(void);

void func_02023018(void)
{
    GameHeap *heap = (GameHeap *)(&data_0204be08)[1];

    REG_DISPCNT = (REG_DISPCNT & 0xffffe0ff) | 0x100;
    if ((func_02020a9c() & 8) != 0) {
        func_02023c30(2);
    }
    if ((data_0204c240 & 4) == 0 || (func_02020a9c() & 2) == 0) {
        func_02003284(heap->saveA, heap->saveB);
        srand(heap->seed);
        SNDi_BroadcastChannelOp(0);
        if (heap->object == 0 && heap->track != -1) {
            func_0203409c(0);
        }
        heap->track = -1;
    }
    if ((func_02020a9c() & 2) != 0) {
        func_02033c24(0x7f, 10);
    }
    if (heap->scene != 0) {
        func_02024d68();
        func_ov002_02056fb8(0, heap->object);
        heap->object = 0;
    }
    heap->state = 5;
    func_02000f48(1, data_02042748, func_02023100);
}
