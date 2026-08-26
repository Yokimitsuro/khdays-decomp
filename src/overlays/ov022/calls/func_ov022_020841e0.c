typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed long long s64;

typedef struct Ov022LowByteBits {
    unsigned short lowByte : 8;
    unsigned short highByte : 8;
} Ov022LowByteBits;

typedef struct Ov022RegisterState {
    int contextType;
    int index;
    struct Ov022Candidate *candidate;
} Ov022RegisterState;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022SelectionRecord {
    int distance;
    int unused;
    int kind;
} Ov022SelectionRecord;

typedef struct Ov022Candidate {
    char pad_0000[4];
    struct Ov022Candidate *next;
    char pad_0008[0xa];
    u16 flags12;
    char pad_0014[0x4c];
    u16 flags60;
    char pad_0062[4];
    s16 group66;
    char pad_0068[0xc];
    VecFx32 position74;
    char pad_0080[0x12c];
    u16 flags1ac;
    char pad_01ae[0x6a];
    s16 state218;
    char pad_021a[0x24a];
    s64 flags464;
    char pad_046c[0x80];
    void *candidateList4ec;
} Ov022Candidate;

typedef struct Ov022SelectorContext {
    int flags;
    char selectionState[4];
    int type;
    Ov022Candidate *typeOneCandidate;
    void *traversalNode;
    char pad_0014[4];
    Ov022Candidate *typeTwoCandidate;
    Ov022Candidate *typeThreeCandidate;
} Ov022SelectorContext;

extern u8 data_0204c248[];
extern u8 data_0204c240;

extern Ov022SelectorContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern Ov022Candidate *func_01fffde0(int index);
extern void *func_01fffdac(void *list);
extern Ov022Candidate *func_01fffd70(void *list);
extern Ov022Candidate *func_01fffd8c(void *list);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 *func_ov022_020881f8(int index);
extern int func_ov022_02083f0c(void);
extern VecFx32 *func_ov002_0204cde8(int value);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern s16 func_ov022_02088474(int index);
extern int func_ov002_02072754(int value);
extern Ov022Candidate *func_ov002_02076688(unsigned int index);
extern int func_ov002_02076d24(Ov022Candidate *candidate);
extern int func_ov002_02076d68(Ov022Candidate *candidate);
extern int func_ov022_02084668(const VecFx32 *position, const VecFx32 *basis,
                               int turn, int bound, int selectorId,
                               int *newBound);
extern void func_ov022_02084810(int *state, Ov022Candidate *candidate,
                                const Ov022SelectionRecord *record);
extern u8 func_ov022_020882f8(void);
extern void func_ov022_020ad44c(VecFx32 *out, Ov022Candidate *candidate);
extern void func_ov022_02084880(int *state, Ov022Candidate *candidate,
                                const Ov022SelectionRecord *record);
extern int func_ov022_02085140(Ov022Candidate *candidate);
extern int func_ov022_02084f34(int *state, void *node, int value);

int func_ov022_020841e0(int selectorId, const VecFx32 *requestedPosition)
{
    Ov022SelectorContext *context;
    VecFx32 delta;
    VecFx32 basis;
    VecFx32 testPosition;
    Ov022SelectionRecord firstRecord;
    VecFx32 candidatePosition;
    Ov022SelectionRecord secondRecord;
    int newBound;
    int distance;
    int result = 0;
    VecFx32 *origin;
    Ov022Candidate *currentCandidate;
    Ov022Candidate *typeOneCandidate;
    Ov022Candidate *typeTwoCandidate;
    Ov022Candidate *typeThreeCandidate;
    int currentIndex;
    int turn;
    int bound;
    Ov022Candidate *entryCandidate;
    int callbackPosition;
    Ov022RegisterState registerState;

    registerState.candidate = 0;
    registerState.index = 0;
    context = NNSi_FndGetCurrentRootHeap();
    currentIndex = func_01fffe14();

    switch (context->type) {
    case 1:
        typeOneCandidate = context->typeOneCandidate;
        registerState.contextType = 1;
        break;
    case 2:
        typeTwoCandidate = context->typeTwoCandidate;
        registerState.contextType = 2;
        break;
    case 3:
        typeThreeCandidate = context->typeThreeCandidate;
        registerState.contextType = 3;
        break;
    default:
        registerState.contextType = 0;
        break;
    }

    origin = func_ov022_020881f8(func_01fffe14());
    currentCandidate = func_01fffde0(func_01fffe14());
    VEC_Subtract(origin, func_ov002_0204cde8(func_ov022_02083f0c()), &basis);

    if (requestedPosition != 0) {
        testPosition = *requestedPosition;
    } else {
        VEC_Add(origin, &basis, &testPosition);
    }
    VEC_Subtract(&testPosition, origin, &delta);

    turn = (int)(((s64)delta.x * basis.z + 0x800) >> 12) -
           (int)(((s64)delta.z * basis.x + 0x800) >> 12);
    bound = selectorId == 0x200 ? 0x7fffffff : (int)0x80000000;

    entryCandidate = func_ov002_02076688((u16)func_ov002_02072754(
        func_ov022_02088474(currentIndex)));
    while (entryCandidate != 0) {
        if (registerState.contextType == 2 &&
            typeTwoCandidate == entryCandidate) {
            goto next_entry_candidate;
        }
        callbackPosition = func_ov002_02076d24(entryCandidate);

        if (callbackPosition != 0 && (entryCandidate->flags12 & 8) != 0) {
            distance = func_01ff8e94((VecFx32 *)callbackPosition, origin);
            if (distance <= func_ov002_02076d68(entryCandidate) &&
                distance <= 0x1e000 &&
                func_ov022_02084668((VecFx32 *)callbackPosition, &basis, turn, bound,
                                    selectorId, &newBound) != 0) {
                firstRecord.distance = distance;
                firstRecord.unused = 0;
                firstRecord.kind = 2;
                func_ov022_02084810((int *)context->selectionState, entryCandidate,
                                    &firstRecord);
                result = 1;
                bound = newBound;
            }
        }
next_entry_candidate:
        entryCandidate = entryCandidate->next;
    }

    if (data_0204c248[0xb] != 0 && (data_0204c240 & 4) != 0) {
        for (registerState.index = 0;
             registerState.index < func_ov022_020882f8();
             registerState.index++) {
            if (registerState.index == func_01fffe14()) {
                continue;
            }
            registerState.candidate = func_01fffde0(registerState.index);
            if (registerState.contextType == 3 &&
                typeThreeCandidate == registerState.candidate) {
                continue;
            }
            if (registerState.candidate->flags12 == 0 ||
                registerState.candidate->group66 != currentCandidate->group66 ||
                (registerState.candidate->flags464 & 0x200000000LL) != 0) {
                continue;
            }
            func_ov022_020ad44c(&candidatePosition, registerState.candidate);
            distance = func_01ff8e94(&candidatePosition, origin);
            if (distance > 0x1e000 ||
                func_ov022_02084668(&candidatePosition, &basis, turn, bound,
                                    selectorId, &newBound) == 0) {
                continue;
            }
            secondRecord.distance = distance;
            secondRecord.unused = 0;
            secondRecord.kind = 3;
            func_ov022_02084880((int *)context->selectionState, registerState.candidate,
                                &secondRecord);
            result = 1;
            bound = newBound;
        }
    }

    if (currentCandidate->candidateList4ec != 0) {
        void *listOwner = *(void **)((char *)currentCandidate->candidateList4ec + 4);
        void *iterator;
        Ov022Candidate *linkedCandidate;

        if (listOwner == 0) {
            return result;
        }
        iterator = func_01fffd70((char *)listOwner + 0x80);
        linkedCandidate = iterator == 0 ? 0 : *(Ov022Candidate **)iterator;
        while (linkedCandidate != 0) {
            if ((linkedCandidate->flags1ac & 2) == 0 &&
                (((Ov022LowByteBits *)&linkedCandidate->flags60)->lowByte & 1) != 0 &&
                linkedCandidate->state218 != 0 &&
                !(registerState.contextType == 1 &&
                  typeOneCandidate == linkedCandidate) &&
                func_ov022_02084668(&linkedCandidate->position74, &basis, turn, bound,
                                    selectorId, &newBound) != 0 &&
                func_ov022_02085140(linkedCandidate) != 0) {
                result = 1;
                bound = newBound;
            }
            iterator = func_01fffd8c((char *)listOwner + 0x80);
            linkedCandidate = iterator == 0 ? 0 : *(Ov022Candidate **)iterator;
        }
    }

    if (result == 0 && context->type == 1) {
        Ov022Candidate *object = context->typeOneCandidate;
        void *node;

        if (context->traversalNode !=
            func_01fffdac((char *)object + 0x22c)) {
            return result;
        }
        node = func_01fffd70((char *)object + 0x22c);
        if (context->traversalNode == node) {
            return result;
        }
        result = func_ov022_02084f34((int *)context->selectionState, node, 1);
    }

    return result;
}
