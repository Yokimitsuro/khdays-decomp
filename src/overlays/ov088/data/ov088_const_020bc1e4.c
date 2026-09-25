/* ov088 .rodata 0x020bc1e4-0x020bc1e8: the word 0x6000 at the head of the overlay's .rodata, shared by
 * the four twin overlays (ov031/ov050/ov070/ov088). No code references it: an initializer
 * whose copy the compiler dropped. */
const int data_ov088_020bc1e4 = 0x6000;
