typedef unsigned char u8;
typedef unsigned int u32;
typedef int fx32;

typedef struct {
    unsigned pad0 : 1;
    int bit1 : 1;
    int bit2 : 1;
    unsigned rest : 29;
} Flags40;

typedef struct {
    char pad0c[0xc];
    void (*cb0c)(void *self, fx32 value); /* +0xc */
    void (*cb10)(void *self, int arg);    /* +0x10 */
    char pad14[0x20 - 0x14];
    void (*cb20)(void *self); /* +0x20 */
    char pad24[0x34 - 0x24];
    void (*cb34)(void *self); /* +0x34 */
    char pad38[0x40 - 0x38];
    u32 flags40; /* +0x40 */
} Obj;

typedef struct {
    Obj *obj; /* +0x00 */
    char pad04[0x3c - 4];
    fx32 base;   /* +0x3c */
    fx32 scaled; /* +0x40 */
    int counter; /* +0x44 */
} Root;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_02030de4(int a);
extern int func_02020a9c(void);
extern unsigned int func_02030788(void);

extern u8 data_0204c058;

int func_ov107_020c9858(void) {
    Root *root = (Root *)NNSi_FndGetCurrentRootHeap();
    int mode;
    int mul;
    Obj *obj;

    func_02030de4(1);
    mode = func_02020a9c();

    if (mode == 0x2a) {
        mul = (data_0204c058 == 1) ? 0x1800 : 0x1000;
    } else {
        if (data_0204c058 == 1) {
            mul = 0x1800;
        } else if (data_0204c058 == 2) {
            mul = 0x800;
        } else {
            mul = 0x1000;
        }
    }

    {
        long long prod = (long long)mul * root->base;
        root->scaled = (fx32)((prod + 0x800) >> 0xc);
    }
    root->counter = root->counter + 1;

    obj = root->obj;
    {
        fx32 scaledVal = root->scaled;
        if (((Flags40 *)&obj->flags40)->bit1) {
            if (obj->cb0c != 0) {
                obj->cb0c(obj, scaledVal);
            }
        }
    }

    if (func_02030788() == 0) {
        obj = root->obj;
        if (obj->cb20 != 0) {
            obj->cb20(obj);
        }
    }

    obj = root->obj;
    if (((Flags40 *)&obj->flags40)->bit2) {
        if (obj->cb10 != 0) {
            obj->cb10(obj, 0);
        }
    }

    obj = root->obj;
    if (obj->cb34 != 0) {
        obj->cb34(obj);
    }

    return 0;
}
