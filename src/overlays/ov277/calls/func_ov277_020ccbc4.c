/* Draw list removal: unregisters the two +0x400 parts (telling each one's +0x1f0 hook 0xa and
 * resetting its +0x2d8 reach to 30.0), the six +0x404 slots and the four +0x408 parts
 * (020c2b20), then the base removal (020c7b70). */
struct Ov244Actor { char pad[0x400]; int *parts2; int *slots6; int *parts4; };

extern void func_ov107_020c2b20(int list, int item);
extern void func_ov107_020c7b70(struct Ov244Actor *self, int list);

void func_ov277_020ccbc4(struct Ov244Actor *self, int list) {
    int i;

    for (i = 0; i < 2; i++) {
        func_ov107_020c2b20(list, self->parts2[i]);
        if (*(void (**)(int, int))(self->parts2[i] + 0x1f0) != 0) {
            (*(void (**)(int, int))(self->parts2[i] + 0x1f0))(self->parts2[i], 0xa);
        }
        *(int *)(self->parts2[i] + 0x2d8) = 0x1e000;
    }
    for (i = 0; i < 6; i++) {
        func_ov107_020c2b20(list, self->slots6[i]);
    }
    for (i = 0; i < 4; i++) {
        func_ov107_020c2b20(list, self->parts4[i]);
    }
    func_ov107_020c7b70(self, list);
}
