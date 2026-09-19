/* Enter the ov125 enemy's spin: build the +0xa0 pose from the +0x390 basis and data_02042240
 * (ed60 + normalise), clear the +0x1c timer, scale the +0x384 sub-node's placement to
 * 0x1000/0x2666/0x1000, set bit 0 and drop bits 2/3/7 of the hw60 high byte, raise bit 0 of
 * the +0x388 target's +8 word, seed the +0xc velocity as 0.75 of the +0x390 basis, clear the
 * +0x18 counter and register the spin think callback. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0202ed60(void *dst, void *src, int m);
extern void func_0202f4a4(void *out, void *in);
extern void func_0203c9d0(void *pose, void *q);
extern void func_0203ca50(void *placement, int x, int y, int z);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203c634(int self, int idx, void *cb);
extern int data_02042240;
extern void func_ov126_020d3a28(void);

void func_ov126_020d390c(int *self) {
    int *state = (int *)self[1];
    int q[4];

    func_0202ed60(q, &data_02042240, *state + 0x390);
    func_0202f4a4(q, q);
    func_0203c9d0((char *)*state + 0xa0, q);
    state[7] = 0;
    func_0203ca50((char *)*(int *)(*state + 0x384) + 4, 0x1000, 0x2666, 0x1000);
    ((struct hw60 *)(*state + 0x60))->hi |= (unsigned char)1;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x8c;
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo |= 1;
    func_01ffa724(0xc00, (char *)*state + 0x390, state + 3);
    state[6] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), &func_ov126_020d3a28);
}
