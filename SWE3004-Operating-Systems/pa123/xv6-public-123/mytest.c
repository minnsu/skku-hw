#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_ANONYMOUS 0x1
#define MAP_POPULATE 0x2
#define PGSIZE 4096

void fork_unmap(int addr){
    printf(1, "freemem %d before fork\n", freemem());
    int cid = fork();
    if(cid)
        printf(1, "freemem %d after fork\n", freemem());
    int ret = 0;
    ret = munmap((uint) addr);
    if(ret < 0)
        printf(1, "munmap failed in %s\n", (cid == 0 ? "child" : "parent"));
    if(cid == 0){
        exit();
    }
    wait();
    printf(1, "after munmap both %d\n-------------------------------------------------------------------------------------------------\n", freemem());
}


int main(int argc, char *argv[]){
    /* TODO: munmap한 주소에서 출력 시 오류가 가끔 발생하지 않고 빈 문자열이 출력되는 현상은? TODO:
     * mmap(addr, length, prot, flags, fd, offset)
     * [flags]
     * 
     * 0 -> file mapping not populate : 첫 접근 시 pagefault handler에서 할당해야 함
     * anonymous -> anonymous not populate : 위와 동일
     * 
     * populate -> file mapping populate : mmap에서 할당해서 존재 = pagefault handler 호출하면 안됨
     * populate | anonymous -> anonymous populate : 위와 동일
     * 
     * [PROTECTION]
     * 
     * PROT_READ -> 읽기만 가능
     * PROT_READ | PROT_WRITE -> 읽기 쓰기
     * 
     * [fork test]
     * 
     * 부모와 자식은 동일한 매핑과 메모리 컨텐츠까지 모두 복사해서 동일, 그러나 한 쪽의 unmap이 다른 쪽에 영향을 주면 안된다.
     */

    printf(1, "Start freemem %d\n", freemem());
    int r_fd = open("README", O_RDONLY);
    int rw_fd = open("README", O_RDWR);

    char *case0;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 0 (flags = 0, prot = PROT_READ)---------------------\n");
    if((case0 = (char *)mmap(0, PGSIZE, PROT_READ, 0, r_fd, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case0[0]);
    // printf(1, "[%c]\n", case0[PGSIZE]); // over length error
    // strcpy(case0, "cause page fault handler's protection fault"); // protection error
    printf(1, "--------------------------- after pagefault freemem %d----------------------------------------\n", freemem());
    fork_unmap((uint) case0);

    char *case1;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 1 (flags = 0, prot = PROT_READ | PROT_WRITE )-------\n");
    if((case1 = (char *)mmap(PGSIZE, PGSIZE * 2, PROT_READ | PROT_WRITE, 0, rw_fd, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case1[0]);
    printf(1, "[%c]\n", case1[PGSIZE]);
    // printf(1, "[%c]\n", case1[PGSIZE * 2]); // over length error
    strcpy(case1, "should be noramlly modified!");
    printf(1, "=> [%s]\n", case1);
    printf(1, "--------------------------- after pagefault freemem %d ---------------------------------------\n", freemem());
    fork_unmap((uint) case1);


    char *case2;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 2 (flags = MAP_ANONYMOUS, prot = PROT_READ)---------\n");
    if((case2 = (char *)mmap(PGSIZE * 3, PGSIZE * 3, PROT_READ, MAP_ANONYMOUS, -1, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case2[PGSIZE * 2]);
    printf(1, "[%c]\n", case2[0]);
    printf(1, "[%c]\n", case2[PGSIZE]);
    // printf(1, "[%c]\n", case2[PGSIZE * 3]); // over length error
    // strcpy(case2, "cause page fault handler's protection fault\n"); // protection error
    printf(1, "--------------------------- after pagefault freemem %d ----------------------------------------\n", freemem());
    fork_unmap((uint) case2);

    char *case3;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 3 (flags = MAP_ANONYMOUS, prot = PROT_READ | PROT_WRITE)---------\n");
    if((case3 = (char *)mmap(PGSIZE * 6, PGSIZE * 4, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case3[PGSIZE * 2]);
    printf(1, "[%c]\n", case3[0]);
    printf(1, "[%c]\n", case3[PGSIZE * 3]);
    printf(1, "[%c]\n", case3[PGSIZE]);
    // printf(1, "[%c]\n", case3[PGSIZE * 4]); // length error
    strcpy(case3, "change contents of memory!");
    printf(1, "[%s]\n", case3);
    printf(1, "----------------------- after pagefault freemem %d -------------------------------------------\n", freemem());
    fork_unmap((uint) case3);
    


    char *case4;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 4 (flags = MAP_POPULATE, prot = PROT_READ)---------------\n");
    if((case4 = (char *)mmap(PGSIZE * 10, PGSIZE * 5, PROT_READ, MAP_POPULATE, r_fd, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case4[0]);
    printf(1, "[%c]\n", case4[PGSIZE]);
    printf(1, "[%c]\n", case4[PGSIZE * 2]);
    printf(1, "[%c]\n", case4[PGSIZE * 3]);
    printf(1, "[%c]\n", case4[PGSIZE * 4]);
    // printf(1, "[%c]\n", case4[PGSIZE * 5]); // length error
    // strcpy(case4 + PGSIZE * 4, "change contents of memory!"); // cause protection error
    printf(1, "----------------------- after test freemem %d -------------------------------------------\n", freemem());
    fork_unmap((uint) case4);

    char *case5;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 5 (flags = MAP_POPULATE, prot = PROT_READ | PROT_WRITE)---------------\n");
    if((case5 = (char *)mmap(PGSIZE * 15, PGSIZE * 6, PROT_READ | PROT_WRITE, MAP_POPULATE, rw_fd, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case5[0]);
    printf(1, "[%c]\n", case5[PGSIZE]);
    printf(1, "[%c]\n", case5[PGSIZE * 2]);
    printf(1, "[%c]\n", case5[PGSIZE * 3]);
    printf(1, "[%c]\n", case5[PGSIZE * 4]);
    printf(1, "[%c]\n", case5[PGSIZE * 5]);
    // printf(1, "[%c]\n", case5[PGSIZE * 6]); // cause error
    strcpy(case5, "modify to this!");
    printf(1, "=> [%s]\n", case5);
    printf(1, "----------------------- after test freemem %d -------------------------------------------\n", freemem());
    fork_unmap((uint) case5);

    char *case6;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 6 (flags = MAP_ANONYMOUS | MAP_POPULATE, prot = PROT_READ)---------------\n");
    if((case6 = (char *)mmap(PGSIZE * 21, PGSIZE * 7, PROT_READ, MAP_ANONYMOUS | MAP_POPULATE, -1, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case6[0]);
    printf(1, "[%c]\n", case6[PGSIZE]);
    printf(1, "[%c]\n", case6[PGSIZE * 2]);
    printf(1, "[%c]\n", case6[PGSIZE * 3]);
    printf(1, "[%c]\n", case6[PGSIZE * 4]);
    printf(1, "[%c]\n", case6[PGSIZE * 5]);
    printf(1, "[%c]\n", case6[PGSIZE * 6]);
    // printf(1, "[%c]\n", case6[PGSIZE * 7]); // length error
    // strcpy(case6, "modify to this!"); // protection error
    // printf(1, "\n=> [%s]\n", case6);
    printf(1, "----------------------- after test freemem %d -------------------------------------------\n", freemem());
    fork_unmap((uint) case6);
    
    char *case7;
    printf(1, "---------------------------------------- freemem %d ------------------------------------------\n", freemem());
    printf(1, "---------------------------------- TEST CASE 7 (flags = MAP_ANONYMOUS | MAP_POPULATE, prot = PROT_READ | PROT_WRITE)---------------\n");
    if((case7 = (char *)mmap(PGSIZE * 28, PGSIZE * 8, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_POPULATE, -1, 0)) == 0){
        printf(1, "mmap failed\n");
    }
    printf(1, "[%c]\n", case7[0]);
    printf(1, "[%c]\n", case7[PGSIZE]);
    printf(1, "[%c]\n", case7[PGSIZE * 2]);
    printf(1, "[%c]\n", case7[PGSIZE * 3]);
    printf(1, "[%c]\n", case7[PGSIZE * 4]);
    printf(1, "[%c]\n", case7[PGSIZE * 5]);
    printf(1, "[%c]\n", case7[PGSIZE * 6]);
    printf(1, "[%c]\n", case7[PGSIZE * 7]);
    // printf(1, "[%c]\n", case7[PGSIZE * 8]); // length error
    strcpy(case7, "modify to this!");
    printf(1, "\n=> [%s]\n", case7);
    printf(1, "----------------------- after test freemem %d -------------------------------------------\n", freemem());
    fork_unmap((uint) case7);

    close(r_fd);
    close(rw_fd);
    printf(1, "End freemem %d\n", freemem());
    exit();
}