typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Entry {
    char pad_0000[8];
    VecFx32 pos;
} Entry;

typedef struct Hit {
    char pad_0000[0xc];
    int distance0c;
} Hit;

extern Entry *func_0202b0a4(void *cont);
extern Hit *func_01fff920(void *world, VecFx32 *from, VecFx32 *dir);
extern void func_01ffd0e8(int s, const VecFx32 *dir, const VecFx32 *from, VecFx32 *out);

int func_0202b0b8(void *cont, int p3, void *out) {
    Entry *entry = func_0202b0a4(cont);
    VecFx32 from;
    VecFx32 dir;
    Hit *hit;

    from.x = entry->pos.x;
    from.y = entry->pos.y + 0x1000;
    from.z = entry->pos.z;
    dir.x = 0;
    dir.y = -0x5000;
    dir.z = 0;

    hit = func_01fff920(cont, &from, &dir);
    if (hit != 0) {
        func_01ffd0e8(hit->distance0c, &dir, &from, (VecFx32 *)out);
        return 1;
    }
    *(VecFx32 *)out = entry->pos;
    return 0;
}
