/* Attack step of an ov036 enemy part (x4: ov036/054/074/091): advances the part's timer, and
 * while it is at least 0x9000 before the end of the part's animation fires the projectile from
 * the part's position (aimed straight -- the zero vector, lifted by 0x6000 when the part's
 * definition asks for the high variant); the part then goes to kind 4, the actor's +0x26c4 gate
 * (neither 0 nor 4) plays 0xcc at +0x26c8, the animation is stepped, and once it reports done the
 * part becomes kind 3, its timer is cleared and the finish handler runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_0202aef8(void *animation, int track);                                 /* Anim_GetLengthQ12 */
extern void func_ov022_02091b48(char *pGroup, char *pPart, Vec3 *pos, Vec3 *dir);
extern void func_ov022_020ad28c(char *pActor, char *pos, int nSound, int nVariant);
extern int func_ov022_02091540(void *animation, int dt);
extern void func_ov022_02091d80(char *pGroup, char *pPart);
extern Vec3 data_02041dc8;                                                            /* kVecZero */

int func_ov092_020bb4a0(char *pGroup, char *pPart, int dt)
{
    Vec3 pos;
    Vec3 dir;
    char *pActor = *(char **)(pGroup + 8);
    int *pDef = *(int **)(pPart + 0x138);
    int len = func_0202aef8(pPart + 0x28, 0);

    pos = *(Vec3 *)(pPart + 0xcc);
    dir = data_02041dc8;
    *(int *)(pPart + 4) += dt;
    if (pDef[1] == 1) {
        dir.y += 0x6000;
    }
    if (*(int *)(pPart + 4) <= len - 0x9000) {
        func_ov022_02091b48(pGroup, pPart, &pos, &dir);
    }
    *(char *)(pPart + 2) = 4;
    if (*(u8 *)(pActor + 0x26c4) != 0 && *(u8 *)(pActor + 0x26c4) != 4) {
        func_ov022_020ad28c(pActor, pActor + 0x2c8 + 0x2400, 0xcc, 2);
    }
    if (func_ov022_02091540(pPart + 0x28, dt) != 0) {
        *(char *)(pPart + 2) = 3;
    }
    if (*(signed char *)(pPart + 2) == 3) {
        *(int *)(pPart + 4) = 0;
        func_ov022_02091d80(pGroup, pPart);
    }
    return 0;
}
