#include "debug.h"

void log_fatal(Emulator* emu, const char* string) {
    printf("[FATAL]");
    printf(" %s", string);
    printf("\n");

    exit(99);
}

void log_warning(Emulator* emu, const char* string) {
    printf("[WARNING]");
    printf(" %s", string);
    printf("\n");
}

static uint16_t read2Bytes(Emulator* emu) {
    uint8_t b1 = read(emu, emu->PC.entireByte + 1);
    uint8_t b2 = read(emu, emu->PC.entireByte + 2);
    uint16_t D16 = (b2 << 8) | b1;
    return D16;
}

static void printFlags(Emulator* emu) {
    uint8_t flagState = emu->AF.bytes.lower;

    printf("[Z%d", flagState >> 7);
    printf(" N%d", (flagState >> 6) & 1);
    printf(" H%d", (flagState >> 5) & 1);
    printf(" C%d]", (flagState >> 4) & 1);
}

static void simpleInstruction(Emulator* emu, char* ins) {
    printf("%s\n", ins);;
}

static void d16(Emulator* emu, char* ins) {
    printf("%s (0x%04x)\n", ins, read2Bytes(emu));
}

static void d8(Emulator* emu, char* ins) {
    printf("%s (0x%02x)\n", ins, read(emu, emu->PC.entireByte + 1));
}

static void a16(Emulator* emu, char* ins) {
    printf("%s (0x%04x)\n", ins, read2Bytes(emu));
}

static void r8(Emulator* emu, char* ins) {
    printf("%s (%d)\n", ins, (int8_t)read(emu, emu->PC.entireByte + 1));
}

void printCBInstruction(Emulator* emu, uint8_t byte) {
#ifdef DEBUG_PRINT_ADDRESS
    printf("[0x%04x]", emu->PC.entireByte.entireByte - 1);
#endif
#ifdef DEBUG_PRINT_FLAGS
    printFlags(emu);
#endif
#ifdef DEBUG_PRINT_CYCLES
    printf("[%ld]", emu->clock);
#endif
#ifdef DEBUG_PRINT_JOYPAD_REG
    printf("[sel:%x|", (emu->IO[R_P1_JOYP] >> 4) & 0x3);
    printf("sig:%x]", (emu->IO[R_P1_JOYP] & 0b00001111));
#endif
#ifdef DEBUG_PRINT_TIMERS
    printf("[%x|%x|%x|%x]", emu->IO[R_DIV], emu->IO[R_TIMA], emu->IO[R_TMA], emu->IO[R_TAC]);
#endif
    printf(" %5s", "");

    switch (byte) {
        case 0x00: return simpleInstruction(emu, "RLC B");
        case 0x01: return simpleInstruction(emu, "RLC C");
        case 0x02: return simpleInstruction(emu, "RLC D");
        case 0x03: return simpleInstruction(emu, "RLC E");
        case 0x04: return simpleInstruction(emu, "RLC H");
        case 0x05: return simpleInstruction(emu, "RLC L");
        case 0x06: return simpleInstruction(emu, "RLC (HL)");
        case 0x07: return simpleInstruction(emu, "RLC A");
        case 0x08: return simpleInstruction(emu, "RRC B");
        case 0x09: return simpleInstruction(emu, "RRC C");
        case 0x0A: return simpleInstruction(emu, "RRC D");
        case 0x0B: return simpleInstruction(emu, "RRC E");
        case 0x0C: return simpleInstruction(emu, "RRC H");
        case 0x0D: return simpleInstruction(emu, "RRC L");
        case 0x0E: return simpleInstruction(emu, "RRC (HL)");
        case 0x0F: return simpleInstruction(emu, "RRC A");
        case 0x10: return simpleInstruction(emu, "RL B");
        case 0x11: return simpleInstruction(emu, "RL C");
        case 0x12: return simpleInstruction(emu, "RL D");
        case 0x13: return simpleInstruction(emu, "RL E");
        case 0x14: return simpleInstruction(emu, "RL H");
        case 0x15: return simpleInstruction(emu, "RL L");
        case 0x16: return simpleInstruction(emu, "RL (HL)");
        case 0x17: return simpleInstruction(emu, "RL A");
        case 0x18: return simpleInstruction(emu, "RR B");
        case 0x19: return simpleInstruction(emu, "RR C");
        case 0x1A: return simpleInstruction(emu, "RR D");
        case 0x1B: return simpleInstruction(emu, "RR E");
        case 0x1C: return simpleInstruction(emu, "RR H");
        case 0x1D: return simpleInstruction(emu, "RR L");
        case 0x1E: return simpleInstruction(emu, "RR (HL)");
        case 0x1F: return simpleInstruction(emu, "RR A");
        case 0x20: return simpleInstruction(emu, "SLA B");
        case 0x21: return simpleInstruction(emu, "SLA C");
        case 0x22: return simpleInstruction(emu, "SLA D");
        case 0x23: return simpleInstruction(emu, "SLA E");
        case 0x24: return simpleInstruction(emu, "SLA H");
        case 0x25: return simpleInstruction(emu, "SLA L");
        case 0x26: return simpleInstruction(emu, "SLA (HL)");
        case 0x27: return simpleInstruction(emu, "SLA A");
        case 0x28: return simpleInstruction(emu, "SRA B");
        case 0x29: return simpleInstruction(emu, "SRA C");
        case 0x2A: return simpleInstruction(emu, "SRA D");
        case 0x2B: return simpleInstruction(emu, "SRA E");
        case 0x2C: return simpleInstruction(emu, "SRA H");
        case 0x2D: return simpleInstruction(emu, "SRA L");
        case 0x2E: return simpleInstruction(emu, "SRA (HL)");
        case 0x2F: return simpleInstruction(emu, "SRA A");
        case 0x30: return simpleInstruction(emu, "SWAP B");
        case 0x31: return simpleInstruction(emu, "SWAP C");
        case 0x32: return simpleInstruction(emu, "SWAP D");
        case 0x33: return simpleInstruction(emu, "SWAP E");
        case 0x34: return simpleInstruction(emu, "SWAP H");
        case 0x35: return simpleInstruction(emu, "SWAP L");
        case 0x36: return simpleInstruction(emu, "SWAP (HL)");
        case 0x37: return simpleInstruction(emu, "SWAP A");
        case 0x38: return simpleInstruction(emu, "SRL B");
        case 0x39: return simpleInstruction(emu, "SRL C");
        case 0x3A: return simpleInstruction(emu, "SRL D");
        case 0x3B: return simpleInstruction(emu, "SRL E");
        case 0x3C: return simpleInstruction(emu, "SRL H");
        case 0x3D: return simpleInstruction(emu, "SRL L");
        case 0x3E: return simpleInstruction(emu, "SRL (HL)");
        case 0x3F: return simpleInstruction(emu, "SRL A");
        case 0x40: return simpleInstruction(emu, "BIT 0, B");
        case 0x41: return simpleInstruction(emu, "BIT 0, C");
        case 0x42: return simpleInstruction(emu, "BIT 0, D");
        case 0x43: return simpleInstruction(emu, "BIT 0, E");
        case 0x44: return simpleInstruction(emu, "BIT 0, H");
        case 0x45: return simpleInstruction(emu, "BIT 0, L");
        case 0x46: return simpleInstruction(emu, "BIT 0, (HL)");
        case 0x47: return simpleInstruction(emu, "BIT 0, A");
        case 0x48: return simpleInstruction(emu, "BIT 1, B");
        case 0x49: return simpleInstruction(emu, "BIT 1, C");
        case 0x4A: return simpleInstruction(emu, "BIT 1, D");
        case 0x4B: return simpleInstruction(emu, "BIT 1, E");
        case 0x4C: return simpleInstruction(emu, "BIT 1, H");
        case 0x4D: return simpleInstruction(emu, "BIT 1, L");
        case 0x4E: return simpleInstruction(emu, "BIT 1, (HL)");
        case 0x4F: return simpleInstruction(emu, "BIT 1, A");
        case 0x50: return simpleInstruction(emu, "BIT 2, B");
        case 0x51: return simpleInstruction(emu, "BIT 2, C");
        case 0x52: return simpleInstruction(emu, "BIT 2, D");
        case 0x53: return simpleInstruction(emu, "BIT 2, E");
        case 0x54: return simpleInstruction(emu, "BIT 2, H");
        case 0x55: return simpleInstruction(emu, "BIT 2, L");
        case 0x56: return simpleInstruction(emu, "BIT 2, (HL)");
        case 0x57: return simpleInstruction(emu, "BIT 2, A");
        case 0x58: return simpleInstruction(emu, "BIT 3, B");
        case 0x59: return simpleInstruction(emu, "BIT 3, C");
        case 0x5A: return simpleInstruction(emu, "BIT 3, D");
        case 0x5B: return simpleInstruction(emu, "BIT 3, E");
        case 0x5C: return simpleInstruction(emu, "BIT 3, H");
        case 0x5D: return simpleInstruction(emu, "BIT 3, L");
        case 0x5E: return simpleInstruction(emu, "BIT 3, (HL)");
        case 0x5F: return simpleInstruction(emu, "BIT 3, A");
        case 0x60: return simpleInstruction(emu, "BIT 4, B");
        case 0x61: return simpleInstruction(emu, "BIT 4, C");
        case 0x62: return simpleInstruction(emu, "BIT 4, D");
        case 0x63: return simpleInstruction(emu, "BIT 4, E");
        case 0x64: return simpleInstruction(emu, "BIT 4, H");
        case 0x65: return simpleInstruction(emu, "BIT 4, L");
        case 0x66: return simpleInstruction(emu, "BIT 4, (HL)");
        case 0x67: return simpleInstruction(emu, "BIT 4, A");
        case 0x68: return simpleInstruction(emu, "BIT 5, B");
        case 0x69: return simpleInstruction(emu, "BIT 5, C");
        case 0x6A: return simpleInstruction(emu, "BIT 5, D");
        case 0x6B: return simpleInstruction(emu, "BIT 5, E");
        case 0x6C: return simpleInstruction(emu, "BIT 5, H");
        case 0x6D: return simpleInstruction(emu, "BIT 5, L");
        case 0x6E: return simpleInstruction(emu, "BIT 5, (HL)");
        case 0x6F: return simpleInstruction(emu, "BIT 5, A");
        case 0x70: return simpleInstruction(emu, "BIT 6, B");
        case 0x71: return simpleInstruction(emu, "BIT 6, C");
        case 0x72: return simpleInstruction(emu, "BIT 6, D");
        case 0x73: return simpleInstruction(emu, "BIT 6, E");
        case 0x74: return simpleInstruction(emu, "BIT 6, H");
        case 0x75: return simpleInstruction(emu, "BIT 6, L");
        case 0x76: return simpleInstruction(emu, "BIT 6, (HL)");
        case 0x77: return simpleInstruction(emu, "BIT 6, A");
        case 0x78: return simpleInstruction(emu, "BIT 7, B");
        case 0x79: return simpleInstruction(emu, "BIT 7, C");
        case 0x7A: return simpleInstruction(emu, "BIT 7, D");
        case 0x7B: return simpleInstruction(emu, "BIT 7, E");
        case 0x7C: return simpleInstruction(emu, "BIT 7, H");
        case 0x7D: return simpleInstruction(emu, "BIT 7, L");
        case 0x7E: return simpleInstruction(emu, "BIT 7, (HL)");
        case 0x7F: return simpleInstruction(emu, "BIT 7, A");
        case 0x80: return simpleInstruction(emu, "RES 0, B");
        case 0x81: return simpleInstruction(emu, "RES 0, C");
        case 0x82: return simpleInstruction(emu, "RES 0, D");
        case 0x83: return simpleInstruction(emu, "RES 0, E");
        case 0x84: return simpleInstruction(emu, "RES 0, H");
        case 0x85: return simpleInstruction(emu, "RES 0, L");
        case 0x86: return simpleInstruction(emu, "RES 0, (HL)");
        case 0x87: return simpleInstruction(emu, "RES 0, A");
        case 0x88: return simpleInstruction(emu, "RES 1, B");
        case 0x89: return simpleInstruction(emu, "RES 1, C");
        case 0x8A: return simpleInstruction(emu, "RES 1, D");
        case 0x8B: return simpleInstruction(emu, "RES 1, E");
        case 0x8C: return simpleInstruction(emu, "RES 1, H");
        case 0x8D: return simpleInstruction(emu, "RES 1, L");
        case 0x8E: return simpleInstruction(emu, "RES 1, (HL)");
        case 0x8F: return simpleInstruction(emu, "RES 1, A");
        case 0x90: return simpleInstruction(emu, "RES 2, B");
        case 0x91: return simpleInstruction(emu, "RES 2, C");
        case 0x92: return simpleInstruction(emu, "RES 2, D");
        case 0x93: return simpleInstruction(emu, "RES 2, E");
        case 0x94: return simpleInstruction(emu, "RES 2, H");
        case 0x95: return simpleInstruction(emu, "RES 2, L");
        case 0x96: return simpleInstruction(emu, "RES 2, (HL)");
        case 0x97: return simpleInstruction(emu, "RES 2, A");
        case 0x98: return simpleInstruction(emu, "RES 3, B");
        case 0x99: return simpleInstruction(emu, "RES 3, C");
        case 0x9A: return simpleInstruction(emu, "RES 3, D");
        case 0x9B: return simpleInstruction(emu, "RES 3, E");
        case 0x9C: return simpleInstruction(emu, "RES 3, H");
        case 0x9D: return simpleInstruction(emu, "RES 3, L");
        case 0x9E: return simpleInstruction(emu, "RES 3, (HL)");
        case 0x9F: return simpleInstruction(emu, "RES 3, A");
        case 0xA0: return simpleInstruction(emu, "RES 4, B");
        case 0xA1: return simpleInstruction(emu, "RES 4, C");
        case 0xA2: return simpleInstruction(emu, "RES 4, D");
        case 0xA3: return simpleInstruction(emu, "RES 4, E");
        case 0xA4: return simpleInstruction(emu, "RES 4, H");
        case 0xA5: return simpleInstruction(emu, "RES 4, L");
        case 0xA6: return simpleInstruction(emu, "RES 4, (HL)");
        case 0xA7: return simpleInstruction(emu, "RES 4, A");
        case 0xA8: return simpleInstruction(emu, "RES 5, B");
        case 0xA9: return simpleInstruction(emu, "RES 5, C");
        case 0xAA: return simpleInstruction(emu, "RES 5, D");
        case 0xAB: return simpleInstruction(emu, "RES 5, E");
        case 0xAC: return simpleInstruction(emu, "RES 5, H");
        case 0xAD: return simpleInstruction(emu, "RES 5, L");
        case 0xAE: return simpleInstruction(emu, "RES 5, (HL)");
        case 0xAF: return simpleInstruction(emu, "RES 5, A");
        case 0xB0: return simpleInstruction(emu, "RES 6, B");
        case 0xB1: return simpleInstruction(emu, "RES 6, C");
        case 0xB2: return simpleInstruction(emu, "RES 6, D");
        case 0xB3: return simpleInstruction(emu, "RES 6, E");
        case 0xB4: return simpleInstruction(emu, "RES 6, H");
        case 0xB5: return simpleInstruction(emu, "RES 6, L");
        case 0xB6: return simpleInstruction(emu, "RES 6, (HL)");
        case 0xB7: return simpleInstruction(emu, "RES 6, A");
        case 0xB8: return simpleInstruction(emu, "RES 7, B");
        case 0xB9: return simpleInstruction(emu, "RES 7, C");
        case 0xBA: return simpleInstruction(emu, "RES 7, D");
        case 0xBB: return simpleInstruction(emu, "RES 7, E");
        case 0xBC: return simpleInstruction(emu, "RES 7, H");
        case 0xBD: return simpleInstruction(emu, "RES 7, L");
        case 0xBE: return simpleInstruction(emu, "RES 7, (HL)");
        case 0xBF: return simpleInstruction(emu, "RES 7, A");
        case 0xC0: return simpleInstruction(emu, "SET 0, B");
        case 0xC1: return simpleInstruction(emu, "SET 0, C");
        case 0xC2: return simpleInstruction(emu, "SET 0, D");
        case 0xC3: return simpleInstruction(emu, "SET 0, E");
        case 0xC4: return simpleInstruction(emu, "SET 0, H");
        case 0xC5: return simpleInstruction(emu, "SET 0, L");
        case 0xC6: return simpleInstruction(emu, "SET 0, (HL)");
        case 0xC7: return simpleInstruction(emu, "SET 0, A");
        case 0xC8: return simpleInstruction(emu, "SET 1, B");
        case 0xC9: return simpleInstruction(emu, "SET 1, C");
        case 0xCA: return simpleInstruction(emu, "SET 1, D");
        case 0xCB: return simpleInstruction(emu, "SET 1, E");
        case 0xCC: return simpleInstruction(emu, "SET 1, H");
        case 0xCD: return simpleInstruction(emu, "SET 1, L");
        case 0xCE: return simpleInstruction(emu, "SET 1, (HL)");
        case 0xCF: return simpleInstruction(emu, "SET 1, A");
        case 0xD0: return simpleInstruction(emu, "SET 2, B");
        case 0xD1: return simpleInstruction(emu, "SET 2, C");
        case 0xD2: return simpleInstruction(emu, "SET 2, D");
        case 0xD3: return simpleInstruction(emu, "SET 2, E");
        case 0xD4: return simpleInstruction(emu, "SET 2, H");
        case 0xD5: return simpleInstruction(emu, "SET 2, L");
        case 0xD6: return simpleInstruction(emu, "SET 2, (HL)");
        case 0xD7: return simpleInstruction(emu, "SET 2, A");
        case 0xD8: return simpleInstruction(emu, "SET 3, B");
        case 0xD9: return simpleInstruction(emu, "SET 3, C");
        case 0xDA: return simpleInstruction(emu, "SET 3, D");
        case 0xDB: return simpleInstruction(emu, "SET 3, E");
        case 0xDC: return simpleInstruction(emu, "SET 3, H");
        case 0xDD: return simpleInstruction(emu, "SET 3, L");
        case 0xDE: return simpleInstruction(emu, "SET 3, (HL)");
        case 0xDF: return simpleInstruction(emu, "SET 3, A");
        case 0xE0: return simpleInstruction(emu, "SET 4, B");
        case 0xE1: return simpleInstruction(emu, "SET 4, C");
        case 0xE2: return simpleInstruction(emu, "SET 4, D");
        case 0xE3: return simpleInstruction(emu, "SET 4, E");
        case 0xE4: return simpleInstruction(emu, "SET 4, H");
        case 0xE5: return simpleInstruction(emu, "SET 4, L");
        case 0xE6: return simpleInstruction(emu, "SET 4, (HL)");
        case 0xE7: return simpleInstruction(emu, "SET 4, A");
        case 0xE8: return simpleInstruction(emu, "SET 5, B");
        case 0xE9: return simpleInstruction(emu, "SET 5, C");
        case 0xEA: return simpleInstruction(emu, "SET 5, D");
        case 0xEB: return simpleInstruction(emu, "SET 5, E");
        case 0xEC: return simpleInstruction(emu, "SET 5, H");
        case 0xED: return simpleInstruction(emu, "SET 5, L");
        case 0xEE: return simpleInstruction(emu, "SET 5, (HL)");
        case 0xEF: return simpleInstruction(emu, "SET 5, A");
        case 0xF0: return simpleInstruction(emu, "SET 6, B");
        case 0xF1: return simpleInstruction(emu, "SET 6, C");
        case 0xF2: return simpleInstruction(emu, "SET 6, D");
        case 0xF3: return simpleInstruction(emu, "SET 6, E");
        case 0xF4: return simpleInstruction(emu, "SET 6, H");
        case 0xF5: return simpleInstruction(emu, "SET 6, L");
        case 0xF6: return simpleInstruction(emu, "SET 6, (HL)");
        case 0xF7: return simpleInstruction(emu, "SET 6, A");
        case 0xF8: return simpleInstruction(emu, "SET 7, B");
        case 0xF9: return simpleInstruction(emu, "SET 7, C");
        case 0xFA: return simpleInstruction(emu, "SET 7, D");
        case 0xFB: return simpleInstruction(emu, "SET 7, E");
        case 0xFC: return simpleInstruction(emu, "SET 7, H");
        case 0xFD: return simpleInstruction(emu, "SET 7, L");
        case 0xFE: return simpleInstruction(emu, "SET 7, (HL)");
        case 0xFF: return simpleInstruction(emu, "SET 7, A");
    }
}

void printInstruction(Emulator* emu) {
    printf("[0x%04x]", emu->PC.entireByte, read(emu, emu->PC.entireByte));
    printFlags(emu);
#ifdef DEBUG_PRINT_CYCLES
    /* We print t-cycles */
    printf("[%ld]", emu->clock * 4);
#endif
#ifdef DEBUG_PRINT_JOYPAD_REG
    printf("[sel:%x|", (emu->IO[R_P1_JOYP] >> 4) & 0x3);
    printf("sig:%x]", (emu->IO[R_P1_JOYP] & 0b00001111));
#endif
#ifdef DEBUG_PRINT_TIMERS
    printf("[%x|%x|%x|%x]", emu->IO[R_DIV], emu->IO[R_TIMA], emu->IO[R_TMA], emu->IO[R_TAC]);
#endif
    printf(" %5s", "");

    switch (read(emu, emu->PC.entireByte)) {
        case 0x00: return simpleInstruction(emu, "NOP");
        case 0x01: return d16(emu, "LD BC, d16");
        case 0x02: return simpleInstruction(emu, "LD (BC), A");
        case 0x03: return simpleInstruction(emu, "INC BC");
        case 0x04: return simpleInstruction(emu, "INC B");
        case 0x05: return simpleInstruction(emu, "DEC B");
        case 0x06: return d8(emu, "LD B, d8");
        case 0x07: return simpleInstruction(emu, "RLCA");
        case 0x08: return a16(emu, "LD a16, SP");
        case 0x09: return simpleInstruction(emu, "ADD HL, BC");
        case 0x0A: return simpleInstruction(emu, "LD A, (BC)");
        case 0x0B: return simpleInstruction(emu, "DEC BC");
        case 0x0C: return simpleInstruction(emu, "INC C");
        case 0x0D: return simpleInstruction(emu, "DEC C");
        case 0x0E: return d8(emu, "LD C, d8");
        case 0x0F: return simpleInstruction(emu, "RRCA");
        case 0x10: return simpleInstruction(emu, "STOP");
        case 0x11: return d16(emu, "LD DE, d16");
        case 0x12: return simpleInstruction(emu, "LD (DE), A");
        case 0x13: return simpleInstruction(emu, "INC DE");
        case 0x14: return simpleInstruction(emu, "INC D");
        case 0x15: return simpleInstruction(emu, "DEC D");
        case 0x16: return d8(emu, "LD D, d8");
        case 0x17: return simpleInstruction(emu, "RLA");
        case 0x18: return r8(emu, "JR r8");
        case 0x19: return simpleInstruction(emu, "ADD HL, DE");
        case 0x1A: return simpleInstruction(emu, "LD A, (DE)");
        case 0x1B: return simpleInstruction(emu, "DEC DE");
        case 0x1C: return simpleInstruction(emu, "INC E");
        case 0x1D: return simpleInstruction(emu, "DEC E");
        case 0x1E: return d8(emu, "LD E, D8");
        case 0x1F: return simpleInstruction(emu, "RRA");
        case 0x20: return r8(emu, "JR NZ, r8");
        case 0x21: return d16(emu, "LD HL, d16");
        case 0x22: return simpleInstruction(emu, "LD (HL+), A");
        case 0x23: return simpleInstruction(emu, "INC HL");
        case 0x24: return simpleInstruction(emu, "INC H");
        case 0x25: return simpleInstruction(emu, "DEC H");
        case 0x26: return d8(emu, "LD H, d8");
        case 0x27: return simpleInstruction(emu, "DAA");
        case 0x28: return r8(emu, "JR Z, r8");
        case 0x29: return simpleInstruction(emu, "ADD HL, HL");
        case 0x2A: return simpleInstruction(emu, "LD A, (HL+)");
        case 0x2B: return simpleInstruction(emu, "DEC HL");
        case 0x2C: return simpleInstruction(emu, "INC L");
        case 0x2D: return simpleInstruction(emu, "DEC L");
        case 0x2E: return d8(emu, "LD L, d8");
        case 0x2F: return simpleInstruction(emu, "CPL");
        case 0x30: return r8(emu, "JR NC, r8");
        case 0x31: return d16(emu, "LD SP,d16");
        case 0x32: return simpleInstruction(emu, "LD (HL-), A");
        case 0x33: return simpleInstruction(emu, "INC SP");
        case 0x34: return simpleInstruction(emu, "INC (HL)");
        case 0x35: return simpleInstruction(emu, "DEC (HL)");
        case 0x36: return d8(emu, "LD (HL), d8");
        case 0x37: return simpleInstruction(emu, "SCF");
        case 0x38: return r8(emu, "JR C, r8");
        case 0x39: return simpleInstruction(emu, "ADD HL, SP");
        case 0x3A: return simpleInstruction(emu, "LD A, (HL-)");
        case 0x3B: return simpleInstruction(emu, "DEC SP");
        case 0x3C: return simpleInstruction(emu, "INC A");
        case 0x3D: return simpleInstruction(emu, "DEC A");
        case 0x3E: return d8(emu, "LD A, d8");
        case 0x3F: return simpleInstruction(emu, "CCF");
        case 0x40: return simpleInstruction(emu, "LD B, B");
        case 0x41: return simpleInstruction(emu, "LD B, C");
        case 0x42: return simpleInstruction(emu, "LD B, D");
        case 0x43: return simpleInstruction(emu, "LD B, E");
        case 0x44: return simpleInstruction(emu, "LD B, H");
        case 0x45: return simpleInstruction(emu, "LD B, L");
        case 0x46: return simpleInstruction(emu, "LD B, (HL)");
        case 0x47: return simpleInstruction(emu, "LD B, A");
        case 0x48: return simpleInstruction(emu, "LD C, B");
        case 0x49: return simpleInstruction(emu, "LD C, C");
        case 0x4A: return simpleInstruction(emu, "LD C, D");
        case 0x4B: return simpleInstruction(emu, "LD C, E");
        case 0x4C: return simpleInstruction(emu, "LD C, H");
        case 0x4D: return simpleInstruction(emu, "LD C, L");
        case 0x4E: return simpleInstruction(emu, "LD C, (HL)");
        case 0x4F: return simpleInstruction(emu, "LD C, A");
        case 0x50: return simpleInstruction(emu, "LD D, B");
        case 0x51: return simpleInstruction(emu, "LD D, C");
        case 0x52: return simpleInstruction(emu, "LD D, D");
        case 0x53: return simpleInstruction(emu, "LD D, E");
        case 0x54: return simpleInstruction(emu, "LD D, H");
        case 0x55: return simpleInstruction(emu, "LD D, L");
        case 0x56: return simpleInstruction(emu, "LD D, (HL)");
        case 0x57: return simpleInstruction(emu, "LD D, A");
        case 0x58: return simpleInstruction(emu, "LD E, B");
        case 0x59: return simpleInstruction(emu, "LD E, C");
        case 0x5A: return simpleInstruction(emu, "LD E, D");
        case 0x5B: return simpleInstruction(emu, "LD E, E");
        case 0x5C: return simpleInstruction(emu, "LD E, H");
        case 0x5D: return simpleInstruction(emu, "LD E, L");
        case 0x5E: return simpleInstruction(emu, "LD E, (HL)");
        case 0x5F: return simpleInstruction(emu, "LD E, A");
        case 0x60: return simpleInstruction(emu, "LD H, B");
        case 0x61: return simpleInstruction(emu, "LD H, C");
        case 0x62: return simpleInstruction(emu, "LD H, D");
        case 0x63: return simpleInstruction(emu, "LD H, E");
        case 0x64: return simpleInstruction(emu, "LD H, H");
        case 0x65: return simpleInstruction(emu, "LD H, L");
        case 0x66: return simpleInstruction(emu, "LD H, (HL)");
        case 0x67: return simpleInstruction(emu, "LD H, A");
        case 0x68: return simpleInstruction(emu, "LD L, B");
        case 0x69: return simpleInstruction(emu, "LD L, C");
        case 0x6A: return simpleInstruction(emu, "LD L, D");
        case 0x6B: return simpleInstruction(emu, "LD L, E");
        case 0x6C: return simpleInstruction(emu, "LD L, H");
        case 0x6D: return simpleInstruction(emu, "LD L, L");
        case 0x6E: return simpleInstruction(emu, "LD L, (HL)");
        case 0x6F: return simpleInstruction(emu, "LD L, A");
        case 0x70: return simpleInstruction(emu, "LD (HL), B");
        case 0x71: return simpleInstruction(emu, "LD (HL), C");
        case 0x72: return simpleInstruction(emu, "LD (HL), D");
        case 0x73: return simpleInstruction(emu, "LD (HL), E");
        case 0x74: return simpleInstruction(emu, "LD (HL), H");
        case 0x75: return simpleInstruction(emu, "LD (HL), L");
        case 0x76: return simpleInstruction(emu, "HALT");
        case 0x77: return simpleInstruction(emu, "LD (HL), A");
        case 0x78: return simpleInstruction(emu, "LD A, B");
        case 0x79: return simpleInstruction(emu, "LD A, C");
        case 0x7A: return simpleInstruction(emu, "LD A, D");
        case 0x7B: return simpleInstruction(emu, "LD A, E");
        case 0x7C: return simpleInstruction(emu, "LD A, H");
        case 0x7D: return simpleInstruction(emu, "LD A, L");
        case 0x7E: return simpleInstruction(emu, "LD A, (HL)");
        case 0x7F: return simpleInstruction(emu, "LD A, A");
        case 0x80: return simpleInstruction(emu, "ADD A, B");
        case 0x81: return simpleInstruction(emu, "ADD A, C");
        case 0x82: return simpleInstruction(emu, "ADD A, D");
        case 0x83: return simpleInstruction(emu, "ADD A, E");
        case 0x84: return simpleInstruction(emu, "ADD A, H");
        case 0x85: return simpleInstruction(emu, "ADD A, L");
        case 0x86: return simpleInstruction(emu, "ADD A, (HL)");
        case 0x87: return simpleInstruction(emu, "ADD A, A");
        case 0x88: return simpleInstruction(emu, "ADC A, B");
        case 0x89: return simpleInstruction(emu, "ADC A, C");
        case 0x8A: return simpleInstruction(emu, "ADC A, D");
        case 0x8B: return simpleInstruction(emu, "ADC A, E");
        case 0x8C: return simpleInstruction(emu, "ADC A, H");
        case 0x8D: return simpleInstruction(emu, "ADC A, L");
        case 0x8E: return simpleInstruction(emu, "ADC A, (HL)");
        case 0x8F: return simpleInstruction(emu, "ADC A, A");
        case 0x90: return simpleInstruction(emu, "SUB B");
        case 0x91: return simpleInstruction(emu, "SUB C");
        case 0x92: return simpleInstruction(emu, "SUB D");
        case 0x93: return simpleInstruction(emu, "SUB E");
        case 0x94: return simpleInstruction(emu, "SUB H");
        case 0x95: return simpleInstruction(emu, "SUB L");
        case 0x96: return simpleInstruction(emu, "SUB (HL)");
        case 0x97: return simpleInstruction(emu, "SUB A");
        case 0x98: return simpleInstruction(emu, "SBC A, B");
        case 0x99: return simpleInstruction(emu, "SBC A, C");
        case 0x9A: return simpleInstruction(emu, "SBC A, D");
        case 0x9B: return simpleInstruction(emu, "SBC A, E");
        case 0x9C: return simpleInstruction(emu, "SBC A, H");
        case 0x9D: return simpleInstruction(emu, "SBC A, L");
        case 0x9E: return simpleInstruction(emu, "SBC A, (HL)");
        case 0x9F: return simpleInstruction(emu, "SBC A, A");
        case 0xA0: return simpleInstruction(emu, "AND B");
        case 0xA1: return simpleInstruction(emu, "AND C");
        case 0xA2: return simpleInstruction(emu, "AND D");
        case 0xA3: return simpleInstruction(emu, "AND E");
        case 0xA4: return simpleInstruction(emu, "AND H");
        case 0xA5: return simpleInstruction(emu, "AND L");
        case 0xA6: return simpleInstruction(emu, "AND (HL)");
        case 0xA7: return simpleInstruction(emu, "AND A");
        case 0xA8: return simpleInstruction(emu, "XOR B");
        case 0xA9: return simpleInstruction(emu, "XOR C");
        case 0xAA: return simpleInstruction(emu, "XOR D");
        case 0xAB: return simpleInstruction(emu, "XOR E");
        case 0xAC: return simpleInstruction(emu, "XOR H");
        case 0xAD: return simpleInstruction(emu, "XOR L");
        case 0xAE: return simpleInstruction(emu, "XOR (HL)");
        case 0xAF: return simpleInstruction(emu, "XOR A");
        case 0xB0: return simpleInstruction(emu, "OR B");
        case 0xB1: return simpleInstruction(emu, "OR C");
        case 0xB2: return simpleInstruction(emu, "OR D");
        case 0xB3: return simpleInstruction(emu, "OR E");
        case 0xB4: return simpleInstruction(emu, "OR H");
        case 0xB5: return simpleInstruction(emu, "OR L");
        case 0xB6: return simpleInstruction(emu, "OR (HL)");
        case 0xB7: return simpleInstruction(emu, "OR A");
        case 0xB8: return simpleInstruction(emu, "CP B");
        case 0xB9: return simpleInstruction(emu, "CP C");
        case 0xBA: return simpleInstruction(emu, "CP D");
        case 0xBB: return simpleInstruction(emu, "CP E");
        case 0xBC: return simpleInstruction(emu, "CP H");
        case 0xBD: return simpleInstruction(emu, "CP L");
        case 0xBE: return simpleInstruction(emu, "CP (HL)");
        case 0xBF: return simpleInstruction(emu, "CP A");
        case 0xC0: return simpleInstruction(emu, "RET NZ");
        case 0xC1: return simpleInstruction(emu, "POP BC");
        case 0xC2: return a16(emu, "JP NZ, a16");
        case 0xC3: return a16(emu, "JP a16");
        case 0xC4: return a16(emu, "CALL NZ, a16");
        case 0xC5: return simpleInstruction(emu, "PUSH BC");
        case 0xC6: return d8(emu, "ADD A, d8");
        case 0xC7: return simpleInstruction(emu, "RST 0x00");
        case 0xC8: return simpleInstruction(emu, "RET Z");
        case 0xC9: return simpleInstruction(emu, "RET");
        case 0xCA: return a16(emu, "JP Z, a16");
        case 0xCB: return simpleInstruction(emu, "PREFIX CB");
        case 0xCC: return a16(emu, "CALL Z, a16");
        case 0xCD: return a16(emu, "CALL a16");
        case 0xCE: return d8(emu, "ADC A, d8");
        case 0xCF: return simpleInstruction(emu, "RST 0x08");
        case 0xD0: return simpleInstruction(emu, "RET NC");
        case 0xD1: return simpleInstruction(emu, "POP DE");
        case 0xD2: return a16(emu, "JP NC, a16");
        case 0xD4: return a16(emu, "CALL NC, a16");
        case 0xD5: return simpleInstruction(emu, "PUSH DE");
        case 0xD6: return d8(emu, "SUB d8");
        case 0xD7: return simpleInstruction(emu, "RST 0x10");
        case 0xD8: return simpleInstruction(emu, "REC C");
        case 0xD9: return simpleInstruction(emu, "RETI");
        case 0xDA: return a16(emu, "JP C, a16");
        case 0xDC: return a16(emu, "CALL C, a16");
        case 0xDE: return d8(emu, "SBC A, d8");
        case 0xDF: return simpleInstruction(emu, "RST 0x18");
        case 0xE0: return d8(emu, "LD (0xFF00 + d8), A");
        case 0xE1: return simpleInstruction(emu, "POP HL");
        case 0xE2: return simpleInstruction(emu, "LD (0xFF00 + C), A");
        case 0xE5: return simpleInstruction(emu, "PUSH HL");
        case 0xE6: return d8(emu, "AND d8");
        case 0xE7: return simpleInstruction(emu, "RST 0x20");
        case 0xE8: return r8(emu, "ADD SP, r8");
        case 0xE9: return simpleInstruction(emu, "JP (HL)");
        case 0xEA: return a16(emu, "LD (a16), A");
        case 0xEE: return d8(emu, "XOR d8");
        case 0xEF: return simpleInstruction(emu, "RST 0x28");
        case 0xF0: return d8(emu, "LD A, (0xFF00 + d8)");
        case 0xF1: return simpleInstruction(emu, "POP AF");
        case 0xF2: return simpleInstruction(emu, "LD A, (0xFF00 + C)");
        case 0xF3: return simpleInstruction(emu, "DI");
        case 0xF5: return simpleInstruction(emu, "PUSH AF");
        case 0xF6: return d8(emu, "OR d8");
        case 0xF7: return simpleInstruction(emu, "RST 0x30");
        case 0xF8: return r8(emu, "LD HL, SP + r8");
        case 0xF9: return simpleInstruction(emu, "LD SP, HL");
        case 0xFA: return a16(emu, "LD A, (a16)");
        case 0xFB: return simpleInstruction(emu, "EI");
        case 0xFE: return d8(emu, "CP d8");
        case 0xFF: return simpleInstruction(emu, "RST 0x38");
        default: return simpleInstruction(emu, "????");
    }
}

void printRegisters(Emulator* emu) {
    printf("[A%02x|B%02x|C%02x|D%02x|E%02x|H%02x|L%02x|SP%04x]\n", A(emu), B(emu), C(emu), D(emu), E(emu), H(emu), L(emu), emu->SP.entireByte);
}