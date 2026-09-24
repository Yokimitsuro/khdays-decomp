/* Multi-joint model object constructor: base setup (func_0203c724), draw / callback hooks (+0x64
 * func_0203c2c4, +0x6c func_0203c304, +0x7c func_0203c3f8, +0x80 func_0203c3fc), a 0x108-byte
 * animation block (+0x88) bound to `res` (12 frames) with the loader's texture flag off during the
 * bind (func_0201f390), and `count` 0x38-byte joints (+0x8c count, +0x90 array) whose rotations
 * (+8) start as the identity quaternion data_020420f8. */
typedef void (*Callback)(void);

typedef struct {
    int x, y, z, w;
} Quat;

typedef struct {
    char pad00[8];
    Quat rot;               /* 0x08 */
    char pad18[0x38 - 0x18];
} Joint;

struct ModelObj {
    char pad00[0x64];
    Callback draw;          /* 0x64 */
    char pad68[4];
    Callback callback;      /* 0x6c */
    char pad70[0x7c - 0x70];
    Callback hook7c;        /* 0x7c */
    Callback hook80;        /* 0x80 */
    char pad84[4];
    char *anim;             /* 0x88 */
    int jointCount;         /* 0x8c */
    Joint *joints;          /* 0x90 */
};

extern void func_0203c724(struct ModelObj *obj, int res);
extern void func_0203c2c4(void);
extern void func_0203c304(void);
extern void func_0203c3f8(void);
extern void func_0203c3fc(void);
extern void *func_0203d15c(int size);
extern void func_0201f390(int flag);
extern void func_0202a634(char *anim, int res, int a, int frames);
extern const Quat data_020420f8;

void func_0203c1dc(struct ModelObj *obj, int res, int count)
{
    int i;

    func_0203c724(obj, res);
    obj->draw = func_0203c2c4;
    obj->callback = func_0203c304;
    obj->hook7c = func_0203c3f8;
    obj->hook80 = func_0203c3fc;
    obj->anim = func_0203d15c(0x108);
    func_0201f390(0);
    func_0202a634(obj->anim, res, 1, 0xc);
    func_0201f390(1);
    obj->jointCount = count;
    obj->joints = func_0203d15c(count * 0x38);
    for (i = 0; i < obj->jointCount; i++) {
        obj->joints[i].rot = data_020420f8;
    }
}
