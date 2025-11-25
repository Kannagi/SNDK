
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef char sint8_t;
typedef short sint16_t;

void SNDK_WaitVBlank(void);
void SNDK_PrintNumber8(void);

void CSNDK_FORCED_BLANK(void);
void CSNDK_Init(void);

uint8_t CSNDK_JOYPAD1A(void);
uint8_t CSNDK_JOYPAD1B(void);
uint8_t CSNDK_JOYPAD1AN(void);
uint8_t CSNDK_JOYPAD1BN(void);
