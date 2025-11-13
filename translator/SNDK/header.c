
void SNES_HEADER (){

const char* = "SUPER STORM BUSTER  ";

const uint8 * = { 0x30 
const uint8 * = { 0x00 
const uint8 * = { 0x09 
const uint8 * = { 0x00 
const uint8 * = { 0x01 
const uint8 * = { 0x00 
const uint8 * = { 0x00 
const uint16 * = { 0x00 
const uint16 * = { 0x00 



.data.l 0x00 ;
const uint16 * = { SNES_ERROR 
const uint16 * = { SNES_ERROR 
const uint16 * = { SNES_ERROR 
const uint16 * = { VBlank 
const uint16 * = { 0x00 
const uint16 * = { SNES_IRQHV 


.data.l 0x00 ;
const uint16 * = { SNES_ERROR 
const uint16 * = { 0x00 
const uint16 * = { SNES_ERROR 
const uint16 * = { VBlank 
const uint16 * = { _start 
const uint16 * = { SNES_IRQHV 
}

void SNES_BANK (){

.org (0x8000*.arg1);
.rodata  ( 0x808000 +  0x10000*.arg1 );

}


.map.void 0x200;
.map.void 0xF0;
.map.void 0xE0;
.map. 0x00;
.map. 0x80;