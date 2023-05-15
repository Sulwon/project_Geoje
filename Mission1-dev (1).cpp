/*헤더파일 선언 */
#include <stdio.h>
#include <windows.h>
#include <math.h>

/* 글자색상 함수선언*/
void color(int cnumber) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cnumber);
}

/* 'Say' 함수선언 */
void say(char* str, int delay) {
	for (int i = 0; i<strlen(str); i++) { //변수 'str' 의 길이수만큼 반복
		if(str[i] == '&') { //문자값이 '&' 일경우 
			int c = str[i + 1]; //'&'의 다음에있는 문자값을 정수형 함수 'c' 로 선언합니다.
			color((c >= 48 && c <= 57) * (c - 48) + (c >= 97 && c <= 102) * (c - 87)); //변수 'c'의 아스키코드값을 변환하여 'color' 함수에 색상을 선언합니다. 
			i += 1; //'&' 다음 문자의 출력을 방지합니다. 
			continue; //문자 '&' 출력을 방지합니다. 
		}
		printf("%c", str[i]); //문자를 한글자씩 출력합니다. 
		Sleep(delay); //문자출력의 지연시간을 설정합니다 
	}
}

/* 'setCourse' 함수선언 */
void setCourse(int* course, int section, int dest, int pass) {
	int connect[4][4] = { { 2,3,4 },{ 1,3,4 },{ 1,2,4 },{ 1,2,3 } }; //연결된경로 배열선언
	int now = (section % (int)pow(10, pass+1)) / (int)pow(10, pass);

	for (int i = 0; i < 3; i++) {
		int check = 0;
		for (int j = 3; j >= pass; j--) {
			if (connect[now - 1][i] == (section % (int)pow(10, j + 1)) / (int)pow(10, j)) {
				check = 1;
				break;
			}
		}
		if (check == 0) {
			if (connect[now - 1][i] == dest) {
				for (int k = 0; k < 5; k++) {
					if (course[k] == 0) {
						course[k] = section + connect[now - 1][i] * (int)pow(10, pass - 1);
						break;
					}
				}
			}
			else {
				setCourse(course, section + connect[now - 1][i] * (int)pow(10, pass - 1), dest, pass - 1);
			}
		}
	}
} 
/* 'travel' 함수선언 */
int travel(int course[], int time[], float dis[], int vehicle, int section) {
	int speed = 5; //'say'함수 출력속도 설정변수
	char* place[4] = { "고현 버스 터미널", "독봉산 웰빙 공원", "거제시공설운동장", "거제 포로 수용소" }; //장소명칭 배열설정
	char* trans[3] = { "자동차", "버스", "자전거" }; //이동수단 배열설정
	char* cmd[4] = {"start http://blog.naver.com/bk32167/220512498216", //관광지별 사진자료주소 배열설정
		"start http://blog.naver.com/bk32167/220513308079",
		"start http://blog.naver.com/s971227/90141467754",
		"start http://blog.naver.com/bk32167/220512961853"};

	system("cls"); //채팅로그를 청소합니다.
	if (course[section] == 0 || section == 4) { //모든코스를 끝냈을경우 
		printf("\n\n\n\n");
		say("\t&e ━━━　┃　┃　　　 　┃　   　 ┏━━┛　┃　 　┏━━━┛  &f\n",0);
		say("\t&e 　　　　┃　  ┃　　　　　┃ 　　　　　 　 ┃　 　┃          &f\n",0);
		say("\t&e 　━━　┃　┏┛　　┏━　┃　   ┏━━┛　  ┃ 　  ━━━┛  &f\n",0);
		say("\t&e 　　　　┃　┃　　━┛　━┛　 　　　　 　 ┏┛　　         　&f\n",0);
		say("\t&e 　　　━┛　┃　 ━━━━━┛　━━━━┛  ┃　　 ━━━━━┛&f\n\n",0);
		say("\n\t\t\t&f드디어 여행을 마쳤습니다!\n\n", speed);
		say("\t\t\t&f그동안 즐거우셨나요-? ^^\n\n", speed);
		say("\t\t\t&f이상, &e카스타드 &f여행사 였습니다!!\n\n\n", speed);
		say("\n\t&b[엔터]&f : 처음화면으로 가서 다시 여행!!\n\n", speed);
		say("  \t&c[ Ⅹ ]&f : 여행 그만할래요...\n\n", speed);
		say("   &a⊙ 입력 : ", speed); //재시작 , 프로그램 종료 선택을 요구합니다. 
		fflush(stdin);
		if(getchar() == '\n') { //입력한 값이 '엔터키' 일경우 
			system("cls");
			return 1; // 값을 '1' 로 반환합니다. 
		}
		else { // 그렇지 않을경우 
			color(0); //색상을 검은색으로 설정해서 cmd 고유의 종료메세지를 보이지않게합니다. 
			return 0; // 값을 '0' 으로 반환하여 프로그램을 종료시킵니다. 
		}
	}
	say("      &f┌┬─────────┬┐    ┌┬─────┬┐\n",0);
	say("      &f││    여행  경로    ││    ││ 교통수단 ││\n",0);
	say("      &f└┴─────────┴┘    └┴─────┴┘",0);

	for (int i = 0; i < 4; i++) {
		if (course[i] == 0) { //표시된 코스가 더이상 존재하지 않을경우 
			break; //'for' 문을 빠져나갑니다. 
		}
		char* v[3] = {"", "", ""};
		if (i == 0) {
			v[0] = "\t      ┏━━━━━┓";
			v[2] = "\t      ┗━━━━━┛";
			/* 앞서 지정해놓은 'vehicle' 변수에 따라 교통수단을 출력합니다. */ 
			switch (vehicle) {
			case 0:
				v[1] = "\t      ▶  자동차  ◀";
				break;
			case 1:
				v[1] = "\t      ▶  버  스  ◀";
				break;
			case 2:
				v[1] = "\t      ▶  자전거  ◀";
				break;
			}
		}
		
		if (section == i) { //진행중인 여행경로가 장소와 같은경우 
			printf("\n\t┏━━━━━━━━━┓%s\n", v[0]);
			printf("        ▶ %s ◀%s\n", place[course[i]-1], v[1]); //코스를 장소배열에 넣어 장소를 '두껍게' 출력합니다. 
			printf("\t┗━━━━━━━━━┛%s", v[2]);
		} else { //그렇지 않을경우 
			printf("\n\t┌─────────┐%s\n", v[0]);
			printf("\t│ %s │%s\n", place[course[i]-1], v[1]); //코스를 장소배열에 넣어 장소를 '얇게' 출력합니다. 
			printf("\t└─────────┘%s", v[2]);
		}
	}
	switch (course[section]) { //장소 'section' 함수에따른 코스 'course' 함수에 따라 장소의 설명문을 출력합니다. 
	case 1:
		say("\n\n\t&f거제의 중심 연결지! 터미널에 오신것을 환영합니다!\n", speed);
		break;
	case 2:
		say("\n\n\t&f거제의 아늑한 쉼터! 독봉산 웰빙 공원에 오신것을 환영합니다!\n", speed);
		break;
	case 3:
		say("\n\n\t&f거제의 체육 공간! 공설 운동장에 오신것을 환영합니다!\n", speed);
		break;
	case 4:
		say("\n\n\t&f거제의 아픈 역사의 공간! 포로 수용소에 오신것을 환영합니다!\n", speed);
		break;
	}
	say("\n\t&b[엔터]&f : 현재 위치 사진으로 감상\n\n", speed); 
	say("  \t&c[ Ⅹ ]&f : 다음 장소로 이동\n\n", speed);
	say("   &a⊙ 입력 : ", speed); //링크를 이용한 사진감상 , 다음 장소 이동을 요구합니다. 
	fflush(stdin);
	if(getchar() == '\n') { //입력한 값이 '엔터키' 일경우 
		system(cmd[course[section] - 1]); //현재 진행중인 장소의 링크를 실행시킵니다. 
		say("\t\t&f계속 하시려면 &b[엔터]&f를 눌러주세요...",0);
		getchar(); //'엔터키' 입력을 요구합니다. 
	}
	return travel(course, time, dis, vehicle, section + 1); //'travel' 함수값을 반환합니다. 
}
/* 메인함수 */
int main() {
	/* 기본변수 선언 */
	int speed = 5, start, dest, vehicle, error=0; //'say' 함수 출력속도 선언. 출발지, 목적지, 교통수단
	int time[3][6] = { {7, 6, 5, 6, 4, 4}, {21, 18, 20, 25, 16, 17}, {7, 8, 8, 9, 5, 5} }; // 자동차, 버스, 자전거의 이동시간 선언
	float dis[3][6] = { {2.53, 1.55, 2.06, 2.09, 1.71, 1.1}, {2.28, 1.42, 2.67, 2, 1.33, 1.48}, {1.79, 2.04, 1.94, 2.35, 1.24, 1.12} }; //자동차, 버스, 자전거의 이동거리 선언 
	char* place[4] = {"고현 버스 터미널", "독봉산 웰빙 공원", "거제시공설운동장", "거제 포로 수용소"}; //장소명칭 배열설정
	char* place_s[4] = {"터미널", " 공원 ", "운동장", "수용소"}; //출력명칭 배열설정
	char* trans[3] = {"자동차", "버스", "자전거"}; //교통수단 배열설정 
	int course[5] = {0, }; //경로 정수형변수선언 
	
	for (int i = 0; i < 4; i++) { //'for' 문을 총 3회 반복합니다.
		/* 'for' 문이 반복될때마다 출력합니다.*/
		say("\n\t&e카스타드 &f여행사에 오신것을 환영합니다!", speed * (i == 0) * (error == 0)); // 'speed * (i == 0)' -> 첫번째 'for' 반복문 에서만 딜레이를 speed(=20)으로 설정합니다. 
		say("\n\t&f여행지는 다음과 같습니다.\n\n", speed * (i == 0) * (error == 0));
		printf("\t┌────①────┐      ┌────②────┐\n");
		printf("\t│ 고현 버스 터미널 │───│ 독봉산 웰빙 공원 │\n");
		printf("\t└─────────┘┐    └─────────┘\n");
		printf("\t          │          └┐┌┘        │        \n");
		printf("\t          │          ┌┼┘          │        \n");
		printf("\t          │        ┌┘└┐          │        \n");
		printf("\t┌─────────┐    └┌─────────┐\n");
		printf("\t│ 거제시공설운동장 │───│ 거제 포로 수용소 │\n");
		printf("\t└────③────┘      └────④────┘\n\n");
		printf("\t┌─────┐┌──①──┬──②──┬──③──┐\n");
		printf("\t│ 교통수단 ││  자동차  │  버  스  │  자전거  │\n");
		printf("\t└─────┘└─────┴─────┴─────┘\n\n");
		say("\t&f여행경로의 &a<출발지> <목적지>&f 그리고\n\n", speed * (i == 0) * (error == 0));
		say("\t&a<교통수단>&f 을 &b[번호]&f로 입력해주세요.\n\n", speed * (i == 0) * (error == 0));

		switch (i) { //'for' 반복문 내에서 첫번째, 두번째, 마지막의 순서를 정합니다. 
		case 0: //첫번째 'for' 반복문 (i=0)
			if(error == 1) { say("   &c[!] 여행지는 ①부터 ④까지 있습니다.\n",0); } //에러값이 1로 '활성화' 되어있을경우 오류메세지를 출력합니다.
			else { printf("\n"); }
			say("   &a<출발지 : ", speed * (error == 0));
			color(10); //입력값 색상을 초록색으로 지정합니다. 
			scanf("%d", &start); //출발지 입력을 요구합니다
			color(7);
			fflush(stdin); //잔여버퍼를 제거합니다.
			error = 0; //에러를 '비활성화' 합니다. 
			if (start < 1 || start > 4) { //입력한 값이 1~4가 아닐경우
				error = 1; //에러1로 '활성화' 합니다.
				i -= 1;
			}
			system("cls"); //채팅로그를 청소합니다.
			break; //구문을 빠져나옵니다.

		case 1: //두번째 'for' 반복문 (i == 1)
			if(error == 1) { say("   &c[!] 여행지는 ①부터 ④까지 있습니다.\n",0); } //에러값이 1로 '활성화' 되어있을경우 오류메세지를 출력합니다.
			else if(error == 2) { say("   &c[!] 목적지가 출발지와 같은 장소가 될 수 없습니다.\n",0); } //에러값이 2로 '활성화' 되어있을경우 오류메세지를 출력합니다.
			else { printf("\n"); }
			color(10); //입력값 색상을 초록색으로 지정합니다. 
			printf("   <출발지 : %s>", place_s[start - 1]); //입력된 출발지 변수를 'place' 배열에서 찾아 한글로 변환하여 출력합니다.
			color(7);
			say("   &a<목적지 : ", speed * (error == 0)); //목적지 입력을 요구합니다.
			color(10); //입력값 색상을 초록색으로 지정합니다. 
			scanf("%d", &dest);
			color(7);
			fflush(stdin); //잔여버퍼를 제거합니다.
			error = 0;
			if (dest < 1 || dest > 4) { //입력한 값이 1~4가 아닐경우
				error = 1; //에러1로 '활성화' 합니다. 
				i -= 1; 
			}
			if (dest == start) { //목적지 값이 출발지값과 같은경우 
				error = 2; //에러2로 '활성화' 합니다. 
				i -= 1;
			}
			system("cls"); //채팅로그를 청소합니다. 
			break; //구문을 빠져나옵니다.

		case 2: //세번째 'for' 반복문 (i == 2)
			if(error == 1) { say("   &c[!] 교통수단은 ①부터 ③까지 있습니다.\n",0); } //에러값이 1로 '활성화' 되어있을경우 오류메세지를 출력합니다. 
			else { printf("\n"); }
			color(10); //출력값 색상을 초록색으로 지정합니다. 
			printf("   <출발지 : %s>", place_s[start - 1]); //출발지에서 입력한 값을 'place'배열에서 찾아 출력합니다.
			printf("   <목적지 : %s>", place_s[dest - 1]); //목적지에서 입력한 값을 'place'배열에서 찾아 출력합니다.
			color(7);
			say("   &a<교통수단 : ", speed * (error == 0)); //에러가 발생할경우 'say' 함수의 출력딜레이를 제거합니다. 
			color(10); //입력값 색상을 초록색으로 지정합니다. 
			scanf("%d", &vehicle); //교통수단 입력을 요구합니다.
			color(7);
			fflush(stdin); //잔여버퍼를 제거합니다.
			if (vehicle < 1 || vehicle > 3) { //입력한 값이 1~3이 아닐경우
				error = 1; //에러1로 '활성화' 합니다.
				i -= 1;
			}
			system("cls"); //채팅로그를 청소합니다.
			break; //구문을 빠져나옵니다.

		case 3: //세번째 'for' 반복문 (i == 2) 
			system("cls");
			color(10);
			printf("   <출발지 : %s>", place_s[start - 1]); //출발지에서 입력한 값을 'place'배열에서 찾아 출력합니다.
			printf("   <목적지 : %s>", place_s[dest - 1]); //목적지에서 입력한 값을 'place'배열에서 찾아 출력합니다.
			printf("   <교통수단 : %s>\n\n", trans[vehicle - 1]); //교통수단에 입력한 값을 'trans'배열에서 찾아 출력합니다. 
			color(7);
			break; //구문을 빠져나옵니다.
		}
	} // 'for' 반복문이 종료됩니다.

	setCourse(course, start * 1000, dest, 3); //
	for (int i = 0; i < 5; i++) { //'for' 문을 총 5회 반복합니다.
		int c[4] = { start, 0, }, total_t = 0;
		char* num[5] = { "①", "②", "③", "④", "⑤" };
		float total_d = 0;
		color(15);
		printf("\t┌────┐ 노선 : %s", place_s[start - 1]);
		for (int j = 2; j>=0; j--) {
			c[3-j] = (course[i] % (int)pow(10, j + 1)) / (int)pow(10, j);
			if (c[3-j] == 0) {
				break;
			}
			printf(" - %s", place_s[c[3 - j] - 1]);
		}
		color(15);
		printf("\n\t│  경로  │ 시간 : ");
		for (int j = 0; j < 3; j++) {
			if (c[j + 1] == 0) {
				for(int k = 0; k < 3 - j; k++) {
					printf("   \t");
				}
				break;
			}
			int t = time[vehicle - 1][c[j] + c[j + 1] - (c[j] == 1 || c[j + 1] == 1) - 2];
			total_t += t;
			color(15);
			printf("      %d분", t);
		}
		color(8);
		printf(" \t(총 %d분)", total_t);
		color(7);
		printf("\n\t│   %s   │ 거리 :    ", num[i]);
		for (int j = 0; j < 3; j++) {
			if (c[j + 1] == 0) {
				for(int k = 0; k < 3 - j; k++) {
					printf("\t");
				}
				break;
			}
			float d = dis[vehicle - 1][c[j] + c[j + 1] - (c[j] == 1 || c[j + 1] == 1) - 2];
			total_d += d;
			printf("   %.2fkm", d);
		}
		color(8);
		printf("\t(총 %.2fkm)\n", total_d);
		color(7);
		printf("\t└────┘\n");
	}
	say("\t&f여행하고자 하는 경로의 &b[번호]&f를 입력해주세요.\n", speed);

	int select; //경로변수 선언
	do {
		say("   &a⊙ 경로선택 : ", speed); //경로 입력을 요구합니다.
		scanf("%d", &select);
		fflush(stdin); //잔여버퍼를 제거합니다.

					   /* 입력한 값이 1~5가 아닐경우 재출력메세지를 보냅니다.*/
		if (select < 1 || select > 5) {
			color(12); //색상을 연한 붉은색으로 설정합니다.
			printf("   [!] 여행경로는 ①부터 ⑤까지 있습니다.\n"); //경고문을 출력합니다. 
			color(7); //색상을 원래대로 돌립니다. 
		}
	} while (select < 1 || select > 5); //여행경로 입력값이 1~5 일경우
	say("\n\t&b[엔터]&f를 눌러주시면 여행을 시작합니다...\n&f",0);
	getchar();

	int c[4] = { start,  0, }, t[4] = { 0, };
	float d[4] = { 0, };
	for (int i = 2; i >= 0; i--) {
		c[3 - i] = (course[i] % (int)pow(10, i + 1)) / (int)pow(10, i);
		if (c[3 - i] == 0) {
			break;
		}
	}
	for (int i = 0; i < 3; i++) {
		c[i + 1] = (course[select-1] % (int)pow(10, 3 - i)) / (int)pow(10, 2 - i);
		if (c[i + 1] == 0) {
			break;
		}
		t[i] = time[vehicle - 1][c[i] + c[i + 1] - (c[i] == 1 || c[i + 1] == 1) - 2];
		d[i] = dis[vehicle - 1][c[i] + c[i + 1] - (c[i] == 1 || c[i + 1] == 1) - 2];
	}
	if (travel(c, t, d, vehicle - 1, 0) == 1) { // 'travel' 반환값이 1일 경우 
		main(); // 메인함수를 재시작합니다. 
	}
	return 0;
}
