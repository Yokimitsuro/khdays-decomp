/* func_ov253_020ccb40 -- draw list registration: handles the +0x460 single, the four +0x458 parts and the
 * eight +0x45c parts (020c2b38), then the base registration (020c7c1c). */
struct Ov253Actor { char pad[0x458]; int *parts4; int *parts8; int single; };

extern void func_ov107_020c2b38(int list, int item);
extern void func_ov107_020c7c1c(struct Ov253Actor *self, int list);

void func_ov253_020ccb40(struct Ov253Actor *self, int list) {
    int i;

    func_ov107_020c2b38(list, self->single);
    for (i = 0; i < 4; i++) {
        func_ov107_020c2b38(list, self->parts4[i]);
    }
    for (i = 0; i < 8; i++) {
        func_ov107_020c2b38(list, self->parts8[i]);
    }
    func_ov107_020c7c1c(self, list);
}
