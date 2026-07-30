typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov009ListObject {
    u8 pad000[2];
    u16 id;
    u8 pad004[0x14];
    int type;
    int rangeValue;
} Ov009ListObject;

extern Ov009ListObject *func_ov005_0204ed20(
    void *list,
    Ov009ListObject *previous
);
extern u32 func_020235d0(u32 field, int index);

int func_ov005_020583b0(
    void *firstList,
    void *secondList,
    int *result,
    int minimum,
    int maximum
)
{
    Ov009ListObject *object;

    object = func_ov005_0204ed20(firstList, 0);
    while (object != 0) {
        if (object->rangeValue >= minimum &&
            object->rangeValue <= maximum &&
            func_020235d0((u32)object->id * 3 + 0x28e4, 3) < 3) {
            *result = 0;
            return 0;
        }
        object = func_ov005_0204ed20(firstList, object);
    }

    object = func_ov005_0204ed20(secondList, 0);
    while (object != 0) {
        if (object->rangeValue >= minimum &&
            object->rangeValue <= maximum &&
            object->type != 4 &&
            func_020235d0((u32)object->id * 3 + 0x2a4c, 3) == 0) {
            *result = 0;
            return 0;
        }
        object = func_ov005_0204ed20(secondList, object);
    }

    return 1;
}
