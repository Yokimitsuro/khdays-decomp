typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long long u64;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022TypeTwoTarget {
    VecFx32 position;
} Ov022TypeTwoTarget;

typedef struct Ov022LowByte16 {
    unsigned short lowByte : 8;
    unsigned short highByte : 8;
} Ov022LowByte16;

typedef struct Ov022LowByte32 {
    unsigned int lowByte : 8;
    unsigned int rest : 24;
} Ov022LowByte32;

typedef struct Ov022Candidate {
    char pad_0000[0x12];
    u16 flags12;
    char pad_0014[0x4c];
    u16 flags60;
    char pad_0062[4];
    s16 group66;
    char pad_0068[0x111];
    u8 special179;
    char pad_017a[0x32];
    u16 flags1ac;
    char pad_01ae[0x2b6];
    u64 flags464;
} Ov022Candidate;

typedef struct Ov022PartNode {
    void *item;
    char pad_0004[4];
    unsigned int flags8;
} Ov022PartNode;

typedef struct Ov022ActorNode {
    char pad_0000[0x80];
    u16 angle80;
} Ov022ActorNode;

typedef struct Ov022Actor {
    u64 flags0;
    char pad_0008[0x18];
    Ov022ActorNode *node20;
    char pad_0024[0x42];
    s16 group66;
    char pad_0068[0x41c];
    u64 flags464;
} Ov022Actor;

typedef struct Ov022SelectorContext {
    unsigned int flags0;
    unsigned int selectionFlags;
    int type;
    Ov022Candidate *typeOneCandidate;
    Ov022PartNode *node;
    char pad_0014[4];
    void *typeTwoEntry;
    Ov022Candidate *typeThreeCandidate;
} Ov022SelectorContext;

extern const s16 data_0203d210[];

extern Ov022SelectorContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern VecFx32 *func_ov022_020881f8(int index);
extern Ov022Actor *func_01fffde0(int index);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern int func_ov022_02084e7c(int index, const VecFx32 *position);
extern Ov022TypeTwoTarget *func_ov002_02076d24(void *entry);
extern int func_ov002_02076d68(void *entry);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *vector);
extern void func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_ov022_020ad44c(VecFx32 *out, Ov022Candidate *candidate);
extern void func_ov022_020852c0(int enabled);

void func_ov022_02085858(void)
{
    Ov022SelectorContext *context;
    int index;
    VecFx32 *origin;
    Ov022Actor *actor;
    int invalid;
    VecFx32 direction;
    VecFx32 facing;
    VecFx32 targetHorizontal;
    VecFx32 originHorizontal;
    VecFx32 candidatePosition;
    VecFx32 generated;

    context = NNSi_FndGetCurrentRootHeap();
    invalid = 0;
    index = func_01fffe14();
    origin = func_ov022_020881f8(index);
    actor = func_01fffde0(index);

    switch (context->type) {
    case 1: {
        int distance = func_01ff8e94(
            (VecFx32 *)((char *)context->node->item + 4), origin);

        if ((((Ov022LowByte32 *)&context->node->flags8)->lowByte & 2) != 0 ||
            (((Ov022LowByte32 *)&context->node->flags8)->lowByte & 1) == 0) {
            invalid = 1;
        }
        if ((context->typeOneCandidate->flags1ac & 2) != 0 ||
            (((Ov022LowByte16 *)&context->typeOneCandidate->flags60)->lowByte &
             1) == 0) {
            invalid = 1;
        }
        if (distance > 0x1e000 &&
            context->typeOneCandidate->special179 != 1) {
            invalid = 1;
        }
        if (invalid == 0 && context->typeOneCandidate->special179 != 1 &&
            func_ov022_02084e7c(index,
                (VecFx32 *)((char *)context->node->item + 4)) == 0) {
            invalid = 1;
        }
        break;
    }

    case 2: {
        int targetValue;
        int distance;
        int angle;
        const s16 *table;

        targetValue = (int)func_ov002_02076d24(context->typeTwoEntry);
        if (targetValue == 0) {
            invalid = 1;
            break;
        }
        distance = func_01ff8e94(
            &((Ov022TypeTwoTarget *)targetValue)->position, origin);
        VEC_Subtract(
            &((Ov022TypeTwoTarget *)targetValue)->position, origin,
            &direction);
        if (VEC_Mag(&direction) != 0) {
            func_01ff8d18(&direction, &direction);
        }

        angle = (u16)(actor->node20->angle80 - 0x8000);
        angle >>= 4;
        table = data_0203d210;
        facing.x = -table[angle << 1];
        facing.z = -table[(angle << 1) + 1];
        direction.y = 0;
        facing.y = 0;

        originHorizontal = *origin;
        targetHorizontal =
            ((Ov022TypeTwoTarget *)targetValue)->position;
        targetHorizontal.y = originHorizontal.y = 0;
        targetValue = func_01ff8e94(&targetHorizontal, &originHorizontal);

        if (VEC_DotProduct(&facing, &direction) < 0x800 &&
            targetValue > 0x1000) {
            invalid = 1;
        }
        if (distance > 0x1e000 ||
            distance > func_ov002_02076d68(context->typeTwoEntry)) {
            invalid = 1;
        }
        break;
    }

    case 3: {
        Ov022Candidate *candidate;

        func_ov022_020ad44c(&generated, context->typeThreeCandidate);
        candidatePosition = generated;
        candidate = context->typeThreeCandidate;
        if (candidate->flags12 == 0) {
            invalid = 1;
        }
        if (candidate->group66 != actor->group66) {
            invalid = 1;
        }
        if ((candidate->flags464 & 0x200000000ULL) != 0) {
            invalid = 1;
        }
        if (func_01ff8e94(&candidatePosition, origin) > 0x1e000) {
            invalid = 1;
        }
        if (invalid == 0 &&
            func_ov022_02084e7c(index, &candidatePosition) == 0) {
            invalid = 1;
        }
        break;
    }

    default:
        break;
    }

    if (invalid != 0) {
        func_ov022_020852c0(0);
    }
}


