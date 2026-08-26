typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Ov022Flags60Bits {
    unsigned short lowByte : 8;
    unsigned short highByte : 8;
} Ov022Flags60Bits;

typedef struct Ov022TypeOneObject {
    char pad_0000[0x60];
    u16 flags60;
    char pad_0062[0x14a];
    u16 flags1ac;
    char pad_01ae[0x6a];
    s16 state218;
    char pad_021a[0x12];
    char traversal22c[1];
} Ov022TypeOneObject;

typedef struct Ov022SelectorContext {
    char pad_0000[4];
    char traversalState[4];
    int type;
    Ov022TypeOneObject *typeOneObject;
    void **node;
    char pad_0014[4];
    void *entry;
    char *base;
} Ov022SelectorContext;

extern Ov022SelectorContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_02076d24(void *entry);
extern void *func_01fffdac(void *traversal);
extern void *func_ov022_02084f34(void *state, void **node, void *previous);
extern void *func_ov022_020841e0(int argument, void *selected);

void *func_ov022_020840fc(int argument)
{
    Ov022SelectorContext *context = NNSi_FndGetCurrentRootHeap();
    void *selected = 0;
    void *result = selected;

    if (context->type == 1) {
        goto type_one;
    }
    if (context->type == 2) {
        goto type_two;
    }
    if (context->type != 3) {
        goto after_switch;
    }
    selected = context->base + 0x8f8;
    goto after_switch;

type_two: {
        int value = func_ov002_02076d24(context->entry);
        if (value != 0) {
            selected = (void *)value;
        }
        goto after_switch;
    }

type_one: {
        Ov022TypeOneObject *object = context->typeOneObject;

        if ((object->flags1ac & 2) != 0 ||
            (((Ov022Flags60Bits *)&object->flags60)->lowByte & 1) == 0 ||
            object->state218 == 0) {
            selected = (char *)object + 0x74;
        } else {
            void **node = context->node;
            selected = (char *)*node + 4;
            if (node != func_01fffdac(object->traversal22c)) {
                result = func_ov022_02084f34(context->traversalState, node, result);
            }
        }
    }

after_switch:
    if (result == 0) {
        result = func_ov022_020841e0(argument, selected);
    }
    return result;
}
