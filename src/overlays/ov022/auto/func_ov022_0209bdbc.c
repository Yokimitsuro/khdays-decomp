/* func_ov022_0209bdbc -- swap the two paired flag bits in an actor's state halfword,
 * but only while the actor is in phase 5 (the signed byte at +0x2770).
 * 0x40 and 0x80 are one pair and 0x10 and 0x20 the other; whichever bit of a pair is set
 * is cleared and its partner is set, so each pair toggles between its two states.
 *
 * Two shapes matter: the clears are `& ~BIT`, not `& 0xffXX` -- the complement of an int
 * literal is what mwcc turns into `bic`, while a 16-bit mask needs a literal-pool word; and
 * within a pair the set comes before the clear (`orr` then `bic`), which is the source order,
 * not the other way round. */
void func_ov022_0209bdbc(int arg0) {
    unsigned short v = *(unsigned short *)(arg0 + 0x1a);

    if (*(char *)(arg0 + 0x2770) != 5) return;

    if ((v & 0x40) != 0) {
        *(unsigned short *)(arg0 + 0x1a) = v | 0x80;
        *(unsigned short *)(arg0 + 0x1a) = *(unsigned short *)(arg0 + 0x1a) & ~0x40;
    } else if ((v & 0x80) != 0) {
        *(unsigned short *)(arg0 + 0x1a) = v | 0x40;
        *(unsigned short *)(arg0 + 0x1a) = *(unsigned short *)(arg0 + 0x1a) & ~0x80;
    }

    if ((v & 0x20) != 0) {
        *(unsigned short *)(arg0 + 0x1a) = (*(unsigned short *)(arg0 + 0x1a) | 0x10) & ~0x20;
        return;
    }
    if ((v & 0x10) == 0) return;
    *(unsigned short *)(arg0 + 0x1a) = (*(unsigned short *)(arg0 + 0x1a) | 0x20) & ~0x10;
}
