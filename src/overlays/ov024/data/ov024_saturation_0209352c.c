/* ov024 .rodata 0x0209352c-0x0209382c: the colour-conversion saturation table.
 *
 * The converter indexes this with a biased component value and gets back a
 * 5-bit channel, saturated, already duplicated into both bytes so one lookup
 * serves the two packed components it is about to write.
 *
 * Measured over all 384 entries, the table is exactly
 *
 *     entry[i] = clamp((i - 128) >> 2, 0, 31) * 0x0101
 *
 * so the 128 entries below the bias and the 132 above it are the clamp's two
 * flat ends: the table absorbs the over- and undershoot the YCoCg to RGB555
 * step produces, which is why it is 384 long and not 256.
 */
typedef unsigned short u16;

#define SAT(c) ((u16)((c) * 0x0101))
#define SAT4(c) SAT(c), SAT(c), SAT(c), SAT(c)

const u16 data_ov024_0209352c[384] = {
    /* i < 132: (i - 128) >> 2 is at most 0, so the channel clamps low */
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),
    SAT4(0),

    /* the ramp proper: one step of the 5-bit channel every four indices */
    SAT4(1),
    SAT4(2),
    SAT4(3),
    SAT4(4),
    SAT4(5),
    SAT4(6),
    SAT4(7),
    SAT4(8),
    SAT4(9),
    SAT4(10),
    SAT4(11),
    SAT4(12),
    SAT4(13),
    SAT4(14),
    SAT4(15),
    SAT4(16),
    SAT4(17),
    SAT4(18),
    SAT4(19),
    SAT4(20),
    SAT4(21),
    SAT4(22),
    SAT4(23),
    SAT4(24),
    SAT4(25),
    SAT4(26),
    SAT4(27),
    SAT4(28),
    SAT4(29),
    SAT4(30),

    /* i >= 252: the channel is saturated */
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
    SAT4(31),
};
