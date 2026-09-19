/* func_ov253_020d25e4 -- queue-driven sub-state tick: while the +0x50 phase is 1 and the actor's
 * kind byte is 2, an idle +0x3d8 latch takes the +0x3dd queue head's kind (when set) mapped
 * through the three-byte data_ov253_020d49e0 table into the +0x1c7 sub-state and raises the
 * latch; once raised, a +0x1c8 state other than 2 pops the head (020d2794) and clears it. Then
 * the base tick (020c7ca4). */
struct Ov253Entry { signed char a; signed char b; short c; };
struct Ov253Queue { char pad[0x3dc]; signed char count; signed char head; char pad3de[6]; struct Ov253Entry *table; };
struct Ov253SubMap { signed char m[3]; };

extern void func_ov253_020d2794(struct Ov253Queue *self);
extern void func_ov107_020c7ca4(struct Ov253Queue *self);
extern const struct Ov253SubMap data_ov253_020d49e0;

void func_ov253_020d25e4(struct Ov253Queue *self) {
    if (*(int *)((char *)self + 0x50) == 1) {
        if (*(int *)((char *)self + 0x3d8) == 0) {
            if (*(signed char *)((char *)self + 0x100 + 0xc6) == 2) {
                signed char kind = self->table[self->head].a;
                if (kind != -1) {
                    struct Ov253SubMap map = data_ov253_020d49e0;
                    *(unsigned char *)((char *)self + 0x1c7) = map.m[kind];
                    *(int *)((char *)self + 0x3d8) = 1;
                }
            }
        } else if (*(signed char *)((char *)self + 0x100 + 0xc8) != 2 &&
                   *(signed char *)((char *)self + 0x100 + 0xc6) == 2) {
            *(int *)((char *)self + 0x3d8) = 0;
            func_ov253_020d2794(self);
        }
    }
    func_ov107_020c7ca4(self);
}
