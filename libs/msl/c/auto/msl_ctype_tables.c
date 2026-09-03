/* MSL C character tables: case folding and the ctype classification map.
 *
 * Three tables covering the 128 ASCII codes, contiguous at 0x02041bc8-0x02041dc8 and
 * sitting with the string routines (abs at 0x0201f7b0, strlen, strncpy, strncmp), which
 * is also where their readers live -- StrniCmp folds through the first one.
 *
 *   02041bc8  to lower  identity except A-Z, which map to a-z
 *   02041c48  to upper  identity except a-z, which map to A-Z
 *   02041cc8  ctype     one u16 of class bits per code
 *
 * The class bits, read off the table itself: every letter carries ALPHA, tab and space
 * carry BLANK, 0-31 and 127 carry CNTRL, and so on through XDIGIT, which covers the
 * digits plus a-f and A-F. Each entry below is computed from those predicates rather
 * than copied, and the result was checked against the delinked image.
 */

typedef unsigned char u8;
typedef unsigned short u16;

#define CT_ALPHA  0x0001
#define CT_BLANK  0x0002
#define CT_CNTRL  0x0004
#define CT_DIGIT  0x0008
#define CT_GRAPH  0x0010
#define CT_LOWER  0x0020
#define CT_PRINT  0x0040
#define CT_PUNCT  0x0080
#define CT_SPACE  0x0100
#define CT_UPPER  0x0200
#define CT_XDIGIT 0x0400

const u8 data_02041bc8[128] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,
     12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,
     24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,
     36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  97,  98,  99, 100, 101, 102, 103,
    104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115,
    116, 117, 118, 119, 120, 121, 122,  91,  92,  93,  94,  95,
     96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107,
    108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127,
};

const u8 data_02041c48[128] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,
     12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,
     24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,
     36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
     72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,
     84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
     96,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,
     76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
     88,  89,  90, 123, 124, 125, 126, 127,
};

const u16 data_02041cc8[128] = {
    0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004,
    0x0004, 0x0106, 0x0104, 0x0104, 0x0104, 0x0104, 0x0004, 0x0004,
    0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004,
    0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004,
    0x0142, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0,
    0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0,
    0x0458, 0x0458, 0x0458, 0x0458, 0x0458, 0x0458, 0x0458, 0x0458,
    0x0458, 0x0458, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0,
    0x00d0, 0x0651, 0x0651, 0x0651, 0x0651, 0x0651, 0x0651, 0x0251,
    0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251,
    0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251,
    0x0251, 0x0251, 0x0251, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0,
    0x00d0, 0x0471, 0x0471, 0x0471, 0x0471, 0x0471, 0x0471, 0x0071,
    0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071,
    0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071,
    0x0071, 0x0071, 0x0071, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x0004,
};
