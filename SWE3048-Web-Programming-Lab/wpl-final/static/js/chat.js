let id2name_cache = {};
function id_caching(participant) {
    // 채팅방 참여자의 id를 name으로 변경
    // id2name_cache에 id -> name 매핑을 저장한다.
    $.ajax({
        type: "POST",
        url: "/id2name",
        contentType: "application/json",
        async: false,
        data: JSON.stringify({"id_list": participant}),
        success: function(data) {
            for(let i = 0; i < participant.length; i++) {
                id2name_cache[participant[i]] = data[i];
            }
        },
        error: function(error) {
            console.log("Error: ", error);
        }
    });
}

function add_img_click_event(){
    // 이미지 클릭하면 새 탭으로 원본 이미지 출력
    $(".img").click(function(event) {
        let new_tap = window.open();
        $(new_tap.document.body).html("<html><head></head><body><img src=\"" + $(this).attr("src") +"\"></body></html>")
    })
}

function fileToBase64(file, callback) {
    // 객체를 읽어서 base64로 인코딩 후 callback으로 제공한다.
    let reader = new FileReader();
    reader.onload = function(e) {
        let Data = e.target.result.split(',')[1];
        callback(Data);
    }
    reader.readAsDataURL(file);
}

let user = "";
let print_item = function(item) {
    // 특정 채팅 데이터 출력
    let target_str = "";
    if(item.sender == user) { // 현재 유저의 채팅이면 우측
        // type에 따라 다른 tag로 data를 감싼다.
        if(item.type=="text") {
            target_str = "<span class=\"text_box\">" + item.message + "</span>";
        } else {
            if(item.type == "INIT") {
                return ;
            }
            if(item.type == "jpg" || item.type == "jpeg") {
                target_str = "<img class=\"img\" style=\"max-width: 300px; max-height: 400px;\" src=\"data:image/jpeg;base64," + item.media + "\">";
            } else if(item.type == "mp4") {
                target_str = "<video controls style=\"max-width: 300px; max-height: 400px;\" src=\"data:video/mp4;base64," + item.media + "\"></video>";
            }
        }
        // 현재 유저이므로 right_div로 감싸 우측에 출력한다.
        $(".chat_box").append(
            "<div class=\"right_div\">" +
                "<span class=\"time\">" + item.time + "</span>" +
                target_str + "</span>" +
            "</div>" +
            "<p style=\"clear: both;\"></p>"
        );
        add_img_click_event();
    } else { // 다른 유저의 채팅이면 좌측
        if(item.type == "text") {
            target_str = "<span class=\"text_box\">" + item.message + "</span>";
        } else {
            if(item.type == "INIT") {
                return ;
            }
            if(item.type == "jpg" || item.type == "jpeg") {
                target_str = "<img class=\"img\" style=\"max-width: 300px; max-height: 400px;\" src=\"data:image/jpeg;base64," + item.media + "\">";
            } else if(item.type == "mp4") {
                target_str = "<video controls style=\"max-width: 300px; max-height: 400px;\" src=\"data:video/mp4;base64," + item.media + "\"></video>";
            }
        }
        // 다른 유저이므로 left_div로 감싸 좌측에 출력한다.
        $(".chat_box").append(
            "<div class=\"left_div\">" +
                "<div class=\"id_div\"><span class=\"other_id\">" + id2name_cache[item.sender] + "</span></div><div>" +
                target_str +
                "<span class=\"time\">" + item.time + "</span></div>" +
            "</div>" +
            "<p style=\"clear: both;\"></p>"
        );
        add_img_click_event();
    }
};

let print_chatLog = function(chatLog) {
    // 전체 비우고, 각 채팅에 알맞게 출력
    $(".chat_box").empty();
    chatLog.forEach(item => print_item(item));
    $("#div_chat_messages").animate({scrollTop: $(".chat_box").prop("scrollHeight")}, 10); // 가장 아래로 이동
};

function get_timestring() {
    // 현재 시간을 받아서 오전, 오후 HH:MM으로 반환
    let current = new Date();
    let hour = current.getHours();
    let min = current.getMinutes();
    
    let time = String();
    time = hour < 12 ? "오전 " : "오후 ";

    hour = hour % 12 == 0 ? 12 : hour % 12;
    min = min < 10 ? "0" + String(min) : min;

    return time + hour + ":" + min;
};

$(document).ready(function() {
    let url = new URL(location.href);
    let participant = url.searchParams.get("participant").split('.');
    // url의 query string으로부터 서버에 요청하여 participant의 name을 가져와 id2name_cache에 저장한다.
    id_caching(participant);
    participant.sort();

    // label만 남기고 <input type="file">은 숨긴다.
    $("#input_file").hide();

    $("#input_file").on("change", function(event) {
        // 파일이 올라가면
        let file = this.files[0];
        // 확장자명 추출
        let ext = $("#input_file").val().split('.')[1];
        // file로부터 base64인코딩 후, 데이터로 만들고 송신
        fileToBase64(file, function(Data) {
            let data = {"sender": user, "participant": participant, "media": Data, "time":get_timestring(), "type": ext};
            ws.send(JSON.stringify(data));
        })        
    });

    $("#btn_send").click(function(event) {
        // 비었거나 개행문자로만 이루어졌을 때에는 탈출한다.
        let text = $("#textarea").val();
        if(text.length == (text.match(/\n/g) || []).length) {
            return ;
        } else if(!fromEnter && text[text.length - 1] == '\n') {
            text += '\n';
        }
        // 개행문자를 <br>로 변경하여 데이터를 생성한다.
        text = text.replaceAll('\n', "<br>");
        let data = {"sender": user, "participant": participant, "message": text, "time": get_timestring(), "type": "text"};
        // 비운다.
        $("textarea").val('');
        // 송신
        ws.send(JSON.stringify(data));
    });

    let fromEnter = false;
    $("#textarea").on("keyup", function(event) {
        // 엔터 입력 시 적절히 개행문자 처리 후 click trigger를 발생시킨다. fromEnter는 개행문자 제거를 위한 flag
        if(event.keyCode == 13){ // Enter
            if(event.shiftKey){
                return ;
            }

            let text = $(this).val();
            if(text.length == (text.match(/\n/g) || []).length) {
                $(this).val(text.slice(0, -1));
                return ;
            }
            fromEnter = true;
            $("#btn_send").trigger("click");
            fromEnter = false;
        }
    });

    // 웹소켓 초기화
    let ws = new WebSocket("ws://localhost:8000/ws");
    ws.onopen = function(event) {
        // 채팅방 채팅 전체 불러오기
        $.ajax({
            type: "POST",
            url: "/load_chats",
            contentType: "application/json",
            data: JSON.stringify({"id_list": participant}),
            async: false,
            success: function(data) {
                user = data.user;
                print_chatLog(data.data);
            },
            error: function(error) {
                console.log("Error: ", error);
            }
        });
        // 웹소켓으로 요청한 사용자와 참여자 리스트 제공
        ws.send(JSON.stringify({"connect": user, "participant": participant}));
        $("#div_chat_messages").animate({scrollTop: $(".chat_box").prop("scrollHeight")}, 10); // 가장 아래로 이동
    };
    ws.onmessage = function(event) {
        // 메시지 도착 시 JSON으로 파싱한 후 출력
        let item = JSON.parse(event.data);
        print_item(item);
        $("#div_chat_messages").animate({scrollTop: $(".chat_box").prop("scrollHeight")}, 10); // 가장 아래로 이동
    };
});