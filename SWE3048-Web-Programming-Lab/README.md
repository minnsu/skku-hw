# 2023-Fall 성균관대학교 웹프로그래밍실습

### wpl-final: A web  similar to KakaoTalk
- backend
    - fastapi
    - sqlite3 with sqlalchemy
- frontend
    - JQuery
- Environment setting
    - ```sudo apt install python3-pip```
    - for python virtual environment
        - ```pip3 install virtualenv```
        - ```python3 -m virtualenv {path}```
        - ```source {path}/bin/activate```
    - for requirements
        - ```pip3 install fastapi[all]```
        - ```pip3 install uvicorn```
        - ```pip3 install sqlalchemy```
        - ```pip3 install fastapi-login```
        - ```SQLite Viewer``` vscode extension
- All requirements are already installed in "env"
    - ```source env/bin/activate```
- How to run
    1. Activate virtualenv
    2. Run ```uvicorn main:app --reload```
    3. Connect to "localhost:8000"