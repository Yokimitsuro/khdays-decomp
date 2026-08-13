typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int radialX;                   /* +0x00 */
    int radialZ;                   /* +0x04 */
    char pad08[4];
    int angleScale;                /* +0x0c */
    int range;                     /* +0x10 */
    char pad14[0x24];
    int stateFlags;                /* +0x38 */
    int featureFlags;              /* +0x3c */
    int field40;
    int selector;                  /* +0x44 */
    int field48;
    int field4c;
    char pad50[4];
    int secondary54;
    int field58;
    int secondary5c;
    int secondary60;
    char pad64[0x18];
    int primary7c;
    int field80;
    int primary84;
    int primary88;
    VecFx32 origin;                /* +0x8c */
    int field98;
    int field9c;
    unsigned short orbitAngleA;    /* +0xa0 */
    unsigned short orbitAngleB;    /* +0xa2 */
    int fielda4;
    int fielda8;
    int fieldac;
    int fieldb0;
    int limitB4;
    int limitB8;
    int fieldbc;
    int fieldc0;
    char padc4[0x0c];
    int fieldd0;
    int fieldd4;
    int fieldd8;
    int fielddc;
    int enabled;                   /* +0xe0 */
    int fielde4;
    int fielde8;
    int fieldec;
    int fieldf0;
    char padf4[6];
    unsigned short modeCount;      /* +0xfa */
} Ov002WorldState;

extern Ov002WorldState *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_02050b90(int selector);
extern int func_ov002_02050b68(int selector);
extern int func_ov002_02050a54(int selector);
extern int func_020235d0(int field, int kind);
extern void func_02023c60(unsigned int *state);
extern int func_02023bf0(void);
extern void func_ov002_0204cce0(int actor, const VecFx32 *origin);
extern void func_ov002_0204d170(void);

extern VecFx32 data_02041dc8;
extern const short data_0203d210[];

void *func_ov002_0204cefc(int enabled)
{
    Ov002WorldState *state;
    int query;
    int tableIndex;

    state = NNSi_FndGetCurrentRootHeap();
    state->stateFlags = 3;
    state->featureFlags = 0;
    state->field4c = 0;
    state->field40 = 0;
    state->field9c = 0;
    state->selector = 0;
    state->field48 = 0;
    state->field58 = 0;
    state->fielda4 = 0;
    state->fielda8 = 0;
    state->fieldac = 0;
    state->fieldb0 = 0;
    state->fieldf0 = 0;
    state->modeCount = 3;
    state->fielde4 = 0;
    state->fielde8 = 0;
    state->fieldec = 0;
    state->field80 = 0;

    state->primary7c = func_ov002_02050b90(state->selector);
    state->primary84 = func_ov002_02050b68(state->selector);
    state->primary88 = func_ov002_02050a54(state->selector);
    state->origin = data_02041dc8;
    state->field98 = 0;
    state->fieldd0 = 0;
    state->fieldd4 = 0;
    state->fieldd8 = 0;
    state->fielddc = 0;
    state->fieldbc = 0;
    state->fieldc0 = 0;
    state->limitB8 = 0x1f;
    state->limitB4 = 0x1f;

    state->secondary54 = func_ov002_02050b90(state->selector);
    state->secondary5c = func_ov002_02050b68(state->selector);
    state->secondary60 = func_ov002_02050a54(state->selector);
    state->orbitAngleA = 0x1555;
    state->orbitAngleB = 0x1555;

    if (func_020235d0(0x37c4, 1) == 1)
        state->featureFlags |= 0x20;
    if (func_020235d0(0x37bf, 1) == 1) {
        state->featureFlags |= 1;
        state->stateFlags |= 0x10000000;
    }

    query = func_020235d0(0x37c0, 2);
    if (query == 0)
        state->featureFlags |= 2;
    if (query == 2)
        state->featureFlags |= 4;
    if (func_020235d0(0x37c2, 1) == 1)
        state->featureFlags |= 8;
    if (func_020235d0(0x37c3, 1) == 1)
        state->featureFlags |= 0x10;

    state->enabled = enabled != 0;
    func_02023c60((unsigned int *)state);
    state->range = 0x6a4000;
    state->angleScale = 0x19a;
    tableIndex = ((int)state->orbitAngleA >> 4) * 2;
    state->radialX = data_0203d210[tableIndex];
    tableIndex = ((int)state->orbitAngleB >> 4) * 2;
    state->radialZ = data_0203d210[tableIndex + 1];

    func_ov002_0204cce0(func_02023bf0(), &data_02041dc8);
    return (void *)func_ov002_0204d170;
}
