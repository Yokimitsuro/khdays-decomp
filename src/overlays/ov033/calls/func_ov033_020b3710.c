/* Per-frame update of the ov033 enemy (x4: ov033/051/071/089): fires the mode's shot at its
 * scheduled tick of the +0x7b0 timer and arms the +0x47a/+0x47b pair when the session is idle
 * and the actor is not flagged 0x10000. Modes 0x2f and 0x33 (the alternate one) shoot at
 * 0x3000 from two units ahead of the origin and 0x333 above it; 0x30 shoots at 0x9000 from the
 * origin itself; 0x31 shoots at 0xc000 from the anchor sample (kind 2, always grounded). The
 * common post-update runs afterwards. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void VEC_MultAdd(int scale, const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov033_020b4804(Vec3 *pos, unsigned int angle, int kind, int grounded);
extern int func_02030788(void);
extern void func_ov022_020ad44c(Vec3 *out, char *self);
extern void func_ov022_020ad588(char *self);
extern short data_0203d210[];

void func_ov033_020b3710(char *self)
{
    Vec3 dir;
    Vec3 pos;
    int mode = *(int *)(self + 0x6bc);
    int alt;
    u16 angle = *(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000;

    switch (mode - 0x2f) {
    case 0:
    case 4:
        alt = 0;
        if (mode == 0x33) {
            alt = 1;
        }
        if (*(int *)(self + 0x7b0) == 0x3000) {
            dir.x = -data_0203d210[(angle >> 4) * 2];
            dir.z = -data_0203d210[(angle >> 4) * 2 + 1];
            dir.y = 0;
            VEC_MultAdd(0x2000, &dir, (Vec3 *)(self + 0x8c + 0x400), &pos);
            pos.y += 0x333;
            func_ov033_020b4804(&pos, angle, alt, *(int *)(self + 0x24) & 4);
            if (func_02030788() == 0 && (int)(*(long long *)self & 0x10000) == 0) {
                *(u8 *)(self + 0x47a) = 3;
                *(u8 *)(self + 0x47b) = 0;
            }
        }
        break;
    case 1:
        if (*(int *)(self + 0x7b0) == 0x9000) {
            pos = *(Vec3 *)(self + 0x8c + 0x400);
            func_ov033_020b4804(&pos, angle, 1, *(int *)(self + 0x24) & 4);
            if (func_02030788() == 0 && (int)(*(long long *)self & 0x10000) == 0) {
                *(u8 *)(self + 0x47a) = 3;
                *(u8 *)(self + 0x47b) = 0;
            }
        }
        break;
    case 2:
        if (*(int *)(self + 0x7b0) == 0xc000) {
            func_ov022_020ad44c(&pos, self);
            func_ov033_020b4804(&pos, angle, 2, 1);
            if (func_02030788() == 0 && (int)(*(long long *)self & 0x10000) == 0) {
                *(u8 *)(self + 0x47a) = 3;
                *(u8 *)(self + 0x47b) = 1;
            }
        }
        break;
    case 3:
        break;
    }
    func_ov022_020ad588(self);
}
