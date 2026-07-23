typedef unsigned char u8;

typedef struct {
    int ids[3];
} EntryIdGroup3;

typedef struct {
    int ids[4];
} EntryIdGroup4;

typedef struct {
    u8 pad_0000[0x78];
    u8 objectList[1];
} Ov000SubSceneContext;

extern EntryIdGroup3 data_ov000_0205a82c;
extern EntryIdGroup4 data_ov000_0205a848;
extern Ov000SubSceneContext *volatile data_ov000_0205ac28;
extern int func_ov000_02055b48(int list, int id);
extern void func_ov000_02055cb4(int list, int entry, int visible);

void func_ov000_02053b0c(int mode) {
    Ov000SubSceneContext *volatile *contextSlot = &data_ov000_0205ac28;
    Ov000SubSceneContext *context;
    EntryIdGroup3 group3 = data_ov000_0205a82c;
    EntryIdGroup4 group4 = data_ov000_0205a848;

    {
        unsigned int i;
        int entry;

        context = *contextSlot;

        switch (mode) {
        case 2:
            for (i = 0; i < 3; i++) {
                entry = func_ov000_02055b48((int)context->objectList,
                                            group3.ids[i]);
                func_ov000_02055cb4((int)context->objectList, entry, 1);
            }
            for (i = 0; i < 4; i++) {
                entry = func_ov000_02055b48((int)context->objectList,
                                            group4.ids[i]);
                func_ov000_02055cb4((int)context->objectList, entry, 0);
            }
            return;
        case 3:
            for (i = 0; i < 3; i++) {
                entry = func_ov000_02055b48((int)context->objectList,
                                            group3.ids[i]);
                func_ov000_02055cb4((int)context->objectList, entry, 0);
            }
            for (i = 0; i < 4; i++) {
                entry = func_ov000_02055b48((int)context->objectList,
                                            group4.ids[i]);
                func_ov000_02055cb4((int)context->objectList, entry, 1);
            }
            return;
        }
    }
}
