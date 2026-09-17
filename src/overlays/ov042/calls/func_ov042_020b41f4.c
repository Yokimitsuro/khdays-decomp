/* Steer one flying part of the ov042 enemy (x4: ov042/061/081/098), the ov031 shape with the
 * trail: the solver moves the part from its +0xcc position by the step it computes, the new
 * position is stored and the trail laid along the step (Ov042_LayTrail). The part lands (state
 * 4) once it has travelled past the model's +0x14 distance from its +0x10 start, or, for a
 * timed part (bit 0 of +0), once its +4 timer reaches the model's +0x18. On landing: effect 0xc7
 * (variant 1) at the landing point if the owner's +0x694 bit is set, the part's +0xc word is
 * set to 0x2080 and its eight +0x13c bone links cleared to -1, its +0x3c animation restarted,
 * and the local player queues reaction 3/1 on the owner. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 b0 : 1; } Bits1;

extern void func_ov022_0209198c(Vec3 *out, char *a, char *part, void *arg);
extern void func_ov022_02091b48(char *a, char *part, Vec3 *c, Vec3 *d);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov042_020b4424(Vec3 *origin, Vec3 *move);                     /* Ov042_LayTrail */
extern int func_01ff8e94(const Vec3 *a, const Vec3 *b);                       /* VEC_Distance */
extern void func_ov022_02091e08(char *a, char *part);
extern void func_02033d0c(int nId, int nSub, Vec3 *pPos, int nFlag);           /* Slot_Spawn */
extern void func_ov022_020914a0(char *part, int anim);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */

int func_ov042_020b41f4(char *group, char *part, void *arg)
{
    Vec3 vTo;
    Vec3 vStep;
    Vec3 vFrom;
    char *owner = *(char **)(group + 8);
    char *model = *(char **)(part + 0x138);
    int i;

    vFrom = *(Vec3 *)(part + 0xcc);
    func_ov022_0209198c(&vStep, group, part, arg);
    func_ov022_02091b48(group, part, &vFrom, &vStep);
    VEC_Add(&vFrom, &vStep, &vTo);
    *(Vec3 *)(part + 0xcc) = vTo;
    func_ov042_020b4424(&vFrom, &vStep);
    if (*(signed char *)(part + 2) != 3) {
        if (func_01ff8e94((Vec3 *)(part + 0x10), &vTo) > *(int *)(model + 0x14)) {
            *(char *)(part + 2) = 4;
        }
    }
    func_ov022_02091e08(group, part);
    if (*(u8 *)part & 1) {
        if (*(int *)(part + 4) >= *(int *)(model + 0x18)) {
            *(char *)(part + 2) = 4;
        }
    }
    if (*(signed char *)(part + 2) != 2) {
        if (((Bits1 *)(owner + 0x694))->b0) {
            func_02033d0c(0xc7, 1, &vTo, 0);
        }
        *(char *)(part + 2) = 4;
        *(int *)(part + 0xc) = 0x2080;
        for (i = 0; i < 8; i++) {
            ((short *)part)[i + 0x9e] = -1;
        }
        func_ov022_020914a0(part, *(int *)(model + 0x3c));
        if (func_02030788() == 0) {
            *(u8 *)(owner + 0x47a) = 3;
            *(u8 *)(owner + 0x47b) = 1;
        }
    }
    return 0;
}
