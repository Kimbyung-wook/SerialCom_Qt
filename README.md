# SerialCom_Qt
유명한 프로그램인 SerialCom을 Qt로 만들어보는 중이다.<br>
SerialCom은 임베디드 시스템을 다루는 사람들에게 익숙하고 쉽게 접하는 프로그램이며, Serial communication program 을 검색하다보면 쉽게 찾을 수 프로그램이다.<br>
SerialCom은 NINETY SYSTEM 이라는 국내 회사에서 2000년에 개발되었으며 해당 회사의 주소는 다음과 같다.<br>
http://www.ninety.co.kr/ <br>
![image](https://user-images.githubusercontent.com/14835344/111903390-6bdf1e80-8a85-11eb-9ab0-319ce447c252.png)

본 저장소는 Qt를 공부하는 겸, SerialCom의 UI와 기능을 따라 만들어보도록 하려고 한다.<br>

### 구현된 기능 ###
현재 Rx Section과 Tx Section의 기본 기능이 구현되어있다.<br>
1초 주기로 사용 가능한 직렬 포트를 검색하여 목록화해주며,<br>
사용가능한 직렬 포트가 있을 때, 포트를 선택하여 열어볼 수 있다.<br>

### 미구현 기능과 버그###
Tx Section의 Radio button인 "Auto", Check box인 "Send Data Repeatly"의 기능은 구현되어있지 않다.<br>
menubar의 action들은 구현되어있지 않다.<br>
Carriage Return과 Line Feed 가 보내는 것은 되는데, 출력창에 제대로 표시되지 않는다.
