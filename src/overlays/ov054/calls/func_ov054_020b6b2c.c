/* Advance the projectile one step and retire it when it has gone too far, lasted too long,
 * or hit something.
 *
 * Reads the current position out of the entity, asks the mover for this step's velocity,
 * lets the collision pass adjust both, and writes the position back.  A positive collision
 * result bumps the entity's sub-state (only from 0 or 2).  Retirement is state 4, and it
 * happens when the distance from the spawn point at +0x10 passes the template's limit at
 * +0x14 OR the age at +4 reaches the one at +0x18.  Finally, unless the entity is already
 * in state 2, it fires the impact effect when the owner is in mode 4 with its low bit set,
 * forces state 4 and reports the template's retire code.
 *
 * ONE LEVER: the two retirement tests share a single `if` with `||`, not an if/else-if with
 * the same body in both arms.  Written as two arms mwcc predicates the assignment inline
 * (`movgt r0, #4 ; strbgt`), which is 4 bytes over; the ROM branches both tests to one
 * shared block.  Same jump-to-versus-fall-into distinction as the switch lever, showing up
 * here in an ordinary if -- when two arms do the SAME thing, that is a single condition in
 * the source.
 */
typedef struct { int x, y, z; } Vec3;
struct Bit0 { unsigned char b : 1; };

extern void func_ov022_0209198c(Vec3 *out, char *a, char *ent, int arg);
extern void func_ov022_02091b48(char *a, char *ent, Vec3 *p, Vec3 *v);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int func_ov022_02091540(char *p, int arg);
extern void func_ov022_020914a0(char *ent, int n);
extern int func_01ff8e94(const Vec3 *a, const Vec3 *b);
extern void func_02033d0c(int a, int b, Vec3 *p, int d);

int func_ov054_020b6b2c(char *a, char *ent, int arg) {
    char *owner = *(char **)(a + 8);
    char *cfg = *(char **)(ent + 0x138);
    Vec3 pos;
    Vec3 vel;

    pos = *(Vec3 *)(ent + 0xcc);
    func_ov022_0209198c(&vel, a, ent, arg);
    func_ov022_02091b48(a, ent, &pos, &vel);
    VEC_Add(&pos, &vel, &pos);
    *(Vec3 *)(ent + 0xcc) = pos;

    if (func_ov022_02091540(ent + 0x28, arg) != 0) {
        int st = *(short *)(ent + 0x2a);
        if (st == 0 || st == 2) {
            func_ov022_020914a0(ent, st + 1);
        }
    }

    if (*(signed char *)(ent + 2) != 3) {
        if (func_01ff8e94((const Vec3 *)(ent + 0x10), &pos) > *(int *)(cfg + 0x14) ||
            *(int *)(ent + 4) >= *(int *)(cfg + 0x18)) {
            *(signed char *)(ent + 2) = 4;
        }
    }

    if (*(signed char *)(ent + 2) != 2) {
        if (*(unsigned char *)(owner + 0x2000 + 0x6c4) == 4 &&
            ((struct Bit0 *)(owner + 0x694))->b != 0) {
            func_02033d0c(0xd3, 6, &pos, 0);
        }
        *(signed char *)(ent + 2) = 4;
        func_ov022_020914a0(ent, *(int *)(cfg + 0x3c));
    }
    return 0;
}
