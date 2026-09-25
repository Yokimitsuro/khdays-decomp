/* ov050 .rodata 0x020b7444-0x020b7448: the word 0x6000 at the head of the overlay's .rodata, shared by
 * the four twin overlays (ov031/ov050/ov070/ov088). No code references it: an initializer
 * whose copy the compiler dropped. */
const int data_ov050_020b7444 = 0x6000;
