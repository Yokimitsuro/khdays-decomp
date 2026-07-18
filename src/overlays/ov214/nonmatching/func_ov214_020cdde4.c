/* NONMATCHING -- 320/320 B. Structure and constants are right; what remains is register
 * COLOURING: mwcc spends a callee-saved (r6) where the ROM uses scratch (ip for the umull
 * low half, r3 for the table pointer), plus one scheduling swap around `adds ip,ip,#0`.
 *
 * Head of a 5-member family (320 B).
 *
 * SOLVED here -- do NOT rediscover:
 *  - the Q12 radians -> 16-bit angle conversion is the documented form from
 *    codegen-cracks.md, and it reproduced the whole 64-bit multiply block first try:
 *        idx = (unsigned short)(((long long)rad * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
 *    with sin/cos read as data_0203d210[idx*2] and [idx*2+1].
 *  - `data_02041dc8` is passed to func_ov107_020c0b90 TWICE, and the ROM copies it to a
 *    STACK TEMPORARY once and passes that. Passing the global directly is 12 B of frame
 *    short (0x14 vs 8). Same crack as ov147_020cc00c.
 *
 * Ruled out for the r6/ip colouring: `z` in an inner block vs at function scope, `idx`
 * declared as unsigned short (that one is 4 B LONG), and inlining the func_02023f08 call
 * instead of holding `rad`. */
struct vec { int x, y, z; };
extern void func_ov107_020c9264(int owner, int mode, int b);
extern int  func_02023f08(void);
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern int  func_02023eb4();
extern void func_0203c634(int self, int index, void *cb);
extern short data_0203d210[];
extern struct vec data_02041dc8;
extern void func_ov214_020cdf24(void);

void func_ov214_020cdde4(int self) {
    int *obj = *(int **)(self + 4);
    int rad;
    int idx;
    struct vec z;

    func_ov107_020c9264(*obj, 6, 0);
    rad = func_02023f08();
    idx = (unsigned short)(((long long)rad * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    obj[5] = data_0203d210[idx * 2];
    obj[6] = 0;
    obj[7] = data_0203d210[idx * 2 + 1];
    z = data_02041dc8;
    func_ov107_020c0b90(*obj, 2, z, 0);
    func_ov107_020c0b90(*obj, 4, z, 0);
    *(signed char *)((int)obj + 0x70) = 0;
    *(signed char *)((int)obj + 0x71) = 0;
    *(signed char *)((int)obj + 0x73) = 0;
    *(signed char *)((int)obj + 0x6e) = 0;
    *(signed char *)((int)obj + 0x6f) = (signed char)(func_02023eb4(0xb) + 0x14);
    *(signed char *)((int)obj + 0x74) = 0;
    obj[0x16] = 0;
    obj[0x1e] = 0;
    obj[0x17] = 0x5000;
    obj[0x18] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov214_020cdf24);
}
