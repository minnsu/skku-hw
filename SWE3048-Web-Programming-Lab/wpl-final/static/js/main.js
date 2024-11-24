function newchat(participants) {
    // 새로운 채팅방을 생성하는 요청이다.
    // 현재 사용자는 채팅방 제목이나 friend 이름에 존재하지 않으므로 추가해준다.
    if(!participants.includes(user_id)) {
        participants.push(user_id);
    }
    // 정렬 후(백엔드 테이블의 participant로 채팅방을 구분하므로) 요청하여 해당 채팅방을 생성하거나 이미 존재하면 그 채팅방으로 이동한다.
    participants.sort();
    $.ajax({
        type: "POST",
        url: "/newchat",
        contentType: "application/json",
        data: JSON.stringify({"id_list": participants}),
        success: function(data) {
            console.log(data);
            if(data.status == "SUCCESS") {
                location.href = "/chat?participant=" + String(data.participant.join('.'));
            }
        },
        error: function(error) {
            console.log("Error: ", error);
        }
    })
}

let id2name_cache = {};
function id_caching(participant) {
    // 참가자 id를 정렬 후 요청하여 id -> name 매핑을 업데이트한다.
    participant.sort();
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

function add_1to1_chat_event_handler() {
    // friend 이름을 클릭하면 1대1 채팅방으로 이동하는 이벤트 핸들러이다.
    $(".friend").click(function(event) {
        let friend_id = $(this).attr("id");
        let participant = [friend_id];
        console.log(participant);
        newchat(participant);
    });
}

function open_chat_room_event_handler() {
    // chat list에 있는 채팅방 클릭 시 이동하는 이벤트 핸들러이다.
    $(".chat").click(function(event) {
        let participant = $(this).attr("id").split('_');
        location.href = "/chat?participant=" + String(participant.join('.'));
    })
}

let user_id = "";
let user_name = "";
$(document).ready(function() {
    $("#input_friend_id").hide();
    
    $("#btn_friends").click(function(event) {
        // friends 버튼을 클릭하면, group_chat 버튼과 add friend 버튼을 보이도록 하고, list를 지운다.
        $("#div_add_friend").show();
        $("#list").empty();

        $.ajax({
            type: "POST",
            url: "/friends",
            success: function(data) {
                let le = $("#list");
                let isMe = true;
                // 첫번째 데이터는 현재 사용자이므로 해당 flag 설정
                data.forEach(friend => {
                    if(isMe) {
                        user_id = friend[0];
                        user_name = friend[1];
                        isMe = false;
                    } else {
                        // 다른 유저면 friend list에 추가
                        le.append("<li class=\"friend\" id=\"" + friend[0] + "\">" + friend[1] + "</li>");
                    }
                    // id -> name 매핑을 업데이트한다.
                    id2name_cache[friend[0]] = friend[1];
                });
                add_1to1_chat_event_handler();
            },
            error: function(error) {
                console.log("Error: ", error);
            }
        });
    });
    $("#btn_friends").trigger("click");

    $("#btn_chats").click(function(event) {
        // chats 버튼을 클릭하면 friend list는 제거하고, group_chat 버튼과 add friend 버튼도 숨긴다.
        $("#div_add_friend").hide();
        $("#list").empty();

        $.ajax({
            type: "POST",
            url: "/chats",
            success: function(data) {
                let le = $("#list");
                data.forEach(chat => {
                    // 각 채팅방 리스트에서 받은 참가자 명단으로 caching을 진행하고, name으로 변경한다.
                    let participant = chat.participant.split(',');
                    id_caching(participant);

                    let names = [];
                    for(let i = 0; i < participant.length; i++) { // id에서 name으로 변경
                        names.push(id2name_cache[participant[i]]);
                    }
                    // 현재 사용자 제거
                    names = names.filter(name => name != user_name);
                    if(chat.message == "INIT") // 만들어지기만 한 채팅방이면 message 미표시
                        chat.message = "";
                    
                    let selector = "#" + participant.join('_');

                    if($(selector).length == 0) { // 없으면 만들기
                        le.append("<li class=\"chat\" id=\"" + participant.join('_') + "\">" + names.join(", ") + "<br><span class=\"message\">" + chat.message + "</span></li>");
                    } else { // 이미 존재하면 바꾸기
                        if(chat.message != null) {
                            $(selector).children("span").html(chat.message);
                        } else {
                            // 사진 또는 비디오는 "미디어 파일"로 표시한다.
                            $(selector).children("span").html("미디어 파일");
                        }
                    }
                });
                // 채팅방 클릭 시 이동하는 event handler를 등록한다.
                open_chat_room_event_handler();
            },
            error: function(error) {
                console.log("Error: ", error);
            }
        });
    });

    let group_flag = 1;
    $("#btn_group_chat").click(function(event) {
        switch(group_flag) {
            case 1:
                // group chat을 위해 friend 앞에 radio button을 추가한다.
                group_flag = 2;
                $(".friend").off("click"); // group chat mode 켜지면 1to1 chat click event를 잠시 꺼둔다.
                $("li").each(function(index, item) {
                    $("<input type=\"radio\">").prependTo(item);
                });
                break;
            case 2:
                // 선택된 friend id를 모아서 newchat 함수를 수행하여 채팅방을 만들고 넘어간다. 이미 있다면 존재하는 방으로 이동한다.
                group_flag = 1;

                let participants_list = [];
                $("input:checked").parent().each(function(index, item) {
                    participants_list.push(item.id);
                });
                if(participants_list.length != 0) {
                    newchat(participants_list);
                } else {
                    alert("Please select chat group.");
                }
                // friend 앞에 있는 radio button을 모두 제거한 뒤, 1to1 chat click event를 다시 킨다.
                $("li").children("input").remove();
                add_1to1_chat_event_handler();
                break;
        }
    });

    let flag = 1;
    $("#btn_add_friend").click(function(event) {
        switch(flag) {
            case 1:
                // 처음 클릭 시 input field를 보여주며, flag를 2로 설정한다.
                $("#btn_group_chat").hide();
                console.log("click button1");
                $("#input_friend_id").val("");
                $("#input_friend_id").show();
                flag = 2;
                break;
            case 2:
                // flag가 2일 때에는 input field로부터 추가할 친구 id를 읽어서 서버에 보낸다.
                console.log("click button2");
                let friend_id = $("#input_friend_id").val();
                // 비어있다면 alert 실행, 존재하면 서버로 해당 id 송신
                if(friend_id == "") {
                    alert("Please fill the blank");
                } else {
                    $.ajax({
                        type: "POST",
                        url: "/add_friend",
                        contentType: "application/json",
                        data: JSON.stringify({"name": "", "id": friend_id, "password": ""}),
                        success: function(data) {
                            // 성공했다면 friends 버튼을 trigger하여 새로 고침한다.
                            $("#btn_friends").trigger("click");
                        },
                        error: function(error) {
                            // 자신의 id, 이미 친구인 id, 존재하지 않는 id 요청 시 Execption 발생으로 alret 수행
                            alert("Invalid user id.");
                        }
                    });
                }
                // input field를 다시 숨기고, group chat 버튼을 다시 보이게 한다.
                $("#input_friend_id").hide();
                $("#btn_group_chat").show();
                //  flag를 다시 1로 바꾼다.
                flag = 1;
                break;
        }
    });
});