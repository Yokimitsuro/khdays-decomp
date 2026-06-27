extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int);
extern void func_02001a34(void *);
extern void OSi_RescheduleThread(void);

typedef struct Node {
    char pad[0x68];
    struct Node *next;  /* +0x68 */
    int pad2;           /* +0x6c */
    int value;          /* +0x70 */
} Node;

typedef struct {
    char pad[0x2c];
    Node *head;         /* +0x2c */
} ListHead;

extern ListHead data_0204430c;
extern Node data_02044340;

int OSi_WaitOnExitProc(Node *target, int newval)
{
    Node *cur;
    Node *prev;
    int intr;

    prev = 0;
    cur = data_0204430c.head;
    intr = OS_DisableInterrupts();
    while (cur != 0 && cur != target) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == 0 || cur == &data_02044340) {
        OS_RestoreInterrupts(intr);
        return 0;
    }
    if (cur->value != newval) {
        if (prev == 0) {
            data_0204430c.head = target->next;
        } else {
            prev->next = target->next;
        }
        target->value = newval;
        func_02001a34(target);
        OSi_RescheduleThread();
    }
    OS_RestoreInterrupts(intr);
    return 1;
}
