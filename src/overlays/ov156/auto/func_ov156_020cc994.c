struct substate {
    signed char _pad[0x1c7];
    signed char status;
};

int func_ov156_020cc994(int obj)
{
    struct substate *state = *(struct substate **)(*(int *)(obj + 0x214));
    if (state->status == -1) {
        state->status = 7;
        return 1;
    }
    return 0;
}
