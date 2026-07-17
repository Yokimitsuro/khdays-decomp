/* Drive the swing sequence (x4: ov038 + 3 twins). While a sequence is live, refresh it
 * (020b42f4) when the owner has left mode 0x2e, is not blocked (bit 16 of the 64-bit flags at
 * +0x464) and reports idle -- and refresh it AGAIN, unconditionally of all that, when the
 * override bit 38 is set. Then run the state: 1 polls and, when done, switches the set to 1;
 * 2 polls and switches to 3; 3 just polls; 4 aborts to set 0 unless the owner is in mode 0x30.
 * State 0 idles.
 *
 * The flags at +0x464 are a 64-BIT field reached as a struct member (bit 16 in the low word,
 * bit 38 = 0x40 in the high). The tell is `and r0, r0, #0` on the high word. Spelling it
 * `*(unsigned long long *)(self + 0x464)` costs 2 instructions -- see codegen-cracks.md.
 *
 * NO `default:` and NO `case 0:` -- both fall through the jump table to the implicit end,
 * which is why those two slots hold bare `pop {r4,r5,r6,pc}` instructions. Matched byte-exact
 * on the first compile with both spellings in place. */
struct Self { char pad[0x464]; unsigned long long flags; };

extern int func_ov022_02095524(void *p);
extern void func_ov057_020b6af4(int self, int *p);
extern unsigned int func_0202a818(void *p, int a);
extern void func_ov057_020b6a34(int self, int *p, int mode);

void func_ov057_020b6b00(int self, int *p, int p3) {
    if (*p != 0) {
        if (*(int *)(self + 0x6bc) != 0x2e &&
            (((struct Self *)self)->flags & 0x10000ULL) == 0 &&
            func_ov022_02095524((void *)(self + 0x22f8)) == 0) {
            func_ov057_020b6af4(self, p);
        }
        if ((((struct Self *)self)->flags & 0x4000000000ULL) != 0) {
            func_ov057_020b6af4(self, p);
        }
    }
    switch (*p) {
    case 1:
        if (func_0202a818((char *)p + 4, p3) != 0) {
            func_ov057_020b6a34(self, p, 1);
        }
        return;
    case 2:
        if (func_0202a818((char *)p + 4, p3) != 0) {
            func_ov057_020b6a34(self, p, 3);
        }
        return;
    case 3:
        func_0202a818((char *)p + 4, p3);
        return;
    case 4:
        if (*(int *)(self + 0x6bc) != 0x30) {
            func_ov057_020b6a34(self, p, 0);
        }
        return;
    }
}
