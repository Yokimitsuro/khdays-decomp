/* Drive the guard/counter sequence (x4: ov034 + 3 twins). While a sequence is live, refresh
 * it (020b5310) if either the owner is not blocked (bit 16 of the 64-bit flags at +0x464 is
 * clear AND ov022_02095524 says idle) or the override bit 38 is set. Then run the state:
 * 1 waits for mode 0x30 and a 0x6000 charge, then retunes channel 0xc6 and advances to 2;
 * 2 polls and clears when done; 3 requires mode 0x31 or 0x33 and advances to 4 past 0x12000;
 * 4 polls, then requires mode 0x31 and clears past 0x18000; 5 just polls. State 0 idles.
 *
 * ★ Two spellings are load-bearing:
 *  - The flags at +0x464 are a 64-BIT field and must be reached as a STRUCT MEMBER. The ROM
 *    reads both words with plain `ldr [r5,#0x464]` / `ldr [r5,#0x468]`; spelling it
 *    `*(unsigned long long *)(self + 0x464)` makes mwcc build the high word's address the long
 *    way (`add r0,r5,#0x64 ; ldr r0,[r0,#0x404]`) -- 2 instructions over. The tell that it IS
 *    64-bit is `and r0, r0, #0` on the high word: a mask whose high half is zero.
 *    Bit 16 = 0x10000 in the low word; bit 38 = 0x40 in the high word.
 *  - NO `default:` and NO `case 0:` -- state 0 and anything above 5 fall through the jump
 *    table to the function's implicit end, which is why the ROM's default and case-0 slots are
 *    bare `pop {r3,r4,r5,pc}` instructions. See codegen-cracks.md. */
struct Self { char pad[0x464]; unsigned long long flags; };

extern int func_ov022_02095524(void *p);
extern void func_ov090_020bc8b0(int self, int p2);
extern void func_ov022_020a4490(int self, int a, int b);
extern unsigned int func_0202a818(void *p, int a);

void func_ov090_020bc8bc(int self, int p2) {
    if (*(int *)(p2 + 0x24) != 0 &&
        (((((struct Self *)self)->flags & 0x10000ULL) == 0 &&
          func_ov022_02095524((void *)(self + 0x22f8)) == 0) ||
         (((struct Self *)self)->flags & 0x4000000000ULL) != 0)) {
        func_ov090_020bc8b0(self, p2);
    }
    switch (*(int *)(p2 + 0x24)) {
    case 1:
        if (*(int *)(self + 0x6bc) != 0x30) {
            *(int *)(p2 + 0x24) = 0;
            return;
        }
        if (*(int *)(self + 0x7b0) < 0x6000) {
            return;
        }
        func_ov022_020a4490(self, 0xc6, 0);
        *(int *)(p2 + 0x24) = 2;
        return;
    case 2:
        if (func_0202a818((void *)(p2 + 0x28), *(short *)(self + 0x2aba)) != 0) {
            *(int *)(p2 + 0x24) = 0;
        }
        return;
    case 3:
        if (*(int *)(self + 0x6bc) != 0x31 && *(int *)(self + 0x6bc) != 0x33) {
            *(int *)(p2 + 0x24) = 0;
            return;
        }
        if (*(int *)(self + 0x7b0) >= 0x12000) {
            *(int *)(p2 + 0x24) = 4;
        }
        return;
    case 4:
        if (func_0202a818((void *)(p2 + 0x28), *(short *)(self + 0x2aba)) == 0) {
            return;
        }
        if (*(int *)(self + 0x6bc) != 0x31) {
            *(int *)(p2 + 0x24) = 0;
            return;
        }
        if (*(int *)(self + 0x7b0) >= 0x18000) {
            *(int *)(p2 + 0x24) = 0;
        }
        return;
    case 5:
        func_0202a818((void *)(p2 + 0x28), *(short *)(self + 0x2aba));
        return;
    }
}
