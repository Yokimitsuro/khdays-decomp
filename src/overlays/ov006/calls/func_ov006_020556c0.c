/* When bit 2 of +0x955c is set, latch +0x94f4 to 9. */
extern int data_ov006_02056664;
struct bf_word { unsigned b0:1, b1:1, b2:1; };
void func_ov006_020556c0(void) {
    if (((struct bf_word *)(data_ov006_02056664 + 0x955c))->b2)
        *(int *)(data_ov006_02056664 + 0x94f4) = 9;
}
