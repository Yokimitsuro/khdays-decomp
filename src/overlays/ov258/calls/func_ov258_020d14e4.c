/* Spawn an ov258 marker effect: a 0x18-byte node (0203c5c0 on the +0x3c model, start 020d1564, end
 * 020d15f4) holds the owner, the effect rig and the position; the rig is moved there (0203ca30).
 * Returns the node handle. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203c5c0(int model, int a, int size, void *start, void *end, int **out);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_ov258_020d1564(void);
extern void func_ov258_020d15f4(void);

int func_ov258_020d14e4(char *self, int rig, Vec3 *pos)
{
    int *state;
    int handle;

    handle = func_0203c5c0(*(int *)(self + 0x3c), 100, 0x18, func_ov258_020d1564, func_ov258_020d15f4, &state);
    state[0] = (int)self;
    state[1] = rig;
    *(Vec3 *)(state + 2) = *pos;
    func_0203ca30((void *)(state[1] + 4), pos);
    return handle;
}
