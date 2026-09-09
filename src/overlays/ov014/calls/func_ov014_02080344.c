typedef signed long s32;
typedef unsigned char u8;
typedef signed short s16;

typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

extern int func_01fffe14(void);
extern void *func_01fffde0(int index);
extern int func_ov002_0207285c(int arg0);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);

int func_ov014_02080344(void *self)
{
    void *owner = *(void **)((char *)self + 8);
    void *entry = func_01fffde0(func_01fffe14());
    s16 key;
    VecFx32 position;
    int distance;

    if (entry == 0)
        return 0;
    key = *(s16 *)((char *)entry + 0x66);
    if (key != func_ov002_0207285c(*(u8 *)((char *)self + 0x10)))
        return 0;
    position = *(VecFx32 *)((char *)entry + 0x48c);
    distance = func_01ff8e94((const VecFx32 *)((char *)self + 0x1c), &position);
    return *(s32 *)((char *)owner + 0x6c) >= distance;
}
