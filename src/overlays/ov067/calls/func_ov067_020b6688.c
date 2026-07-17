/* Drive the charge sequence (x4: ov048 + 3 twins). If a sequence is running but the owner
 * has left mode 0x2f, abort it. Otherwise tick the phase timer (except in the final state 4)
 * and run the current state: 1 waits for the timer to go non-negative, then plays step 0 and
 * advances; 2 polls the emitter and, past 0xf000, plays step 1, retunes channel 0xd5 to 2 and
 * advances; 3 does the same past 0xf000 but only once the owner reports ready
 * (ov022_02095554), playing step 2 and retuning to 3; 4 just polls.
 *
 * NO `default:` and NO `case 0:` -- state 0 and anything above 4 fall through the jump table
 * to the function's implicit end, which is why the ROM's table slots for the default and for
 * case 0 are bare `pop {r3,r4,r5,pc}` instructions rather than branches. See
 * codegen-cracks.md. Matched byte-exact on the first compile with that shape. */
extern void func_ov067_020b6850(int p2, int a);
extern unsigned int func_0202a818(void *p, int a);
extern void func_ov022_020a4490(int self, int a, int b);
extern int func_ov022_02095554(void *p);

void func_ov067_020b6688(int self, int p2, int p3) {
    if (*(int *)(p2 + 0x358) != 0 && *(int *)(self + 0x6bc) != 0x2f) {
        *(int *)(p2 + 0x358) = 0;
    }
    if (*(int *)(p2 + 0x358) == 0) {
        return;
    }
    if (*(int *)(p2 + 0x358) != 4) {
        *(int *)(p2 + 0x35c) += p3;
    }
    switch (*(int *)(p2 + 0x358)) {
    case 1:
        if (*(int *)(p2 + 0x35c) < 0) {
            return;
        }
        func_ov067_020b6850(p2, 0);
        *(int *)(p2 + 0x358) = 2;
        *(int *)(p2 + 0x35c) = 0;
        return;
    case 2:
        func_0202a818((void *)(p2 + 0x24c), p3);
        if (*(int *)(p2 + 0x35c) < 0xf000) {
            return;
        }
        func_ov067_020b6850(p2, 1);
        func_ov022_020a4490(self, 0xd5, 2);
        *(int *)(p2 + 0x358) = 3;
        *(int *)(p2 + 0x35c) = 0;
        return;
    case 3:
        func_0202a818((void *)(p2 + 0x24c), p3);
        if (*(int *)(p2 + 0x35c) < 0xf000) {
            return;
        }
        if (func_ov022_02095554((void *)(self + 0x22f8)) == 0) {
            return;
        }
        func_ov067_020b6850(p2, 2);
        func_ov022_020a4490(self, 0xd5, 3);
        *(int *)(p2 + 0x358) = 4;
        *(int *)(p2 + 0x35c) = 0;
        return;
    case 4:
        func_0202a818((void *)(p2 + 0x24c), p3);
        return;
    }
}
