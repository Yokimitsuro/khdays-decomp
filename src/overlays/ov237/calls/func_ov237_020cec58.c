/* Lunge tick of the ov237 actor: the +0x3c aim point follows the +0x3d8 partner's +0x2c point
 * (020cdb50); once the +4 rig finishes the next pose is picked by the +0x3dc target's height: above
 * 3.0 bit 6 of the +0x60 high byte is set with poses 0x16 / partner 9, else poses 10 / partner 6; the
 * +0x30 timer and the +0x57 flag clear, +0x34 = 1 and the brain waits on 020ced4c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern Vec3 func_ov237_020cdb50(int *node, Vec3 *target);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int actor, int pose, int c);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020ced4c(void);

void func_ov237_020cec58(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 0xf) = func_ov237_020cdb50(node, (Vec3 *)(*(int *)(*state + 0x3d8) + 0x2c));
    if (*(u8 *)(state[1] + 0xad) == 0) {
        return;
    }
    if (*(int *)(*(int *)(*state + 0x3dc) + 0x194) > 0x3000) {
        u16 hw = *(u16 *)(state + 0x18);

        *(u16 *)(state + 0x18) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
        func_ov107_020c9264(*state, 0x16, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3d8), 9, 0);
    } else {
        func_ov107_020c9264(*state, 10, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3d8), 6, 0);
    }
    state[0xc] = 0;
    state[0xd] = 1;
    *((u8 *)state + 0x57) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020ced4c);
}
