/* func_ov107_020c1370 -- broadcast a positioning update to every entry of a
 * target list, per self->mode:
 *   0: no repositioning, just refresh + notify each entry.
 *   1: scatter each entry to a random point in the square
 *      [-spread/2, +spread/2] around self->pos on x and z (y is copied
 *      through unchanged).
 *   2/3/4: line the entries up along a world axis (X/Y/Z respectively),
 *      spaced by a step derived from func_02020400(self->spread, total);
 *      modes 2 and 4 start half a spread back from self->pos, mode 3 starts
 *      exactly at self->pos.
 *   5: arrange the entries evenly around a circle of radius self->spread/2
 *      centred on self->pos, using the angle table data_0203d210.
 * Bails out immediately if the target list's count (list->total) is 0,
 * regardless of mode.
 *
 * MATCH NOTE (mode 1): the range width is computed once before the loop with
 * RangeWidth(), a subtraction on its own parameter. That is the only form found
 * that gives the ROM's `add r6, r7, r7`: `half * 2`, `half + half` and a fresh
 * `span = hi - lo` all emit `lsl`, and a width computed inside the loop's
 * roll helper hoists `-half` ahead of the width. Tentative reconstruction of
 * how the original split its random-in-range routine. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int x, y, z;
} VecFx32;

typedef struct TargetList {
    u8  pad00[0x20];
    int total;      /* +0x20 */
} TargetList;

typedef struct Entry Entry;
struct Entry {
    u8 pad000[0x1cc];
    void (*onEvent)(Entry *self, int mode); /* +0x1cc */
};

typedef struct Self {
    u8      pad000[0x4a];
    u16     mode;        /* +0x4a */
    u8      pad04c[0x104 - 0x4c];
    VecFx32 pos;          /* +0x104 */
    u8      pad110[0x118 - 0x110];
    int     spread;       /* +0x118 */
} Self;

extern void        *func_01fffd70(void *list);
extern void        *func_01fffd8c(void *list);
extern void         func_ov107_020c5c54(char *node, VecFx32 *v);
extern int           func_02023eb4(int range);
extern void          func_01ffa724(int factor, VecFx32 *src, VecFx32 *dst);
extern void          VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int           func_02020400(int a, int b);

extern VecFx32      data_02042270;
extern VecFx32      data_02042264;
extern VecFx32      data_02042258;
extern const short   data_0203d210[];

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))
#define ANGLE_TO_INDEX(angle) \
    ((int)(((unsigned)(((long long)(int)(unsigned)(angle) * 0x28be60db9391LL + \
           0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4)

/* Width of the range [lo, hi]. */
static inline int RangeWidth(int lo, int hi)
{
    hi -= lo;
    return hi;
}

/* Random value in [lo, lo + |span|]. */
static inline int RandSpan(int lo, int span)
{
    return lo + func_02023eb4((span < 0 ? -span : span) + 1);
}

void func_ov107_020c1370(Self *self, TargetList *list)
{
    int total;
    int half;
    u16 mode;
    void *node;

    total = list->total;
    half = self->spread >> 1;
    if (total == 0)
        return;

    mode = self->mode;
    switch (mode) {
    case 0: {
        node = func_01fffd70(list);
        while (node != 0) {
            Entry *entry = *(Entry **)node;
            func_ov107_020c5c54((char *)entry, &self->pos);
            if (entry->onEvent)
                entry->onEvent(entry, 0);
            node = func_01fffd8c(list);
        }
        break;
    }
    case 1: {
        Entry *entry;
        VecFx32 pos;
        node = func_01fffd70(list);
        if (node != 0) {
            int span = RangeWidth(-half, half);

            do {
                entry = *(Entry **)node;
                pos.x = self->pos.x + RandSpan(-half, span);
                pos.y = self->pos.y;
                pos.z = self->pos.z + RandSpan(-half, span);

                func_ov107_020c5c54((char *)entry, &pos);
                if (entry->onEvent)
                    entry->onEvent(entry, 0);
                node = func_01fffd8c(list);
            } while (node != 0);
        }
        break;
    }
    case 2:
    case 3:
    case 4: {
        VecFx32 start;
        VecFx32 step;
        int factor;

        if (mode == 2) {
            func_01ffa724(-half, &data_02042270, &start);
            VEC_Add(&self->pos, &start, &start);
            factor = func_02020400(self->spread, total);
            func_01ffa724(factor, &data_02042270, &step);
        } else if (mode == 3) {
            start = self->pos;
            factor = func_02020400(self->spread, total);
            func_01ffa724(factor, &data_02042264, &step);
        } else if (mode == 4) {
            func_01ffa724(-half, &data_02042258, &start);
            VEC_Add(&self->pos, &start, &start);
            factor = func_02020400(self->spread, total);
            func_01ffa724(factor, &data_02042258, &step);
        }

        node = func_01fffd70(list);
        while (node != 0) {
            Entry *entry = *(Entry **)node;
            func_ov107_020c5c54((char *)entry, &start);
            VEC_Add(&start, &step, &start);
            func_ov107_020c5c54((char *)entry, &start);
            if (entry->onEvent)
                entry->onEvent(entry, 0);
            node = func_01fffd8c(list);
        }
        break;
    }
    case 5: {
        node = func_01fffd70(list);
        if (node != 0) {
            Entry *entry;
            int angle = 0;
            do {
                entry = *(Entry **)node;
                int raw = func_02020400(angle, total);
                int idx = ANGLE_TO_INDEX(raw);
                int cosv = data_0203d210[idx * 2];
                int sinv = data_0203d210[idx * 2 + 1];
                VecFx32 pos;
                pos.x = self->pos.x + FX_MUL(cosv, half);
                pos.y = self->pos.y;
                pos.z = self->pos.z + FX_MUL(sinv, half);
                func_ov107_020c5c54((char *)entry, &pos);
                if (entry->onEvent)
                    entry->onEvent(entry, 0);
                angle += 0x6488;
                node = func_01fffd8c(list);
            } while (node != 0);
        }
        break;
    }
    default:
        break;
    }
}
