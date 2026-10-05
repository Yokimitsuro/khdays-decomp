/* NNSi_G3dFuncSbc_POSSCALE (NitroSystem sbc.c): the SBC POSSCALE command -- MTX_SCALE by the
 * model's position scale (render state +0xe0), or by the second one (+0xe4) for the command's
 * other form. */

#include "nitro/types.h"

typedef struct RenderCommandState {
    u8 *stream00;
    u8 pad04[4];
    u32 flags08;
    u8 pad0c[0xe0 - 0x0c];
    u32 scaleE0;
    u32 alternateScaleE4;
} RenderCommandState;

extern void GX_SendFifoWords(u32 command, const void *words, u32 count);

void NNSi_G3dFuncSbc_POSSCALE(RenderCommandState *state, int useAlternate)
{
    u32 values[3];

    if ((state->flags08 & 0x100) == 0 &&
        (state->flags08 & 0x200) == 0) {
        if (useAlternate == 0) {
            values[0] = values[1] = values[2] = state->scaleE0;
        } else {
            values[0] = values[1] = values[2] = state->alternateScaleE4;
        }
        GX_SendFifoWords(0x1b, values, 3);
    }
    state->stream00++;
}
