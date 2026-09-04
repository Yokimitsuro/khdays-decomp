/* Per-frame step: folds the motion the shared sampler returns into the actor's
 * position on the ground plane, then asks the actor's own hook whether it is
 * still active and latches the answer.
 *
 * Becoming active shows the node, raises the actor's own flag and, on the local
 * player only, raises one more. The two 64-bit flag words are written as whole
 * long longs, which is why one half reads and writes itself unchanged.
 *
 * The sample is copied into the step whole and only then flattened, and the
 * sample is declared before the step: the other order costs five instructions
 * of shuffling.
 */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

struct Vec3 { int x, y, z; };

extern int func_ov022_0209fe20(int self, void *out);
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern void func_0202af1c(int node);
extern int func_02030788(void);

int func_ov030_020b38a4(int self) {
    int r;
    struct Vec3 sample;
    struct Vec3 step;

    *(int *)(self + 0x24) &= ~0x80;
    func_ov022_0209fe20(self, &sample);
    *(int *)(self + 0x58) = sample.y;

    step = sample;
    step.y = 0;
    VEC_Add((struct Vec3 *)(self + 0x498), &step, (struct Vec3 *)(self + 0x498));

    r = (*(int (**)(int))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        int *p;

        *(unsigned long long *)self |= 0x2000000000000ULL;
        p = *(int **)(self + 0x20);
        if ((*(unsigned int *)p & 0x20) == 0) {
            func_0202af1c((int)p + 4);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)((char *)self + 0x464) |= 2;
        }
    }
    return 0;
}
