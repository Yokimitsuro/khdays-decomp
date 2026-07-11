/* NONMATCHING — instruction-scheduling tie (byte-structurally identical otherwise).
 *
 * Every instruction matches the original in opcode, operand and order EXCEPT one
 * 2-instruction swap at the very top: the ROM materialises 0x800 and stores it to
 * field [0] *before* loading the first pool constant (0xddb), i.e.
 *     mov r1,#0x800 ; str r1,[r0] ; ldr r2,[pc] (0xddb) ; ...
 * whereas every mwcc build we have hoists the pool load ahead of the store to hide
 * load-use latency:
 *     mov r1,#0x800 ; ldr r2,[pc] (0xddb) ; str r1,[r0] ; ...
 * All 14 field stores, both pool constants (0xddb, 0x1555), the 0x1000/r3 reuse and
 * the exact store ORDER are otherwise byte-identical.
 *
 * Proven unsteerable: swept all 27 checked-in mwccarm builds (1.2..sp4, 2.0..sp2p4,
 * 3.0/136, 3.0/139, dsi) x {-O4,p / -O4,s / -O4} — none emits the store-first schedule.
 * The ROM's original compiler kept the store adjacent; we don't have that exact build.
 * The blob keeps the build byte-exact; this file records the intended, readable source.
 *
 * Initialises a state struct with default constants (fixed-point: 0x1000 == 1.0 in
 * .12, 0x800 == 0.5). Field/store order matches the ROM.
 */
void func_02023c60(unsigned int *p) {
    p[0]  = 0x800;
    p[1]  = 0xddb;
    p[2]  = 0x1555;
    p[3]  = 0x1000;
    p[4]  = 0x3e8000;
    p[7]  = 0;
    p[6]  = 0;
    p[5]  = 0;
    p[9]  = 0;
    p[8]  = 0;
    p[10] = 0x64000;
    p[13] = 0;
    p[11] = 0;
    p[12] = 0x1000;
}
