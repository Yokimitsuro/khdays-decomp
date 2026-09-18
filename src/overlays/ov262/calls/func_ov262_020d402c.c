/* Grab-slot search of the ov261 enemy (and its byte-identical twin): for a slot id below 0x80,
 * clears bit 16-23 of every +0x3a0 list entry's +0x18 word, picks the entry whose +0x2c point is
 * nearest the +4 position into the +0x48 byte, and runs the recursive path search from it with
 * a fresh 16-entry order buffer (depth limit 0x3e7), the +0x49 order table and a depth counter;
 * returns the search result, 0 for an invalid id. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Vecx32 { int x, y, z; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_ov262_020d4130(int *state, int slot, u16 *order, unsigned int id, u8 depth, u16 *out, int *limit);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

int func_ov262_020d402c(int *state, unsigned int id)
{
    u16 order[16];
    struct Vecx32 d;
    int limit;
    int i;
    int best;
    int list;
    int dist;

    limit = 0x3e7;
    best = 0x7fffffff;
    if (id >= 0x80) {
        return 0;
    }
    list = *(int *)(*state + 0x3a0);
    for (i = 0; i < *(int *)(list + 0x14); i++) {
        *(unsigned int *)(list + 0x18 + i * 0x24) &= 0xff00ffff;
        VEC_Subtract((void *)(*(int *)(*state + 0x3a0) + 0x2c + i * 0x24), (void *)state[1], &d);
        dist = (int)(((long long)d.x * d.x + (long long)d.y * d.y + (long long)d.z * d.z + 0x800) >> 12);
        if (dist < best) {
            *(u8 *)(state + 0x12) = (u8)i;
            best = dist;
        }
        list = *(int *)(*state + 0x3a0);
    }
    return func_ov262_020d4130(state, *(u8 *)(state + 0x12), order, id, 0, (u16 *)((char *)state + 0x49), &limit);
}
