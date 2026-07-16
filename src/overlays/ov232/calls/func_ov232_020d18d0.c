/* func_ov232_020d18d0 -- per-tick update: refresh the cached aim point, then re-arm the driver.
 * The aim point is recomputed from the owner's rig (+0x388, offset 0x2c) and copied into +0x30.
 * Nothing else happens while the gate byte at *(+0x10) is set.
 * Otherwise the pending value (+0x28) and the retry flag (+0x48) are cleared, and when the owner
 * is in state 0xe the target is re-acquired and its bearing (+0x1c) promoted to the live one
 * (+0x18). Either way the driver is re-armed through func_ov232_020d0cd4 with
 * func_ov232_020d197c as the continuation. */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern void func_ov232_020d06b4(Vec3 *out, int self, int rig);
extern int func_ov232_020d0620(int self);
extern void func_ov232_020d0cd4(int self, int a, int b, int c, void (*cb)(void));
extern void func_ov232_020d197c(void);

void func_ov232_020d18d0(int self) {
    int *ctx;
    Vec3 aim;

    ctx = *(int **)(self + 4);
    func_ov232_020d06b4(&aim, self, *(int *)(ctx[0] + 0x388) + 0x2c);
    *(Vec3 *)((char *)ctx + 0x30) = aim;

    if (**(unsigned char **)(ctx + 4) != 0) {
        return;
    }
    ctx[0xa] = 0;
    *(unsigned char *)((char *)ctx + 0x48) = 0;

    if (*(signed char *)(ctx[0] + 0x1c6) == 0xe && *(unsigned char *)((char *)ctx + 0x48) == 0) {
        func_ov232_020d0620(self);
        ctx[6] = ctx[7];
    }
    func_ov232_020d0cd4(self, 3, 3, 1, func_ov232_020d197c);
}
