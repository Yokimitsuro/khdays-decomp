typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OSThread {
    u8 reserved_00[0x68];
    struct OSThread *next;
    u32 id;
    u32 priority;
} OSThread;

typedef struct OSThreadInfo {
    u8 reserved_00[0x2c];
    OSThread *list;
} OSThreadInfo;

extern OSThreadInfo data_0204430c;

void OSi_InsertThreadByPriority(OSThread *thread)
{
    OSThread *current = data_0204430c.list;
    OSThread *previous = 0;

    while (current != 0 && current->priority < thread->priority) {
        previous = current;
        current = current->next;
    }

    if (previous == 0) {
        thread->next = data_0204430c.list;
        data_0204430c.list = thread;
    } else {
        thread->next = previous->next;
        previous->next = thread;
    }
}
