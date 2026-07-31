/*
 * Ov002_RunPendingCallbacks - one of the gameplay-state handlers returned by
 * Ov002_TickGameplayState (the flag-0x2087 path). Flushes the two pending context callbacks and
 * advances to the next handler (func_ov002_02068dc4).
 *
 * No-op (returns NULL) while the global busy byte data_0204be04 is set. Otherwise it invokes the
 * callback at heap+0x8b8c with argument heap+0x8bb0 (if present), then begins a timed phase
 * (func_ov002_0206f4e0); if that is not ready it returns NULL. On success it clears the global
 * byte (func_02020878(0)), runs func_ov002_0206eb20, and invokes the second callback at
 * heap+0x8b44 with argument heap+0x8b48 (clearing both fields first), clears heap+0x8da8, and
 * returns func_ov002_02068dc4 as the next handler.
 *
 * THUMB. The heap base is NNSi_FndGetCurrentRootHeap(). blk = heap+0x8ba8 is computed before the
 * busy-flag check (mwcc schedules it into the load-delay slot); the first callback pointer sits
 * 0x1c below it (heap+0x8b8c).
 */

typedef unsigned char u8;
typedef void (*CbFn)(int);

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_ov002_0206f4e0(void);
extern void func_02020878(int a);
extern void func_ov002_0206eb20(void);
extern void func_ov002_02068dc4(void);
extern u8   data_0204be04;

void *func_ov002_02068d54(void)
{
    int base = NNSi_FndGetCurrentRootHeap();
    int *blk = (int *)(base + 0x8ba8);
    CbFn cb;

    if (data_0204be04 != 0) {
        return 0;
    }
    cb = *(CbFn *)(base + 0x8b8c);
    if (cb != 0) {
        cb(blk[2]);
    }
    if (func_ov002_0206f4e0() == 0) {
        return 0;
    }
    func_02020878(0);
    func_ov002_0206eb20();
    cb = *(CbFn *)(base + 0x8b44);
    if (cb != 0) {
        int arg = *(int *)(base + 0x8b48);
        *(int *)(base + 0x8b44) = 0;
        *(int *)(base + 0x8b48) = 0;
        cb(arg);
    }
    *(int *)(base + 0x8da8) = 0;
    return (void *)func_ov002_02068dc4;
}
