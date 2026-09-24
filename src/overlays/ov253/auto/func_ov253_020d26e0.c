/* func_ov253_020d26e0 -- push a queue entry at the +0x3de tail of the +0x3e4 table: the kind
 * byte, the hit's +2 slot (or -1 without a hit) and the running +0x3e0 sequence, which then
 * advances modulo 0x7fff; the tail wraps modulo 16 and the +0x3dc count grows. Returns the
 * sequence used. */
struct Ov253Entry { signed char a; signed char b; short c; };
struct Ov253Queue { char pad[0x3dc]; signed char count; signed char head; signed char tail; char pad3df; short seq; char pad3e2[2]; struct Ov253Entry *table; };

int func_ov253_020d26e0(struct Ov253Queue *self, unsigned char kind, unsigned char *hit) {
    short seq = self->seq;
    signed char slot;

    self->table[self->tail].a = kind;
    if (hit != 0) {
        slot = *(unsigned short *)(hit + 2);
    } else {
        slot = -1;
    }
    self->table[self->tail].b = slot;
    self->table[self->tail].c = seq;
    self->seq = (self->seq + 1) % 0x7fff;
    self->tail = (self->tail + 1) % 16;
    self->count = self->count + 1;
    return seq;
}
