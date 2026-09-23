/* Spawn an ov256 shard task (020d0d18 / 020d0e44, 0x20 bytes) under the owner's +0x3c scene: it
 * records the owner and `model`, starts at `pos` (+0xc) and the model is placed there. Returns the
 * task. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_ov256_020d0d18(void);
extern void func_ov256_020d0e44(void);

int func_ov256_020d0c8c(int owner, int model, Vec3 *pos)
{
    int *entry;
    Vec3 at;
    int task = func_0203c5c0(*(int *)(owner + 0x3c), 100, 0x20, func_ov256_020d0d18, func_ov256_020d0e44, &entry);

    entry[1] = owner;
    entry[0] = model;
    at = *pos;
    *(Vec3 *)(entry + 3) = *pos;
    func_0203ca30((void *)(entry[0] + 4), &at);
    return task;
}
