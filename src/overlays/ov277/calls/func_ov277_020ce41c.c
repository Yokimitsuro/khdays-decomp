/* Spawn of the ov244 leap entry: registers a 0x14-byte entry (func_0203c5c0, callbacks
 * ce4ac/ce590) holding the owner and the actor and places the owner at the actor's +0x3c8 item's
 * +0x14 point raised by 0x200 plus the actor's +0xb4 height. Returns the spawn result. */
struct vec { int x, y, z; };
extern int func_0203c5c0(int list, int a, int b, void *cb2, void *cb1, int **out);
extern void func_0203ca30(int dst, struct vec *src);
extern void func_ov277_020ce598(void);
extern void func_ov277_020ce4b4(void);

int func_ov277_020ce41c(int actor, int owner)
{
    int *entry;
    struct vec at;
    int r = func_0203c5c0(*(int *)(actor + 0x3c), 100, 0x14,
                          &func_ov277_020ce4b4, &func_ov277_020ce598, &entry);
    entry[0] = owner;
    entry[3] = actor;
    at = *(struct vec *)(*(int *)(entry[3] + 0x3c8) + 0x14);
    at.y = *(int *)(entry[3] + 0xb4) + 0x200;
    func_0203ca30(*entry + 4, &at);
    return r;
}
