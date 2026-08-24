#pragma opt_strength_reduction off

extern void func_ov022_020b06d8(unsigned char *channel, int mode);

struct ChannelFlags020b064c {
    unsigned char playing : 1;
    unsigned char looping : 1;
    unsigned char rest : 6;
};

struct ChannelGrid020b064c {
    unsigned char _pad00[2];
    unsigned char mode;
    unsigned char _pad03[0x30 - 3];
    short count;
    unsigned char _pad32[2];
    unsigned char *channels;
    unsigned char _pad38[4];
    struct ChannelFlags020b064c flags;
    unsigned char _pad3d;
    short cells[4][8];
};

void func_ov022_020b064c(struct ChannelGrid020b064c *self) {
    int column;
    int row;

    self->flags.playing = 0;
    self->flags.looping = 0;

    row = 0;
    do {
        column = 0;
        do {
            self->cells[row][column] = -1;
            column = column + 1;
        } while (column < 8);
        row = row + 1;
    } while (row < 4);

    column = 0;
    if (self->count <= 0) {
        return;
    }

    row = column;
    do {
        func_ov022_020b06d8(self->channels + row, self->mode);
        column = column + 1;
        row = row + 0x48;
    } while (column < self->count);
}
