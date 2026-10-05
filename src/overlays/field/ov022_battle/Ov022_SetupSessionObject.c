/* Ov022_SetupSessionObject -- set up the ov022 object: run the kind handler (+0x3c, signed byte),
 * fill the three slots at +0x08..+0x10 from the table at data_ov022_020b2888, hand slot[0] to
 * Ov022_SetBit3OnPtr20, then -- if Ov002_GetRootField8d68 returns non-negative -- pass its result
 * plus the func_ov022_02083f0c handle to Ov002_SetValueAndDerive.
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

extern int Ov002_InstantiateSceneClass(int first, ...);
extern void *InstantiateClass(int a, int b);
extern void Ov022_SetBit3OnPtr20(void *p, int a);
extern int Ov002_GetRootField8d68(void);
extern int func_ov022_02083f0c(void);
extern void Ov002_SetValueAndDerive(int owner, int value, int unused);

void Ov022_SetupSessionObject(void) {
    Ov022Obj *obj = data_ov022_020b2e60;
    unsigned int i;
    int r;

    Ov002_InstantiateSceneClass(obj->kind);
    for (i = 0; i < 3; i++) {
        obj->slot[i] = InstantiateClass(data_ov022_020b2888[i], 0);
    }
    Ov022_SetBit3OnPtr20(obj->slot[0], 1);
    r = Ov002_GetRootField8d68();
    data_0204be04 = 0;
    if (r >= 0) {
        Ov002_SetValueAndDerive(func_ov022_02083f0c(), r, 0);
    }
}
