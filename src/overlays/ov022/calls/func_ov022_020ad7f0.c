/* Read a slot's position: if bit 2 of the slot's flag word is clear, copy the vec3 at +0x4c out;
 * otherwise answer the zero vector.
 *
 * Parked as a scheduling tie -- the original materialises the slot address INSIDE the taken
 * branch, using register-offset addressing for the flag read, while mwcc hoisted the add above
 * the test. Declaring the slots as a real array of structs is what reproduces it: the flag read
 * becomes `[base, idx*0x58]` with no add of its own, and the add only appears where the vec3
 * copy needs a base to reach +0x4c from. */
typedef struct { int a, b, c; } Vec3i;

struct Ov022Slot {
    unsigned int uFlags;        /* +0x00, bit 2 = no position */
    char _pad4[0x4c - 4];
    Vec3i pos;                  /* +0x4c */
    char _pad58[0x58 - 0x58];
};

void func_ov022_020ad7f0(int self, int idx, Vec3i *out) {
    struct Ov022Slot *slots = *(struct Ov022Slot **)(self + 0x2684);
    if ((slots[idx].uFlags & 4) == 0) {
        *out = slots[idx].pos;
        return;
    }
    out->c = 0;
    out->b = 0;
    out->a = 0;
}
