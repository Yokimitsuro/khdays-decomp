/* Volley tick of an ov235 state: the +0x44 timer accumulates the owner's rate; after 0.5 the
 * owner's +0x24 hook receives note 7 of data_ov235_020d24d0, animation 0x20 plays, +0x63 and the
 * timer clear, the +0x78 volley counter advances (+0x74 cleared) and reaction +0x3c8 fires at the
 * +4 point twice -- with the mode of data_ov235_020d24f0 picked by the counter mod 3, then mode 0x10
 * -- before the tick hands over to func_ov235_020d10ec.
 * Codegen: compiled with opt_dead_assignments off (push/pop scoped); the note's high half is read
 * right after the mode table copy and stored last, as in the ROM's load/store order. */
typedef unsigned short u16;
typedef struct { u16 lo; u16 hi; } Cmd4;
typedef struct { int mode[3]; } ModeTable;

typedef struct { Cmd4 note[8]; } NoteTable;
extern const NoteTable data_ov235_020d24d0;
extern const ModeTable data_ov235_020d24f0;
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c5af8(int owner, int id, u16 mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d10ec(int *node);

#pragma push
#pragma opt_dead_assignments off
void func_ov235_020d161c(int *node)
{
    Cmd4 note;
    ModeTable modes;
    u16 noteHi;
    int *state = (int *)node[1];

    state[0x11] += *(int *)(node[0] + 0x2c);
    if (state[0x11] < 0x800) {
        return;
    }
    modes = data_ov235_020d24f0;
    noteHi = data_ov235_020d24d0.note[7].hi;
    {
        Cmd4 *p = &note;

        p->lo = data_ov235_020d24d0.note[7].lo;
        p->hi = noteHi;
        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
    }
    func_ov107_020c9264(*state, 0x20, 0);
    *((unsigned char *)state + 0x63) = 0;
    state[0x11] = 0;
    state[0x1e]++;
    state[0x1d] = 0;
    func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), modes.mode[state[0x1e] % 3], (void *)state[1]);
    func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x10, (void *)state[1]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d10ec);
}
#pragma pop
