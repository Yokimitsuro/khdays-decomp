/* Message handler of the ov039 enemy (x4: ov039/058/078/095). 0x21 resets the shared rig's
 * +0x2cdc / +0x2ce8 words, tells the slot callback 0x2f (or 0x32 while the effect context is
 * busy), turns the node to face the target (target minus the +0x48c origin, normalised, atan2 of
 * the negated x/z, +0x8000) unless the node's bit 0x20 says the facing is locked, and hands
 * over to the ground step. 0x22 clears +0x2cd8, sets +0x2ce0, tells the callback 0x30 (0x31
 * once the rig's +0x2cd4 flag is set), raises bit 0x20000 of the high flag word and enables the
 * node unless it is locked, then hands over to the second step. 0x23 starts the flight
 * (Ov039_StartFlight), tells the callback 0x33 and hands over to the flight step. Anything else
 * is refused (null). Codegen: `next` is assigned before the zero stores of a case, which keeps
 * the shared zero (next's initial value) ahead of the self copy in the prologue schedule. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct { int x, y, z; } Vec3;

extern int func_ov022_02095554(void *context);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern void func_0202af1c(u16 *nodeFlags);                                     /* SceneNode_Enable */
extern void func_ov058_020b7020(char *self);                                    /* Ov039_StartFlight */
extern char *data_ov058_020b7e00;
extern void func_ov058_020b7320(void);
extern void func_ov058_020b770c(void);
extern void func_ov058_020b79b4(void);

void *func_ov058_020b630c(char *self, int msg)
{
    void *next = 0;
    char *rig = data_ov058_020b7e00 + 0xd4 + 0x2c00;
    Vec3 d;
    u16 a;
    u32 *node;

    switch (msg) {
    case 0x21:
        next = (void *)&func_ov058_020b7320;
        *(int *)(rig + 8) = 0;
        *(int *)(rig + 0x14) = 0;
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) == 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        }
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
        break;
    case 0x22:
        *(int *)(rig + 4) = 0;
        *(int *)(rig + 0xc) = 1;
        next = (void *)&func_ov058_020b770c;
        if (*(int *)rig != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        }
        *(u64 *)self |= 0x2000000000000ULL;
        if ((**(u32 **)(self + 0x20) & 0x20) == 0) {
            func_0202af1c((u16 *)(*(char **)(self + 0x20) + 4));
        }
        break;
    case 0x23:
        next = (void *)&func_ov058_020b79b4;
        func_ov058_020b7020(self);
        (*(void (**)(char *, int))(self + 0x664))(self, 0x33);
        break;
    }
    return next;
}
