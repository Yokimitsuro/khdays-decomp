/* Runs the scene's extra-class timer, then refreshes the state slots.
 *
 * The timer only runs while the actor is drivable and not linked, and only
 * while the extra class exists. It starts at 0x3000 when the class reports a
 * non-negative result for the zero vector -- and only if the actor carries flag
 * bit 22, which lives in the 64-bit word at +0x464. Each frame it counts down
 * by the shared tick; reaching zero raises the actor's panel bit and parks the
 * timer back at its idle value.
 */
struct Vec3 { int x, y, z; };

extern int func_ov022_0209fc78(int self, int a);
extern int func_ov022_0209fc48(int self, int a);
extern int func_ov022_020893f4(int object, const struct Vec3 *at, int mode);
extern void func_ov022_0208954c(int object, int result, int source);
extern int func_ov022_02083f90(void);
extern void func_ov030_020b564c(int slots, int id);
extern int data_ov030_020b5a00;
extern struct Vec3 data_02041dc8;

void func_ov030_020b3d18(int self) {
    int base = *(int *)&data_ov030_020b5a00;

    if (func_ov022_0209fc78(self, 1) != 0
        && func_ov022_0209fc48(self, 1) == 0
        && *(int *)(base + 0x2cac) != 0) {
        if (*(int *)(base + 0x2ca8) == (int)0x80000000
            && (*(unsigned long long *)((char *)self + 0x464) & 0x400000) != 0) {
            int r = func_ov022_020893f4(*(int *)(base + 0x2cac), &data_02041dc8, 0);

            if (r >= 0) {
                *(int *)(base + 0x2ca8) = 0x3000;
                func_ov022_0208954c(*(int *)(base + 0x2cac), r, self + 0x558);
            }
        }
        if (*(int *)(base + 0x2ca8) != (int)0x80000000) {
            *(int *)(base + 0x2ca8) -= func_ov022_02083f90();
            if (*(int *)(base + 0x2ca8) <= 0) {
                if (*(signed char *)(self + 0xf0d) != 0) {
                    *(unsigned char *)(self + 0xf0c) |= 1;
                }
                *(int *)(base + 0x2ca8) = (int)0x80000000;
            }
        }
    }

    func_ov030_020b564c(base + 0x2cb0, *(short *)(self + 0x2aba));
}
