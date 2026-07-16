/* NONMATCHING: 412B vs 416B -- 415 of 416 bytes are byte-identical; exactly ONE instruction
 * differs, and it is the pure register-allocator form of the known address-rematerialisation tie
 * (see references/deferred-ties.md). At the two scene-slot stores the ROM emits:
 *     add r1,r4,#0x5000 ; str r0,[r1,#0x6c]
 *     add r0,r4,#0x5000 ; mov r1,#0 ; str r1,[r0,#0x70] ; str r1,[r4]
 * i.e. it parks the constant 0 in r1 (live across both stores) and REMATERIALISES the base into
 * r0. mwcc 3.0/139 instead keeps the base in r1 and puts the 0 in r0, so it needs no second `add`.
 * Same stores, same order, same offsets -- only which value the allocator chose to keep live.
 * Not expressible in C: tried the second store as a raw `*(int*)((int)heap + 0x5070)` (still
 * CSE'd) and reordering. This is the cleanest isolated instance of the tie found so far, and it
 * shows retail's compiler rematerialises addresses where 3.0/139 CSEs them.
 *
 * func_ov000_0204ef84 -- ov000 boot step: wait out the intro fade, then bring up the sub screen
 * and hand off to the first scene.
 * While the frame counter (heap[0]) is still below 0x11 it just steps the fade
 * (func_0201e3cc(-n)) and returns 0. Once past it, it programs the four sub-screen BG control
 * registers (0x04001008..) with priorities 2/3/1/0 and char/screen bases 0x4004/0x4204/0x4404/
 * 0x0604, enables the BG bits in REG_DISPCNT_SUB, resets the text engine at heap+0x1b0, kicks the
 * fade to -0x10, and instantiates the first scene class (data_ov000_0205aa34) -- on a resume boot
 * (heap+0x4c31 == 1) with the saved slot's id + 1, otherwise with 0. Returns the next step
 * func_ov000_0204f124. */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void func_02023d70(int p, int a, int b, int c, int d);
extern void func_0202aa9c(unsigned short *p);
extern void func_0201e3cc(int n);
extern void func_02032494(int *p);
extern void func_0203255c(int *p);
extern void func_0203253c(int p);
extern void func_02032428(int *p);
extern int  func_02023930(int class_desc, int arg);   /* InstantiateClass */
extern int  data_ov000_0205aa34;
extern void func_ov000_0204f124(void);

int func_ov000_0204ef84(void) {
    int *heap = (int *)NNSi_FndGetCurrentRootHeap();
    volatile unsigned short *bg = (volatile unsigned short *)0x04001008;
    int inst;

    func_02023d70((int)(heap + 0x45), 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
    func_0202aa9c((unsigned short *)(heap + 3));

    if (*heap <= 0x10) {
        func_0201e3cc(-*heap);
    } else {
        short base = 0x4004;
        bg[0] = bg[0] & 0x43 | base;
        bg[1] = bg[1] & 0x43 | (base + 0x200);
        bg[2] = bg[2] & 0x43 | (base + 0x400);
        bg[3] = bg[3] & 0x43 | (base - 0x3a00);
        *(volatile unsigned int *)0x04001000 =
            *(volatile unsigned int *)0x04001000 & ~0x1f00 | 0x1f00;
        bg[1] = bg[1] & ~3 | 3;
        bg[0] = bg[0] & ~3 | 2;
        bg[2] = bg[2] & ~3 | 1;
        bg[3] = bg[3] & ~3;

        func_02032494(heap + 0x6c);
        func_0203255c(heap + 0x6c);
        func_0203253c((int)(heap + 0x6c));
        func_02032428(heap + 0x6c);
        func_0201e3cc(-0x10);

        if (*(char *)((int)heap + 0x4c31) == 1) {
            inst = func_02023930((int)&data_ov000_0205aa34,
                                 *(char *)((int)heap + *(char *)((int)heap + 0x4c2d) + 0x4c2e) + 1);
        } else {
            inst = func_02023930((int)&data_ov000_0205aa34, 0);
        }
        heap[0x141b] = inst;
        heap[0x141c] = 0;
        *heap = 0;
        return (int)func_ov000_0204f124;
    }
    *heap = *heap + 1;
    return 0;
}
