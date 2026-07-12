/* Return bit 0 of the byte at +0x28 of the global object, or 0 when it is null. */
extern int data_ov008_02090f00;

struct bits_0204ebf0 { unsigned char b0 : 1; };

int func_ov008_0204ebf0(void) {
    int g = *(int *)&data_ov008_02090f00;
    if (g != 0) return ((struct bits_0204ebf0 *)(g + 0x28))->b0;
    return 0;
}
