/* Enter the ov258 actor's leap: the actor's +0x424 clears, the +0x53 step countdown is 5 and the
 * +0x44 clock clears, the rig switches (020cd028 mode 1), the +0x1c point is (0, 15.6, 11.0), pose 5
 * plays with effect 0x21 there and the brain waits on 020cf7c8. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern void func_ov258_020cd028(int *node, int mode);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020cf7c8(void);

void func_ov258_020cf63c(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x424) = 0;
    ((NibblePair *)((u8 *)state + 0x53))->lo = 5;
    state[0x11] = 0;
    func_ov258_020cd028(node, 1);
    state[7] = 0;
    state[8] = 0xfa00;
    state[9] = 0xb000;
    func_ov107_020c9264(*state, 5, 0);
    func_ov107_020c0b90(*state, 0x21, *(Vec3 *)(state + 7), 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020cf7c8);
}
