/* Scatter entry: builds the 0x44-byte spread message from the data_ov273_020d6b24 template
 * (kind 5/4), fills its eight offsets with rand(0x6489) - 0x3244 and its eight heights with
 * rand(0x3001) + 0x1000, sends it through the actor's +0x24 hook (when set), plays pose 0x10,
 * spawns effect 8 at the zero vector unless the actor is being torn down (+0x1c4 & 0xa), and
 * moves the node to 020cf5fc. */
struct vec3 { int x, y, z; };
struct SpreadMsg { int w[17]; };
typedef void (*MsgHook)(int actor, struct SpreadMsg *m, int size);
extern int  func_02023eb4(int bound);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int obj, int mode, struct vec3 v, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern const struct SpreadMsg data_ov273_020d6b24;
extern struct vec3 data_02041dc8;
extern void func_ov273_020d323c(void);

void func_ov273_020d312c(int *self) {
    int *state = (int *)self[1];
    struct SpreadMsg msg = data_ov273_020d6b24;
    int i;

    for (i = 0; i < 8; i++) {
        msg.w[1 + i] = func_02023eb4(0x6489) - 0x3244;
        msg.w[9 + i] = func_02023eb4(0x3001) + 0x1000;
    }
    {
        MsgHook hook = *(MsgHook *)(*state + 0x24);
        if (hook != 0) {
            hook(*state, &msg, 0x44);
        }
    }
    func_ov107_020c9264(*state, 0x10, 0);
    {
        int actor = *state;
        if ((*(unsigned char *)(actor + 0x1c4) & 0xa) == 0) {
            func_ov107_020c0b90(actor, 8, data_02041dc8, 0);
        }
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d323c);
}
