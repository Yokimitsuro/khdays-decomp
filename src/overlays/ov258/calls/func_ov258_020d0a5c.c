/* Spawn an ov258 effect task (priority 100, 0x1c bytes, 020d0af4 / 020d0ba4): it keeps the owner,
 * the item and the start position (the item is placed there) and the kind byte at +0x1a; returns
 * the task handle. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct {
    int item;
    int owner;
    Vec3 pos;
    char pad14[6];
    u8 kind;
} Ov258Spawn;

extern int func_0203c5c0(int list, int prio, int size, void *cb, void *init, Ov258Spawn **out);
extern void func_0203ca30(int srt, Vec3 *pos);
extern void func_ov258_020d0af4(void);
extern void func_ov258_020d0ba4(void);

int func_ov258_020d0a5c(int owner, int item, Vec3 *pos, int kind)
{
    Ov258Spawn *spawn;
    Vec3 at;
    int handle;

    handle = func_0203c5c0(*(int *)(owner + 0x3c), 100, 0x1c, func_ov258_020d0af4, func_ov258_020d0ba4, &spawn);
    spawn->owner = owner;
    spawn->item = item;
    at = *pos;
    spawn->pos = *pos;
    func_0203ca30(spawn->item + 4, &at);
    spawn->kind = kind;
    return handle;
}
