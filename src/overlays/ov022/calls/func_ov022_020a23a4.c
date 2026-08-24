struct Row020a23a4 {
    char _pad00[8];
    unsigned short scaleA;
    unsigned short scaleB;
    char _pad0c[0x104 - 0x0c];
};

extern struct Row020a23a4 data_0204c678[];

struct Gauge020a23a4 {
    char _pad00[2];
    short scaleA;
    short scaleB;
};

struct GaugeBlock020a23a4 {
    char _pad000[0x800];
    struct Gauge020a23a4 gauge;
};

struct Object020a23a4 {
    char _pad00[9];
    unsigned char kind;
    char _pad00a[0x118 - 0x0a];
    struct GaugeBlock020a23a4 gaugeBlock;
};

void func_ov022_020a23a4(
    int obj, int factor, int *outValue, int *outOther)
{
    int kind;
    int row;
    unsigned short rowA;
    unsigned short rowB;
    short gaugeA;
    short gaugeB;
    int sum = 0;
    long long product;
    unsigned int shifted;

    kind = *(unsigned char *)(obj + 9);
    obj += 0x118;
    row = (int)&data_0204c678[kind];
    rowA = ((struct Row020a23a4 *)row)->scaleA;
    obj += 0x800;
    rowB = ((struct Row020a23a4 *)row)->scaleB;
    sum += rowA * 0x1000;
    gaugeA = ((struct Gauge020a23a4 *)obj)->scaleA;
    sum += rowB * 0x1000;
    gaugeB = ((struct Gauge020a23a4 *)obj)->scaleB;
    sum += gaugeA * 0x1000;
    sum += gaugeB * 0x1000;
    if (sum >= 0x3e7000) {
        sum = 0x3e7000;
    }
    product = (long long)sum * factor + 0x800;
    shifted = (unsigned int)((unsigned long long)product >> 12);
    *outValue = (int)(shifted + (shifted >> 31)) >> 13;
    *outOther = 0;
}
