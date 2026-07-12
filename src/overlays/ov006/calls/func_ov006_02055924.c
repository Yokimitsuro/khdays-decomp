/* Read bit 2 of +0x955c of the ov006 global object, or 1 if absent. */
extern int data_ov006_02056664;
struct bf_word2 { unsigned b0:1, b1:1, b2:1; };
int func_ov006_02055924(void) {
    if (data_ov006_02056664 != 0)
        return ((struct bf_word2 *)(data_ov006_02056664 + 0x955c))->b2;
    return 1;
}
