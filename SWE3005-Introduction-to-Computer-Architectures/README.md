# 2023-Spring 성균관대학교 컴퓨터구조개론

### Project 1 - RISC-V Binary Code
- Goal: Disassemble RISC-V machine code to assembliy code.
- Implement the following command
    ```
    lui, auipc, jal, jalr, beq, bne, blt, bge, bltu, bgeu,
    lb, lh, lw, lbu, lhu,
    sb, sh, sw, addi, slti, sltiu,
    xori, ori, andi, slli, srli, srai,
    add, sub, sll, slt, sltu,
    xor, srl, sra, or, and
    ```
- Format of result
    ```
    inst 0: 00208033 add x0, x1, x2
    inst 1: 41450fb3 sub x31, x10, x20
    ...
    ```
- score: 100/100


### Project 2 - Single-cycle RISC-V CPU Simulator
- Implement the following command
    ```
    add, sub, addi
    xor, or, and, xori , ori , andi
    slli, srli , srai , sll , srl , sra
    slti, slt
    auipc, lui
    jal, jalr
    beq, bne , blt , bge
    lw, sw
    ```
- Program takes 2 or 3 command-line arguments.
    - if the program takes 2 arguments, first argument is input file name that has binary instructions. And second argument is number of instructions to execute.
    - if the program takes 3 arguments, first argument is same as above. Second argument is input file name of binary data(data memory), and third argument is number of instructions to execute.
- Registers
    - Every registers are initialized to 0 and x0 register is fixed to 0
    - At the last of program should print registers values.
- Memory
    - Address range from 0x10000000 to 0x1000FFFF is used to data memory(total 64KB).
    - Therefore, input binary data file is loaded onto 0x10000000~ and remaining bytes are initialized to 0xFF.
- score: 100/100

### Project 3 - Spike RISC-V Simulator
- Goal 1: Find best cache configuration
    - Using --dc=[sets]:[ways]:[block_size] options
    - Total data cache capacity is fixed to 16KB. Also, block size is fixed to 64 bytes.
    - Therefore, possible cache configuration is
        ```
        --dc=1:256:64
        --dc=2:128:64
        --dc=4:64:64
        --dc=8:32:64
        --dc=16:16:64
        --dc=32:8:64
        --dc=64:4:64
        --dc=128:2:64
        --dc=256:1:64
        ```
- Goal 2: Modify cache replacement algorithm to LRU
    - Find and modify the appropriate file that solves Goal 2.
    - As with Goal 1, find the best cache configurations.
- score: unknown
