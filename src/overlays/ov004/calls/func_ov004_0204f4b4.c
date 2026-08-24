typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov004ListConfig {
    u32 resourceId;
    int baseValue;
    int capacity;
} Ov004ListConfig;

typedef struct Ov004ObjectList {
    u32 words[9];
} Ov004ObjectList;

typedef struct Ov004ListObject {
    u8 pad000[2];
    u16 id;
    u8 pad004[6];
    u16 fallbackValue;
    u8 pad00c[0x10];
    int rangeValue;
} Ov004ListObject;

extern const Ov004ListConfig data_ov004_020510a4;
extern void func_ov004_0204d25c(Ov004ObjectList *list,
                                const Ov004ListConfig *config);
extern Ov004ListObject *func_ov004_0204d328(Ov004ObjectList *list);
extern Ov004ListObject *func_ov004_0204d2ec(
    Ov004ObjectList *list,
    Ov004ListObject *previous);
extern void func_ov004_0204d2bc(Ov004ObjectList *list);
extern u32 func_020235d0(u32 field, int width);

int func_ov004_0204f4b4(int value) {
    Ov004ListConfig config = data_ov004_020510a4;
    Ov004ObjectList list;
    Ov004ListObject *first;
    int matched;
    int total;
    Ov004ListObject *object;
    int result;

    config.capacity = 4;
    config.baseValue = value;
    func_ov004_0204d25c(&list, &config);
    first = func_ov004_0204d328(&list);
    matched = 0;
    total = 0;
    object = func_ov004_0204d2ec(&list, 0);
    while (object != 0) {
        int enabled =
            func_020235d0((u32)object->id * 3 + 0x28e4, 3) >= 2;

        if (enabled != 0) {
            matched++;
        }
        if (object->rangeValue < value) {
            value = object->rangeValue;
        }
        total++;
        object = func_ov004_0204d2ec(&list, object);
    }
    if (first != 0 && matched >= total) {
        result = first->fallbackValue;
    } else {
        result = value + matched;
    }
    func_ov004_0204d2bc(&list);
    return result;
}
