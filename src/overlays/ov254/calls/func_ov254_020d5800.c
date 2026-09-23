/* Mount entry: every rider of the two +0x384 slots still mounted (+0xad) gets its +0xa8..+0xac
 * hold flags raised; with none mounted the actor plays pose 0 (looping). The node moves to
 * 020d57fc. */
typedef unsigned char u8;
struct Riders { char pad[0x384]; int rider[2]; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d57fc(void);

void func_ov254_020d5800(int *node)
{
    int *state = (int *)node[1];
    int i;
    int busy = 0;
    int rider;

    for (i = 0; i < 2; i++) {
        rider = ((struct Riders *)*state)->rider[i];
        if (*(u8 *)(rider + 0xad) != 0) {
            *(u8 *)(rider + 0xa8) = *(u8 *)(rider + 0xaa) = *(u8 *)(rider + 0xac) = *(u8 *)(rider + 0xa9) = 1;
            busy = 1;
        }
    }
    if (busy == 0) {
        func_ov107_020c9264(*state, 0, 1);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d57fc);
}
