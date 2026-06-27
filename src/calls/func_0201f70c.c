extern void *func_0201e4c8(void);
extern void OS_SendMessage(void *queue, void *message, int flags);

extern int data_0204bc1c;

typedef struct {
    char _0[4];
    int type;
    unsigned short id;
    char _a[2];
    int arg1;
    int arg2;
} Message_0201f70c;

void func_0201f70c(unsigned short id, int arg1, int arg2)
{
    Message_0201f70c *msg = func_0201e4c8();

    if (msg == 0)
        return;

    msg->type = 2;
    msg->id = id;
    msg->arg1 = arg1;
    msg->arg2 = arg2;
    OS_SendMessage(&data_0204bc1c, msg, 1);
}
