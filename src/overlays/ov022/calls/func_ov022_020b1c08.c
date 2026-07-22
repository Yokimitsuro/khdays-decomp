/* Re-cue the track for the states that own one: state 2 also has to stop the
 * previous cue first, states 3 and 4 fall straight into the re-cue. Any other
 * state skips it. The follow-up runs either way. */
extern void func_0201ef58(void);
extern void func_020339b0(int channel, int cue);
extern void func_ov022_020b1be8(void *self, int channel);

typedef struct {
    unsigned char bState;   /* +0 */
    char pad0001[1];
    short wCue;             /* +2 */
    char pad0004[2];
    signed char bChannel;   /* +6 */
} Ov022Track;

void func_ov022_020b1c08(Ov022Track *self) {
    switch (self->bState) {
    case 2:
        func_0201ef58();
        /* fall through */
    case 3:
    case 4:
        func_020339b0(self->bChannel, self->wCue);
        break;
    }

    func_ov022_020b1be8(self, self->bChannel);
}
