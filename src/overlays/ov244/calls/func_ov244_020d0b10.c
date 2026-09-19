/* Summon wait tick: counts the +0x1c timer up by the scene step; past 1.5 the first of the four
 * +0x408 parts whose +0x60 low byte has bit 0 clear is launched (020d0c74) at the nearest mate's
 * +0x190 point raised by 10.0, the low half of +0x18 counts up and the timer resets. Once that
 * count reaches 8 the +0x384 item's +0xa8 flag clears and the node moves to 020d0c14. */
struct Vec3 { int x, y, z; };
struct Hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct Count18 { int lo : 16; int hi : 16; };
extern char *func_ov244_020cd300(char *actor);
extern void func_ov244_020d0c74(int part, struct Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov244_020d0c14(void);

void func_ov244_020d0b10(int *node) {
    int *state = (int *)node[1];
    struct Vec3 at;
    int i;

    state[7] += *(int *)(*node + 0x2c);
    if (state[7] > 0x1800) {
        for (i = 0; i < 4; i++) {
            int part = ((int *)*(int *)(*state + 0x408))[i];
            if ((((struct Hw60 *)(part + 0x60))->lo & 1) == 0) {
                char *mate = func_ov244_020cd300((char *)*state);
                at.x = *(int *)(mate + 0x190);
                at.y = *(int *)(mate + 0x194) + 0xa000;
                at.z = *(int *)(mate + 0x198);
                func_ov244_020d0c74(((int *)*(int *)(*state + 0x408))[i], &at);
                ((struct Count18 *)(state + 6))->lo += 1;
                state[7] = 0;
                break;
            }
        }
    }
    if (((struct Count18 *)(state + 6))->lo < 8) {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov244_020d0c14);
}
