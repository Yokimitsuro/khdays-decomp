typedef int (*Ov022InitCallback)(void *object);

typedef struct Ov022CameraRoot {
    int flags;
    char padding004[0x34];
    int instance;
} Ov022CameraRoot;

typedef struct Ov022ConfigRecord {
    unsigned char type;
    unsigned char value;
    unsigned char padding002;
    unsigned char special;
    unsigned short padding004;
    unsigned short limit;
    char padding008[0xfc];
} Ov022ConfigRecord;

typedef struct Ov022MetadataRecord {
    char padding000[0x24];
    signed char flags;
    signed char entryValue;
    char padding026[0x1e];
} Ov022MetadataRecord;

typedef struct Ov022CallbackArgs {
    Ov022InitCallback callback;
    int padding004;
    int type;
    int duplicateType;
    unsigned char value;
    char padding011[3];
    int sessionActive;
    int inputValue;
    int inputValue4;
    int allowed;
    int specialHandled;
} Ov022CallbackArgs;

typedef struct Ov022PlayerEntry {
    unsigned long long flags;
    char padding008[0xa];
    unsigned short selectedLimit;
    char padding014[2];
    unsigned short currentLimit;
} Ov022PlayerEntry;

extern Ov022CameraRoot *NNSi_FndGetCurrentRootHeap(void);
extern int func_02030670(void);
extern int func_ov022_020882f8(void);
extern int func_02020a9c(void);
extern int func_ov029_020b2ee0(int index, int group);
extern Ov022PlayerEntry *func_01fffde0(int index);
extern int func_02023930(void *classData, int argument);

extern unsigned char data_02042a1d;
extern Ov022MetadataRecord data_0204c3d8[];
extern Ov022ConfigRecord data_0204c678[];
extern Ov022CallbackArgs data_ov022_020b2e78;
extern unsigned char data_0204c240;
extern char data_ov022_020b2e80;
extern char data_ov022_020b2944;

void func_ov022_0208700c(int *input)
{
    unsigned char *rootFlags;
    Ov022CameraRoot *root = NNSi_FndGetCurrentRootHeap();
    int index = 0;
    int count = data_02042a1d;

    if (count > 0 && count > 0) {
        int *inputCursor = input;
        unsigned char *stateCursor = (unsigned char *)root;
        Ov022MetadataRecord *metadata = data_0204c3d8;
        Ov022ConfigRecord *config = data_0204c678;
        rootFlags = (unsigned char *)root + 0x3c;
        Ov022CallbackArgs *args = &data_ov022_020b2e78;
        int clearBit0Mask = 1;
        int clearBit4Mask = 0x10;

        do {
            unsigned char special = config->special;
            unsigned char type = config->type;
            Ov022PlayerEntry *entry;
            unsigned short limit;
            int inputValue;
            int inputValue4;

            switch (special) {
            case 0x14:
                special = 0;
                args->specialHandled = 1;
                break;
            case 0x15:
                special = 0xe;
                args->specialHandled = 1;
                break;
            default:
                args->specialHandled = 0;
                break;
            }
            args->duplicateType = type;
            args->type = config->type;
            args->value = config->value;
            args->sessionActive = func_02030670();
            if (input != 0) {
                inputValue = inputCursor[0];
            } else {
                if (index > 0 && func_02030670() == 0) {
                    inputValue = 1;
                } else {
                    inputValue = 0;
                }
            }
            args->inputValue = inputValue;
            if (input != 0) {
                inputValue4 = inputCursor[4];
            } else {
                inputValue4 = 0;
            }
            args->inputValue4 = inputValue4;
            args->allowed = 1;
            if (func_ov022_020882f8() > 2 || func_02020a9c() == 0x2a) {
                args->allowed = 0;
            }
            if (*(unsigned short *)((char *)&data_0204c240 + 2) == 0x1f48) {
                args->inputValue4 = 1;
            }
            stateCursor[0xe] = config->value;
            stateCursor[0xc] = special;
            args->callback = 0;
            *(int *)(stateCursor + 8) = func_ov029_020b2ee0(index, special);
            *(int *)(stateCursor + 4) = args->callback(&data_ov022_020b2e80);
            *rootFlags = (*rootFlags & ~clearBit0Mask) | 1;
            *rootFlags &= ~clearBit4Mask;
            entry = func_01fffde0(index);
            if (*(int *)((char *)entry + 0x4ec) != 0 && input[8] != 0 &&
                func_02030670() == 0) {
                *(int *)(*(int *)((char *)entry + 0x4ec) + 0x1dc) = 0x3c000;
                *(int *)(*(int *)((char *)entry + 0x4ec) + 0x1e0) = 0x3c000;
            }
            limit = entry->currentLimit;
            if (config->limit <= entry->currentLimit) {
                limit = config->limit;
            }
            entry->selectedLimit = limit;
            if ((((int)metadata->flags << 31) >> 31) != 0) {
                entry->flags |= 0x4000000000ULL;
            }
            if ((((int)metadata->flags << 30) >> 31) != 0) {
                entry->flags |= 0x2000000000ULL;
            }
            *(signed char *)((char *)entry + 0x2bb0) = metadata->entryValue;
            stateCursor += 0xc;
            config++;
            inputCursor++;
            metadata++;
            index++;
        } while (index < data_02042a1d);
    }
    if (func_02030670() != 0) {
        root->flags |= 2;
    }
    root->instance = func_02023930(&data_ov022_020b2944, 0);
}
