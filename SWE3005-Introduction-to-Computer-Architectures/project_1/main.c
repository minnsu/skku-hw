#include <stdio.h>
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

/* SB format -> SBIM12 | SBI105 | RS2 | RS1 | FUNCT3 | SBIM41 | SBIM11 | OPCODE */
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

int type_check(unsigned int instruction) {
    /* 1->R, 2->I, 3->S, 4->SB, 5->UJ, 6->U, 7->SHIFT, 0->unknown */
    if ((instruction & OPCODE) == OP_R)
        return 1;
    else if ((instruction & OPCODE) == OP_S)
        return 3;
    else if ((instruction & OPCODE) == OP_SB)
        return 4;
    else if ((instruction & OPCODE) == OP_UJ_JAL)
        return 5;
    else if ((instruction & OPCODE) == OP_SH &&
             ((instruction & FUNCT3) == 0x5000 ||
              (instruction & FUNCT3) == 0x1000))
        return 7;
    else if ((instruction & OPCODE) == OP_U_LUI ||
             (instruction & OPCODE) == OP_U_AUIPC)
        return 6;
    else if ((instruction & OPCODE) == OP_I_JALR ||
             (instruction & OPCODE) == OP_I_L ||
             (instruction & OPCODE) == OP_I)
        return 2;
    else
        return 0;
}

int get_rs1(unsigned int instruction) { return (instruction & RS1) >> 15; }
int get_rs2(unsigned int instruction) { return (instruction & RS2) >> 20; }
int get_rd(unsigned int instruction) { return (instruction & RD) >> 7; }

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

void format_R(unsigned int instruction) {
    char oper[5];
    switch ((instruction & FUNCT3) >> 12) {
    case 0: /* add sub */
        if (instruction & FUNCT7)
            strcpy(oper, "sub");
        else
            strcpy(oper, "add");
        break;
    case 1: /* sll */
        strcpy(oper, "sll");
        break;
    case 2: /* slt */
        strcpy(oper, "slt");
        break;
    case 3: /* sltu */
        strcpy(oper, "sltu");
        break;
    case 4: /* xor */
        strcpy(oper, "xor");
        break;
    case 5: /* srl sra */
        if (instruction & FUNCT7)
            strcpy(oper, "sra");
        else
            strcpy(oper, "srl");
        break;
    case 6: /* or */
        strcpy(oper, "or");
        break;
    case 7: /* and */
        strcpy(oper, "and");
        break;
    }
    printf("%s %s x%d, x%d, x%d\n", HexAlign(instruction),
           oper, get_rd(instruction), get_rs1(instruction),
           get_rs2(instruction));
}

void format_I(unsigned int instruction) {
    int immediate = 0;
    immediate = (instruction & IIMMED) >> 20;
    if (instruction & SIGN)
        immediate = immediate | 0xFFFFF800;

    char oper[6];
    if ((instruction & OPCODE) == OP_I_JALR)
        strcpy(oper, "jalr");
    else if ((instruction & OPCODE) == OP_I_L) {
        switch ((instruction & FUNCT3) >> 12) {
        case 0:
            strcpy(oper, "lb");
            break;
        case 1:
            strcpy(oper, "lh");
            break;
        case 2:
            strcpy(oper, "lw");
            break;
        case 4:
            strcpy(oper, "lbu");
            break;
        case 5:
            strcpy(oper, "lhu");
            break;
        default:
            break;
        }
    } else {
        switch ((instruction & FUNCT3) >> 12) {
        case 0:
            strcpy(oper, "addi");
            break;
        case 2:
            strcpy(oper, "slti");
            break;
        case 3:
            strcpy(oper, "sltiu");
            break;
        case 4:
            strcpy(oper, "xori");
            break;
        case 6:
            strcpy(oper, "ori");
            break;
        case 7:
            strcpy(oper, "andi");
            break;
        default:
            break;
        }
        printf("%s %s x%d, x%d, %d\n", HexAlign(instruction),
               oper, get_rd(instruction), get_rs1(instruction), immediate);
        return;
    }
    printf("%s %s x%d, %d(x%d)\n", HexAlign(instruction),
           oper, get_rd(instruction), immediate, get_rs1(instruction));
}

void format_S(unsigned int instruction) {
    int offset = 0;
    offset = (instruction & SIM40) >> 7;
    offset = offset | ((instruction & SIM115) >> 20);
    if (instruction & SIGN)
        offset = offset | 0xFFFFFC00;
    printf("%s %s x%d, %d(x%d)\n", HexAlign(instruction),
           instruction & FUNCT3 ? ((instruction & FUNCT3) == 0x1000 ? "sh" : "sw") : "sb",
           get_rs2(instruction), offset, get_rs1(instruction));
}

void format_SB(unsigned int instruction) {
    int immediate = 0;
    immediate = (instruction & SBIM41) >> 7;                /* [4:0] */
    immediate = immediate | ((instruction & SBI105) >> 20); /* [10:0] */
    immediate = immediate | ((instruction & SBIM11) << 3);  /* [11:0] */
    immediate = immediate | ((instruction & SBIM12) >> 19); /* [12:0] */
    if (instruction & SIGN)
        immediate = immediate | 0xFFFFF800;

    char oper[5];
    switch ((instruction & FUNCT3) >> 12) {
    case 0:
        strcpy(oper, "beq");
        break;
    case 1:
        strcpy(oper, "bne");
        break;
    case 4:
        strcpy(oper, "blt");
        break;
    case 5:
        strcpy(oper, "bge");
        break;
    case 6:
        strcpy(oper, "bltu");
        break;
    case 7:
        strcpy(oper, "bgeu");
        break;
    }
    printf("%s %s x%d, x%d, %d\n", HexAlign(instruction),
           oper, get_rs1(instruction), get_rs2(instruction), immediate);
}

void format_UJ(unsigned int instruction) {
    int immediate = 0;
    immediate = (instruction & UJI101) >> 20;               /* [10:0] */
    immediate = immediate | ((instruction & UJIM11) >> 9);  /* [11:0] */
    immediate = immediate | (instruction & UJ1912);         /* [19:0] */
    immediate = immediate | ((instruction & UJIM20) >> 11); /* [20:0] */
    if (instruction & SIGN)
        immediate = immediate | 0xFFF80000;

    printf("%s jal x%d, %d\n", HexAlign(instruction), get_rd(instruction), immediate);
}

void format_U(unsigned int instruction) {
    int immediate = 0;
    immediate = instruction & UIMMED;
    printf("%s %s x%d, %d\n", HexAlign(instruction),
           (instruction & OPCODE) == 0x17 ? "auipc" : "lui",
           get_rd(instruction), immediate);
}

void format_SH(unsigned int instruction) {
    printf("%s %s x%d, x%d, %d\n", HexAlign(instruction),
           (instruction & FUNCT7) == 0
               ? ((instruction & FUNCT3) == 0x5000 ? "srli" : "slli")
               : "srai",
           get_rd(instruction), get_rs1(instruction), get_rs2(instruction));
}

void translate(unsigned int instruction) {
    int type = type_check(instruction);
    switch (type) {
    case 1:
        format_R(instruction);
        break;
    case 2:
        format_I(instruction);
        break;
    case 3:
        format_S(instruction);
        break;
    case 4:
        format_SB(instruction);
        break;
    case 5:
        format_UJ(instruction);
        break;
    case 6:
        format_U(instruction);
        break;
    case 7:
        format_SH(instruction);
        break;
    default:
        printf("%s unknown instruction\n", HexAlign(instruction));
    }
}

void disassemble(char *file_name) {
    FILE *fd = fopen(file_name, "rb");

    unsigned int instruction;
    int i = 0;
    while (fread(&instruction, 4, 1, fd)) {
        printf("inst %d: ", i++);
        translate(instruction);
    }
    fclose(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Enter target binary file!");
        return 0;
    }
    char target_file[256];
    strcpy(target_file, argv[1]);

    disassemble(target_file);
    return 0;
}