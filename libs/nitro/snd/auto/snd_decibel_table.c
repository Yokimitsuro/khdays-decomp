/* NitroSDK SND decibel table: volume level to attenuation, 128 entries.
 *
 * Entry i is round(200 * log10(i / 127)), i.e. the attenuation of a 0..127 volume
 * level expressed in tenths of a decibel against full scale. Entry 127 is 0 because
 * full volume is no attenuation, and entry 0 is -32768 standing in for silence,
 * where the logarithm has no value.
 *
 * Read by the two sound routines at 0x0201a170 and 0x0201cc50, which sit inside the
 * SND address range (SND_SetActiveSlotSwap is at 0x0201b3c0, between them).
 *
 * Every entry is the rounded formula above, checked against the delinked image.
 */

typedef short s16;

const s16 data_02041488[128] = {
    -32768,   -421,   -361,   -325,   -300,   -281,   -265,   -252,
      -240,   -230,   -221,   -212,   -205,   -198,   -192,   -186,
      -180,   -175,   -170,   -165,   -161,   -156,   -152,   -148,
      -145,   -141,   -138,   -134,   -131,   -128,   -125,   -122,
      -120,   -117,   -114,   -112,   -110,   -107,   -105,   -103,
      -100,    -98,    -96,    -94,    -92,    -90,    -88,    -86,
       -85,    -83,    -81,    -79,    -78,    -76,    -74,    -73,
       -71,    -70,    -68,    -67,    -65,    -64,    -62,    -61,
       -60,    -58,    -57,    -56,    -54,    -53,    -52,    -51,
       -49,    -48,    -47,    -46,    -45,    -43,    -42,    -41,
       -40,    -39,    -38,    -37,    -36,    -35,    -34,    -33,
       -32,    -31,    -30,    -29,    -28,    -27,    -26,    -25,
       -24,    -23,    -23,    -22,    -21,    -20,    -19,    -18,
       -17,    -17,    -16,    -15,    -14,    -13,    -12,    -12,
       -11,    -10,     -9,     -9,     -8,     -7,     -6,     -6,
        -5,     -4,     -3,     -3,     -2,     -1,     -1,      0,
};
