#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SIGN */
#define SIGN 0x80000000 /* 1000 0000 0000 0000 0000 0000 0000 0000 */

/* R format */
#define OPCODE 0x7F       /* 0000 0000 0000 0000 0000 0000 0111 1111 */
#define RD 0xF80          /* 0000 0000 0000 0000 0000 1111 1000 0000 */
#define FUNCT3 0x7000     /* 0000 0000 0000 0000 0111 0000 0000 0000 */
#define RS1 0xF8000       /* 0000 0000 0000 1111 1000 0000 0000 0000 */
#define RS2 0x1F00000     /* 0000 0001 1111 0000 0000 0000 0000 0000 */
#define FUNCT7 0xFE000000 /* 1111 1110 0000 0000 0000 0000 0000 0000 */

#define OP_R 0x33

/* I format -> IIMED | RS1 | FUNCT3 | RD | OPCODE */
#define IIMMED 0xFFF00000 /* 1111 1111 1111 0000 0000 0000 0000 0000 */

#define OP_I_JALR 0x67
#define OP_I_L 0x3
#define OP_I 0x13

/* S format -> SIM115 | RS2 | RS1 | FUNCT3 | SIM40 | OPCODE */
#define SIM115 FUNCT7 /* 1111 1110 0000 0000 0000 0000 0000 0000 */
#define SIM40 RD      /* 0000 0000 0000 0000 0000 1111 1000 0000 */

#define OP_S 0x23

/* SB format -> SBIM12 | SBI105 | RS2 | RS1 | FUNCT3 | SBIM41 | SBIM11 | OPCODE
 */
#define SBIM12 SIGN       /* 1000 0000 0000 0000 0000 0000 0000 0000 */
#define SBI105 0x7E000000 /* 0111 1110 0000 0000 0000 0000 0000 0000 */
#define SBIM41 0xF00      /* 0000 0000 0000 0000 0000 1111 0000 0000 */
#define SBIM11 0x80       /* 0000 0000 0000 0000 0000 0000 1000 0000 */

#define OP_SB 0x63

/* UJ format -> UJIM20 | UJI101 | UJIM11 | UJ1912 | RD | OPCODE */
#define UJIM20 SIGN       /* 1000 0000 0000 0000 0000 0000 0000 0000 */
#define UJI101 0x7FE00000 /* 0111 1111 1110 0000 0000 0000 0000 0000 */
#define UJIM11 0x100000   /* 0000 0000 0001 0000 0000 0000 0000 0000 */
#define UJ1912 0xFF000    /* 1000 0000 0000 1111 1111 0000 0000 0000 */

#define OP_UJ_JAL 0x6F

/* U format -> UIMMED | RD | OPCODE */
#define UIMMED 0xFFFFF000 /* 1111 1111 1111 1111 1111 0000 0000 0000 */

#define OP_U_LUI 0x37
#define OP_U_AUIPC 0x17

/* SHIFT format -> 7bits | SHAMT | RS1 | FUNCT3 | RD | OPCODE */
#define SHAMT RS2 /* 0000 0001 1111 0000 0000 0000 0000 0000 */

#define OP_SH OP_I

unsigned int reg_file[32];
unsigned int *instruction = NULL;
char data_memory[0x10000]; /* 0x10000 byte = 0x4000 * 4 byte */
int pc = 0;
int running = 0;

char hex[8];
char *HexAlign(unsigned int instruction) {
    unsigned int key = 0xF;
    unsigned int tmp;
    for (int i = 7; i >= 0; i--) {
        tmp = (instruction & key) >> (7 - i) * 4;
        if (tmp >= 10)
            hex[i] = 'a' + tmp - 10;
        else
            hex[i] = '0' + tmp;
        key = key << 4;
    }
    return hex;
}

int loadword(unsigned int address){
    int ret = 0;
    unsigned int mask = 0xFF000000;
    ret |= ((unsigned int) data_memory[address + 3] << 24) & mask;
    mask >>= 8;
    ret |= ((unsigned int) data_memory[address + 2] << 16) & mask;
    mask >>= 8;
    ret |= ((unsigned int) data_memory[address + 1] << 8) & mask;
    mask >>= 8;
    ret |= ((unsigned int) data_memory[address]) & mask;
    return ret;
}
void storeword(unsigned int address, int value){
    unsigned int mask = 0xFF000000;
    data_memory[address + 3] = (value & mask) >> 24;
    mask >>= 8;
    data_memory[address + 2] = (value & mask) >> 16;
    mask >>= 8;
    data_memory[address + 1] = (value & mask) >> 8;
    mask >>= 8;
    data_memory[address] = value & mask;
}

int get_f7() { return (instruction[pc] & FUNCT7) >> 25; }
int get_rs2() { return (instruction[pc] & RS2) >> 20; }
int get_rs1() { return (instruction[pc] & RS1) >> 15; }
int get_f3() { return (instruction[pc] & FUNCT3) >> 12; }
int get_rd() { return (instruction[pc] & RD) >> 7; }
int get_opcode() { return (instruction[pc] & OPCODE); }

int type_check() {
    /* 1->R, 2->I, 3->S, 4->SB, 5->UJ, 6->U, 7->SHIFT, 0->unknown */
    int opcode = get_opcode();
    if (opcode == OP_R)
        return 1;
    else if (opcode == OP_S)
        return 3;
    else if (opcode == OP_SB)
        return 4;
    else if (opcode == OP_UJ_JAL)
        return 5;
    else if (opcode == OP_SH && ((instruction[pc] & FUNCT3) == 0x5000 ||
                                 (instruction[pc] & FUNCT3) == 0x1000))
        return 7;
    else if (opcode == OP_U_LUI || opcode == OP_U_AUIPC)
        return 6;
    else if (opcode == OP_I_JALR || opcode == OP_I_L || opcode == OP_I)
        return 2;
    else
        return 0;
}

int immediate_generator() {
    int ret = 0;
    switch (type_check()) {
    case 2: // I
        ret = (int)(instruction[pc] & (int)IIMMED) >> 20;
        break;
    case 3: // S
        ret = (instruction[pc] & SIM40) >> 7;
        ret = ret | (((int)instruction[pc] & (int)SIM115) >> 20);
        break;
    case 4: // B
        ret = (instruction[pc] & SBIM41) >> 7;
        ret = ret | ((instruction[pc] & SBI105) >> 20);
        ret = ret | ((instruction[pc] & SBIM11) << 4);
        ret = ret | (((int)instruction[pc] & (int)SBIM12) >> 19);
        break;
    case 5: // J
        ret = (instruction[pc] & UJI101) >> 20;
        ret = ret | ((instruction[pc] & UJIM11) >> 9);
        ret = ret | (instruction[pc] & UJ1912);
        ret = ret | (((int)instruction[pc] & (int)UJIM20) >> 11);
        break;
    case 6: // U
        ret = instruction[pc] & UIMMED;
        break;
    default:
        printf("No immeidate exist!\n");
    }
    return ret;
}

void R_format(unsigned int rd_idx, unsigned int rs1_idx, unsigned int rs2_idx) {
    if (get_opcode() == OP_SH) {
        switch (get_f3()) {
        case 1: // slli
            reg_file[rd_idx] = reg_file[rs1_idx] << rs2_idx;
            break;
        case 5: // srli / srai
            if (get_f7() == 0x20)
                reg_file[rd_idx] = (int)reg_file[rs1_idx] >> (int)rs2_idx;
            else
                reg_file[rd_idx] = reg_file[rs1_idx] >> rs2_idx;
            break;
        default:
            printf("Error in R_format\n");
        }
        goto end;
    }

    switch (get_f3()) {
    case 0:                     // add / sub
        if (get_f7() == 0x20) { // sub
            reg_file[rd_idx] = reg_file[rs1_idx] - reg_file[rs2_idx];
        } else { // add
            reg_file[rd_idx] = reg_file[rs1_idx] + reg_file[rs2_idx];
        }
        break;
    case 1: // sll
        reg_file[rd_idx] = reg_file[rs1_idx] << (reg_file[rs2_idx] & 0x1F);
        break;
    case 2: // slt
        reg_file[rd_idx] = (int)reg_file[rs1_idx] < (int)reg_file[rs2_idx];
        break;
    case 3: // sltu
        reg_file[rd_idx] = reg_file[rs1_idx] < reg_file[rs2_idx];
        break;
    case 4: // xor
        reg_file[rd_idx] = reg_file[rs1_idx] ^ reg_file[rs2_idx];
        break;
    case 5:                   // srl / sra
        if (get_f7() == 0x20) // sra
            reg_file[rd_idx] =
                (int)reg_file[rs1_idx] >> (reg_file[rs2_idx] & 0x1F);
        else
            reg_file[rd_idx] = reg_file[rs1_idx] >> (reg_file[rs2_idx] & 0x1F);

        break;
    case 6: // or
        reg_file[rd_idx] = reg_file[rs1_idx] | reg_file[rs2_idx];
        break;
    case 7: // and
        reg_file[rd_idx] = reg_file[rs1_idx] & reg_file[rs2_idx];
        break;
    }
    end:
    pc++;
}
void I_format(unsigned int rd_idx, unsigned int rs1_idx, int immediate) {
    int opcode = get_opcode();
    if (opcode == OP_I_JALR) { // jalr
        reg_file[rd_idx] = pc * 4 + 4;
        pc = (reg_file[rs1_idx] + immediate) / 4;
        return;
    } else if (opcode == OP_I) {
        switch (get_f3()) {
        case 0:
            reg_file[rd_idx] = reg_file[rs1_idx] + immediate;
            break;
        case 2:
            reg_file[rd_idx] = (int)reg_file[rs1_idx] < (int)immediate;
            break;
        case 3:
            reg_file[rd_idx] = reg_file[rs1_idx] < immediate;
            break;
        case 4:
            reg_file[rd_idx] = reg_file[rs1_idx] ^ immediate;
            break;
        case 6:
            reg_file[rd_idx] = reg_file[rs1_idx] | immediate;
            break;
        case 7:
            reg_file[rd_idx] = reg_file[rs1_idx] & immediate;
            break;
        }
    } else if (opcode == OP_I_L) { // load
        int address = reg_file[rs1_idx] + immediate;
        if(address == 0x20000000)
            scanf("%d", &reg_file[rd_idx]);
        else{
            reg_file[rd_idx] = loadword(address - 0x10000000);
            // reg_file[rd_idx] = data_memory[(address - 0x10000000) >> 2];
        }
    }
    pc++;
}
void U_format(unsigned int rd_idx, int immediate) {
    int opcode = get_opcode();
    if (opcode == OP_U_AUIPC) { // auipc
        reg_file[rd_idx] = pc * 4 + immediate;
    } else { // lui
        reg_file[rd_idx] = immediate;
    }
    pc++;
}
void J_format(unsigned int rd_idx, int immediate) {
    reg_file[rd_idx] = pc * 4 + 4;
    pc = pc + immediate / 4;
}
void B_format(unsigned int rs1_idx, unsigned int rs2_idx, int immediate) {
    switch (get_f3()) {
    case 0:
        if (reg_file[rs1_idx] == reg_file[rs2_idx])
            goto success;
        break;
    case 1:
        if (reg_file[rs1_idx] != reg_file[rs2_idx])
            goto success;
        break;
    case 4:
        if ((int)reg_file[rs1_idx] < (int)reg_file[rs2_idx])
            goto success;
        break;
    case 5:
        if ((int)reg_file[rs1_idx] >= (int)reg_file[rs2_idx])
            goto success;
        break;
    case 6:
        if (reg_file[rs1_idx] < reg_file[rs2_idx])
            goto success;
        break;
    case 7:
        if (reg_file[rs1_idx] >= reg_file[rs2_idx])
            goto success;
        break;
    default:
        printf("Error in B_format\n");
    }
    pc++;
    return;
success:
    pc = pc + immediate / 4;
}
void S_format(unsigned int rs1_idx, unsigned int rs2_idx, int immediate) {
    int address = reg_file[rs1_idx] + immediate;
    if(address == 0x20000000){
        printf("%c", (char) reg_file[rs2_idx]);
    }
    else{
        storeword(address - 0x10000000, reg_file[rs2_idx]);
        // data_memory[(address - 0x10000000) >> 2] = reg_file[rs2_idx];
    }
    pc++;
}

int file_to_memory(FILE *inst_fd, FILE *data_fd) {
    fseek(inst_fd, 0, SEEK_END);
    int file_size = ftell(inst_fd);
    fseek(inst_fd, 0, SEEK_SET);

    int i = 0;
    int inst_bound = file_size / sizeof(int);
    instruction = (unsigned int *)malloc(file_size);

    while (fread(&instruction[i++], 4, 1, inst_fd))
        ;
    

    if (data_fd) {
        fseek(data_fd, 0, SEEK_END);
        file_size = ftell(data_fd);
        fseek(data_fd, 0, SEEK_SET);
        i = 0;
        memset(data_memory, 0xFF, 0x10000); /* byte unit */
        while (fread(&data_memory[i++], 1, 1, data_fd))
            ;
    }
    return inst_bound;
}

void execute(int inst_bound) {
    unsigned int tmp_inst;
    unsigned rd_idx, rs1_idx, rs2_idx;

    while (running && pc < inst_bound) {
        rd_idx = get_rd();
        rs1_idx = get_rs1();
        rs2_idx = get_rs2();

        switch (type_check()) {
        case 7:
        case 1:
            R_format(rd_idx, rs1_idx, rs2_idx);
            break;
        case 2:
            I_format(rd_idx, rs1_idx, immediate_generator());
            break;
        case 3:
            S_format(rs1_idx, rs2_idx, immediate_generator());
            break;
        case 4:
            B_format(rs1_idx, rs2_idx, immediate_generator());
            break;
        case 5:
            J_format(rd_idx, immediate_generator());
            break;
        case 6:
            U_format(rd_idx, immediate_generator());
            break;
        default:
            printf("Error in execute\n");
        }
        reg_file[0] = 0;
        running--;
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Please input target file\n");
        return 1;
    }

    FILE *inst_fd = fopen(argv[1], "rb");
    int inst_bound;

    if (argc == 3) {
        running = atoi(argv[2]);
        inst_bound = file_to_memory(inst_fd, NULL);
    } else if (argc >= 4) {
        running = atoi(argv[3]);
        FILE *data_fd = fopen(argv[2], "rb");
        inst_bound = file_to_memory(inst_fd, data_fd);
        fclose(data_fd);
    }
    execute(inst_bound);
    fclose(inst_fd);

    for (int i = 0; i < 32; i++) {
        printf("x%d: 0x%s\n", i, HexAlign(reg_file[i]));
    }
    return 0;
}