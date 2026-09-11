typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Blk44 { int w[11]; } Blk44; /* 44 bytes */

typedef struct Inner09a0 {
    char pad00[4];
    Blk44 body;              /* offset 4 .. 0x30 */
    char pad30[0x5c - 0x30];
    int flags;                /* offset 0x5c */
} Inner09a0;

typedef struct ObjType {
    Inner09a0 *field0;
    Blk44 *field4;
    u8 field8;
    u8 field9;
    char pad0a[0xc - 0xa];
    int field_c;
} ObjType;

extern int func_0203c5c0(int param_1, unsigned int param_2, unsigned int param_3,
                          int param_4, int param_5, int *param_6);
extern void func_0203b9fc(Inner09a0 *a, u16 b, int c, int d);
extern void func_0203c7ac(Inner09a0 *ptr, int arg);
extern void func_ov107_020c0ab4(void *a);
extern int func_ov107_020c0a9c(int param_1);

int func_ov107_020c09a0(int resource, int node, int kind, void *transform,
                         unsigned char e, int f)
{
    ObjType *object;
    int i;
    int id;

    id = func_0203c5c0(resource, 0xc8, 0x10, (int)func_ov107_020c0a9c,
                        (int)func_ov107_020c0ab4, (int *)&object);

    object->field0 = (Inner09a0 *)node;
    object->field4 = (Blk44 *)transform;

    object->field0->body = *object->field4;

    object->field8 = (u8)kind;
    object->field_c = f;
    object->field9 = (u8)e;

    object->field0->flags &= ~2;

    for (i = 0; i < 5; i++) {
        if (object->field8 & (1 << i))
            func_0203b9fc(object->field0, (u16)i, object->field9, object->field_c);
    }

    func_0203c7ac(object->field0, 0);

    return id;
}
