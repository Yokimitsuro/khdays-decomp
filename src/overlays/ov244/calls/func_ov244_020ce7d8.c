/* Spawn of the ov244 pounce entry: registers a 0x14-byte entry (func_0203c5c0, callbacks
 * cebd8/cec70) linking the actor (entry[1]) and the owner (entry[0]); when the actor's +0x50
 * kind is 1 the owner gets the ce8bc handler at +0x74 and a back-link at +0x84; the owner is
 * then placed at the actor's +0x3cc item's +0x14 point raised by 0x200 plus the actor's +0xb4
 * height, with entry[3] holding its "DM002" joint handle. Returns the spawn result. */
struct vec { int x, y, z; };
extern int func_0203c5c0(int list, int a, int b, void *cb2, void *cb1, int **out);
extern int func_0203bdfc(int owner, const char *name);
extern void func_0203ca30(int dst, struct vec *src);
extern void func_ov244_020cec70(void);
extern void func_ov244_020cebd8(void);
extern void func_ov244_020ce8bc(void);
extern const char data_ov244_020d38a0[];

int func_ov244_020ce7d8(int actor, int owner)
{
    int *entry;
    struct vec at;
    int r = func_0203c5c0(*(int *)(actor + 0x3c), 100, 0x14,
                          &func_ov244_020cebd8, &func_ov244_020cec70, &entry);
    entry[1] = actor;
    entry[0] = owner;
    if (*(int *)(entry[1] + 0x50) == 1) {
        *(void **)(entry[0] + 0x74) = (void *)&func_ov244_020ce8bc;
        *(int **)(entry[0] + 0x84) = entry;
    }
    at = *(struct vec *)(*(int *)(entry[1] + 0x3cc) + 0x14);
    at.y = *(int *)(entry[1] + 0xb4) + 0x200;
    entry[3] = func_0203bdfc(entry[0], data_ov244_020d38a0);
    func_0203ca30(*entry + 4, &at);
    return r;
}
