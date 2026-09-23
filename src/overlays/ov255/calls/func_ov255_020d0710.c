/* Take-off enter tick of an ov255 state: the owner's +0x24 hook receives note 6 of
 * data_ov255_020d2b20, the +0x40 rate clears, bit 6 of the owner's +0x60 high byte is raised,
 * animation 0x18 plays, the +0x3a4 part plays motion 0x13, reaction +0x3f8 mode 0xf fires at the
 * +4 point, the +0x50 timer clears and the tick hands over to func_ov255_020d07d4. */
typedef unsigned short u16;
typedef struct { u16 lo; u16 hi; } Cmd4;

extern const struct { Cmd4 n[8]; } data_ov255_020d2b20;
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020d07d4(int *node);

void func_ov255_020d0710(int *node)
{
    int *state = (int *)node[1];
    Cmd4 note = data_ov255_020d2b20.n[6];
    u16 hw;

    if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, &note, 4);
    }
    state[0x10] = 0;
    hw = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    func_ov107_020c9264(*state, 0x18, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a4), 0x13, 0);
    func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3f8), 0xf, (void *)state[1]);
    state[0x14] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020d07d4);
}
