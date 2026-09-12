typedef struct {
    int x;          /* +0x00 */
    int pad_04;
    int z;           /* +0x08 */
    int radius;       /* +0x0c */
} Rect;

typedef struct {
    char pad_00[0x84];
    int field_84;
    int field_88;
    int field_8c;
    char pad_90[0x9c - 0x90];
    int field_9c;
    char pad_a0[0xa4 - 0xa0];
    int field_a4;
} Inner;

typedef struct {
    Inner *field_00;
} Wrapper;

typedef struct {
    char pad_00[4];
    Wrapper *field_04;   /* +0x04 */
} Obj;

typedef struct {
    int a;
    int b;
} Pair;

extern void func_ov107_020ca4b4(Pair *pair, int b, int c, int d, Rect *rect,
                                 int *box, int *result, int param2, int param3);

int func_ov107_020ca860(Obj *obj, Rect *rect, int param2, int param3) {
    int result = 0;
    int box[4];
    Pair pair;
    Inner *inner;

    box[0] = rect->x - rect->radius;
    box[1] = rect->z - rect->radius;
    box[2] = rect->x + rect->radius;
    box[3] = rect->z + rect->radius;

    inner = obj->field_04->field_00;
    pair.a = inner->field_84;
    pair.b = inner->field_88;

    func_ov107_020ca4b4(&pair, inner->field_8c, inner->field_9c, inner->field_a4,
                         rect, box, &result, param2, param3);
    return result;
}
