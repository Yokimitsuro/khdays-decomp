/* Release entry of an ov259 helper: +0x2c and +0x24 clear, the owner's +0x60 high byte sets bit 0
 * and drops bit 7, the +0x384 rig shows, the +0x38c shape is knocked back at the +8 point (mode 3),
 * sound 0x172/0x13 fires there and the node moves on to 020d2d3c. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d2d3c(void);

void func_ov259_020d2c48(int *node)
{
    int *state = (int *)node[1];

    state[0xb] = 0;
    state[9] = 0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x384) + 8))->f |= 1;
    func_ov107_020c0b90(*(int *)(*state + 0x38c), 3, *(Vec3 *)state[2], 0);
    func_ov259_020cd3c4(*(int *)(*state + 0x38c), 0x172, 0x13, (void *)state[2]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d2d3c);
}
