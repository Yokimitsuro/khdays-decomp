typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    int kind;
    int paramB;
    int paramA;
    int paramC;
    int angle;
} PlaceParams;

typedef struct PoolDesc PoolDesc;

typedef struct {
    char pad00[0x1c];
    VecFx32 position;
    int value28;
} Entry;

extern void *func_ov002_02076a38(PoolDesc *pool, int index);
extern int func_ov002_0207c4c0(void *obj, int node, PlaceParams *out,
                                int entryByte, int kind, int paramA, int paramB,
                                int paramC, int angle, int flag);
extern void func_ov002_0207c53c(VecFx32 *out, const VecFx32 *pos,
                                 const PlaceParams *params);
extern void func_0202b450(int *ptr, VecFx32 *src);
extern void func_ov002_02076480(int idx, int *node);
extern int func_02005418(int a, int b);
extern void func_02029438(char *p, int i, char v);
extern void func_ov014_0207fd78(void);
extern unsigned char data_0204c240;

void *func_ov014_020800a8(PoolDesc *pool, unsigned short node,
                          unsigned short bucket, unsigned short kind,
                          unsigned char entryByte, VecFx32 *pos, short angle, int index)
{
    Entry *entry = (Entry *)func_ov002_02076a38(pool, node);
    VecFx32 start;
    PlaceParams params;
    int height;

    func_ov002_0207c4c0(entry, (int)((char *)entry + 0x2c), &params, node,
                        *(signed char *)((char *)pool + 0x6c),
                        *(short *)((char *)pool + 0x6e),
                        *(short *)((char *)pool + 0x70),
                        *(short *)((char *)pool + 0x72), angle, 1);
    func_ov002_0207c53c(&start, pos, &params);
    func_0202b450((int *)((char *)entry + 0x38), pos);
    *(short *)((char *)entry + 0x18) = angle;
    entry->position = start;
    entry->value28 = params.paramA;
    *(unsigned char *)((char *)entry + 0x10) = (unsigned char)bucket;
    *(void **)((char *)entry + 0x0c) = func_ov014_0207fd78;
    *(unsigned short *)((char *)entry + 0x12) |= 0x48;
    *(unsigned short *)((char *)entry + 0x14) = kind;
    *(unsigned char *)((char *)entry + 0x16) = entryByte;
    *(unsigned char *)((char *)entry + 0x17) = 0;
    func_ov002_02076480(bucket, (int *)entry);
    *(unsigned char *)((char *)entry + 0x1b1) = 0;
    height = (data_0204c240 & 4) ? (index >> 16) : (index & 0xffff);
    *(short *)((char *)entry + 0x1d0) = (short)height;
    *(int *)((char *)entry + 0x1cc) = 0;
    *(unsigned char *)((char *)entry + 0x1b3) = 0;
    *(int *)((char *)entry + 0x1b4) = 0x46bd;
    *(int *)((char *)entry + 0x1b8) = func_02005418(*(int *)((char *)pool + 0x74), *(int *)((char *)entry + 0x1b4));
    *(int *)((char *)entry + 0x1bc) = func_02005418(*(int *)((char *)pool + 0x78), *(int *)((char *)entry + 0x1b4));
    *(int *)((char *)entry + 0x1c0) = func_02005418(*(int *)((char *)pool + 0x7c), *(int *)((char *)entry + 0x1b4));
    *(int *)((char *)entry + 0x1c8) = *(int *)((char *)entry + 0x1b4);
    func_02029438((char *)entry + 0x148, 1, 3);
    return entry;
}
