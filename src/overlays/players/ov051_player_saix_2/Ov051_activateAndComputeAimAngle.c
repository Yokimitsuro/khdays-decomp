/* Begins the special attack: for the local player sets bit 16 of the two 64-bit flag words, picks
 * the range for the game mode, faces the locked target and switches to state 0x21. */

#include "game/engine.h"

extern int Ov022_ValidateTargetRef();
extern void *func_ov022_020ad0c0();
extern void VEC_Subtract();
extern int VEC_Mag();
extern void VEC_Normalize();
extern int FX_Atan2Idx();
extern void Ov022_ActorSetState();

void Ov051_activateAndComputeAimAngle(void *this)
{
    int buf[3];
    if (!Session_GetLocalPlayerIndex()) {
        *(unsigned long long *)((char *)this + 0x464) |= 0x10000;
    }
    if (!Session_GetLocalPlayerIndex()) {
        *(unsigned long long *)((char *)this + 0x46c) |= 0x10000;
    }
    *(int *)((char *)this + 0x4b0) = (GetFrameRateMode() == 1) ? 0x240 : 0x180;
    if (Ov022_ValidateTargetRef(this) != 0) {
        int t;
        void *r = func_ov022_020ad0c0(this);
        VEC_Subtract(r, (char *)this + 0x48c, buf);
        if (VEC_Mag(buf) != 0) {
            VEC_Normalize(buf, buf);
        }
        t = (unsigned short)FX_Atan2Idx(-buf[0], -buf[2]);
        {
            int *disp = *(int **)((char *)this + 0x20);
            if ((*disp & 0x20) == 0) {
                *(short *)((char *)disp + 0x80) = (short)(t + 0x8000);
                *(unsigned short *)((char *)disp + 4) |= 0x20;
            }
        }
    }
    Ov022_ActorSetState(this, 0x21);
}
