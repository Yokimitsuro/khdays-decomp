/* NitroSDK IRQ-callback bit index table: 0x020422a0..0x020422b0.
 *
 * OSi_IrqCallback takes a slot number and needs the hardware interrupt bit that
 * slot stands for, both to set the check flag and to disable the source again.
 * This table is that mapping, one entry per slot of the 8-slot callback record
 * array at 0x020442a8.
 *
 * The values are the IE/IF bit numbers of the eight sources NitroSDK routes
 * through a callback: the four DMA channels first, then the four timers.
 *
 *   slot 0..3  ->  bits 8..11   DMA 0..3
 *   slot 4..7  ->  bits 3..6    Timer 0..3
 *
 * The eight dispatch veneers confirm the order independently: OSi_IrqDma0 calls
 * OSi_IrqCallback(0) and OSi_IrqTimer0 calls OSi_IrqCallback(4), which is also why
 * the table is exactly eight entries long.
 *
 * The table lives in .data rather than .rodata, so it is not const.
 */

typedef unsigned short u16;

u16 data_020422a0[8] = {
     8,  9, 10, 11,   /* DMA 0, 1, 2, 3   */
     3,  4,  5,  6,   /* Timer 0, 1, 2, 3 */
};
