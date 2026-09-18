/* Hover tick of the ov178 enemy (x3: ov178/179/180): keeps the previous step (+0x20 <- +0x2c)
 * and damps the step by 0xb00; below hover height 0x20 with no override pending (+0x88) the
 * +0x60 high-byte bit 6 is dropped. With no override, the actor must be hit-flagged (+0x17a or
 * +0x17c bit 0) to continue; then, once the actor's +0xad flag is clear, a positive +0x58
 * counter goes to sub-state 0xb, otherwise an 80 % roll with a free target (020ccb8c) goes to
 * sub-state 8 and the rest to 5 -- each with the slot cleared. */
typedef unsigned short u16;
struct v3 { int x, y, z; };
struct b1 { unsigned char b:1; };

extern void func_01ffa724(int a, void *b, void *c);
extern int func_02023eb4(int bound);
extern int func_ov179_020d25ec(int node);
extern void func_0203c634(int node, int slot, void *cb);

void func_ov179_020d3e14(int node) {
    int *state = *(int **)(node + 4);
    struct v3 *src = (struct v3 *)(state + 0xb);
    u16 hw;
    *(struct v3 *)(state + 8) = *src;
    func_01ffa724(0xb00, src, src);
    if (state[0x22] == 0 && state[9] < 0x20) {
        hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    if (state[0x22] == 0) {
        int obj = *state;
        if (!((struct b1 *)(obj + 0x17a))->b && !((struct b1 *)(obj + 0x17c))->b) {
            return;
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x16] > 0) {
        *(unsigned char *)(*state + 0x1c7) = 0xb;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if ((unsigned int)func_02023eb4(100) < 80 && func_ov179_020d25ec(node) != 0) {
        *(unsigned char *)(*state + 0x1c7) = 8;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 5;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
