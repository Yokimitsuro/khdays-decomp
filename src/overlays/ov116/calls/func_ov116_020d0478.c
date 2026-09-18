/* Spawn of the ov115 enemy's action entry (and its byte-identical twins): registers a 0x20-byte
 * entry (func_0203c5c0, callbacks cc8f8/cc994) holding the spawner, the owner actor and an
 * optional target, sets bit 2 of the owner's +0x5c flags and places the owner at the target's
 * +0x190 point (or its own +0x74 position without a target). Returns the spawn result. */
struct vec { int x, y, z; };
extern int func_0203c5c0(int list, int a, int b, void *cb2, void *cb1, int **out);
extern void func_0203ca30(int dst, struct vec *src);
extern void func_ov116_020d05d4(void);
extern void func_ov116_020d0538(void);

static inline void PlaceAt(int obj, struct vec at)
{
    func_0203ca30(obj + 4, &at);
}

int func_ov116_020d0478(int owner, int spawner, int target)
{
    int *entry;
    struct vec at;
    int r = func_0203c5c0(*(int *)(owner + 0x3c), 100, 0x20,
                          &func_ov116_020d0538, &func_ov116_020d05d4, &entry);
    entry[1] = owner;
    entry[0] = spawner;
    entry[2] = target;
    *(unsigned int *)(*entry + 0x5c) |= 4;
    at = entry[2] != 0 ? *(struct vec *)(entry[2] + 0x190) : *(struct vec *)(entry[1] + 0x74);
    PlaceAt(*entry, at);
    return r;
}
