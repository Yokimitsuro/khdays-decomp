/* Spawn a size-0xc registry entry (func_0203c5c0, cbs cf098/cf134) into *entry, then link it:
 * entry[0]=self, entry[1]=the given owner, and copy the self's +0x3b8 item's pose (+4) into the
 * owner's +4. */
struct blk11 { int w[11]; };
struct Ov244Clip { int pad0; struct blk11 pose; };
extern int func_0203c5c0(int list, int a, int b, void *cb2, void *cb1, int **out);
extern void func_ov244_020cf134(void);
extern void func_ov244_020cf098(void);
int func_ov244_020cf010(int param_1, int owner) {
    int *entry;
    int spawn = func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0xc,
                              &func_ov244_020cf098, &func_ov244_020cf134, &entry);
    entry[0] = param_1;
    entry[1] = owner;
    ((struct Ov244Clip *)entry[1])->pose = ((struct Ov244Clip *)*(int *)(entry[0] + 0x3b8))->pose;
    return spawn;
}
