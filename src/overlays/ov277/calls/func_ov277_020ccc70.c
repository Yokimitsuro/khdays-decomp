/* Draw list registration: registers the two +0x400 parts, the six +0x404 slots and the four
 * +0x408 parts (020c2b38), then the base registration (020c7c1c). */
struct Ov244Actor { char pad[0x400]; int *parts2; int *slots6; int *parts4; };

extern void func_ov107_020c2b38(int list, int item);
extern void func_ov107_020c7c1c(struct Ov244Actor *self, int list);

void func_ov277_020ccc70(struct Ov244Actor *self, int list) {
    int i;

    for (i = 0; i < 2; i++) {
        func_ov107_020c2b38(list, self->parts2[i]);
    }
    for (i = 0; i < 6; i++) {
        func_ov107_020c2b38(list, self->slots6[i]);
    }
    for (i = 0; i < 4; i++) {
        func_ov107_020c2b38(list, self->parts4[i]);
    }
    func_ov107_020c7c1c(self, list);
}
