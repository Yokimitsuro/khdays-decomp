typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct MtxFx33 {
    int value[9];
} MtxFx33;

typedef struct Ov022AnimationSlot {
    u8 active00;
    char padding001[0xa7];
    VecFx32 positionA8;
    char padding0b4[0x60];
} Ov022AnimationSlot;

typedef struct Ov022AnimationRoot {
    u8 countAndFlags00;
    char padding001[0x0b];
    Ov022AnimationSlot *slots0c;
} Ov022AnimationRoot;

typedef struct Ov022DispatchContext {
    char padding000[0x20];
    Ov022AnimationRoot *animation20;
} Ov022DispatchContext;

extern MtxFx33 data_020473e0;
extern s16 data_0203d210[];

extern void MI_Copy36B(const void *source, void *destination);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern int func_02023e80(u32 range);
extern void func_01ffa724(int scale, const VecFx32 *source, VecFx32 *destination);
extern void MTX_MultVec33(const VecFx32 *source, const MtxFx33 *matrix,
                          VecFx32 *destination);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *destination);

void func_ov022_02088e50(Ov022DispatchContext *context,
                          const VecFx32 *position, int radius,
                          VecFx32 *output)
{
    int index;
    Ov022AnimationRoot *root;
    VecFx32 displacement;
    VecFx32 result;
    MtxFx33 viewMatrix;

    root = context->animation20;
    result = *position;
    MI_Copy36B(&data_020473e0, &viewMatrix);

    index = 0;
    if ((int)(((u32)root->countAndFlags00 << 24) >> 26) > 0) {
        int offset;
        int minusOne;

        offset = 0;
        minusOne = -1;
        do {
            Ov022AnimationSlot *slots;

            slots = root->slots0c;
            if (*(u8 *)((char *)slots + offset) != 0 &&
                func_01ff8e94(&result,
                    (VecFx32 *)((char *)slots + offset + 0xa8)) < radius) {
                int angle;

                angle = func_02023e80(0x8000) >> 4;
                displacement.x = data_0203d210[angle * 2];
                displacement.y = data_0203d210[angle * 2 + 1];
                displacement.z = 0;
                if (displacement.y < 0) {
                    displacement.y = displacement.y * minusOne;
                }
                func_01ffa724(radius, &displacement, &displacement);
                MTX_MultVec33(&displacement, &viewMatrix, &displacement);
                VEC_Add(&displacement, &result, &result);
            }
            index++;
            offset += 0x114;
        } while (index <
                 (int)(((u32)root->countAndFlags00 << 24) >> 26));
    }

    *output = result;
}
