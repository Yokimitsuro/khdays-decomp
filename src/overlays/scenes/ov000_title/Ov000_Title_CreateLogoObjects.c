/* Loads the title's cell resource and creates the ten logo objects at their positions. */

#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void ObjNode_InitFromDesc(void *mgr, void *desc);
extern void G2x_SetBlendAlpha_(int reg, int a, int b, int c, int d);
extern int VeneerTo_SlotTable_AddEntry(void *mgr, int index, int);
extern void Slot_ForwardToEntry(void *mgr, int obj, int);
extern void Slot_ClearFlagBit1(void *mgr, int obj);
extern void Slot_SetMode2Bit(void *mgr, int obj, int);
extern void Slot_SetPosition(void *mgr, int obj, int *params);

typedef struct Ov000ResourceDescriptor {
    unsigned int address;
    int kind;
    int reserved0;
    int reserved1;
} Ov000ResourceDescriptor;

typedef struct Ov000ObjectSlot {
    int handle;
} Ov000ObjectSlot;

typedef struct Ov000BootGridContext {
    int resourceFallback;
    int resourcePrimary;
    int resourceAlternate;
    u8 pad_000c[0x1a4];
    u8 objectManager[1];
    u8 pad_01b1[0x4a53];
    Ov000ObjectSlot objects[10];
} Ov000BootGridContext;

typedef struct Ov000ObjectPosition {
    int x;
    int y;
} Ov000ObjectPosition;

void Ov000_Title_CreateLogoObjects(void) {
    Ov000BootGridContext *context =
        (Ov000BootGridContext *)NNSi_FndGetCurrentRootHeap();
    unsigned int address;
    int i;
    int object;
    int mode = 0;
    int j;
    Ov000ResourceDescriptor descriptor;

    if (context->resourceAlternate != 0) {
        address =
            ((context->resourceAlternate + 0x8000 & 0xfffffc) << 7) |
            0x80000001;
    } else {
        address =
            ((context->resourcePrimary + 0x8000 & 0xfffffc) << 7) | 0x80000002;
    }
    descriptor.address = address;
    descriptor.kind = 2;
    descriptor.reserved0 = 0;
    descriptor.reserved1 = 0;
    ObjNode_InitFromDesc(context->objectManager, &descriptor);

    G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, 0, 0x10);

    for (i = 0; i < 10; i++) {
        context->objects[i].handle =
            VeneerTo_SlotTable_AddEntry(context->objectManager, i, 0);
    }

    for (j = 0; j < 10; j++) {
        Ov000ObjectPosition position;
        object = context->objects[j].handle;
        int active = 1;

        switch (j) {
        case 0:
            position.x = 0x8000;
            position.y = 0x84000;
            mode = 1;
            break;
        case 5:
            position.x = 0;
            position.y = 0x58000;
            mode = 0;
            break;
        case 1:
        case 3:
        case 6:
        case 8:
            position.x = 0;
            position.y = 0x74000;
            mode = 0;
            break;
        case 2:
        case 4:
        case 7:
        case 9:
            position.x = 0;
            position.y = 0x90000;
            mode = 0;
            break;
        default:
            active = 0;
            break;
        }
        if (active) {
            Slot_ForwardToEntry(context->objectManager, object, 0);
            if (mode == 0) {
                Slot_ClearFlagBit1(context->objectManager, object);
            }
            Slot_SetMode2Bit(context->objectManager, object, 1);
            Slot_SetPosition(context->objectManager, object, (int *)&position);
        }
    }
}
