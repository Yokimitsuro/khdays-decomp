struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct vec3 { int x, y, z; };

extern int func_01fffe14(void);
extern void func_0203c634(void *obj, int slot, void *cb);
extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_ov234_020cc95c(void);
extern void func_ov234_020cca84(void);
extern void func_ov234_020ccedc(void);

/* Enter the "recoil/knockback" node sub-state: reset the marker + sub-state bytes,
 * seed the physics tuning (+0x54..0x60), clear the hw60 flags 1/2, push the node's
 * current position to the render hook (cmd 5), and install the update/event/draw
 * callbacks. */
void func_ov234_020cc864(void *param_1) {
    int *node = *(int **)((char *)param_1 + 4);

    *(unsigned char *)(*node + 0x1c6) = 0;
    *(char *)(*node + 0x1c7) = -1;
    *(unsigned short *)((char *)node + 0x70) = 0;
    *(int *)((char *)node + 0x54) = -0x280;
    *(int *)((char *)node + 0x58) = -0x38;
    *(int *)((char *)node + 0x5c) = 0xe00;
    *(int *)((char *)node + 0x60) = 0x400;
    *(int *)((char *)node + 8) = *node + 0xb0;
    ((struct hw60 *)(*node + 0x60))->hi &= ~6;
    {
        int inner = *node;
        int q = func_01fffe14();
        func_ov107_020c0b90(inner, 5, *(struct vec3 *)(inner + 0x74), q & 0xff);
    }
    func_0203c634(param_1, 1, func_ov234_020ccedc);
    func_0203c634(param_1, 0, func_ov234_020cc95c);
    func_0203c634(param_1, 2, func_ov234_020cca84);
}
