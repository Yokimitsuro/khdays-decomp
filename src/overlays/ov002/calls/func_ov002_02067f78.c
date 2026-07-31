/*
 * Ov002_TickGameplayState - main per-frame gameplay-state dispatcher, called from the ov002
 * gameplay constructor (func_ov002_020679d4). Returns the next scene/handler function pointer
 * (or NULL to stay).
 *
 * Runs SetGameMode with the low byte of the record at heap+0x8b54, then ticks the optional
 * callback held at heap+0x8b98. If flag 0x2087 is set, hands off to func_ov002_02068d54.
 * Otherwise, if the counter at heap+0x8ba8 has reached the 0x2710 cap and either flag 0x18bd
 * or 0x18c9 is set, it enqueues command 0xd (exactly at the cap) or 2 (over it), marks the
 * counter's follow field to -5, and hands off to func_ov002_02068fc4. Otherwise, unless
 * func_02020e58 reports busy, it advances the sub-state (func_ov002_02069540) and dispatches on
 * heap+0x134: state 1 first notifies func_ov002_0206ba28 (heap+0x138) then falls into state 0,
 * which clears heap+0x8da8 and hands off to func_ov002_02068dc4; state 2 hands off to
 * func_ov002_02068058; any other state stays (NULL).
 *
 * THUMB. The heap base is NNSi_FndGetCurrentRootHeap() (== the ov002 root context). The state
 * dispatch is a switch so mwcc emits the linear cmp #0/#1/#2 chain with the state-1->state-0
 * fall-through and a single shared return-in-r6 epilogue.
 */

typedef unsigned char u8;
typedef void (*CodeFn)(int);

extern int  NNSi_FndGetCurrentRootHeap(void);
extern void func_02023c30(int mode);
extern int  func_02023588(int flag);
extern void func_02033770(u8 cmd, int b);
extern int  func_02020e58(int *p);
extern void func_ov002_02069540(void);
extern void func_ov002_0206ba28(int a);
extern void func_ov002_02068d54(void);
extern void func_ov002_02068fc4(void);
extern void func_ov002_02068dc4(void);
extern void func_ov002_02068058(void);

void *func_ov002_02067f78(void)
{
    int base = NNSi_FndGetCurrentRootHeap();
    short *rec = (short *)(base + 0x8ba8);
    void *result = 0;

    func_02023c30((u8)*(int *)(base + 0x8b54));
    if (*(CodeFn *)(base + 0x8b98) != 0) {
        (*(CodeFn *)(base + 0x8b98))(1);
    }
    if (func_02023588(0x2087) != 0) {
        return (void *)func_ov002_02068d54;
    }
    if (0x2710 <= *rec &&
        (func_02023588(0x18bd) != 0 || func_02023588(0x18c9) != 0)) {
        int cmd;
        if (*rec == 0x2710) cmd = 0xd;
        else cmd = 2;
        func_02033770(cmd, 0x1e);
        rec[1] = -5;
        return (void *)func_ov002_02068fc4;
    }
    if (func_02020e58((int *)(base + 8)) == 0) {
        int st;
        func_ov002_02069540();
        st = *(int *)(base + 0x134);
        switch (st) {
        case 1:
            func_ov002_0206ba28(*(int *)(base + 0x138));
            /* fall through */
        case 0:
            *(int *)(base + 0x8da8) = 0;
            result = (void *)func_ov002_02068dc4;
            break;
        case 2:
            result = (void *)func_ov002_02068058;
            break;
        }
    }
    return result;
}
