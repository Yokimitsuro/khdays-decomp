/* Teardown hook: unless the current kind (+0x1c6) is 5, drop the +4 children of +0x3b8 slots 1
 * and 2 (index + 1 folded into the offset) via func_0203c650; unless it is 0xb, also drop the first slot's +4 child and release
 * the +0x3c4 handle; then the common release. */
struct Ov236Slot { int pItem; int pChild; };
extern void func_0203c650(int a, int b);
extern void func_ov107_020cb100();
extern void func_ov107_020c7ca4(int self);

void func_ov278_020cd780(int self) {
    if (*(signed char *)(self + 0x100 + 0xc6) != 5) {
        signed char i;
        for (i = 0; i < 2; i++) {
            if ((*(struct Ov236Slot **)(self + 0x3b8))[i + 1].pChild != 0) {
                func_0203c650(*(int *)(self + 0x3c), (*(struct Ov236Slot **)(self + 0x3b8))[i + 1].pChild);
                (*(struct Ov236Slot **)(self + 0x3b8))[i + 1].pChild = 0;
            }
        }
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 0xb) {
        if ((*(struct Ov236Slot **)(self + 0x3b8))[0].pChild != 0) {
            func_0203c650(*(int *)(self + 0x3c), (*(struct Ov236Slot **)(self + 0x3b8))[0].pChild);
            (*(struct Ov236Slot **)(self + 0x3b8))[0].pChild = 0;
        }
        if (*(int *)(self + 0x3c4) != 0) {
            func_ov107_020cb100();
            *(int *)(self + 0x3c4) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}
