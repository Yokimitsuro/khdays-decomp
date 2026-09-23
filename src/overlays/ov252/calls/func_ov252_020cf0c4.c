/* Collapse entry of the ov252 actor: poses 0x2f, 0x31 and 0x35 are stacked, bits 1 and 7 of the +0x60
 * high byte are set, the +0xc velocity rests and the node moves on to 020cf150. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020cf150(void);
extern const Vec3 data_02041dc8;

void func_ov252_020cf0c4(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0x2f, 0);
    func_ov107_020c9264(*state, 0x31, 0);
    func_ov107_020c9264(*state, 0x35, 0);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    *(Vec3 *)(state + 3) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cf150);
}
