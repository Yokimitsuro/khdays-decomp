/* Begin the ov178 enemy's "settle" pose (x3: ov178/179/180): push the zero offset vector to the
 * render hook (cmd 0), play pose 0, set bit 0 and clear bit 7 of the +0x60 high byte, reset the
 * two timers at +0xc/+0x10 and advance to the hold handler (020cecdc). Codegen: the bit-0 set is the
 * explicit u16 form and the bit-7 clear the hw60 bitfield form (the mix fixes the ip/lr roles).
 * hw60 = *(u16*)(*state+0x60), reloaded each op (the func_ov283_020cf158 spelling). */
typedef unsigned short u16;
struct vec3 { int x, y, z; };

extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_ov107_020c9264(int obj, int anim, int flag);
extern void func_0203c634(int obj, int slot, void *cb);
extern struct vec3 data_02041dc8;
extern void func_ov179_020d473c(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov179_020d4678(int node) {
    int *state = *(int **)(node + 4);
    u16 hw;
    {
        struct vec3 v = data_02041dc8;
        func_ov107_020c0b90(*state, 0, v, 0);
    }
    func_ov107_020c9264(*state, 0, 0);
    hw = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    state[3] = 0;
    state[4] = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov179_020d473c);
}
