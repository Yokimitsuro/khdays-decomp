void func_ov014_0207fa7c(int actor, unsigned char *msg)
{
    switch (msg[0]) {
    case 1:
        if ((*(unsigned char *)(actor + 0x1b1) & 0x80) == 0) {
            *(unsigned char *)(actor + 0x1b2) = msg[9];
            *(int *)(actor + 0x1c4) += *(int *)(msg + 4);
        }
        break;
    case 2:
        *(int *)(actor + 0x1c4) = 0;
        *(int *)(actor + 0x1c8) = 0;
        *(unsigned char *)(actor + 0x1b1) |= 0x80;
        break;
    }
    *(unsigned char *)(actor + 0x1b1) &= ~1;
}
