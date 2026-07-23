typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov000ObjectList {
    u8 data[0x4a80];
} Ov000ObjectList;

typedef struct Ov000SelectionGroup {
    u8 pad_00[0x10];
    int state;
    u8 pad_14[8];
    int mode;
} Ov000SelectionGroup;

typedef struct Ov000SceneContext {
    u8 pad_0000[0x4c];
    Ov000ObjectList objectList;
    u8 positionShifted;
    u8 pad_4acd[0x43];
    Ov000SelectionGroup selectionGroups[4];
} Ov000SceneContext;

typedef struct Ov000EntryIdGrid {
    int ids[4][8];
} Ov000EntryIdGrid;

extern Ov000SceneContext *volatile data_ov000_0205ac24;
extern Ov000EntryIdGrid data_ov000_0205a7ac;

extern int *func_ov000_02055b48(Ov000ObjectList *objectList, int id);
extern void func_ov000_02055cb4(Ov000ObjectList *objectList, int *entry,
                                int visible);
extern void func_ov000_02055d54(Ov000ObjectList *objectList, int *entry,
                                u16 mode);
extern void func_ov000_02055e10(Ov000ObjectList *objectList, int *entry,
                                int mode);

void func_ov000_020506d0(void) {
    Ov000SceneContext *context = data_ov000_0205ac24;
    int group = 0;
    int groupOffset = 0;
    unsigned int slot;

    do {
        Ov000SelectionGroup *selectionGroup =
            (Ov000SelectionGroup *)((u8 *)data_ov000_0205ac24 +
                                    0x4b10 + groupOffset);
        int *entry =
            func_ov000_02055b48(&context->objectList, group + 1);

        func_ov000_02055e10(&context->objectList, entry, 3);
        if (group >= 3) {
            func_ov000_02055d54(&context->objectList, entry, 5);
        } else if (selectionGroup->state == 1) {
            func_ov000_02055d54(
                &context->objectList, entry,
                (u16)(data_ov000_0205ac24->selectionGroups[group].mode + 2));
        } else if (selectionGroup->state == 2) {
            func_ov000_02055d54(&context->objectList, entry, 0);
        } else {
            func_ov000_02055d54(&context->objectList, entry, 1);
        }

        {
            for (slot = 0; slot < 8; slot++) {
                int id = data_ov000_0205a7ac.ids[group][slot];

                if (id != 0) {
                    entry = func_ov000_02055b48(&context->objectList, id);
                    switch (slot) {
                    case 0:
                        if (data_ov000_0205ac24->positionShifted == 0 &&
                            group >= 3) {
                            func_ov000_02055cb4(&context->objectList, entry, 0);
                        } else {
                            func_ov000_02055cb4(&context->objectList, entry, 1);
                        }
                        break;
                    case 1:
                        func_ov000_02055cb4(&context->objectList, entry, 1);
                        break;
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        if (group < 3) {
                            if (selectionGroup->state == 1) {
                                func_ov000_02055cb4(
                                    &context->objectList, entry, 1);
                            } else {
                                func_ov000_02055cb4(
                                    &context->objectList, entry, 0);
                            }
                        }
                        break;
                    }
                }
            }
        }

        group++;
        groupOffset += 0x20;
    } while (group < 4);
}
