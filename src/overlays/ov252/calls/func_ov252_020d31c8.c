/* Spawn an ov252 gem at `pos` for `owner` (0203c5c0: 0x64/0x40 node, tick 020d326c, class 020d3454):
 * it remembers the spawner, the owner and the point, its model moves there (0203ca30), and it keeps
 * its slot, its kind and a live flag. Returns the node handle. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct Gem { int owner; char *spawner; char pad8[4]; Vec3 pos; char pad18[0x1c]; u8 slot; u8 kind; u8 live; };

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cls, struct Gem **out);
extern void func_0203ca30(void *srt, const Vec3 *v);
extern void func_ov252_020d326c(void);
extern void func_ov252_020d3454(void);

int func_ov252_020d31c8(char *self, int owner, Vec3 *pos, signed char slot, u8 kind)
{
    struct Gem *gem;
    int handle;

    handle = func_0203c5c0(*(int *)(self + 0x3c), 0x64, 0x40, func_ov252_020d326c, func_ov252_020d3454, &gem);
    gem->spawner = self;
    gem->owner = owner;
    gem->pos = *pos;
    func_0203ca30((void *)(gem->owner + 4), pos);
    gem->slot = slot;
    gem->kind = kind;
    gem->live = 1;
    return handle;
}
