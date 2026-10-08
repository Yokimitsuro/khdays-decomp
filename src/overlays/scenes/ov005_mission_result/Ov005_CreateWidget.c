/* Allocates and fills a 0x9c-byte widget from its descriptor: slots, tweens, position and
 * visibility. */

typedef struct {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} NNSFndList;

typedef struct {
    unsigned b0 : 1;
    unsigned b1 : 1;
    unsigned b2 : 1;
    unsigned b3 : 1;
} Flags84;

typedef struct {
    char reserved[0x4a38];
    NNSFndList children;
    char reserved2[0x2c];
    int focused;
    int style;
} Root;

typedef struct {
    int elementId;
    int groupId;
    int keysDefault[2];
    int values10[2];
    int keysAlternate[2];
    int point20[2];
    int point28[2];
    int point30[2];
    unsigned short value38;
    unsigned short value3a;
    int value3c;
    int neighborIds[4];
    int flags;
    int priorityBase;
} WidgetDescriptor;

typedef struct Widget Widget;

struct Widget {
    char reserved00[0xc];
    int elementId;
    int groupId;
    int slots[2];
    unsigned short value1c;
    unsigned short value1e;
    int value20;
    int point24[2];
    int point2c[2];
    int keysDefault[2];
    int values10[2];
    int keysAlternate[2];
    char tween4c[0x1c];
    char tween68[0x1c];
    unsigned int flags;
    Widget *neighbors[4];
    char reserved98[4];
};

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void *MI_CpuFill8(void *dst, unsigned char v, unsigned int n);
extern void *MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void Tween_Clear(void *p);
extern int VeneerTo_SlotTable_AddEntry(Root *self, int key, int a);
extern void SlotTable_SetEntryVelocity(Root *self, int slot, int prio);
extern void SlotTable_SetEntryStyle(Root *self, int slot, int a);
extern void Ov005_EmitSplinePair(Root *self, void *obj, int n, void *a, void *b, int span);
extern void Ov005_ReleaseTwoSlotsEx(Root *self, void *obj, void *a);
extern void Slot_SetVisible(Root *self, int slot, int a);
extern void SlotTable_SetEntryFlag(Root *self, int slot, int a);
extern void NNS_FndAppendListObject(NNSFndList *list, void *obj);

void *Ov005_CreateWidget(Root *self, WidgetDescriptor *desc) {
    Widget *obj;
    int i;
    char *keys;
    obj = NNSi_FndAllocFromDefaultExpHeap(0x9c);
    if (obj != 0) {
        MI_CpuFill8(obj, 0, 0x9c);
        obj->elementId = desc->elementId;
        Tween_Clear(obj->tween4c);
        Tween_Clear(obj->tween68);

        if (desc->flags & 1) {
            if (desc->keysAlternate[0] >= 0 || desc->keysAlternate[1] >= 0) {
                keys = (char *)desc->keysAlternate;
            } else {
                keys = (char *)desc->keysDefault;
            }
            ((Flags84 *)&obj->flags)->b0 = 1;
        } else {
            keys = (char *)desc->keysDefault;
            ((Flags84 *)&obj->flags)->b0 = 0;
        }

        for (i = 0; i < 2; i++) {
            obj->keysDefault[i] = desc->keysDefault[i];
            obj->values10[i] = desc->values10[i];
            obj->keysAlternate[i] = desc->keysAlternate[i];

            if (((int *)keys)[i] >= 0) {
                obj->slots[i] = VeneerTo_SlotTable_AddEntry(self, ((int *)keys)[i], desc->groupId);
                SlotTable_SetEntryVelocity(self, obj->slots[i], (unsigned char)(desc->priorityBase + 1 - i));
                SlotTable_SetEntryStyle(self, obj->slots[i], self->style);
            } else {
                obj->slots[i] = -1;
            }
        }

        obj->groupId = desc->groupId;
        obj->value1c = desc->value38;
        obj->value1e = desc->value3a;
        obj->value20 = desc->value3c;

        if (desc->flags & 4) {
            Ov005_EmitSplinePair(self, obj, 2, desc->point20, desc->point30, 0x3e8);
            MI_CpuCopy8(desc->point28, obj->point24, 8);
            obj->flags |= 4;
        } else {
            Ov005_ReleaseTwoSlotsEx(self, obj, desc->point30);
            obj->flags &= ~4;
        }
        MI_CpuCopy8(desc->point30, obj->point2c, 8);

        if (desc->flags & 2) {
            for (i = 0; i < 2; i++) {
                if (obj->slots[i] != -1) {
                    Slot_SetVisible(self, obj->slots[i], 0);
                }
            }
            obj->flags &= ~2;
        } else {
            obj->flags |= 2;
        }

        if (desc->flags & 0x10) {
            for (i = 0; i < 2; i++) {
                if (obj->slots[i] != -1) {
                    SlotTable_SetEntryFlag(self, obj->slots[i], 1);
                }
            }
        }

        ((Flags84 *)&obj->flags)->b3 = (desc->flags & 8) != 0;
        NNS_FndAppendListObject(&self->children, obj);
    }

    return obj;
}
