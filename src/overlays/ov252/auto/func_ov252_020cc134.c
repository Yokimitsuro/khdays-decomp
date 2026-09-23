/* Show armour piece `i` of the ov252 actor when `show` is set: its +0x38c model unhides (+0x5c bit 1),
 * its +0x4f4 shape hides (bit 0) and its +0x518 record's high nibble gains bit 0. */
typedef unsigned char u8;
typedef struct { unsigned f : 8; } B8;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

void func_ov252_020cc134(char *self, int i, int show)
{
    char *slot;

    if (show == 0) {
        return;
    }
    slot = self + i * 4;
    *(int *)(*(int *)(slot + 0x38c) + 0x5c) &= ~2;
    ((B8 *)(*(int *)(slot + 0x4f4) + 8))->f &= ~1;
    ((NibblePair *)*(int *)(slot + 0x518))->hi |= 1;
}
