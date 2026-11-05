/* Once this part's animation has passed all but the last 0x9000 of its length, launch it as a
 * projectile: the launch block carries the part's position (+0xa8), the same point lifted by
 * 0xa000 as the target, the enemy's owner id (+0x66 of the shared object), a 0x1000 range and the
 * part's +0x110 anchor; the hit parameters get flags 0x625 and an extent of {0xa00, 0x66, 0xa00}
 * with both busy bits cleared, and the spin comes from the object's 0x2400 pair. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Launch {
    VecFx32 vFrom;
    VecFx32 vTo;
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
    VecFx32 vExtent;
    int w20;
    u8 pad24;
    u8 b25;
    u8 pad26[2];
};
extern int Anim_GetLengthQ12(unsigned short *p, unsigned int idx);                  /* Anim_GetLengthQ12 */
extern int Anim_GetFrame(unsigned short *p, unsigned int idx);                  /* Anim_GetFrame */
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Ov022_ScaleMoveDamage(char *obj, int spin, void *a, void *b);
extern void Ov022_RunReachHandlers(char *obj, struct Launch *launch, struct Params *params);
extern char *data_ov101_020bc0e0;
void Ov101_LaunchPartProjectile(char *part)
{
    struct Launch launch;
    struct Params prm;
    VecFx32 vLift;
    char *obj = data_ov101_020bc0e0;
    int animLen;
    int frame;
    animLen = Anim_GetLengthQ12((unsigned short *)(part + 4), 0);
    frame = Anim_GetFrame((unsigned short *)(part + 4), 0);
    if (frame > animLen - 0x9000) {
        return;
    }
    launch.nRange = 0x1000;
    launch.pAnchor = part + 0x110;
    launch.nOwner = *(short *)(obj + 0x66);
    launch.nFlags = 0;
    launch.vFrom = *(VecFx32 *)(part + 0xa8);
    vLift.x = 0;
    vLift.y = 0xa000;
    vLift.z = 0;
    VEC_Add(&launch.vFrom, &vLift, &launch.vTo);
    prm.uFlags = 0x625;
    Ov022_ScaleMoveDamage(obj, 0x2400, &prm.pA, &prm.pB);
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.z = 0xa00;
    prm.vExtent.y = 0x66;
    prm.w20 = 0;
    prm.b10 = 0;
    Ov022_RunReachHandlers(obj, &launch, &prm);
}
