/* The stream's current 64-bit timestamp, or 0 when there is no stream. Both
 * halves are read separately and both are zeroed on the null path, which is what
 * a predicated long long return looks like. */
extern void *func_01fffde0(void);

typedef struct {
    char pad0000[0x464];
    unsigned long long qwTimestamp; /* +0x464 */
} Ov022Stream;

unsigned long long func_ov022_02088314(void) {
    Ov022Stream *stream = (Ov022Stream *)func_01fffde0();

    if (stream == 0) {
        return 0;
    }

    return stream->qwTimestamp;
}
