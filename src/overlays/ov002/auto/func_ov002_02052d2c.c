/* Maps the two runs of item ids (9..0xb and 0x19..0x1b) onto slots 0..5; -1 for anything else. */
int func_ov002_02052d2c(int id) {
    switch (id) {
    case 9:
        return 0;
    case 0xa:
        return 1;
    case 0xb:
        return 2;
    case 0x19:
        return 3;
    case 0x1a:
        return 4;
    case 0x1b:
        return 5;
    }
    return -1;
}
