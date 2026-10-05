/* NNSi_G3dFuncSbc_NODE (NitroSystem sbc.c): the SBC NODE command. Sends nothing: it sets the
 * node's visibility, from the visibility animations when the node has one, otherwise from the
 * command's own flag, and keeps it in the render state's flag bit 0. */

#include "nitro/types.h"

typedef struct VisibilityResource {
    u8 pad00[6];
    u16 stride06;
    u8 pad08[4];
    u32 masks0c[1];
} VisibilityResource;

typedef struct VisibilityNode {
    s32 flags00;
    u8 pad04[4];
    VisibilityResource *resource08;
    u8 pad0c[4];
    struct VisibilityNode *next10;
    u8 pad14[5];
    u8 entryCount19;
    u16 entries1a[1];
} VisibilityNode;

typedef struct RenderContext {
    u8 pad00[0x18];
    VisibilityNode *visibilityNodes18;
    u8 pad1c[0x30];
    u32 enabled4c[1];
} RenderContext;

typedef struct RenderCommandState {
    u8 *stream00;
    RenderContext *context04;
    u32 flags08;
    u8 pad0c[0xa0];
    u8 commandAc;
    u8 padAd[0x0b];
    u32 *visibilityResultB8;
    u8 padBc[0xc8];
    u32 visibilityResult184;
} RenderCommandState;

static inline u32 BlendVisibility(u32 *result, VisibilityNode *node, u32 command)
{
    u32 found;
    u16 entry;
    u32 index;
    VisibilityResource *resource;

    found = 0;
    *result = 0;
    do {
        if (command < node->entryCount19) {
            entry = node->entries1a[command];
            if ((entry & 0x100) != 0) {
                resource = node->resource08;
                index = ((node->flags00 >> 12) * resource->stride06) +
                        (entry & 0xff);
                found = 1;
                *result |= resource->masks0c[index >> 5] &
                           (1U << (index & 0x1f));
            }
        }
        node = node->next10;
    } while (node != 0);

    return found;
}

void NNSi_G3dFuncSbc_NODE(RenderCommandState *state)
{
    u32 command;
    VisibilityNode *node;

    if ((state->flags08 & 0x200) != 0) {
        goto advance;
    }

    command = state->stream00[1];
    state->commandAc = (u8)command;
    state->flags08 |= 4;
    state->visibilityResultB8 = &state->visibilityResult184;
    node = state->context04->visibilityNodes18;

    if (node == 0 ||
        (state->context04->enabled4c[command >> 5] &
         (1U << (command & 0x1f))) == 0) {
        goto fallback;
    }

    if (BlendVisibility(state->visibilityResultB8, node, command) != 0) {
        goto update_flag;
    }

fallback:
    *state->visibilityResultB8 = state->stream00[2] & 1;

update_flag:
    if (*state->visibilityResultB8 != 0) {
        state->flags08 |= 1;
    } else {
        state->flags08 &= ~1U;
    }

advance:
    state->stream00 += 3;
}
