solution : add_xy 이용하여 cookie string 위치 가리키는 rdi 만들기

farm에서 가능한 코드를 모두 모으기
rsp 값이 rdi, offset 값이 rsi로 가는 코드를 만들어야 함.

mov를 조합하여 rsp -> rdi
pop과 mov를 조합하여 offset -> rsi
	offset 주소는 rdi에 저장하는 줄과 cookie string의 주소 차이
	(ex) 1번째 줄에 mov %regN, %rdi, 7번째 줄에 cookie string 있다면
			6줄 차이, 한 줄에 8byte로 저장했다면 10진수 48, 16진수 30
			-> offset == 30 00 00 00 00 00 00 00
add_xy 호출하면 rax = rdi + rsi
mov rax, rdi 하여 touch3의 매개변수로 cookie 주소 사용
touch3 주소
cookie string : 아스키코드 16진수 해석 string
