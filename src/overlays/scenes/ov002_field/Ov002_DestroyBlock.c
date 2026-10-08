/* Destroys the field block: stops its sound when active, frees its six buffers, releases its owner
 * and clears the block pointer. */

#include "game/engine.h"

typedef struct {
    void *owner;      /* +0x00 */
    char pad04[4];
    void *bufA;       /* +0x08 */
    void *bufB;       /* +0x0c */
    void *bufC;       /* +0x10 */
    void *bufD;       /* +0x14 */
    void *bufE;       /* +0x18 */
    void *bufF;       /* +0x1c */
} Ov002Block;

typedef struct {
    char pad00[8];
    int active;       /* +0x08 */
} Ov002Handle;

extern Ov002Block *data_ov002_0207f634;
extern Ov002Handle *Ov002_Field_GetBlock194(void);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void VeneerTo_Obj_Destroy(void *p);

void Ov002_DestroyBlock(void) {
    Ov002Block *b = data_ov002_0207f634;
    Ov002Handle *h = Ov002_Field_GetBlock194();

    if (h->active != 0) {
        ForwardToHandlerOrCurrentObject(0, 0x32, 0);
        h->active = 0;
    }
    if (b->bufA != 0) NNSi_FndFreeFromDefaultHeap(b->bufA);
    if (b->bufB != 0) NNSi_FndFreeFromDefaultHeap(b->bufB);
    if (b->bufE != 0) NNSi_FndFreeFromDefaultHeap(b->bufE);
    if (b->bufF != 0) NNSi_FndFreeFromDefaultHeap(b->bufF);
    if (b->bufC != 0) NNSi_FndFreeFromDefaultHeap(b->bufC);
    if (b->bufD != 0) NNSi_FndFreeFromDefaultHeap(b->bufD);
    VeneerTo_Obj_Destroy(b->owner);
    data_ov002_0207f634 = 0;
}
