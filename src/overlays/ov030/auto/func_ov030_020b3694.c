/* Maps an actor's kind byte to the cue it should play.
 *
 * Kinds 0x16 through 0x19 share one offset, 0x1a and 0x1b have their own fixed
 * cues, and everything else falls back one below the shared offset. The six
 * listed kinds are contiguous, which is why the original reaches them through a
 * jump table rather than a compare chain.
 */
typedef unsigned char u8;

struct Ov030Actor {
    char pad000[0x918];
    u8 bKind918;                            /* 0x918 */
};

int func_ov030_020b3694(struct Ov030Actor *actor)
{
    u8 kind = actor->bKind918;

    switch (kind) {
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
        return kind + 0x56;
    case 0x1a:
        return 0x6b;
    case 0x1b:
        return 0x56;
    }
    return kind + 0x55;
}
