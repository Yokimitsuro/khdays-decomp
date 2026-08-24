extern int func_020358f4(int kind, int property);
extern int func_ov022_020ad7b0(int obj);
extern unsigned int func_020307f4(int value);
extern int data_0204c678;

struct GaugeFields020a2230 {
    char _pad00[8];
    int additiveValue;
    short additiveScale;
};

struct GaugeBlock020a2230 {
    char _pad000[0x800];
    struct GaugeFields020a2230 gauge;
};

struct Ov022Object020a2230 {
    unsigned long long flags;
    unsigned char _pad08;
    unsigned char kind;
    char _pad0a[0x118 - 0x0a];
    struct GaugeBlock020a2230 gaugeBlock;
};

struct Row020a2230 {
    char _pad00[0x10];
    unsigned short baseScale;
    short _pad12;
    int baseValue;
    char _pad18[0x104 - 0x18];
};

#pragma opt_propagation off
unsigned int func_ov022_020a2230(
    struct Ov022Object020a2230 *obj, int arg1, int mode)
{
    int zero = 0;
    struct Row020a2230 *row;
    int objectBase;
    int gaugeAddress;
    int scaled;
    int value;

    row = (struct Row020a2230 *)&data_0204c678;
    arg1 = obj->kind;
    row += arg1;
    objectBase = (int)obj + 0x118;
    value = (int)((char *)0 + row->baseValue);
    scaled = zero + row->baseScale * 0x1000;
    gaugeAddress = objectBase + 0x800;
    value = (int)((char *)value +
                  ((struct GaugeFields020a2230 *)gaugeAddress)->additiveValue);
    scaled += ((struct GaugeFields020a2230 *)gaugeAddress)->additiveScale *
              0x1000;
    zero = mode;

    if (func_020358f4(obj->kind, 0x3d) > 0 &&
        func_ov022_020ad7b0((int)obj)) {
        value += 0x1e000;
    }
    if (zero == 0) {
        value = value / 4;
        scaled = scaled / 2;
    }
    if ((obj->flags & 0x100000000ULL) == 0 &&
        func_020307f4(0x64000) > (unsigned int)value) {
        scaled = 0;
    }
    return (unsigned int)(scaled << 4) >> 16;
}
