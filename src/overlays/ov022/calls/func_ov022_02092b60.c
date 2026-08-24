struct MtxFx33_02092b60 { int m[3][3]; };
extern void MTX_RotY33_(struct MtxFx33_02092b60 *a, int b, int c);
extern const short data_0203d210[];

struct vec3_02092b60 { int a; int b; int c; };

struct Ov022TransformTail {
    int value168;
    int value16c;
    int value170;
    int value174;
};

struct Ov022TransformContext {
    unsigned char flags00;
    unsigned char pad001[0xa7];
    struct vec3_02092b60 vec0a8;
    unsigned char pad0b4[0x81];
    unsigned char active135;
    unsigned char pad136[2];
    struct vec3_02092b60 vec138;
    struct MtxFx33_02092b60 transform144;
    struct Ov022TransformTail tail168;
};

void func_ov022_02092b60(struct Ov022TransformContext *param_1, const struct vec3_02092b60 *param_2, int param_3) {
    short trigFirst;
    short trigSecond;
    struct vec3_02092b60 tmp;
    int k;

    if ((param_1->flags00 & 1) == 0) {
        return;
    }
    k = (param_3 >> 4) * 2;
    trigFirst = data_0203d210[k];
    trigSecond = data_0203d210[k + 1];
    {
        struct Ov022TransformContext *self = param_1;
        self->tail168.value168 = 0xa000;
        self->tail168.value16c = 0;
        self->tail168.value174 = 0;
        MTX_RotY33_(&self->transform144,
                    -(int)trigFirst, -(int)trigSecond);
        tmp = *param_2;
        self->active135 = 1;
        self->vec138 = tmp;
        self->vec0a8 = tmp;
    }
}
