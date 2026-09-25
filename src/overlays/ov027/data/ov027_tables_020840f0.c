/* ov027 .data tables, 0x020840f0-0x02084148.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

signed char data_ov027_020840f0[20] = {
    13, 3, 19, 14, 17, 15, 4, 7, 8, 9,
    10, 12, 16, 18, 20, 21, 11, 5, 6, 13,
};

char data_ov027_02084104[68] = "Hast du Probleme? Nimm doch die Gegner-\nprofile im Men\xc3\xbc zur Hilfe!";
