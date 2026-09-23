/* Draw hook of the ov146 actor's +0x384 model: while its owner shows the effect (+0x38c), every entity
 * of the owner's scene list (+0x388 set's +4 grid, +0x80 list) flagged 0x10 (+0x1c4) is drawn with it:
 * the model's +0x78 animation takes frame n % 28 + 3, and the model is scaled to twice the entity's
 * radius and placed on its +0x74 point before the draw (0203bc78). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(void *srt);
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void func_02016b60(int a, int b, int c);
extern void func_0203ca9c(void *srt, int scale);
extern void func_0203ca30(void *srt, const Vec3 *v);
extern int func_0203bc78(char *model, int arg);

void func_ov146_020ced34(char *model, int arg)
{
    int n;
    char *owner;
    int grid;
    int *it;
    char *e;

    owner = *(char **)(model + 0x84);
    grid = *(int *)(*(int *)(owner + 0x388) + 4);
    n = 0;
    func_0203c960(model + 0x30);
    if (*(int *)(owner + 0x38c) == 0) {
        return;
    }
    it = func_01fffd70((void *)(grid + 0x80));
    e = it == 0 ? 0 : (char *)*it;
    while (e != 0) {
        if (*(u8 *)(e + 0x1c4) & 0x10) {
            func_02016b60(*(int *)(*(int *)(*(int *)(owner + 0x384) + 0x88) + 0x78), 0, n % 28 + 3);
            func_0203ca9c(model + 0x30, *(int *)(e + 0x80) * 2);
            func_0203ca30(model + 0x30, (Vec3 *)(e + 0x74));
            func_0203bc78(model, arg);
            n++;
        }
        it = func_01fffd8c((void *)(grid + 0x80));
        e = it == 0 ? 0 : (char *)*it;
    }
}
