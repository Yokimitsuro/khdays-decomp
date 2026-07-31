/*
 * Ov002_TeardownGameplayScene - gameplay scene teardown handler (returned by
 * Ov002_TickGameplayState). Tears the gameplay slice down and returns the next scene handler.
 *
 * No-op (NULL) while the global busy byte data_0204be04 is set, or until func_ov002_020735bc
 * and Ov002_ClosePause (func_ov002_02069d10) both report ready. For local player 0 with a
 * non-negative flag at heap+0x8d78 it refreshes the active mask from the slot table. It then
 * notifies func_ov002_0206bbb8 for each set bit of the heap+0x8c8a mask (and clears it), ends
 * key sharing, destroys the pause object, closes key sharing, releases resources, and issues the
 * deferred-draw release (func_02020cf8(-1) returns the u64 fed straight into func_0202ded8).
 * If an overlay class is loaded (heap+0x8b4c != -1) it calls its +0x38 method, unloads the
 * overlay (heap+0x8b50) and marks it gone; frees the heap+0x8dbc buffer if any. Finally, when
 * heap+0x8bb4 is -1 it runs func_ov002_020697cc/func_0202b788 and hands off to
 * func_ov002_02068f7c, otherwise it enqueues command 0x14 and hands off to func_ov002_02068698.
 *
 * THUMB, void(void): the caller's r0-r3 are not used (the deferred-draw call takes only the u64
 * from func_02020cf8, whose arg is -1 via mvn, not 0xff). rec=heap+0x8ba8 is spilled to the
 * stack for the final heap+0x8bb4 test; the final branch is written else-first so the -1 arm is
 * the branch target.
 */

typedef unsigned char u8;
typedef unsigned int  u32;
typedef void (*CodeFn)(void);

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_ov002_020735bc(void);
extern int  func_ov002_02069d10(void);
extern int  func_02030788(void);
extern int  func_ov022_02088474(int a);
extern int  func_ov002_02072754(int a);
extern void func_ov002_0207669c(int a);
extern void func_ov002_0206bbb8(int a, int b, int c);
extern void func_ov002_02069844(void);
extern void func_ov002_02069ca4(void);
extern void func_ov002_0206a098(void);
extern void func_ov002_020736c0(void);
extern long long func_02020cf8(int a);
extern void func_0202ded8(int a, int b);
extern void func_0201e4a8(int a, int b);
extern void NNSi_FndFreeFromDefaultHeap(int p);
extern void func_020336a4(int a);
extern void func_ov002_020697cc(void);
extern void func_0202b788(void);
extern void func_ov002_02068698(void);
extern void func_ov002_02068f7c(void);
extern u8   data_0204be04;

void *func_ov002_02068e68(void)
{
    int base = NNSi_FndGetCurrentRootHeap();
    int rec = base + 0x8ba8;
    void *result;
    u32 i;

    if (data_0204be04 != 0) return 0;
    if (func_ov002_020735bc() == 0) return 0;
    if (func_ov002_02069d10() == 0) return 0;
    if (func_02030788() == 0 && *(char *)(base + 0x8d78) >= 0) {
        int x = func_ov022_02088474(0);
        u32 b = func_ov002_02072754(x);
        func_ov002_0207669c(b & 0xffff);
    }
    i = 0;
    do {
        if (*(u8 *)(base + 0x8c8a) & (1 << i)) {
            func_ov002_0206bbb8(i, 1, 1);
        }
        i++;
    } while ((int)i < 4);
    *(u8 *)(base + 0x8c8a) = 0;
    func_ov002_02069844();
    func_ov002_02069ca4();
    func_ov002_0206a098();
    func_ov002_020736c0();
    {
        long long v = func_02020cf8(-1);
        func_0202ded8((int)v, (int)((unsigned long long)v >> 0x20));
    }
    if (*(int *)(base + 0x8b4c) != -1) {
        (**(CodeFn *)(base + 0x8b84))();
        func_0201e4a8(0, *(int *)(base + 0x8b50));
        *(int *)(base + 0x8b4c) = -1;
    }
    if (*(int *)(base + 0x8dbc) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(base + 0x8dbc));
        *(int *)(base + 0x8dbc) = 0;
    }
    if (*(int *)(rec + 0xc) != -1) {
        func_020336a4(0x14);
        result = (void *)func_ov002_02068698;
    } else {
        func_ov002_020697cc();
        result = (void *)func_ov002_02068f7c;
        func_0202b788();
    }
    return result;
}
