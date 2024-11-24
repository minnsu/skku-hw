#include <stdio.h>
#include <stdlib.h>
typedef unsigned short sfp;

char* sfp2bits(sfp result);

sfp int2sfp(int input);
int sfp2int(sfp input);

sfp float2sfp(float input);
float sfp2float(sfp input);

sfp sfp_add(sfp a, sfp b);
sfp sfp_mul(sfp a, sfp b);

int main()
{
//     NaN input test statement
//     printf("RANDOM NAN ver2\n");
//     sfp tmp1 = 0x0000, tmp2 = 0x7FCF;
//     sfp add = sfp_add(tmp1, tmp2);
//     sfp mul = sfp_mul(tmp1, tmp2);
//     printf("0 + NaN = %s\n", sfp2bits(add));
//     printf("0 * NaN = %s\n", sfp2bits(mul));
//     add = sfp_add(tmp2, tmp1);
//     mul = sfp_mul(tmp2, tmp1);
//     printf("NaN + 0 = %s\n", sfp2bits(add));
//     printf("NaN * 0 = %s\n", sfp2bits(mul));
//     printf("*********************\n");

//     tmp1 = 0x0017, tmp2 = 0x7FF3;
//     add = sfp_add(tmp1, tmp2);
//     mul = sfp_mul(tmp1, tmp2);
//     printf("Normal + NaN = %s\n", sfp2bits(add));
//     printf("Normal * NaN = %s\n", sfp2bits(mul));
//     add = sfp_add(tmp2, tmp1);
//     mul = sfp_mul(tmp2, tmp1);
//     printf("NaN + Normal = %s\n", sfp2bits(add));
//     printf("NaN * Normal = %s\n", sfp2bits(mul));
//     printf("*********************\n");

//     tmp1 = 0x7C00, tmp2 = 0x7FD9;
//     add = sfp_add(tmp1, tmp2);
//     mul = sfp_mul(tmp1, tmp2);
//     printf("inf + NaN = %s\n", sfp2bits(add));
//     printf("inf * NaN = %s\n", sfp2bits(mul));
//     add = sfp_add(tmp2, tmp1);
//     mul = sfp_mul(tmp2, tmp1);
//     printf("NaN + inf = %s\n", sfp2bits(add));
//     printf("NaN * inf = %s\n", sfp2bits(mul));
//     printf("*********************\n");

//     tmp1 = 0xFC00, tmp2 = 0x7F11;
//     add = sfp_add(tmp1, tmp2);
//     mul = sfp_mul(tmp1, tmp2);
//     printf("-inf + NaN = %s\n", sfp2bits(add));
//     printf("-inf * NaN = %s\n", sfp2bits(mul));
//     add = sfp_add(tmp2, tmp1);
//     mul = sfp_mul(tmp2, tmp1);
//     printf("NaN + -inf = %s\n", sfp2bits(add));
//     printf("NaN * -inf = %s\n", sfp2bits(mul));
//     printf("*********************\n");

//     tmp1 = 0x7F79, tmp2 = 0x7FBF;
//     add = sfp_add(tmp1, tmp2);
//     mul = sfp_mul(tmp1, tmp2);
//     printf("NaN + NaN = %s\n", sfp2bits(add));
//     printf("NaN * NaN = %s\n", sfp2bits(mul));
//     add = sfp_add(tmp2, tmp1);
//     mul = sfp_mul(tmp2, tmp1);
//     printf("NaN + NaN = %s\n", sfp2bits(add));
//     printf("NaN * NaN = %s\n", sfp2bits(mul));
    while(1){
        printf("Enter operation: \n1. int in/output\n2. float in/output\n3. int add/mul\n4. float add/mul\n=> ");
        int mode;
        int a = 0, b = 0;
        float aa = 0, bb = 0;
        sfp tmp1 = 0, tmp2 = 0;
        sfp add = 0, mul = 0;
        scanf("%d", &mode);
        switch(mode){
            case 1:
                printf("Enter integer number: ");
                scanf("%d", &a);
                tmp1 = int2sfp(a);
                printf("bit pattern: %s\n", sfp2bits(tmp1));
                printf("sfp to int: %d\n", sfp2int(tmp1));
                break;
            case 2:
                printf("Enter float number: ");
                scanf("%f", &aa);
                tmp1 = float2sfp(aa);
                printf("bit pattern: %s\n", sfp2bits(tmp1));
                printf("sfp to float: %f\n", sfp2float(tmp1));
                break;
            case 3:
                printf("Enter two integer number: ");
                scanf("%d %d", &a, &b);
                tmp1 = int2sfp(a);
                tmp2 = int2sfp(b);
                printf("bit pattern of tmp1: %s\n", sfp2bits(tmp1));
                printf("bit pattern of tmp2: %s\n", sfp2bits(tmp2));
                add = sfp_add(tmp1, tmp2);
                mul = sfp_mul(tmp1, tmp2);
                printf("sfp to int: %d %d\n", sfp2int(tmp1), sfp2int(tmp2));
                printf("value of add: %d\n", sfp2int(add));
                printf("bit pattern of add: %s\n", sfp2bits(add));
                printf("value of mul: %d\n", sfp2int(mul));
                printf("bit pattern of mul: %s\n", sfp2bits(mul));
                break;
            case 4:
                printf("Enter two float number: ");
                scanf("%f %f", &aa, &bb);
                tmp1 = float2sfp(aa);
                tmp2 = float2sfp(bb);
                printf("bit pattern of tmp1: %s\n", sfp2bits(tmp1));
                printf("bit pattern of tmp2: %s\n", sfp2bits(tmp2));
                add = sfp_add(tmp1, tmp2);
                mul = sfp_mul(tmp1, tmp2);
                printf("sfp to float: %f %f\n", sfp2float(tmp1), sfp2float(tmp2));
                printf("value of add: %f\n", sfp2float(add));
                printf("bit pattern of add: %s\n", sfp2bits(add));
                printf("value of mul: %f\n", sfp2float(mul));
                printf("bit pattern of mul: %s\n", sfp2bits(mul));
                break;
        }
    }
}

sfp int2sfp(int input){ // 16 bit 중 10 bit pattern과 5 bit exp로 수를 표현
    if(input == 0x00000000){ // input: 0
        sfp zero = 0x0000; // +0.0
        return zero;
    }
    else if(input > 65535){ // input: inf(>=2^16)
        sfp posinf = 0x7C00; // 0111 1100 0000 0000
        return posinf;
    }
    else if(input < -65535){ // input: -inf(<-2^16)
        sfp neginf = 0xFC00; // 1111 1100 0000 0000
        return neginf;
    }

	sfp SIGN = 0x0000;
    sfp FRAC;
    sfp EXP;

    if(input < 0) {
        input = -input; SIGN = 0x8000;
    }
    int key = 0, twop = 1; // 크기를 재기 위한 변수들
    while(1) {
        if(twop <= input && twop*2 > input) break;
        key++;
        twop = twop*2;
    }

    // FRAC part
    if(key <= 10) { FRAC = input << (10-key); } // key 값에 따라 비트 움직여서 frac 위치에 맞추기
    else { FRAC = input >> (key-10); }
    FRAC = 0x03FF & FRAC; // 0000 0011 1111 1111 and frac : hiding implied leading 1 bit

    // EXP part
    EXP = key + 15; // EXP = E + Bias

    sfp ret = SIGN | (EXP << 10) | FRAC; // frac과 EXP or 연산하여 합하기
    return ret;
}

int sfp2int(sfp input){
    if(input == 0x0000){ // input: 0
        int zero = 0;
        return zero;
    }
    else if(input == 0x7C00){ // input: inf: 0111 1100 0000 0000
        int posinf = 0x7FFFFFFF; // 0111 1111 1111 1111 1111 1111 1111 1111 : Int's max
        return posinf;
    }
    else if(input == 0xFC00){ // input: -inf: 1111 1100 0000 0000
        int neginf = 0x80000000; // 1000 0000 0000 0000 0000 0000 0000 0000 : Int's min
        return neginf;
    }
    else if(((input & 0x7C00) == 0x7C00) && (input & 0x03FF)){ // input: NaN(Not a Number)
        int NaN = 0x80000000; // Int's min
        return NaN;
    }

    int SIGN = (0x00008000 & input) << 16;

    int ret = 0x03FF; // 0000 0011 1111 1111
    ret = (input & ret) | 0x0400; // (make FRAC part) | 0000 0100 0000 0000 (make implied leading 1 bit)

    sfp EXP = 0x7C00 & input; // 0111 1100 0000 0000 & input: make exp part
    EXP = EXP >> 10; // right shift for translate as int
    EXP = EXP - 15; // E = Exp - Bias

    if(EXP <= 10){ ret = ret >> (10-EXP); } // shift for real int position
    else{ ret = ret << (EXP-10);}

    if(SIGN) ret = -ret; // sign bit
    return ret;
}

sfp float2sfp(float input){
    if(input == 0x00000000){ // input: +0.0
        sfp poszero = 0x0000;
        return poszero;
    }
    else if(input == 0x80000000){ // input: -0.0
        sfp negzero = 0x8000;
        return negzero;
    }
    else if(input > 65535){ // input: inf(>=2^16)
        sfp posinf = 0x7C00; // 0111 1100 0000 0000
        return posinf;
    }
    else if(input < -65535){ // input: -inf(<-2^16)
        sfp neginf = 0xFC00; // 1111 1100 0000 0000
        return neginf;
    }

    sfp SIGN = 0x0000;
    if(input < 0){ SIGN = 0x8000;}

    // unsigned int tmp = *(unsigned int*)&input;
    union memory{
        unsigned asInt;
        float input;
    };
    union memory inputfloat;
    inputfloat.input = input;

    int EXP_int = 0x7F800000; // 0|111 1111 1|000 0000 0000 0000 0000 0000
    int FRAC_int = 0x007FFFFF; // 0|000 0000 0|111 1111 1111 1111 1111 1111, get frac part and hiding implied leading 1 bit

    EXP_int = (EXP_int & inputfloat.asInt) >> 23; // get exp part and shift to right end : translate as real int value
    sfp EXP_sfp = EXP_int - 127; // E = Exp - Bias, Bias in 32-bit: 2^(8-1) - 1 = 127
    EXP_sfp = (EXP_sfp + 15) << 10; // Exp in sfp = E + 15 : Bias in 16-bit: 2^(5-1) - 1 = 15
    // shift to left 10 : move sfp's exp position

    sfp FRAC_sfp = (FRAC_int & inputfloat.asInt) >> 13; // frac in sfp : only 10 bits => 23 - 13 = 10, float's right 13 bits are abandoned.

    sfp ret = SIGN | EXP_sfp | FRAC_sfp;
    return ret;
}

float sfp2float(sfp input){
    if(input == 0x0000){ // input: +0.0
        float poszero = 0x00000000;
        return poszero;
    }
    else if(input == 0x8000){// input: -0.0
        float negzero = 0x80000000;
        return negzero;
    }

    unsigned int SIGN = (0x00008000 & input) << 16; // get sign bit as int type
    unsigned int EXP_int = 0x00007C00; // 0000 0000 0000 0000 0111 1100 0000 0000
    unsigned int FRAC_int = 0x000003FF; // 0000 0000 0000 0000 0000 0011 1111 1111

    EXP_int = (EXP_int & input) >> 10; // get exp part and shift to right end : translate as real int value
    unsigned int E = EXP_int - 15; // E = Exp - Bias, Bias in 16-bit: 2^(5-1) -1 = 15
    unsigned int EXP_new = (E + 127) << 23; // Exp in float = E + 127 : Bias in 32-bit: 2^(8-1) - 1 = 127
    // shift to left 23 : move float(32-bit)'s exp position

    unsigned int FRAC_new = (FRAC_int & input) << 13;
    // frac in float : 23 bits => 10 + 13 = 23, sfp's right 13 bits are filled by 0.

    unsigned int tmp = SIGN | EXP_new | FRAC_new;

    union memory{
        unsigned int tmp;
        float asFloat;
    };
    union memory inputuint;
    inputuint.tmp = tmp;
    float ret = inputuint.asFloat;
    return ret;
}

sfp sfp_add(sfp a, sfp b){
    if( ( ((a & 0x7C00) == 0x7C00) && (a & 0x03FF) ) || ( ((b & 0x7C00) == 0x7C00) && (b & 0x03FF) ) ){ // input: NaN
        sfp NaN = 0x7FFF; // 0111 1111 1111 1111 : NaN example
        printf("input: NaN = NaN\n");
        return NaN;
    }
    else if(a == 0x7C00 || a == 0xFC00 || b == 0x7C00 || b == 0xFC00){ // input: inf or -inf
        sfp posinf = 0x7C00;
        sfp neginf = 0xFC00;
        sfp NaN = 0x7FFF; // 0111 1111 1111 1111 : NaN example
        if(a == 0x7C00){ // a: inf
            if(b == 0xFC00){ // b: -inf
                printf("inf + -inf = NaN\n");
                return NaN;
            }
            else{ // b: inf or Normal value
                printf("inf + (inf or Normal value) = inf\n");
                return posinf;
            }
        }
        else if(a == 0xFC00){ // a: -inf
            if(b == 0x7C00){ // b: inf
                printf("-inf + inf = NaN\n");
                return NaN;
            }
            else{ // b: -inf or Normal value
                printf("-inf + (-inf or Normal value) = -inf\n");
                return neginf;
            }
        }
        else{ // a == Normal value
            printf("Normal value + (+,-)inf = (+,-)inf\n");
            return b;
        }
    }

    sfp signA = 0x8000 & a;
    sfp signB = 0x8000 & b;
    sfp getfracA = (0x03FF & a) | 0x0400;
    sfp getfracB = (0x03FF & b) | 0x0400; // 0000 0011 1111 1111 & PARAMETER | 0000 0100 0000 0000
    if(((0x7C00 & a) >> 10) == 0x0000 && ((0x7C00 & b) >> 10) == 0x0000 && getfracA == 0x0400 && getfracB == 0x0400){
        sfp zero = 0x0000;
        return zero;
    }
    sfp SIGN;
    sfp EXP;
    sfp FRAC = 0x0000;
    short diff = ((0x7C00 & a) >> 10) - ((0x7C00 & b) >> 10); // signed short
    // exp of a - exp of b: which absolute value is big?: 
    // diff > 0: a's abosulute value is big, diff < 0: b's absolute value is big, diff == 0: should compare frac part

    if(diff > 0){
        for(int i = 0; i < diff; i++){
            if((getfracB & 0x0001) && (getfracB & 0x0002)){ // round to even
                printf("***** add : ROUND TO EVEN in frac B part *****\n");
                getfracB = getfracB + 0x0001;
            }
            getfracB = getfracB >> 1;
        }
        EXP = (0x7C00 & a) >> 10; // (0111 1100 0000 0000 and a) >> 10
        SIGN = signA;
    }
    else if(diff < 0){
        for(int i = 0; i < (-diff); i++){
            if((getfracA & 0x0001) && (getfracA & 0x0002)){ // round to even
                printf("***** add : ROUND TO EVEN in frac A part *****\n");
                getfracA = getfracA + 0x0001;
            }
            getfracA = getfracA >> 1;
        }
        EXP = (0x7C00 & b) >> 10; // (0111 1100 0000 0000 and b) >> 10
        SIGN = signB;
    } // diff < 0
    else{ // diff == 0
        EXP = (0x7C00 & a) >> 10; // also, b able.
        SIGN = getfracA > getfracB ? signA : signB;
    }
    
    if(signA == signB){ FRAC = getfracA + getfracB; }
    else{
        if(diff > 0){
            FRAC = getfracA - getfracB;
        }
        else if(diff < 0){
            FRAC = getfracB - getfracA;
        }
        else{ // diff == 0
            FRAC = getfracA > getfracB ? (getfracA - getfracB) : (getfracB - getfracA);
        }
    }

    if(FRAC == 0x0000){
        sfp zero = 0x0000;
        return zero;
    }

    if(FRAC >= 0x0800){ // > 0000 1000 0000 0000 : increased number of digits, number of digits that can be increased is 1 digit
        EXP++;
        if((FRAC & 0x0001) && (FRAC & 0x0002)){ // round to even
            printf("***** add : ROUND TO EVEN in frac part *****\n");
            FRAC = FRAC + 0x0001;
        }
        FRAC = FRAC >> 1;
    }
    else{
        for(int i = 0; i < 10; i++){
            if(FRAC >= 0x0400){ // and 0000 0100 0000 0000 : 기존 자리
                break;
            }
            FRAC = FRAC << 1; // 자리 수 줄어들었다면 앞으로 당기고, EXP - 1
            EXP--;
        }
    }

    FRAC = FRAC & 0x03FF; // 0000 0011 1111 1111 : hiding implied leading 1 bit
    sfp ret = SIGN | (EXP << 10) | FRAC;
    if(EXP >= 31){
        ret = 0x7C00 | SIGN;
    }
    return ret;
}

sfp sfp_mul(sfp a, sfp b){
    if( ( ((a & 0x7C00) == 0x7C00) && (a & 0x03FF) ) || ( ((b & 0x7C00) == 0x7C00) && (b & 0x03FF) ) ){ // input: NaN
        sfp NaN = 0x7FFF; // 0111 1111 1111 1111 : NaN example
        printf("input: NaN = NaN\n");
        return NaN;
    }
    else if(a == 0x7C00 || a == 0xFC00 || b == 0x7C00 || b == 0xFC00){ // if a or b are inf or -inf
        sfp posinf = 0x7C00;
        sfp neginf = 0xFC00;
        sfp NaN = 0x7FFF; // 0111 1111 1111 1111 : NaN example
        if(a == 0x7C00){
            if(b == 0x7C00){
                printf("inf * inf = inf\n");
                return posinf;
            }
            else if(b == 0xFC00){
                printf("inf * -inf = -inf\n");
                return neginf;
            }
            else if(b == 0x0000 || b == 0x8000){
                printf("inf * 0 = NaN\n");
                return NaN;
            }
            else{ // b: Normal value
                if(b & 0x8000){
                    printf("inf * -Normal value = -inf\n");
                    return neginf;
                }
                else{
                    printf("inf * +Normal value = inf\n");
                    return posinf;
                }
            }
        }
        else if(a == 0xFC00){
            if(b == 0x7C00){
                printf("-inf * inf = -inf\n");
                return neginf;
            }
            else if(b == 0xFC00){
                printf("-inf * -inf = inf\n");
                return posinf;
            }
            else if(b == 0x0000 || b == 0x8000){
                printf("-inf * 0 = NaN\n");
                return NaN;
            }
            else{ // b: Normal value
                if(b & 0x8000){
                    printf("-inf * -Normal value = inf\n");
                    return posinf;
                }
                else{
                    printf("-inf * +Normal value = -inf\n");
                    return neginf;
                }
            }
        }
        else{ // a == 0x0000 or Normal value
            if(a == 0x0000 || a == 0x8000){ // a == 0
                printf("0 * (+,-)inf = NaN\n");
                return NaN;
            }
            else{ // a == Normal value
                if(a & 0x8000){
                    if(b & 0x8000){
                        printf("-Normal value * -inf = inf\n");
                        return posinf;
                    }
                    else{
                        printf("-Normal value * inf = -inf\n");
                        return neginf;
                    }
                }
                else{
                    if(b & 0x8000){
                        printf("+Normal value * -inf = -inf\n");
                        return neginf;
                    }
                    else{
                        printf("+Normal value * inf = inf\n");
                        return posinf;
                    }
                }
            }
        }
    }
    if(a == 0x0000 || a == 0x8000 || b == 0x0000 || b == 0x8000){ // (0 and normal) or (normal and 0) -> return 0
        sfp zero = 0x0000;
        return zero;
    }

    sfp getexpA = (0x7C00 & a) >> 10;
    sfp getexpB = (0x7C00 & b) >> 10; // 0111 1100 0000 0000 and >> 10 for translate as integer

    sfp getfracA = (0x03FF & a) | 0x0400; // 덧셈과 다르게 implied leading 1 bit도 가져옴
    sfp getfracB = (0x03FF & b) | 0x0400; // 0000 0011 1111 1111 & PARAMETER | 0000 0100 0000 0000

    sfp SIGN = (0x8000 & a)^(0x8000 & b); // sign of A xor sign of B
    getexpA = getexpA - 15;
    getexpB = getexpB - 15; // E = Exp - Bias
    sfp EXP = getexpA + getexpB + 15; // add E of A and B, and Bias

    sfp FRAC;
    // FRAC => 각각 오른쪽이로 민다 -> 곱셈 -> 정규화 -> exp에 반영
    int moveA = 0, moveB = 0, tmp;
    while(!(getfracA & 0x0001) || !(getfracB & 0x0001)){
        if(!(getfracA & 0x0001)){
            getfracA = getfracA >> 1;
            moveA++;
        }
        if(!(getfracB & 0x0001)){
            getfracB = getfracB >> 1;
            moveB++;
        }
        tmp = (11 - moveA) + (11 - moveB); // fracA, fracB의 각각 자리수, 그 합
    }

    while(tmp > 16){
        if(moveA >= moveB){ // 자리수 같음 = 짝수 = 최소 18 = 어차피 각각 1개씩 할 것이므로 순서 상관 X
            if((getfracB & 0x0001) && (getfracB & 0x0002)){
                printf("***** mul : ROUND TO EVEN in frac B part *****\n");
                getfracB = getfracB + 0x0001;
            }
            getfracB = getfracB >> 1;
            moveB++;
        }
        else if(moveA < moveB){
            if((getfracA & 0x0001) && (getfracA & 0x0002)){
                printf("***** mul : ROUND TO EVEN in frac A part *****\n");
                getfracA = getfracA + 0x0001;
            }
            getfracA = getfracA >> 1;
            moveA++;
        }
        tmp = (11 - moveA) + (11 - moveB); // fracA, fracB의 각각 자리수, 그 합
    }

    FRAC = getfracA * getfracB;

    sfp tmp16 = 0x0001;
    for(int i = 1; i < tmp; i++){ // tmp - 1번 좌측 shift
        tmp16 = tmp16 << 1;
    }
    if(FRAC >= tmp16){ // tmp == FRAC의 자리수: exp of A + exp of B + 1 = 새로운 자리수
        EXP = EXP + 1; // increased number of digits
    }
    
    if(FRAC >= 0x0800){ // 0000 1000 0000 0000 : 우측 shift 해야하는 경우
        while(FRAC >= 0x0800){
            if((FRAC & 0x0001) && (FRAC & 0x0002)){
                printf("***** mul : ROUND TO EVEN in frac part *****\n");
                FRAC = FRAC + 0x0001;
            }
            FRAC = FRAC >> 1;
        }
    }
    else if(FRAC < 0x0400){ // 0000 0100 0000 0000
        while(FRAC < 0x0400){
            FRAC = FRAC << 1;
        }
    }
    FRAC = FRAC & 0x03FF; // 0000 0011 1111 1111 : hiding implied leading 1 bit
    sfp ret = SIGN | (EXP << 10) | FRAC;
    if(EXP >= 31){
        ret = 0x7C00 | SIGN;
    }
    return ret;
}

char* sfp2bits(sfp result){
    char *answer = (char*)malloc(sizeof(char) * 17);
    sfp filter = 0x8000;
    for(int i = 0; i < 16; i++, filter = filter >> 1)
    {
        if(result & filter) { answer[i] = '1'; }
        else { answer[i] = '0'; }
    }
    answer[16] = '\0';
    return answer;
}