/* ov024 .rodata 0x020933ac-0x0209352c: the byte-pair saturation table.
 *
 * The 8-bit counterpart of the 5-bit table that follows it. One lookup with a
 * biased value returns two consecutive output bytes, both saturated, packed
 * into the halfword:
 *
 *     entry[i] = clamp(2*(i - 32) + 1, 0, 255) << 8 | clamp(2*(i - 32), 0, 255)
 *
 * The 32 entries below the bias and the 32 above are the clamp's flat ends.
 */
typedef unsigned short u16;

#define PAIR(lo) ((u16)((((lo) + 1) << 8) | (lo)))

const u16 data_ov024_020933ac[192] = {
    /* i < 32: both bytes clamp low */
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

    /* the ramp proper: two output bytes per entry, stepping by two */
    PAIR(0), PAIR(2), PAIR(4), PAIR(6), PAIR(8), PAIR(10),
    PAIR(12), PAIR(14), PAIR(16), PAIR(18), PAIR(20), PAIR(22),
    PAIR(24), PAIR(26), PAIR(28), PAIR(30), PAIR(32), PAIR(34),
    PAIR(36), PAIR(38), PAIR(40), PAIR(42), PAIR(44), PAIR(46),
    PAIR(48), PAIR(50), PAIR(52), PAIR(54), PAIR(56), PAIR(58),
    PAIR(60), PAIR(62), PAIR(64), PAIR(66), PAIR(68), PAIR(70),
    PAIR(72), PAIR(74), PAIR(76), PAIR(78), PAIR(80), PAIR(82),
    PAIR(84), PAIR(86), PAIR(88), PAIR(90), PAIR(92), PAIR(94),
    PAIR(96), PAIR(98), PAIR(100), PAIR(102), PAIR(104), PAIR(106),
    PAIR(108), PAIR(110), PAIR(112), PAIR(114), PAIR(116), PAIR(118),
    PAIR(120), PAIR(122), PAIR(124), PAIR(126), PAIR(128), PAIR(130),
    PAIR(132), PAIR(134), PAIR(136), PAIR(138), PAIR(140), PAIR(142),
    PAIR(144), PAIR(146), PAIR(148), PAIR(150), PAIR(152), PAIR(154),
    PAIR(156), PAIR(158), PAIR(160), PAIR(162), PAIR(164), PAIR(166),
    PAIR(168), PAIR(170), PAIR(172), PAIR(174), PAIR(176), PAIR(178),
    PAIR(180), PAIR(182), PAIR(184), PAIR(186), PAIR(188), PAIR(190),
    PAIR(192), PAIR(194), PAIR(196), PAIR(198), PAIR(200), PAIR(202),
    PAIR(204), PAIR(206), PAIR(208), PAIR(210), PAIR(212), PAIR(214),
    PAIR(216), PAIR(218), PAIR(220), PAIR(222), PAIR(224), PAIR(226),
    PAIR(228), PAIR(230), PAIR(232), PAIR(234), PAIR(236), PAIR(238),
    PAIR(240), PAIR(242), PAIR(244), PAIR(246), PAIR(248), PAIR(250),
    PAIR(252), PAIR(254),

    /* i >= 160: both bytes are saturated */
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
};
