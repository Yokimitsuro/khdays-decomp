/* Model-object constructor: base setup (func_0203c724), the draw / callback / release hooks
 * (+0x64 func_0203b968, +0x6c func_0203bc78, +0x68 func_0203bb34), a 0x108-byte animation block
 * (+0x88, func_0203d15c) bound to `res` (func_0202a634, 12 frames) and started (func_0202afc4); its
 * +0xe0 part is kept in +0x8c, bit 0 of +0xb2 cleared and the five channel weights (+0x94) reset
 * to 1.0 with their +0xa8 / +0xad bytes cleared. */
typedef unsigned char u8;
typedef void (*Callback)(void);

struct ModelObj {
    char pad00[0x64];
    Callback draw;          /* 0x64 */
    Callback release;       /* 0x68 */
    Callback callback;      /* 0x6c */
    char pad70[0x88 - 0x70];
    char *anim;             /* 0x88 */
    char *animPart;         /* 0x8c */
    int field90;            /* 0x90 */
    int weight[5];          /* 0x94 */
    u8 chanA[5];            /* 0xa8 */
    u8 chanB[5];            /* 0xad */
    u8 flagsB2;             /* 0xb2 */
};

extern void func_0203c724(struct ModelObj *obj, int res);
extern void func_0203b968(void);
extern void func_0203bc78(void);
extern void func_0203bb34(void);
extern char *func_0203d15c(int size);
extern void func_0202a634(char *anim, int res, int a, int frames);
extern void func_0202afc4(char *anim, int a);

void func_0203b8bc(struct ModelObj *obj, int res)
{
    int i;

    func_0203c724(obj, res);
    obj->draw = func_0203b968;
    obj->callback = func_0203bc78;
    obj->release = func_0203bb34;
    obj->field90 = 0;
    obj->anim = func_0203d15c(0x108);
    func_0202a634(obj->anim, res, 1, 0xc);
    func_0202afc4(obj->anim, 1);
    obj->animPart = obj->anim + 0xe0;
    obj->flagsB2 &= ~1;
    for (i = 0; i < 5; i++) {
        obj->weight[i] = 0x1000;
        obj->chanA[i] = 0;
        obj->chanB[i] = 0;
    }
}
