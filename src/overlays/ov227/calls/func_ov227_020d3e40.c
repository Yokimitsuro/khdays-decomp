/* Constructor of an ov227 part (spawned by the enemy, owner at +0x38c). Installs the handlers (+8,
 * +0x1c message, +0x30), sets bits 1/3/4/6 of the +0x60 high byte (0x5a), bit 2 of +0x1ae and the
 * +0x70 scale 0.63, clears +0x54/+0x58 and flags its +0x9c body (bit 2 of +0x5c); builds the +0x384
 * rig from the owner's pose 0x1e (subscribed to +0x9c, channels 0/2/4/1 looped, reset) and the two
 * sub-items of data_ov227_020d4b6c into the +0x390 pair table (registered, bit 1 of +0x5c). */
typedef struct { int id[2]; } IdPair;
struct Pair { int res; int handle; };
struct Ov227Part { char pad[0x390]; struct Pair pairs[2]; };

extern void *func_ov107_020c9440(int owner, int kind);
extern int func_0203b898(void *res);
extern void func_0203bfb4(int list, int node);
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c7ac(int obj, int a);
extern void func_ov107_020c9074(char *self, int obj);
extern void func_ov227_020d3fb0(void);
extern void func_ov227_020d3ff0(void);
extern void func_ov227_020d428c(void);
extern IdPair data_ov227_020d4b6c;

void func_ov227_020d3e40(char *self)
{
    IdPair ids = data_ov227_020d4b6c;
    int owner = *(int *)(self + 0x38c);
    unsigned short v;
    int i;

    *(void **)(self + 8) = (void *)func_ov227_020d3fb0;
    *(void **)(self + 0x1c) = (void *)func_ov227_020d3ff0;
    *(void **)(self + 0x30) = (void *)func_ov227_020d428c;
    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x5a) << 0x18) >> 0x10));
    *(unsigned short *)(self + 0x1ae) |= 4;
    *(int *)(self + 0x70) = 0xa00;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x1e));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    for (i = 0; i < 2; i++) {
        func_ov107_020c9074(self, ((struct Ov227Part *)self)->pairs[i].res =
                                      func_0203b898(func_ov107_020c9440(owner, ids.id[i])));
        *(int *)(((struct Ov227Part *)self)->pairs[i].res + 0x5c) |= 2;
    }
}
