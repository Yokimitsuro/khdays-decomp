/* Set up the ov146 actor: its update (020cef24), message (020cf084), two draw hooks (020cf0cc,
 * 020cf134), helper spawner (020cf220) and armour replay (020cf168) callbacks are installed, bits 1-3 of
 * the +0x60 high byte and bits 2/4 of +0x1ae are set, the +0x384 model is taken from the +0x388 set
 * (+0x3dc), made visible and given the 020ced34 hook with the actor as owner, and the +0x9c model's
 * +0x5c bit 1 clears. */
typedef unsigned short u16;
typedef struct { unsigned b0 : 1; } Bit0;

extern void func_ov146_020cef24(void);
extern void func_ov146_020cf084(void);
extern void func_ov146_020cf0cc(void);
extern void func_ov146_020cf134(void);
extern void func_ov146_020cf220(void);
extern void func_ov146_020cf168(void);
extern void func_ov146_020ced34(void);

void func_ov146_020cee64(char *self)
{
    *(void **)(self + 0xc) = func_ov146_020cef24;
    *(void **)(self + 0x1c) = func_ov146_020cf084;
    *(void **)(self + 0x20) = func_ov146_020cf0cc;
    *(void **)(self + 0x24) = func_ov146_020cf134;
    *(void **)(self + 0x30) = func_ov146_020cf220;
    *(void **)(self + 0x1dc) = func_ov146_020cf168;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 0x14;
    *(int *)(self + 0x384) = *(int *)(*(int *)(self + 0x388) + 0x3dc);
    ((Bit0 *)(*(int *)(self + 0x384) + 0x5c))->b0 = 1;
    *(void **)(*(int *)(self + 0x384) + 0x6c) = func_ov146_020ced34;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) &= ~2;
}
