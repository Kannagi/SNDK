

extern uint8_t _sndk_arg1;
extern uint8_t _sndk_arg2;
extern uint8_t _sndk_arg3;
extern uint8_t _sndk_arg4;
extern uint8_t _sndk_arg5;
extern uint8_t _sndk_arg6;
extern uint8_t _sndk_arg7;

extern uint8_t _sndk_arg8;
extern uint8_t _sndk_arg9;
extern uint8_t _sndk_arg10;
extern uint8_t _sndk_arg11;
extern uint8_t _sndk_arg12;
extern uint8_t _sndk_arg13;
extern uint8_t _sndk_arg14;

inline void CSNDK_WaitVBlank(void)
{
    SNDK_WaitVBlank();
}

inline void CSNDK_PrintNumber8(uint8_t number,uint8_t px,uint8_t py,uint8_t pal)
{
    _sndk_arg1 = number;

    _sndk_arg2 = px;
    _sndk_arg3 = 0;

    _sndk_arg4 = py;
    _sndk_arg5 = 0;

    _sndk_arg6 = pal;

    SNDK_PrintNumber8();
}