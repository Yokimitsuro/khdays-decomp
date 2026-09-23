/* Draw pre-pass of the ov259 actor: effects that outlive their move end (+0x46c outside move 0x11;
 * +0x45c unless move 0x11 keeps it while the +0x384 rig is airborne and 020d1838 holds; +0x474 in
 * move 0xf), then the base pre-pass runs. */
typedef unsigned char u8;
struct Flag17a { u8 b0 : 1; };

extern void func_0203c650(void *taskList, void *handle);
extern int func_ov259_020d1838(int rig);
extern void func_ov107_020c7ca4(char *self);

void func_ov259_020ccb0c(char *self)
{
    if (*(signed char *)(self + 0x100 + 0xc6) != 0x11 && *(void **)(self + 0x46c) != 0) {
        func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x46c));
        *(void **)(self + 0x46c) = 0;
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 0x11 ||
        ((struct Flag17a *)(*(int *)(self + 0x384) + 0x17a))->b0 ||
        func_ov259_020d1838(*(int *)(self + 0x384)) == 0) {
        if (*(void **)(self + 0x45c) != 0) {
            func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x45c));
            *(void **)(self + 0x45c) = 0;
        }
    }
    if (*(signed char *)(self + 0x100 + 0xc6) == 0xf && *(void **)(self + 0x474) != 0) {
        func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x474));
        *(void **)(self + 0x474) = 0;
    }
    func_ov107_020c7ca4(self);
}
