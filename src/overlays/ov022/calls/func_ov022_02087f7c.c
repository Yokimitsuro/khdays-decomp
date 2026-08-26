typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022Root {
    char padding000[0x34];
    unsigned char entryCount34;
} Ov022Root;

typedef struct Ov022Actor {
    char padding000[9];
    unsigned char entryId09;
    char padding00a[0x5c];
    short field066;
    char padding068[0x424];
    VecFx32 position48c;
    char padding498[0x1fc];
    unsigned char stateFlags694;
    char padding695[0x2023];
    int verticalOffset26b8;
} Ov022Actor;

extern Ov022Root *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov022_02083f0c(void);
extern int func_ov002_0204cb18(void);
extern int func_ov002_0206aaa0(void);
extern VecFx32 *func_ov002_0204cde8(int owner);
extern int func_01ff8e94(VecFx32 *a, VecFx32 *b);
extern int func_ov022_02083f90(void);
extern void func_ov022_020b2118(int kind, int entryId,
                                VecFx32 *position, int value);

void func_ov022_02087f7c(void)
{
    Ov022Root *root = NNSi_FndGetCurrentRootHeap();
    int owner = func_ov022_02083f0c();
    VecFx32 actorPosition;
    VecFx32 targetPosition;
    int index;
    Ov022Actor *actor;
    char *entryCursor;
    int minusOne;

    if (func_ov002_0204cb18() == 0) {
        return;
    }

    index = 0;
    if (index >= root->entryCount34) {
        return;
    }

    entryCursor = (char *)root;
    minusOne = -1;
    do {
        if (func_ov002_0206aaa0() != 0) {
            actor = *(Ov022Actor **)(*(int *)(entryCursor + 4) + 0x20);
            if (actor->field066 != minusOne &&
                ((unsigned int)(actor->stateFlags694 << 31) >> 31) != 0) {
                actorPosition = actor->position48c;
                targetPosition = *func_ov002_0204cde8(owner);
                if (func_01ff8e94(&actorPosition, &targetPosition) <= 0x3c000) {
                    func_ov022_020b2118(0, actor->entryId09,
                        &actorPosition, func_ov022_02083f90());
                    actorPosition.y += actor->verticalOffset26b8;
                    func_ov022_020b2118(1, actor->entryId09,
                        &actorPosition, func_ov022_02083f90());
                }
            }
        }
        index++;
        entryCursor += 0xc;
    } while (index < root->entryCount34);
}

