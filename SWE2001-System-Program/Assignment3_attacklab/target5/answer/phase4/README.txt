solution : code 삽입하지 않고 touch2 실행하기
0x38만큼 버퍼 채우기
popq %regN
cookie 16진수 그 자체 값 -> pop으로 regN에 저장됨
mov %regN, %rdi -> rdi에 cookie 값을 옮겨서 touch2 매개변수로 만듦
touch2 주소 -> call touch2, 매개변수는 위에서 저장한 cookie값
