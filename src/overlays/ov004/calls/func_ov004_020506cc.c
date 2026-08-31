/* Build up to six glyph draws for a rolling Q12 decimal display.
 * Signed digit -1 suppresses leading zeros; changing digits cross-fade
 * vertically using RGB555 grayscale.
 */
typedef signed char s8;
typedef unsigned short u16;
typedef struct { int x, y, z; } VecFx32;
typedef struct { unsigned char opaque[0x108]; } Ov004DigitGlyph;
typedef struct {
    Ov004DigitGlyph digitGlyphs[10];
    int digitDrawCount;
    Ov004DigitGlyph *digitDrawGlyphs[6];
    VecFx32 digitDrawPositions[6];
    u16 digitDrawColors[6];
} Ov004Context;
extern Ov004Context *data_ov004_02051384;
extern void func_ov004_02050634(s8 *digits, int value);

void func_ov004_020506cc(int valueFx12)
{
    int drawCount;
    int fraction;
    int baseY;
    int currentLevel;
    int digit;
    int inverseFraction;
    int right;
    int step;
    int nextLevel;
    s8 currentDigits[3];
    s8 nextDigits[3];

    fraction = valueFx12 & 0xfff;
    inverseFraction = 0x1000 - fraction;
    drawCount = 0;
    func_ov004_02050634(currentDigits, valueFx12 >> 12);
    func_ov004_02050634(nextDigits, (valueFx12 >> 12) + 1);
    nextLevel = fraction * 28;
    currentLevel = inverseFraction * 28;
    baseY = 1800;
    right = 7000;
    step = 2500;
    for (digit = 2; digit >= 0; digit--) {
        if (currentDigits[digit] != nextDigits[digit] && fraction > 0) {
            if (currentDigits[digit] >= 0) {
                int normalizedLevel = currentLevel >> 12;
                data_ov004_02051384->digitDrawGlyphs[drawCount] = &data_ov004_02051384->digitGlyphs[currentDigits[digit]];
                data_ov004_02051384->digitDrawPositions[drawCount].x = right - digit * step;
                data_ov004_02051384->digitDrawPositions[drawCount].y = (((fraction * 3600) >> 12) + 1800);
                data_ov004_02051384->digitDrawPositions[drawCount].z = 0;
                data_ov004_02051384->digitDrawColors[drawCount] = ((u16)(normalizedLevel | (normalizedLevel << 5) | (normalizedLevel << 10)));
                drawCount++;
            }
            if (nextDigits[digit] >= 0) {
                int normalizedLevel = nextLevel >> 12;
                data_ov004_02051384->digitDrawGlyphs[drawCount] = &data_ov004_02051384->digitGlyphs[nextDigits[digit]];
                data_ov004_02051384->digitDrawPositions[drawCount].x = right - digit * step;
                data_ov004_02051384->digitDrawPositions[drawCount].y = (1800 - ((inverseFraction * 3600) >> 12));
                data_ov004_02051384->digitDrawPositions[drawCount].z = 0;
                data_ov004_02051384->digitDrawColors[drawCount] = ((u16)(normalizedLevel | (normalizedLevel << 5) | (normalizedLevel << 10)));
                drawCount++;
            }
        } else if (currentDigits[digit] >= 0) {
            data_ov004_02051384->digitDrawGlyphs[drawCount] = &data_ov004_02051384->digitGlyphs[currentDigits[digit]];
            data_ov004_02051384->digitDrawPositions[drawCount].x = right - digit * step;
            data_ov004_02051384->digitDrawPositions[drawCount].y = baseY;
            data_ov004_02051384->digitDrawPositions[drawCount].z = 0;
            data_ov004_02051384->digitDrawColors[drawCount] = 0x739c;
            drawCount++;
        }
    }
    data_ov004_02051384->digitDrawCount = drawCount;
}
