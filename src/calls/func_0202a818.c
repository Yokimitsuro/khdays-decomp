extern void func_0202a75c(void *this_);

typedef struct AnmChannel {
    int current;            // +0x00: Q12 accumulated value
    int field_04;           // +0x04: unknown, unused here
    unsigned short *info;   // +0x08: -> target value lives at info[2] (+4 bytes)
} AnmChannel;

typedef struct {
    unsigned short flags;      // +0x00
    short active[5];           // +0x02: >=0 while channels[i] is live
    AnmChannel *channels[5];   // +0x0c
    char pad_20[0xca - 0x20];
    short inActive[5];         // +0xca: >=0 while inChannel should advance for slot i
    AnmChannel *inChannel;     // +0xd4
} AnmGroup;

unsigned short func_0202a818(AnmGroup *this_, int delta)
{
    unsigned short result = 0;
    int i;

    if (this_->flags & 4) {
        func_0202a75c(this_);
    }
    if (!(this_->flags & 2)) {
        for (i = 0; i < 5; i++) {
            if (this_->active[i] >= 0) {
                AnmChannel *ch = this_->channels[i];
                int target = ch->info[2] << 12;
                if (!(this_->flags & 4)) {
                    ch->current += delta;
                }
                if (ch->current >= target) {
                    if ((this_->flags & 4) && i == 0) {
                        ch->current = target;
                    } else {
                        result |= (1 << i);
                        ch->current -= target;
                    }
                }
            }
            if (this_->flags & 4) {
                if (this_->inActive[i] >= 0) {
                    AnmChannel *in = this_->inChannel;
                    int target2 = in->info[2] << 12;
                    in->current += delta;
                    if (in->current >= target2) {
                        result |= (1 << i);
                        in->current = target2;
                    }
                }
            }
        }
    }
    return result;
}
