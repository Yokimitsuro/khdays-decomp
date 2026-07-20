/* UNFINISHED. 96 vs 100 bytes -- exactly one literal-pool word short.
 *
 * Sets up the ov022 object: run the kind handler (+0x3c, signed byte), fill the
 * three slots at +0x08..+0x10 from the table at data_ov022_020b2888, hand slot[0]
 * to 02086638, then -- if 0206d9b8 returns non-negative -- pass its result plus
 * the 02083f0c handle to Ov002_SetValueAndDerive.
 *
 * WHAT DIFFERS: the ROM materialises the 0 stored into data_0204be04 with
 *   ldr r1,[pc,#0x1c]   + a pool word 00000000
 * where mwcc 3.0/139 emits `movs r1,#0`.  0 is an encodable THUMB immediate, so
 * the compiler never spends a pool word on it; that word is the whole 4-byte gap.
 *
 * VERIFIED it really is a literal and not a symbol: the pool entry at +0x5c has
 * NO RELOC (the function's nine relocs are all elsewhere).  A reloc there would
 * have meant a symbol whose value happens to be 0, which is the one way this
 * could have been fixable.  It is the same tie as its neighbour
 * func_ov022_02083bd8, which was checked the same way and also holds.
 *
 * Everything else is byte-exact, so the C below is correct and readable -- the
 * three slots really are an array, and the flags on the r4 test come from the
 * `adds r4, r0, #0` that survives the intervening ldr/strb.
 */
typedef struct {
    char pad00[8];
    void *slot[3];   /* +0x08, +0x0c, +0x10 */
    char pad14[0x28];
    signed char kind; /* +0x3c */
} Ov022Obj;

extern Ov022Obj *data_ov022_020b2e60;
extern int data_ov022_020b2888[];
extern unsigned char data_0204be04;

extern void func_ov002_020518ac(int kind);
extern void *func_02023930(int a, int b);
extern void func_ov022_02086638(void *p, int a);
extern int func_ov002_0206d9b8(void);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cc9c(int owner, int value, int unused);

void func_ov022_02083178(void) {
    Ov022Obj *obj = data_ov022_020b2e60;
    int i;
    int r;

    func_ov002_020518ac(obj->kind);
    for (i = 0; i < 3; i++) {
        obj->slot[i] = func_02023930(data_ov022_020b2888[i], 0);
    }
    func_ov022_02086638(data_ov022_020b2e60->slot[0], 1);
    r = func_ov002_0206d9b8();
    data_0204be04 = 0;
    if (r >= 0) {
        func_ov002_0204cc9c(func_ov022_02083f0c(), r, 0);
    }
}
