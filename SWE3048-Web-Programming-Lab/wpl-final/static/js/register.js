$(document).ready(function() {
    $("#btn_register").click(function() {
        // 회원가입 버튼 클릭 시 input field에서 정보를 읽는다.
        let name = $("#input_name").val();
        let id = $("#input_id").val();
        let pw = $("#input_pw").val();
        // 하나라도 비어있으면 alert 후 종료
        if(name == "" || id == "" || pw == "") {
            alert('Please fill the blanks');
            return ;
        }
        // 데이터 만들어서 송신
        let data = {"id": id, "name": name, "password": pw};
        $.ajax({
            type: "POST",
            url: "/register",
            contentType:"application/json",
            data: JSON.stringify(data),
            success: function(response) {
                // 성공하면 index 페이지로 이동
                console.log(response);
                if(response.status == 'SUCCESS') {
                    location.href = "/";
                }
            },
            error: function(error) {
                console.log("Error: ", error);
            }
        });
    });
});