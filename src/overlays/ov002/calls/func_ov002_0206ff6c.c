/* Allocate and seed a 0x1c-byte task node carrying the two caller words at
 * +0x14/+0x18, with the default step handler in the first callback slot and the
 * other two empty.
 *
 * The three slots go through a `static inline` setter whose guard is an INT
 * comparison against -1, not a pointer comparison. That distinction is the whole
 * function: `value != (void *)-1` builds the sentinel one way and reuses it,
 * `(int)value != -1` builds it fresh for the third expansion, which is what the
 * ROM does. Nothing here can ever pass -1, so the guard is dead either way --
 * only its spelling shows. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_ov002_0206fd90(void);

typedef struct {
    void *pStep;    /* +0 */
    void *pAlt;     /* +4 */
    void *pDone;    /* +8 */
    char pad000c[8];
    int nA;         /* +0x14 */
    int nB;         /* +0x18 */
} Ov002TaskNode;

static inline void set_callback(void **slot, void *value) {
    if ((int)value != -1) {
        *slot = value;
    }
}

void *func_ov002_0206ff6c(int a, int b) {
    Ov002TaskNode *node =
        (Ov002TaskNode *)NNSi_FndAllocFromDefaultExpHeap(0x1c);

    node->nA = a;
    node->nB = b;

    set_callback(&node->pStep, (void *)func_ov002_0206fd90);
    set_callback(&node->pAlt, (void *)0);
    set_callback(&node->pDone, (void *)0);

    return node;
}
