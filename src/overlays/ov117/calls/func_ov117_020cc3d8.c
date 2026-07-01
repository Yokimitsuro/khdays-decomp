extern int func_ov107_020c89e8();
extern int func_ov107_020c5af8();

typedef struct { int a, b, c; } Blk3;

typedef struct {
    unsigned char bit : 1;
} BitByte;

int func_ov117_020cc3d8(int this, int a1, int a2)
{
    int s = (int)*(short *)(this + 0x21a);
    int *p4 = *(int **)(this + 0x214);
    int n;
    int d;
    int result;
    unsigned int w;
    unsigned int h;
    BitByte *bf;

    if (s <= 0)
        return 0;

    n = func_ov107_020c89e8(this, a2);
    *(int *)(a2 + 0x28) = n;

    d = (int)*(short *)(this + 0x21a) - n;
    if (d < 0) {
        result = 0;
    } else {
        result = (int)*(short *)(this + 0x218);
        if (d <= result)
            result = d;
    }
    *(short *)(this + 0x21a) = (short)result;

    *(int *)(p4 + 0x13) = a1;
    *(Blk3 *)((char *)p4 + 0x50) = *(Blk3 *)(a2 + 4);

    if ((int)*(short *)(this + 0x21a) == 0) {
        *(char *)(*(int *)p4 + 0x1c7) = 3;
    } else {
        if ((unsigned short)*(int *)a2 & 0x8000)
            *(char *)(*(int *)p4 + 0x1c7) = 5;
    }

    if (*(int *)(a2 + 0x28) > 0) {
        w = *(int *)a2;
        h = (unsigned short)w;
        if ((h & 8) && (h & 0x80) && (w >> 16) == 0x80)
            return 1;

        bf = (BitByte *)(p4 + 0x25);
        if (h & 0x22) {
            unsigned short val;
            bf->bit = bf->bit + 1;
            val = bf->bit ? 2 : 3;
            func_ov107_020c5af8(this, 0x120, val, *(int *)(p4 + 0x11));
        } else {
            unsigned short val;
            bf->bit = bf->bit + 1;
            val = bf->bit ? 0 : 1;
            func_ov107_020c5af8(this, 0x120, val, *(int *)(p4 + 0x11));
        }
    }

    return 1;
}
