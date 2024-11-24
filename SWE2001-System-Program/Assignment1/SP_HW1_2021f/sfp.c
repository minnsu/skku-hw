#include "sfp.h"
#include <stdlib.h>
sfp int2sfp(int input){
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

    unsigned int SIGN = (0x00008000 & input) << 16;

    unsigned int ret = 0x000003FF; // 0000 0011 1111 1111
    ret = (input & ret) | 0x00000400; // (make FRAC part) | 0000 0100 0000 0000 (make implied leading 1 bit)

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
    union memory{
        unsigned int tmp;
        float asFloat;
    };
    union memory inputuint;
    if(input == 0x0000){ // input: +0.0
        float poszero = 0x00000000;
        return poszero;
    }
    else if(input == 0x8000){// input: -0.0
        float negzero = 0x80000000;
        return negzero;
    }
    else if( ((input & 0x7C00) == 0x7C00) && (input & 0x03FF) ){ // input: NaN
        unsigned int NaN = 0x7FFFFFFF; // 0111 1111 1111 1111 1111 1111 1111 1111
        inputuint.tmp = NaN;
        return inputuint.asFloat;
    }
    else if(input == 0x7C00){ // input: pos inf
        unsigned int posinf = 0x7F800000; // 0111 1111 1000 0000 0000 0000 0000 0000
        inputuint.tmp = posinf;
        return inputuint.asFloat;
    }
    else if(input == 0xFC00){ // input: neg inf
        unsigned int neginf = 0xFF800000; // 1111 1111 1000 0000 0000 0000 0000 0000
        inputuint.tmp = neginf;
        return inputuint.asFloat;
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
    inputuint.tmp = tmp;
    float ret = inputuint.asFloat;
    return ret;
}

sfp sfp_add(sfp a, sfp b){
    if( ( ((a & 0x7C00) == 0x7C00) && (a & 0x03FF) ) || ( ((b & 0x7C00) == 0x7C00) && (b & 0x03FF) ) ){ // input: NaN
        sfp NaN = 0x7FFF; // 0111 1111 1111 1111 : NaN example
        return NaN;
    }
    else if(a == 0x7C00 || a == 0xFC00 || b == 0x7C00 || b == 0xFC00){ // input: inf or -inf
        sfp posinf = 0x7C00;
        sfp neginf = 0xFC00;
        sfp NaN = 0x7FFF; // 0111 1111 1111 1111 : NaN example
        if(a == 0x7C00){ // a: inf
            if(b == 0xFC00){ // b: -inf
                return NaN;
            }
            else{ // b: inf or Normal value
                return posinf;
            }
        }
        else if(a == 0xFC00){ // a: -inf
            if(b == 0x7C00){ // b: inf
                return NaN;
            }
            else{ // b: -inf or Normal value
                return neginf;
            }
        }
        else{ // a == Normal value
            return b;
        }
    }

    sfp signA = 0x8000 & a;
    sfp signB = 0x8000 & b;
    unsigned int getfracA = (0x03FF & a) | 0x0400;
    unsigned int getfracB = (0x03FF & b) | 0x0400; // 0000 0000 0000 0000 0000 0011 1111 1111 & PARAMETER | 0000 0100 0000 0000
    if(((0x7C00 & a) >> 10) == 0x0000 && ((0x7C00 & b) >> 10) == 0x0000 && getfracA == 0x0400 && getfracB == 0x0400){
        sfp zero = 0x0000;
        return zero;
    }
    sfp SIGN;
    sfp EXP;
    unsigned int FRAC = 0x00000000;
    short diff = ((0x7C00 & a) >> 10) - ((0x7C00 & b) >> 10); // signed short
    // exp of a - exp of b: which absolute value is big?: 
    // diff > 0: a's abosulute value is big, diff < 0: b's absolute value is big, diff == 0: should compare frac part
    getfracA = getfracA << 20;
    getfracB = getfracB << 20; // 왼쪽 2번째 자리까지 밀기
    unsigned int tmp_diff1 = 0x00000001;
    unsigned int tmp_diff2 = 0x00000001;
    if(diff > 0){
        for(int i = 1; i < diff; i++){
            tmp_diff1 = (tmp_diff1 << 1) + 0x00000001;
            tmp_diff2 = tmp_diff2 << 1;
        }
        if( ((tmp_diff1 & getfracB) > tmp_diff2) || ( (tmp_diff2 & getfracB) && ((tmp_diff2 << 1) & getfracB) )){ // round to even
            getfracB = getfracB >> diff;
            getfracB = getfracB + 0x00000001;
        }
        else{
            getfracB = getfracB >> diff;
        }
        EXP = (0x7C00 & a) >> 10; // (0111 1100 0000 0000 and a) >> 10
        SIGN = signA;
    }
    else if(diff < 0){
        for(int i = 0; i < (-diff); i++){
            tmp_diff1 = (tmp_diff1 << 1) + 0x00000001;
            tmp_diff2 = tmp_diff2 << 1;
        }
        if( ((tmp_diff1 & getfracA) > tmp_diff2) || ( (tmp_diff2 & getfracA) && ((tmp_diff2 << 1) & getfracA) )){ // round to even
            getfracA = getfracA >> (-diff);
            getfracA = getfracA + 0x00000001;
        }
        else{
            getfracA = getfracA >> (-diff);
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
    if(FRAC >= 0x00000800){ // > 0000 1000 0000 0000 : increased number of digits, number of digits that can be increased is 1 digit
        if( ((0x000FFFFF & FRAC) > 0x00080000) || ( (0x00080000 & FRAC) && (0x00100000 & FRAC) ) ){ // > 1/2 or 1.1xxx -> +1 // round to even
            FRAC = FRAC >> 20;
            FRAC = FRAC + 0x00000001;
        }
        else{
            FRAC = FRAC >> 20;
        }
        if(FRAC >= 0x00000800){ // 처음부터 더한값이 자리 수 늘어남 or round to even으로 인한 자리수 늘어남
            if((FRAC & 0x0001) && (FRAC & 0x0002)){ // round to even
                FRAC = FRAC + 0x0001;
            }
            FRAC = FRAC >> 1;
            EXP = EXP + 1; // 더해야 하나 둬야 하나
        }
    }
    for(int i = 0; i < 10; i++){
        if(FRAC >= 0x0400){ // and 0000 0100 0000 0000 : 기존 자리
            break;
        }
        FRAC = FRAC << 1; // 자리 수 줄어들었다면 앞으로 당기고, EXP - 1
        EXP--;
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
        return NaN;
    }
    else if(a == 0x7C00 || a == 0xFC00 || b == 0x7C00 || b == 0xFC00){ // if a or b are inf or -inf
        sfp posinf = 0x7C00;
        sfp neginf = 0xFC00;
        sfp NaN = 0x7FFF; // 0111 1111 1111 1111 : NaN example
        if(a == 0x7C00){
            if(b == 0x7C00){
                return posinf;
            }
            else if(b == 0xFC00){
                return neginf;
            }
            else if(b == 0x0000 || b == 0x8000){
                return NaN;
            }
            else{ // b: Normal value
                if(b & 0x8000){
                    return neginf;
                }
                else{
                    return posinf;
                }
            }
        }
        else if(a == 0xFC00){
            if(b == 0x7C00){
                return neginf;
            }
            else if(b == 0xFC00){
                return posinf;
            }
            else if(b == 0x0000 || b == 0x8000){
                return NaN;
            }
            else{ // b: Normal value
                if(b & 0x8000){
                    return posinf;
                }
                else{
                    return neginf;
                }
            }
        }
        else{ // a == 0x0000 or Normal value
            if(a == 0x0000 || a == 0x8000){ // a == 0
                return NaN;
            }
            else{ // a == Normal value
                if(a & 0x8000){
                    if(b & 0x8000){
                        return posinf;
                    }
                    else{
                        return neginf;
                    }
                }
                else{
                    if(b & 0x8000){
                        return neginf;
                    }
                    else{
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

    unsigned int FRAC;
    // FRAC => 각각 오른쪽이로 민다 -> 곱셈 -> 정규화 -> exp에 반영
    FRAC = getfracA * getfracB;
    if(FRAC >= 0x00200000){ // >= 0000 0000 0010 0000 0000 0000 0000 0000
        EXP = EXP + 1; // increased number of digits
    }
    unsigned int tmp_check = 0x80000000;
    unsigned int loc = 32;
    while(!(tmp_check & FRAC)){
        tmp_check = tmp_check >> 1;
        loc--;
    }
    tmp_check = tmp_check >> 11; // 현재 부분부터 짤림
    loc = loc - 11;
    if(FRAC >= 0x0800){ // 0000 1000 0000 0000 : 우측 shift 해야하는 경우
        // round to even
        if( ((((tmp_check << 1) - 0x00000001) & FRAC) > tmp_check) || ( (tmp_check & FRAC) && ((tmp_check << 1) & FRAC) ) ){ // > 1/2 or 1.1xxx -> +1
            FRAC = FRAC >> loc;
            FRAC = FRAC + 0x00000001;
        }
        else{
            FRAC = FRAC >> loc;
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