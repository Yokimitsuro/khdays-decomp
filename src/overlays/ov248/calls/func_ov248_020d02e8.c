/* Setup of the ov248 actor: installs the +8 tick (020d03cc), +0x1c message (020d03fc), +0x30 (020d0578)
 * and +0x34 release (020d0534) handlers, sets bits 1-3 of the +0x60 high byte and bits 2 and 4 of
 * +0x1ae, the +0x70 scale to 0.875, and builds the two +0x388 slot models from the +0x384 pool (kinds
 * from data_ov248_020d0c04), attached and hidden (bit 1 on their +0x5c). */
typedef unsigned short u16;
typedef void (*Callback)(void);
struct Slot { int model; int effect; };
struct Ov248Actor { char pad[0x388]; struct Slot slots[2]; };

extern void func_ov248_020d03cc(void);
extern void func_ov248_020d03fc(void);
extern void func_ov248_020d0578(void);
extern void func_ov248_020d0534(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern void func_ov107_020c9074(char *self, int item);
typedef struct { int w[2]; } KindTable;
extern const KindTable data_ov248_020d0c04;

void func_ov248_020d02e8(char *self)
{
    KindTable kinds;
    int pool;
    int i;

    kinds = data_ov248_020d0c04;
    pool = *(int *)(self + 0x384);
    *(Callback *)(self + 0x8) = func_ov248_020d03cc;
    *(Callback *)(self + 0x1c) = func_ov248_020d03fc;
    *(Callback *)(self + 0x30) = func_ov248_020d0578;
    *(Callback *)(self + 0x34) = func_ov248_020d0534;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0xe00;
    for (i = 0; i < 2; i++) {
        ((struct Ov248Actor *)self)->slots[i].model = func_0203b898(func_ov107_020c9440(pool, kinds.w[i]));
        func_ov107_020c9074(self, ((struct Ov248Actor *)self)->slots[i].model);
        *(int *)(((struct Ov248Actor *)self)->slots[i].model + 0x5c) |= 2;
    }
}
