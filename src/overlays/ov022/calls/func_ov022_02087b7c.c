typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022NetRecord {
    unsigned long long state;
    VecFx32 position;
    unsigned int field14;
    unsigned short angle18;
    unsigned short field1a;
    short field1c;
    unsigned short field1e;
    unsigned short field20;
    short field22;
    unsigned short packed24;
    unsigned short packed26;
    unsigned int packed28;
    signed char packed2c;
    char padding2d[3];
} Ov022NetRecord;

typedef struct Ov022PackedWord {
    unsigned int low4 : 4;
    unsigned int mid10 : 10;
    unsigned int high10 : 10;
    unsigned int bit24 : 1;
    unsigned int rest : 7;
} Ov022PackedWord;

typedef struct Ov022RootBits {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char rest : 3;
} Ov022RootBits;

typedef struct Ov022Root {
    unsigned int flags;
    char padding004[0x30];
    unsigned char entryCount34;
    char padding035[7];
    Ov022RootBits stateBits3c;
} Ov022Root;

typedef struct Ov022Actor {
    char padding000[0x18];
    unsigned short flags018;
    unsigned short flags01a;
    char padding01c[4];
    int child20;
    char padding024[0x42];
    short field066;
    char padding068[0x3fc];
    unsigned long long state464;
    char padding46c[0xc];
    unsigned short angle478;
    char padding47a[0x12];
    VecFx32 position48c;
    char padding498[0x4b];
    unsigned char packedLow4_4e3;
    unsigned short packedMid10_4e4;
    unsigned short packedHigh10_4e6;
    char padding4e8[8];
    unsigned char packedLow2_4f0;
    unsigned char packedHigh_4f1;
    unsigned char packedShift3_4f2;
    unsigned char padding4f3;
    unsigned int packedBit2_4f4;
    char padding4f8[0x10];
    int field508;
    unsigned int field50c;
    unsigned short field510;
    char padding512[0x25a1];
    unsigned char packed2ab3;
    unsigned char packed2ab4;
    unsigned char packed2ab5;
    char padding2ab6[2];
    unsigned char packed2ab8;
    char padding2ab9;
    short field2aba;
} Ov022Actor;

extern char data_ov022_020b2e78[];

extern int func_02030788(void);
extern int CARD_GetResultCode_0x0202bfb8(void);
extern int func_ov022_0208a28c(void);
extern void func_02030de4(int index);
extern int func_01fffe14(void);
extern void func_ov022_020acc94(Ov022Actor *actor, int value);
extern void func_ov022_020acfa4(Ov022Actor *actor, int bit2,
                                void *arg2, void *arg3);
extern int func_ov022_020886f8(int index);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cb70(int arg0, int arg1, int arg2);
extern void func_ov022_02087298(int index);
extern void func_ov022_02088428(int index, int value);
extern void func_0202b450(void *child, VecFx32 *position);
extern void func_ov022_020a0678(Ov022Actor *actor, int value);

int func_ov022_02087b7c(void)
{
    Ov022Root *root = *(Ov022Root **)(data_ov022_020b2e78 + 4);
    int cardResult;
    char *resource;
    Ov022Actor *searchActor;
    int searchIndex;
    char *searchCursor;
    int searchOffset;
    int packedClass;
    Ov022NetRecord *record;
    int changed;
    char *entryCursor;
    unsigned int index;
    Ov022Actor *actor;
    unsigned int packedWord;
    unsigned int packedBit2;
    VecFx32 position;
    short localField66 = -1;

    if (func_02030788() == 0) {
        return 0;
    }

    cardResult = CARD_GetResultCode_0x0202bfb8();
    resource = (char *)func_ov022_0208a28c();
    if (*(unsigned char *)(resource + 0xc0) == 0) {
        func_02030de4(0);
    }
    if (*(unsigned char *)(resource + 0xc0) == 0) {
        return 0;
    }

    searchIndex = 0;
    if (searchIndex < root->entryCount34) {
        searchCursor = (char *)root;
        searchOffset = 0;
        do {
            searchActor = *(Ov022Actor **)(*(int *)(searchCursor + 4) + 0x20);

            if (*(unsigned char *)(*(int *)(data_ov022_020b2e78 + 4) +
                                   searchOffset + 0xe) == func_02030788()) {
                localField66 = searchActor->field066;
                break;
            }
            searchIndex++;
            searchCursor += 0xc;
            searchOffset += 0xc;
        } while (searchIndex < root->entryCount34);
    }

    index = 0;
    if ((int)index < root->entryCount34) {
        entryCursor = (char *)root;
        do {
            actor = *(Ov022Actor **)(*(int *)(entryCursor + 4) + 0x20);
            record = (Ov022NetRecord *)(resource +
                *(unsigned char *)(entryCursor + 0xe) * 0x30);
            changed = 0;

            actor->flags01a = changed;
            actor->flags018 = actor->flags01a;
            actor->state464 = 0;
            func_ov022_020acc94(actor, record->field20);

            packedWord = record->packed28;
            packedClass = packedWord >> 29;
            actor->field508 = record->field1c;
            actor->field50c = record->field14;
            actor->field510 = record->field1a;
            actor->packedLow4_4e3 =
                ((Ov022PackedWord *)&record->packed28)->low4;
            actor->packedMid10_4e4 =
                ((Ov022PackedWord *)&record->packed28)->mid10;
            actor->packedHigh10_4e6 =
                ((Ov022PackedWord *)&record->packed28)->high10;
            actor->angle478 = record->field1e;
            actor->field2aba = record->field22;
            actor->packed2ab8 =
                (unsigned int)(record->packed26 << 16) >> 28;
            actor->packedLow2_4f0 =
                (unsigned int)(record->packed24 << 30) >> 30;
            actor->packedHigh_4f1 =
                (unsigned int)(record->packed24 << 16) >> 24;
            actor->packedShift3_4f2 =
                (unsigned int)(record->packed24 << 24) >> 27;
            packedBit2 =
                (unsigned int)(record->packed24 << 29) >> 31;
            actor->packedBit2_4f4 = packedBit2;
            func_ov022_020acfa4(actor, packedBit2,
                                (char *)actor + 0x2a00,
                                (char *)actor + 0x2000);

            {
                char *packedStateBase = (char *)actor + 0x2aa4;

                *(unsigned char *)(packedStateBase + 0xf) =
                    (unsigned int)(record->packed26 << 28) >> 28;
                *(unsigned char *)(packedStateBase + 0x11) =
                    (unsigned int)(record->packed26 << 23) >> 27;
                *(unsigned char *)(packedStateBase + 0x10) =
                    (unsigned int)(record->packed26 << 20) >> 29;
            }

            if (packedClass < cardResult) {
                if (index == (unsigned int)func_01fffe14()) {
                    root->stateBits3c.bit4 =
                        ((Ov022PackedWord *)&record->packed28)->bit24;
                    if ((((int)record->packed2c << 28) >> 28) > 0 &&
                        func_ov022_020886f8(index) == 0) {
                        int callbackOwner = func_ov022_02083f0c();
                        int packedByte = record->packed2c;

                        func_ov002_0204cb70(callbackOwner,
                            (packedByte << 28) >> 28,
                            (packedByte << 24) >> 28);
                    }
                    if ((((unsigned int)*(unsigned char *)
                          ((char *)root + 0x3c) << 30) >> 31) == 0) {
                        goto apply_entry;
                    } else {
                        continue;
                    }
                } else if (packedClass != actor->field066) {
                    func_ov022_02087298(index);
                    func_ov022_02088428(index, packedClass);
                    changed = 1;
                }

            apply_entry:
                position = record->position;
                {
                    unsigned short childAngle = record->angle18;
                    char *child = (char *)actor->child20;

                    if ((*(unsigned int *)child & 0x20) == 0) {
                        *(short *)(child + 0x80) = childAngle + 0x8000;
                        *(unsigned short *)(child + 4) |= 0x20;
                    }
                }
                func_0202b450((void *)actor->child20, &position);
                actor->position48c = position;
                actor->state464 = record->state;
                if (changed) {
                    actor->state464 |= 0x200000000ULL;
                }

                searchIndex = 0;
                if (localField66 != -1 &&
                    localField66 == actor->field066 && !changed) {
                    searchIndex = 1;
                }
                func_ov022_020a0678(actor, searchIndex);
            }

        } while ((entryCursor += 0xc, index++,
                  (int)index < root->entryCount34));
    }

    return 1;
}

