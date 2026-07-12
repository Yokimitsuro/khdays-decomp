/* Clear the 0x80 bit of the hw60 hi byte; unless busy, kick anim 1, clear +0x1c/+0x20 and
 * dispatch 020d2538. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov245_020d2538(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov245_020d24bc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~0x80;
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 1, 0);
    *(int *)(owner + 0x1c) = 0;
    *(unsigned char *)(owner + 0x20) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020d2538);
}
