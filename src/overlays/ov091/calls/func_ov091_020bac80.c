typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;
struct Part { int header; u16 flags; };
struct StreamGroup { u8 bytes[0x30]; };
struct Scroll { u8 bytes[8]; };
struct Widget { u8 bytes[8]; };
struct Runtime {
    u8 pad000[0x20];
    struct Part *part20;
    u8 pad024[0x440];
    u64 flags464;
    u64 flags46c;
    u8 pad474[0xa98];
    struct Widget widgetf0c;
    u8 padf14[0x1730];
    struct StreamGroup *groups2644;
    u8 pad2648[0x472];
    short row2aba;
    u8 pad2abc[0x194];
    struct Scroll scroll2c50;
};
extern struct Runtime *data_ov091_020bc240;
extern int func_0202aee0(u16 *, int);
extern int func_02020a9c(void);
extern unsigned int func_02030788(void);
extern void func_ov002_020521e4(struct Widget *, struct Scroll *, int, int);
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(struct StreamGroup *, int);
extern void func_ov022_02091474(struct StreamGroup *);
extern int func_ov022_020912d8(struct StreamGroup *);
extern int func_ov022_020ad588(struct Runtime *);

int func_ov091_020bac80(struct Runtime *self)
{
    struct Runtime *base = data_ov091_020bc240;
    int row = func_0202aee0(&self->part20->flags, 0);
    func_ov002_020521e4(&self->widgetf0c, &base->scroll2c50, self->row2aba, row);
    if (func_02020a9c() != 0x2a) {
        int i;
        for (i = 0; i < 2; i++) {
            func_ov022_0209145c(&self->groups2644[i], func_ov022_02083f90());
            func_ov022_02091474(&self->groups2644[i]);
        }
        if (func_ov022_020912d8(&self->groups2644[0]) == 0 ||
            func_ov022_020912d8(&self->groups2644[1]) == 0) {
            if (func_02030788() == 0) self->flags464 |= 0x10000;
            if (func_02030788() == 0) self->flags46c |= 0x10000;
        }
    }
    return func_ov022_020ad588(base);
}
