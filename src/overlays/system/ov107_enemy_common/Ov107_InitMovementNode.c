/* Constructs a movement-type AI node: base-init, set flag bit 1, install two callbacks (plus two
 * more only for local player 0), clear the movement fields, seed the scale at +0x118 to 0x1000, and
 * copy the zero vector into the position at +0x104. */

#include "nitro/types.h"

typedef struct {
    int nX;
    int nY;
    int nZ;
} VecFx32;

extern void Ov107_InitNodeBase(u16 *node);
extern short Session_GetLocalPlayerIndex(void);
extern void Ov107_Spawner_FreeDataBlocks(int node);
extern void Ov107_StartObject(int node);
extern void Ov107_DestroyActorInstance(void);
extern void Ov107_Spawner_ReleaseDeadActors(void);
extern void Ov107_Spawner_Tick(void);
extern void Ov107_MovementNode_SetRequest(void);
extern const VecFx32 data_02041dc8;

void Ov107_InitMovementNode(u16 *node) {
    Ov107_InitNodeBase(node);
    *node |= 2;
    *(void **)(node + 4) = (void *)Ov107_DestroyActorInstance;
    *(void **)(node + 0x1a) = (void *)Ov107_Spawner_ReleaseDeadActors;
    if (Session_GetLocalPlayerIndex() == 0) {
        *(void **)(node + 6) = (void *)Ov107_Spawner_Tick;
        *(void **)(node + 10) = (void *)Ov107_MovementNode_SetRequest;
    }
    *(int *)((char *)node + 0x44) = 0;
    *(int *)((char *)node + 0xf4) = 0;
    node[0x24] = 0;
    *(int *)((char *)node + 0x118) = 0x1000;
    node[0x25] = 0;
    *(VecFx32 *)((char *)node + 0x104) = data_02041dc8;
    *(int *)((char *)node + 0x110) = 0;
    Ov107_Spawner_FreeDataBlocks((int)node);
    Ov107_StartObject((int)node);
}
