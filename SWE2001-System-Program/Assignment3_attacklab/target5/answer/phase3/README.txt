solution : match string, 매개변수 넘겨주기
첫 줄에 mov $0x...., %rdi, ret 코드 존재
	-> string 주소(getbuf 호출 시 rsp + 0x10)를 rdi에 저장
		(한 번에 8 byte씩 넘겨주고 16진수이므로 0x10 = 16)
0x38만큼 버퍼 채우기
첫 줄 위치 가리킴(getbuf 호출 시 rsp - 0x38) -> 첫 줄 코드 실행되도록
첫 줄에서 ret하므로 다음 줄이 return 주소, 따라서 touch3 주소 삽입
cookie를 아스키코드 16진수 string으로 변환한 것(첫 줄 코드에서 rdi에 삽입하는 주소)
