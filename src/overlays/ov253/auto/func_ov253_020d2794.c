/* func_ov253_020d2794 -- release the +0x3dd queue head: clears the entry (two bytes and a
 * halfword to -1) in the +0x3e4 table, advances the head modulo 16 and drops the +0x3dc count. */
struct Ov253Entry { signed char a; signed char b; short c; };
struct Ov253Queue { char pad[0x3dc]; signed char count; signed char head; char pad3de[6]; struct Ov253Entry *table; };

void func_ov253_020d2794(struct Ov253Queue *self) {
    if (self->head == -1) {
        return;
    }
    self->table[self->head].a = -1;
    self->table[self->head].b = -1;
    self->table[self->head].c = -1;
    self->head = (self->head + 1) % 16;
    self->count = self->count - 1;
}
