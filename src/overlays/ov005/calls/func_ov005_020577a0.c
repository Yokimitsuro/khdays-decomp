/* Ov005_CalculateGaugeRange: select the score interval from database 0x1c.
 * Rows contain a signed threshold after the 12-byte message record header.
 * The first threshold above score supplies the upper bound; the preceding
 * row supplies the lower bound. A negative threshold terminates the search.
 * Both fetched records are released on every path before unloading the DB.
 *
 * Codegen: these are independent, non-volatile scalar locals. Their declaration
 * order controls the spill slots. Keep nextLower distinct from lower: shadowing
 * lower would silently discard the chosen lower bound. No wide-zero idiom is
 * needed. ARM: 292 bytes, 10 relocations, byte-exact.
 */
typedef unsigned char u8;

typedef struct Ov005ThresholdRecord {
    char header[12];
    int threshold;
} Ov005ThresholdRecord;

typedef struct Ov005GaugeRange {
    int maximum;
    int value;
} Ov005GaugeRange;

extern int func_02034150(int database, int heap);
extern int func_020342e8(Ov005ThresholdRecord **record, int database,
                       unsigned int index, int heap);
extern int func_020343cc(Ov005ThresholdRecord **record);
extern int func_02034258(int database);

void func_ov005_020577a0(Ov005GaugeRange *range, int score)
{
    int lower;
    int upper;
    Ov005ThresholdRecord *previous;
    Ov005ThresholdRecord *current;
    u8 index;

    lower = 0;
    upper = lower;
    func_02034150(28, 14);
    for (index = 0; index < 100; index++) {
        current = previous = 0;
        func_020342e8(&current, 28, index, 14);
        func_020342e8(&previous, 28, index != 0 ? index - 1 : 0, 14);
        if (current->threshold > score) {
            int nextLower = previous->threshold;
            upper = current->threshold;
            lower = nextLower;
            func_020343cc(&current);
            func_020343cc(&previous);
            break;
        }
        if (current->threshold < 0) {
            func_020343cc(&current);
            func_020343cc(&previous);
            break;
        }
        func_020343cc(&current);
        func_020343cc(&previous);
    }
    func_02034258(28);
    range->maximum = upper - lower;
    range->value = score - lower;
}
