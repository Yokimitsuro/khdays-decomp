/* Message handler of the ov042 enemy (x4: ov042/061/081/098): only 0x21 is accepted. It tells
 * the slot callback 0x2f (0x30 while the effect context is busy), clears the trail state at
 * +0x2c30 / +0x2c38 / +0x2c3c, and, if there is a target, turns the node to face it (target minus
 * the +0x48c origin, normalised, atan2 of the negated x/z, +0x8000) unless the node's bit 0x20
 * says the facing is locked; then hands over to the per-frame step. Other messages are refused. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;

extern int func_ov022_02095554(void *context);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern void func_ov042_020b38d4(void);

void *func_ov042_020b3690(char *self, int msg)
{
    void *next = 0;
    Vec3 d;
    u16 a;
    u32 *node;

    if (msg == 0x21) {
        char *trail = self + 0x2c + 0x2c00;
        next = (void *)&func_ov042_020b38d4;
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        }
        *(int *)(trail + 4) = 0;
        *(int *)(trail + 0xc) = 0;
        *(int *)(trail + 0x10) = 0;
        if (func_ov022_020ad114(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), (Vec3 *)(self + 0x8c + 0x400), &d);
            if (VEC_Mag(&d) != 0) {
                func_01ff8d18(&d, &d);
            }
            a = (u16)FX_Atan2(-d.x, -d.z);
            node = *(u32 **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(u16 *)((char *)node + 0x80) = a + 0x8000;
                *(u16 *)((char *)node + 4) |= 0x20;
            }
        }
    }
    return next;
}
