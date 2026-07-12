/* Clear the 0x40 bit of the hw60 hi byte, kick anim 0x1a, restart sub-anim 020c9ee8, clear +0x4c,
 * latch sub-state 0xf and dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov256_020cfff4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~0x40;
    func_ov107_020c9264(*(int *)owner, 0x1a, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x450), 0xb, 0);
    *(int *)(owner + 0x4c) = 0;
    *(unsigned char *)(*(int *)owner + 0x1c7) = 0xf;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
