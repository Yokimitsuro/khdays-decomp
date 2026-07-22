/* Looks up parameter word `b` in data_0204c590 and feeds its two packed fields to
 * func_020256b8 together with the sub-record at +0x28 of record `a` in data_0204c678.
 *
 * The packing must be written as a bitfield pair: the ROM extracts both halves with
 * lsl/lsr shift pairs (lsl#16/lsr#20 and lsl#28/lsr#28), which is bitfield codegen --
 * a plain `v >> 4` gives an `asrs` and `v & 0xf` gives `movs #0xf` + `ands`.
 * Access through a pointer, not a copy: a struct copy costs four bytes here. */
struct Params {
    unsigned short lo : 4;
    unsigned short hi : 12;
};

extern struct Params data_0204c590[];
extern unsigned char data_0204c678[];
extern int func_020256b8(unsigned char *p, int hi, int lo);

int func_020358f4(int a, int b) {
    struct Params *v = &data_0204c590[b - 1];
    return (unsigned char)func_020256b8(data_0204c678 + a * 260 + 0x28, v->hi, v->lo);
}
