/* Maps the two runs of item ids (9..0xb and 0x19..0x1b) onto slots 4..6 and 0..2; -1 for anything else. */
int func_ov026_02085124(int id) {
    switch (id) {
    case 9:
        return 4;
    case 0xa:
        return 5;
    case 0xb:
        return 6;
    case 0x19:
        return 0;
    case 0x1a:
        return 1;
    case 0x1b:
        return 2;
    }
    return -1;
}
