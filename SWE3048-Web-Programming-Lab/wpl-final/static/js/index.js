$(document).ready(function () {
    $("#btn_login").click(function(event) {
        // 로그인 버튼 클릭 시 input field에서 읽어서 데이터 송신 후 성공하면 main page로 이동
        let id = $("#input_id").val();
        let pw = $("#input_pw").val();
        let data = {"name": "", "id": id, "password": pw};
        $.ajax({
            type: "POST",
            url: "/token",
            data: JSON.stringify(data),
            contentType: "application/json",
            success: function(data) {
                console.log(data);
                location = "/main";
            },
            error: function(error) {
                // 실패하면 alert 수행 후 field 지우기
                alert("Invalid id or password.");
                $("#input_id").val("");
                $("#input_pw").val("");
            }
        })
    });

    $("#btn_register").click(function(event) {
        // 회원가입 버튼 클릭 시 페이지 이동
        $.ajax({
            type: "GET",
            url: "/register",
            success: function(data) {
                $("body").html(data);
            },
            error: function(error) {
                console.error("Error: can not load register page, ", error);
            }
        });
    });
});