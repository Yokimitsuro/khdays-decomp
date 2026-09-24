/* Trail draw of the ov052 enemy (twin of ov032 020b470c): the drawing key is the +0xae byte while bit 4 of the +8 flags is set
 * (else -1); only the four keys listed at +0x2e68 of the scene block draw. The current matrix is read
 * back (NNS_G3dGetCurrentMtx); the first key seeds the ten-point trail of the +0x2c part (+0x14c,
 * count +0x1c4, head +0x1c6) with the current translation and records it at the head slot, the later
 * keys take their translation from older slots (head - index, two and four more for the last two).
 * Both matrices are loaded back into the geometry engine (projection, then position), and the last
 * key advances the count and the ring head. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[4][3]; } MtxFx43;
typedef struct { int m[3][3]; } MtxFx33;
typedef struct {
    Vec3 pos[10];
    short count;
    signed char head;
} Trail;

extern void func_02016294(MtxFx43 *m, MtxFx33 *n);
extern void func_01ff9f00(int cmd, const void *words, int count);
extern char *data_ov052_020b80c0;

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov052_020b6f0c(char *self)
{
    MtxFx33 n;
    MtxFx43 m;
    u32 mode1;
    u32 mode2;
    u32 mode3;
    char *part;
    char *base;
    Trail *trail;
    int key;
    int found;
    int first;
    int last;
    int idx;
    int i;

    part = *(char **)(*(char **)(self + 4) + 0x2c);
    trail = (Trail *)(part + 0x14c);
    base = data_ov052_020b80c0;
    found = -1;
    key = (*(u32 *)(self + 8) & 0x10) ? *(u8 *)(self + 0xae) : -1;
    for (i = 0; i < 4; i++) {
        if (key == ((int *)base)[i + 0xb9a]) {
            found = i;
            break;
        }
    }
    if (found < 0) {
        return;
    }
    first = *(int *)(base + 0x2e68);
    last = *(int *)(base + 0x2e74);
    func_02016294(&m, &n);
    if (key == first && trail->count == 0) {
        for (i = 0; i < 10; i++) {
            VEC_Set(&trail->pos[i], m.m[3][0], m.m[3][1], m.m[3][2]);
        }
    }
    idx = trail->head - found;
    if (key == last - 1) {
        idx -= 2;
    }
    if (key == last) {
        idx -= 4;
    }
    if (idx < 0) {
        idx += 10;
    }
    if (trail->count > 0 && key > first) {
        m.m[3][0] = trail->pos[idx].x;
        m.m[3][1] = trail->pos[idx].y;
        m.m[3][2] = trail->pos[idx].z;
    }
    if (key == first) {
        VEC_Set(&trail->pos[idx], m.m[3][0], m.m[3][1], m.m[3][2]);
    }
    mode1 = 2;
    func_01ff9f00(0x10, &mode1, 1);
    func_01ff9f00(0x17, &n, 0xc);
    mode2 = 1;
    func_01ff9f00(0x10, &mode2, 1);
    func_01ff9f00(0x17, &m, 0xc);
    mode3 = 2;
    func_01ff9f00(0x10, &mode3, 1);
    if (key != last) {
        return;
    }
    trail->count++;
    trail->head++;
    if (trail->head >= 10) {
        trail->head = 0;
    }
}
