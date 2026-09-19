/* Enter the ov125 enemy's charge: clear bit 0 and set bits 1-2 of the hw60 high byte, drop
 * bit 0 of the +0x388 target's +8 word, request animation 0x49 with the +0x24 blend, reset the
 * +0x2c timer and register the charge think callback. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c5af8(int owner, int a, int anim, int blend);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov125_020ce3fc(void);

void func_ov125_020ce344(int self) {
    int *node = *(int **)(self + 4);
    ((struct hw60 *)(*node + 0x60))->hi &= ~1;
    ((struct hw60 *)(*node + 0x60))->hi |= (unsigned char)6;
    ((struct w8 *)(*(int *)(*node + 0x388) + 8))->lo &= ~1;
    func_ov107_020c5af8(*node, 0, 0x49, node[9]);
    node[0xb] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov125_020ce3fc);
}
