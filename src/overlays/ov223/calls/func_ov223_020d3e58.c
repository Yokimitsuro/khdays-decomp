/* Construction of the ov223 enemy's item: installs the handlers (+8 020d4030, +0xc 020d405c,
 * +0x1c 020d4068, +0x20 020d4278, +0x24 020d42e0, +0x30 020d4808), raises bits 1-3 and 6 and
 * then bit 5 of the +0x60 high byte (the data_ov223_020d50f4 kind is copied to the stack
 * between the two writes), bits 2 and 4 of +0x1ae and bit 2 of the +0x9c parent's +0x5c, sets
 * +0x70 to 1 and clears +0x54/+0x58; builds the +0x384 item from pose 0x1a of the +0x38c pool
 * (channel 0 enabled), subscribes it to the parent and finalises it; builds the +0x398
 * sub-item from the saved kind and the +0x394 one from resource 0x20 entry 0x22 (both
 * registered on the actor, bit 1 of +0x5c raised), binds channels 0, 2 and 4 of the latter's
 * +0x88 track's +0xe0 block (0202accc), allocates the +0x390 ring (ov223 4e24) and clears
 * +0x388. */
extern int func_ov107_020c9440(int owner, int kind);
extern int func_0203b898(int a);
extern void func_0203b9fc(int obj, int mode, int a, int b);
extern void func_0203bfb4(int a, int obj);
extern void func_0203c7ac(int obj, int a);
extern void func_ov107_020c9074(int self, int obj);
extern int func_0203c1b0(int res, int n);
extern void func_0202accc(int track, int channel, int block, int flag);
extern int func_ov223_020d4e24(char *self);
extern void func_ov223_020d4030(void);
extern void WM_EndKeySharing_0x020d405c(void);   /* misnamed: an ov223 veneer to func_ov107_020c6980 */
extern void func_ov223_020d4068(void);
extern void func_ov223_020d4278(void);
extern void func_ov223_020d42e0(void);
extern void func_ov223_020d4808(void);

struct Ov223Saved { int w; };
extern const struct Ov223Saved data_ov223_020d50f4;

void func_ov223_020d3e58(char *self) {
    int owner;
    unsigned short v;
    struct Ov223Saved saved;
    int sub;
    int *grip = (int *)(self + 0x394);     /* the +0x394 item slot, read back through this pointer */

    owner = *(int *)(self + 0x38c);
    *(void **)(self + 8) = (void *)func_ov223_020d4030;
    *(void **)(self + 0xc) = (void *)WM_EndKeySharing_0x020d405c;
    *(void **)(self + 0x1c) = (void *)func_ov223_020d4068;
    *(void **)(self + 0x20) = (void *)func_ov223_020d4278;
    *(void **)(self + 0x24) = (void *)func_ov223_020d42e0;
    *(void **)(self + 0x30) = (void *)func_ov223_020d4808;

    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x4e) << 0x18) >> 0x10));

    saved = data_ov223_020d50f4;

    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x20) << 0x18) >> 0x10));

    *(unsigned short *)(self + 0x1ae) |= 0x14;
    *(int *)(self + 0x70) = 1;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;

    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x1a));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);

    sub = *(int *)(self + 0x398) = func_0203b898(func_ov107_020c9440(owner, saved.w));
    func_ov107_020c9074((int)self, sub);
    *(int *)(*(int *)(self + 0x398) + 0x5c) |= 2;

    sub = *grip = func_0203c1b0(func_ov107_020c9440(owner, 0x20), 0x22);
    func_ov107_020c9074((int)self, sub);
    *(int *)(*grip + 0x5c) |= 2;
    func_0202accc(*(int *)(*grip + 0x88), 0, *(int *)(*grip + 0x88) + 0xe0, 0);
    func_0202accc(*(int *)(*grip + 0x88), 2, *(int *)(*grip + 0x88) + 0xe0, 0);
    func_0202accc(*(int *)(*grip + 0x88), 4, *(int *)(*grip + 0x88) + 0xe0, 0);

    *(int *)(self + 0x390) = func_ov223_020d4e24((char *)self);
    *(int *)(self + 0x388) = 0;
}
