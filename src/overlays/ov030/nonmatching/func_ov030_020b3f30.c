/* NONMATCHING: equivalent C, global callee-saved coloring-direction tie
 * (count=5, 208B). Logic/structure/size byte-exact, but mwcc assigns the
 * callee-saved regs in the opposite direction: orig i->r5/slot->r6/acc7->r7/
 * acc8->r8 (earlier-defined -> higher), mwcc gives acc8->r5/i->r6/slot->r8.
 * 54 bytes differ, all register numbers. No C form flips it (decl order,
 * ptr-vs-int walker, single-vs-two-var loop). Same class as ov127/ov142.
 * Semantics: for i in 0..3: scan up to 8 slots at this+0x234 (stride 0x170)
 * for the first with byte[+0x12c]==0; init that slot (0x148/0x14c=0, 0x150/
 * 0xb0/0xb4/0xb8=0x1000, 0x138=obj->0x490, 0x154=0xa000, 0x158=0x119a, 0x15c=
 * (s16)obj->0x66, 0x12c=1, 0x130=0, 0x134=i*0x2000, 0x15e=i*0x3fff), call
 * func_ov030_020b4048 mid-init and func_ov030_020b4024 at end. */
extern void func_ov030_020b4048(int slot);
extern void func_ov030_020b4024(int slot);

void func_ov030_020b3f30(int this_) {
    int obj = *(int *)(this_ + 0xdb4);
    int i;
    int acc7 = 0;
    int acc8 = 0;

    for (i = 0; i < 4; i++) {
        char *p = (char *)(this_ + 0x234);
        int slot;
        int j;
        for (j = 0; j < 8; j++) {
            slot = (int)p;
            if (*(unsigned char *)(p + 0x12c) == 0) break;
            p += 0x170;
        }
        *(int *)(slot + 0x148) = 0;
        *(int *)(slot + 0x14c) = 0;
        *(int *)(slot + 0x150) = 0x1000;
        func_ov030_020b4048(slot);
        *(int *)(slot + 0xb8) = 0x1000;
        *(int *)(slot + 0xb4) = 0x1000;
        *(int *)(slot + 0xb0) = 0x1000;
        *(int *)(slot + 0x138) = *(int *)(obj + 0x490);
        *(int *)(slot + 0x154) = 0xa000;
        *(int *)(slot + 0x158) = 0x119a;
        *(signed char *)(slot + 0x15c) = *(short *)(obj + 0x66);
        *(unsigned char *)(slot + 0x12c) = 1;
        *(int *)(slot + 0x130) = 0;
        *(int *)(slot + 0x134) = acc7;
        *(unsigned short *)(slot + 0x15e) = acc8;
        func_ov030_020b4024(slot);
        acc7 += 0x2000;
        acc8 += 0x3fff;
    }
}
