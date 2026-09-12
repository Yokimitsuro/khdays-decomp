/* Pops the head record from a 4-slot ring buffer of 2-halfword records at
 * base+0xb47a2, copying it into the "current" output field at base+0xb479e.
 * If the queue is already empty (count byte at +0xb47b3 == 0), only the low
 * byte of the output field is cleared and the head/count are left alone. */
extern char *data_0204c234;

typedef struct {
    unsigned short field_00;
    unsigned short field_02;
} QueueRec;

void func_02032c40(void) {
    char *base = data_0204c234;

    if (*(unsigned char *)(base + 0xb47b3) == 0) {
        *(unsigned char *)(base + 0xb479e) = 0;
        return;
    }

    *(QueueRec *)(base + 0xb479e) =
        *(QueueRec *)(base + *(unsigned char *)(base + 0xb47b2) * 4 + 0xb47a2);

    *(unsigned char *)(base + 0xb47b2) = (*(unsigned char *)(base + 0xb47b2) + 1) % 4;
    *(unsigned char *)(base + 0xb47b3) = *(unsigned char *)(base + 0xb47b3) - 1;
}
