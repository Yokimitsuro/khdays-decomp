/* Enter tick of an ov235 state: the owner's +0x24 hook receives note 3 of the
 * data_ov235_020d24d0 table, bit 6 of the owner's +0x60 high byte is raised, animation 0x18 plays,
 * the +0x44 and +0x54 timers and the +0x65 flag clear and the tick hands over to
 * func_ov235_020d0970. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { u16 lo; u16 hi; } Cmd4;

extern const struct { Cmd4 n[4]; } data_ov235_020d24d0;
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d0970(int *node);

void func_ov235_020d08d4(int *node)
{
    int *state = (int *)node[1];
    Cmd4 note = data_ov235_020d24d0.n[3];
    unsigned short v;

    if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, &note, 4);
    }
    v = *(unsigned short *)(*state + 0x60);
    *(unsigned short *)(*state + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    func_ov107_020c9264(*state, 0x18, 0);
    state[0x11] = 0;
    state[0x15] = 0;
    *((u8 *)state + 0x65) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d0970);
}
