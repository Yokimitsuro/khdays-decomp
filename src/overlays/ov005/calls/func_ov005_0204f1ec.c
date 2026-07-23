typedef unsigned short u16;

typedef struct {
    int id;
    u16 quantity;
    u16 amount;
} CommandSlot;

typedef struct {
    int unk_00;
    int command;
    int unk_08;
    int quantityBase;
    char pad_10[0xc];
    CommandSlot slots[4];
    char pad_3c[0x3c];
    union {
        struct {
            int deltas[7];
            int counters[14];
        } accumulator;
        struct {
            char pad_78[0x10];
            int deltas[7];
            int counters[14];
        } command;
    } values;
} TallyState;

typedef TallyState TallyAccumulator;
typedef TallyState TallyCommand;

extern void func_ov005_0204ef70(
    int accumulator,
    int id,
    int quantity,
    int amount,
    unsigned int flags);
extern void func_ov005_0204eedc(
    int accumulator,
    int id,
    int amount,
    unsigned int flags);

static inline void applySlots(int accumulator, TallyState *cmd, int type)
{
    int i;
    u16 quantity;
    int quantityBase;

    for (i = 0; i < 4; i++) {
        if (type == 1) {
            char *row = (char *)cmd + i * sizeof(CommandSlot);
            if (*(int volatile *)(row + 0x1c) != 0) {
                quantity = *(volatile u16 *)(row + 0x20);
                quantityBase = *(volatile int *)&cmd->quantityBase;
                func_ov005_0204ef70(
                    accumulator,
                    *(int *)(row + 0x1c),
                    quantity + (quantityBase - 1),
                    0,
                    1U);
            }
        } else if (cmd->slots[i].id != 0) {
            func_ov005_0204eedc(
                accumulator,
                cmd->slots[i].id,
                cmd->slots[i].amount,
                1U);
        }
    }
}

void func_ov005_0204f1ec(
    int accumulator,
    int command)
{
    TallyState *cmd = (TallyState *)command;
    TallyState *acc = (TallyState *)accumulator;

    switch (cmd->command) {
    case 1:
        applySlots((int)acc, cmd, 1);
        break;

    case 3:
        applySlots((int)acc, cmd, 3);
        /* Fall through: command 3 also applies all deltas. */
    case 6: {
        int i;
        int cap = 0x64000;
        acc->values.accumulator.deltas[0] += cmd->values.command.deltas[0];
        acc->values.accumulator.deltas[1] += cmd->values.command.deltas[1];
        acc->values.accumulator.deltas[2] += cmd->values.command.deltas[2];
        acc->values.accumulator.deltas[3] += cmd->values.command.deltas[3];
        acc->values.accumulator.deltas[4] += cmd->values.command.deltas[4];
        acc->values.accumulator.deltas[5] += cmd->values.command.deltas[5];
        acc->values.accumulator.deltas[6] += cmd->values.command.deltas[6];

        for (i = 0; i < 14; i++) {
            acc->values.accumulator.counters[i] +=
                cmd->values.command.counters[i];
            if (acc->values.accumulator.counters[i] > cap) {
                acc->values.accumulator.counters[i] = cap;
            }
        }
        break;
    }
    }
}
