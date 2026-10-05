/* Message handler of the ov048 enemy (x4: ov048/067/086/103). 0x21 tells the slot callback 0x2f
 * and hands over to the hover step. 0x22 arms the attack: the rig's mode (+0x2f84: 2, 3 or 4)
 * picks the pattern index and duration (0x6000 / 0x15000 / 0x27000), the target is refreshed,
 * 0x33 (mode 4) or 0x32 is told, the animation is set to 0x9000, bit 29 is raised, the rig's
 * counter cleared and its speed set to 0x800 (0xc00 at 20 fps, scaled by 1.2 in mode 4),
 * the fall speed to 0x180 (0x240 at 20 fps), the node turns to face the target unless locked,
 * and the attack step takes over. 0x23/0x24 tell 0x31/0x30 and hand over to the landing step. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern void Ov022_FillEightHalvesMinus1At0x2bd4(char *self);
extern void Anim_SetFrameWrapped(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern int FX_Atan2Idx(int x, int z);
extern char *data_ov103_020bc120;
extern void Ov103_HoverStep(void);
extern void Ov103_AttackStep(void);
extern void Ov103_LandingStep(void);

void *Ov103_HandleMessage(char *self, int msg)
{
    char *rig = data_ov103_020bc120 + 0x2c + 0x2c00;
    void *next = 0;
    VecFx32 d;
    u16 a;
    unsigned int *node;

    switch (msg - 0x21) {
    case 0:
        next = (void *)&Ov103_HoverStep;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        break;
    case 1:
        next = (void *)&Ov103_AttackStep;
        switch (*(int *)(rig + 0x358)) {
        case 2:
            *(int *)(rig + 0x360) = 0;
            *(int *)(rig + 0x36c) = 0x6000;
            break;
        case 3:
            *(int *)(rig + 0x360) = 1;
            *(int *)(rig + 0x36c) = 0x15000;
            break;
        case 4:
            *(int *)(rig + 0x360) = 2;
            *(int *)(rig + 0x36c) = 0x27000;
            break;
        }
        Ov022_FillEightHalvesMinus1At0x2bd4(self);
        if (*(int *)(rig + 0x358) == 4) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x33);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        }
        Anim_SetFrameWrapped(*(char **)(self + 0x20) + 4, 0, 0x9000);
        *(int *)(self + 0x7b0) = 0x9000;
        *(unsigned long long *)self |= 0x20000000;
        *(int *)(rig + 0x364) = 0;
        *(int *)(rig + 0x368) = GetFrameRateMode() == 1 ? 0xc00 : 0x800;
        if (*(int *)(rig + 0x358) == 4) {
            *(int *)(rig + 0x368) = (int)(((long long)*(int *)(rig + 0x368) * 0x1333 + 0x800) >> 12);
        }
        *(int *)(self + 0x4b0) = GetFrameRateMode() == 1 ? 0x240 : 0x180;
        if (Ov022_ValidateTargetRef(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), (VecFx32 *)(self + 0x8c + 0x400), &d);
            if (VEC_Mag(&d) != 0) {
                VEC_Normalize(&d, &d);
            }
            a = (u16)FX_Atan2Idx(-d.x, -d.z);
            node = *(unsigned int **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(u16 *)((char *)node + 0x80) = a + 0x8000;
                *(u16 *)((char *)node + 4) |= 0x20;
            }
        }
        break;
    case 2:
    case 3:
        next = (void *)&Ov103_LandingStep;
        if (msg == 0x24) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        }
        break;
    }
    return next;
}
