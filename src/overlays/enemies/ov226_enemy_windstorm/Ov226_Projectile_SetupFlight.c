/* Queues action 1 and stores the mode, destination and zero velocity. */

#include "nitro/fx_types.h"

extern VecFx32 data_02041dc8;

void Ov226_Projectile_SetupFlight(void *this_, int val, VecFx32 dest, VecFx32 vec) {
    void *owner = *(void **)this_;
    *((signed char *)owner + 0x1c7) = 1;
    *(int *)((char *)this_ + 0x44) = val;
    *(VecFx32 *)((char *)this_ + 0x24) = vec;
    *(VecFx32 *)((char *)this_ + 0x18) = data_02041dc8;
}
