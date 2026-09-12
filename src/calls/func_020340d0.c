typedef struct ListenerNode020340d0 {
    struct ListenerNode020340d0 *next;   /* +0x00 */
    char pad04[0x10];
    unsigned short flags;                /* +0x14 */
} ListenerNode020340d0;

typedef struct {
    char pad0000[0xb46e8];
    ListenerNode020340d0 *list;          /* +0xb46e8 */
    char pad06ec[0xc8];
    unsigned char enabled;               /* +0xb47b4 */
} S_020340d0;

extern S_020340d0 *data_0204c234;

void func_020340d0(int enabled) {
    S_020340d0 *base = data_0204c234;
    ListenerNode020340d0 *node;

    base->enabled = (unsigned char)enabled;
    node = base->list;

    if (enabled != 0) {
        for (; node != 0; node = node->next) {
            node->flags |= 4;
        }
    } else {
        for (; node != 0; node = node->next) {
            node->flags &= ~4;
        }
    }
}
