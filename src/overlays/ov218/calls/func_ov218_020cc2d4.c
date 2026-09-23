/* Update of the ov218 actor: its +0x3ac part advances (020c9ec8), the base update runs, the +0xa0 pose
 * is copied to the +0x3b0 shadow transform (scaled 1.3) and to the +0x38c model, and the model's
 * transform is mirrored onto the +0x388 set's first model. */
typedef struct { int w[11]; } SrtTransform;
struct Posed { char pad[0x10]; SrtTransform srt; };
struct Ov218Actor { char pad[0xa0]; SrtTransform pose; };

extern void func_ov107_020c9ec8(int part);
extern void func_ov107_020c6980(void *obj, int arg2);
extern void func_0203ca9c(void *srt, int scale);

void func_ov218_020cc2d4(char *self, int arg)
{
    func_ov107_020c9ec8(*(int *)(self + 0x3ac));
    func_ov107_020c6980(self, arg);
    *(SrtTransform *)(self + 0x3b0) = *(SrtTransform *)(self + 0xa0);
    func_0203ca9c(self + 0x3b0, 0x14cd);
    (*(struct Posed **)(self + 0x38c))->srt = ((struct Ov218Actor *)self)->pose;
    (**(struct Posed ***)(self + 0x388))->srt = (*(struct Posed **)(self + 0x38c))->srt;
}
