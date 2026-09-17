/* Once this part's animation has passed all but the last 0x9000 of its length, launch it as a
 * projectile: the launch block carries the part's position (+0xa8), the same point lifted by
 * 0xa000 as the target, the enemy's owner id (+0x66 of the shared object), a 0x1000 range and the
 * part's +0x110 anchor; the hit parameters get flags 0x625 and an extent of {0xa00, 0x66, 0xa00}
 * with both busy bits cleared, and the spin comes from the object's 0x2400 pair. */
typedef unsigned char u8;
struct Vec3 { int x, y, z; };
struct Launch {
    struct Vec3 vFrom;
    struct Vec3 vTo;
    int nOwner;
    int nRange;
    void *pAnchor;
    int nFlags;
};
struct Params {
    void *pA;
    void *pB;
    unsigned int uFlags;
    int w0c;
    u8 b10;
    u8 pad11[3];
    struct Vec3 vExtent;
    int w20;
    u8 pad24;
    u8 b25;
    u8 pad26[2];
};
extern int func_0202aef8(unsigned short *p, unsigned int idx);                  /* Anim_GetLengthQ12 */
extern int func_0202aee0(unsigned short *p, unsigned int idx);                  /* Anim_GetFrame */
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern void func_ov022_020a23a4(char *obj, int spin, void *a, void *b);
extern void func_ov022_020a1064(char *obj, struct Launch *launch, struct Params *params);
extern char *data_ov046_020b4b40;
void func_ov046_020b4504(char *part)
{
    struct Launch launch;
    struct Params prm;
    struct Vec3 vLift;
    char *obj = data_ov046_020b4b40;
    int animLen;
    int frame;
    animLen = func_0202aef8((unsigned short *)(part + 4), 0);
    frame = func_0202aee0((unsigned short *)(part + 4), 0);
    if (frame > animLen - 0x9000) {
        return;
    }
    launch.nRange = 0x1000;
    launch.pAnchor = part + 0x110;
    launch.nOwner = *(short *)(obj + 0x66);
    launch.nFlags = 0;
    launch.vFrom = *(struct Vec3 *)(part + 0xa8);
    vLift.x = 0;
    vLift.y = 0xa000;
    vLift.z = 0;
    VEC_Add(&launch.vFrom, &vLift, &launch.vTo);
    prm.uFlags = 0x625;
    func_ov022_020a23a4(obj, 0x2400, &prm.pA, &prm.pB);
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.z = 0xa00;
    prm.vExtent.y = 0x66;
    prm.w20 = 0;
    prm.b10 = 0;
    func_ov022_020a1064(obj, &launch, &prm);
}
