/* Land tick of the ov252 actor: the +0xc velocity follows the +0x574 part's +0x2c vector turned by the
 * +0x54 heading; once the partner holds no queued move pose 0x16 plays, the part takes motion 0x15,
 * bit 3 of the +0x60 high byte is set and bit 2 clears, +0x64 clears and the node moves on to
 * 020d0c28. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d0c28(void);

void func_ov252_020d0b44(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0x16, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0x15, 0);
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 8) << 0x18) >> 0x10);
        }
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~4) << 0x18) >> 0x10);
        }
        state[0x19] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d0c28);
        return;
    }
}
