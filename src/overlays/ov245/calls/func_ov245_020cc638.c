/* func_ov245_020cc638 -- draw list registration: registers the actor's nine +0x3fc parts, the
 * three +0x420 parts, the four +0x42c..+0x438 singles and the three +0x43c parts on the draw
 * list (020c2b38), then the base registration (020c7c1c). */
struct Ov245Actor {
    char pad[0x3fc];
    int parts[9];
    int arms[3];
    int single42c;
    int single430;
    int single434;
    int single438;
    int tails[3];
};

extern void func_ov107_020c2b38(int list, int item);
extern void func_ov107_020c7c1c(struct Ov245Actor *self, int list);

void func_ov245_020cc638(struct Ov245Actor *self, int list) {
    int i;

    for (i = 0; i < 9; i++) {
        func_ov107_020c2b38(list, self->parts[i]);
    }
    for (i = 0; i < 3; i++) {
        func_ov107_020c2b38(list, self->arms[i]);
    }
    func_ov107_020c2b38(list, self->single42c);
    func_ov107_020c2b38(list, self->single430);
    func_ov107_020c2b38(list, self->single434);
    func_ov107_020c2b38(list, self->single438);
    for (i = 0; i < 3; i++) {
        func_ov107_020c2b38(list, self->tails[i]);
    }
    func_ov107_020c7c1c(self, list);
}
