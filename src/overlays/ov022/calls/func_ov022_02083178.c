/* func_ov022_02083178 -- set up the ov022 object: run the kind handler (+0x3c, signed byte),
 * fill the three slots at +0x08..+0x10 from the table at data_ov022_020b2888, hand slot[0] to
 * func_ov022_02086638, then -- if func_ov002_0206d9b8 returns non-negative -- pass its result
 * plus the func_ov022_02083f0c handle to func_ov002_0204cc9c.
 *
 * This was parked for months as a "literal-pool word for an encodable immediate" tie: the ROM
 * materialises the 0 stored into data_0204be04 with `ldr r1,[pc]` plus a pool word, and the note
 * concluded mwcc would never spend a pool word on a 0. It does, and it does so here -- the
 * `adds r4, r0, #0` that captures the call result sets the flags that the `bmi` two instructions
 * later consumes, so the constant cannot be built with a flag-setting `movs`. That half was
 * already right in our output; the 4-byte gap was somewhere else entirely.
 *
 * The two real fixes:
 *   - `i` is UNSIGNED (`cmp r6,#3 ; blo`, not `blt`).
 *   - `obj` is used again AFTER the loop. Re-reading the global instead costs a second pool load
 *     plus a deref; keeping the local alive across the loop makes mwcc spill it to the frame slot
 *     the `push {r3,...}` already reserves, which is what the ROM's `str r0,[sp]` / `ldr r0,[sp]`
 *     pair is.
 * Lesson worth keeping: a park note that explains one instruction can be right about that
 * instruction and still be pointing at the wrong four bytes. */
typedef struct {
    char pad00[8];
    void *slot[3];    /* +0x08, +0x0c, +0x10 */
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
    unsigned int i;
    int r;

    func_ov002_020518ac(obj->kind);
    for (i = 0; i < 3; i++) {
        obj->slot[i] = func_02023930(data_ov022_020b2888[i], 0);
    }
    func_ov022_02086638(obj->slot[0], 1);
    r = func_ov002_0206d9b8();
    data_0204be04 = 0;
    if (r >= 0) {
        func_ov002_0204cc9c(func_ov022_02083f0c(), r, 0);
    }
}
