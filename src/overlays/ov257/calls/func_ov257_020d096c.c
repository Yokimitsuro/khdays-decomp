/* Swoop enter tick of an ov257 state: the owner's +0x24 hook receives note 1 of
 * data_ov257_020d325c, animation 0x1f plays, the +0x3d0 part plays motion 0x1c, +0x44, +0x74,
 * +0x75, the +0x54 timer and +0x76 clear and the tick hands over to func_ov257_020d0a00. */
typedef unsigned short u16;
typedef struct { u16 lo; u16 hi; } Cmd4;

/* the note table seen as a word-aligned record: its note 1 follows a 4-byte word */
extern const struct { int w0; Cmd4 n1; } data_ov257_020d325c;
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d0a00(int *node);

void func_ov257_020d096c(int *node)
{
    int *state = (int *)node[1];
    Cmd4 note = data_ov257_020d325c.n1;

    if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, &note, 4);
    }
    func_ov107_020c9264(*state, 0x1f, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x1c, 0);
    state[0x11] = 0;
    *((unsigned char *)state + 0x74) = 0;
    *((unsigned char *)state + 0x75) = 0;
    state[0x15] = 0;
    *((unsigned char *)state + 0x76) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d0a00);
}
