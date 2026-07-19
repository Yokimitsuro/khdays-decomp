/* Clears the "busy" bit in the high byte of the node's 0x60 flag word. */
void func_ov258_020d029c(int *self) {
    int *s = (int *)self[1];
    unsigned short *p = (unsigned short *)(*s + 0x60);
    unsigned short hi = (unsigned short)((((unsigned)*p << 0x10) >> 0x18) & ~0x80);
    *p = (unsigned short)((*p & ~0xff00) | (((unsigned)hi << 0x18) >> 16));
}
