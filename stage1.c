#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 10
#define DAYS_IN_WEEK 6
#define MAX_STRING 50

// ──────────────────────── 전역 배열 선언 ────────────────────────

// 멤버 이름과 닉네임
char milliways_members[MAX_MEMBERS][2][MAX_STRING] = {
    {"Alice", "A1"}, {"Bob", "B2"}, {"Charlie", "C3"},
    {"Diana", "D4"}, {"Eve", "E5"}, {"Frank", "F6"},
    {"Grace", "G7"}, {"Heidi", "H8"}, {"Ivan", "I9"}, {"Judy", "J10"}
};

// 체력 점수 저장 배열
char health_scores[MAX_MEMBERS][8][MAX_STRING]; // 7개 항목 + 닉네임

// 운동 유형
const char *exercise_types[][3] = {
    {"러닝", "자전거", "빠른 걷기"},   // 유산소
    {"푸시업", "스쿼트"},             // 전신 근력
    {"레그 프레스", "레그 컬"},        // 하체 근력
    {"철봉", "풀업 바"},             // 상체 근력
    {"플랭크", "크런치"}             // 코어
};

// 멤버별 운동 루틴
char member_routine[MAX_MEMBERS][DAYS_IN_WEEK][MAX_STRING];

// 훈련 통과 상태
char training_result[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// ──────────────────────── 공통 유틸 ────────────────────────

void showMembers() {
    printf("\n[ 멤버 목록 ]\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("  %d. %s (%s)\n", i + 1, milliways_members[i][0], milliways_members[i][1]);
    }
    printf("\n");
}

// ──────────────────────── 체력 상태 입력 ────────────────────────

void setHealth() {
    char nickname[MAX_STRING], input[MAX_STRING];
    int memberIndex = -1;

    showMembers();
    printf("체력 데이터를 입력할 멤버 닉네임을 입력하세요: ");
    scanf("%s", nickname);

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_members[i][1], nickname) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("닉네임을 찾을 수 없습니다.\n");
        return;
    }

    printf("7가지 체력 데이터를 쉼표로 구분해 입력하세요.\n");
    printf("입력 순서: 1마일 러닝, 스프린트, 푸시업, 스쿼트, 팔굽혀펴기, 수영, 무게들기\n");
    printf("예시 입력: 10.2, 12.5, 2.3, 2.7, 2.4, 6.8, 1.2\n");
    scanf(" %[^\n]", input);

    char *token = strtok(input, ",");
    int col = 0;
    while (token && col < 7) {
        strncpy(health_scores[memberIndex][col], token, MAX_STRING);
        token = strtok(NULL, ",");
        col++;
    }

    strncpy(health_scores[memberIndex][7], nickname, MAX_STRING);
    printf("체력 데이터가 저장되었습니다.\n");
}

// ──────────────────────── 체력 상태 조회 ────────────────────────

void getHealth() {
    char nickname[MAX_STRING];
    printf("조회할 멤버 닉네임을 입력하세요 (전체: all): ");
    scanf("%s", nickname);

    if (strcmp(nickname, "all") == 0) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("%s (%s): ", milliways_members[i][0], milliways_members[i][1]);
            for (int j = 0; j < 7; j++) {
                printf("%s ", health_scores[i][j]);
            }
            printf("\n");
        }
    } else {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(milliways_members[i][1], nickname) == 0) {
                printf("%s (%s): ", milliways_members[i][0], nickname);
                for (int j = 0; j < 7; j++) {
                    printf("%s ", health_scores[i][j]);
                }
                printf("\n");
                return;
            }
        }
        printf("해당 닉네임을 찾을 수 없습니다.\n");
    }
}

// ──────────────────────── 운동 루틴 설정 ────────────────────────

void setExerciseRoutine() {
    char name[MAX_STRING], cardio[MAX_STRING], strength[MAX_STRING];
    int memberIndex = -1, coreCount = 0;

    showMembers();
    printf("운동 루틴을 설정할 멤버 이름을 입력하세요: ");
    scanf("%s", name);

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_members[i][0], name) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("해당 멤버를 찾을 수 없습니다.\n");
        return;
    }

    for (int d = 0; d < DAYS_IN_WEEK; d++) {
        printf("\n%s요일 운동 루틴 설정:\n", (char*[]){"월", "화", "수", "목", "금", "토"}[d]);

        printf("  유산소 운동 선택 (러닝/자전거/빠른 걷기): ");
        scanf("%s", cardio);

        printf("  근력 또는 코어 운동 선택: ");
        scanf("%s", strength);

        if (strcmp(strength, "플랭크") == 0 || strcmp(strength, "크런치") == 0) {
            if (coreCount >= 1) {
                printf("  코어 운동은 주 1회만 가능합니다. 다시 입력하세요.\n");
                d--; continue;
            } else {
                coreCount++;
            }
        }

        snprintf(member_routine[memberIndex][d], MAX_STRING, "%s, %s", cardio, strength);
    }

    printf("\n운동 루틴이 저장되었습니다!\n");
}

// ──────────────────────── 운동 루틴 조회 ────────────────────────

void getExerciseRoutine() {
    char name[MAX_STRING];
    int memberIndex = -1;

    printf("운동 루틴을 조회할 멤버 이름을 입력하세요: ");
    scanf("%s", name);

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_members[i][0], name) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("해당 멤버를 찾을 수 없습니다.\n");
        return;
    }

    printf("\n%s (%s)님의 운동 루틴:\n", 
        milliways_members[memberIndex][0], 
        milliways_members[memberIndex][1]);

    for (int d = 0; d < DAYS_IN_WEEK; d++) {
        printf("  %s요일: %s\n", 
            (char*[]){"월", "화", "수", "목", "금", "토"}[d],
            member_routine[memberIndex][d]);
    }
}

// ──────────────────────── 훈련 메뉴 ────────────────────────

void trainingMenu() {
    char choice;
    while (1) {
        printf("\n[II. 훈련 메뉴]\n");
        printf("1. 체력과 지식\n");
        printf("2. 자기관리 및 팀워크\n");
        printf("3. 언어 및 발음\n");
        printf("4. 보컬\n");
        printf("5. 댄스\n");
        printf("6. 비주얼 및 이미지\n");
        printf("7. 연기 및 무대 퍼포먼스\n");
        printf("8. 팬 소통\n");
        printf("Q. 상위 메뉴로\n");
        printf("선택: ");
        scanf(" %c", &choice);

        if (choice == '1') {
            char sub;
            while (1) {
                printf("\n[1. 체력과 지식 서브 메뉴]\n");
                printf("A. 체력 상태 입력\n");
                printf("B. 체력 상태 조회\n");
                printf("C. 기초 운동 루틴 설정\n");
                printf("D. 기초 운동 루틴 조회\n");
                printf("Q. 상위 메뉴로\n");
                printf("선택: ");
                scanf(" %c", &sub);
                if (sub == 'A') setHealth();
                else if (sub == 'B') getHealth();
                else if (sub == 'C') setExerciseRoutine();
                else if (sub == 'D') getExerciseRoutine();
                else if (sub == 'Q' || sub == 'q') break;
                else printf("잘못된 선택입니다.\n");
            }
        } else if (choice == 'Q' || choice == 'q') {
            break;
        } else {
            printf("현재 구현되지 않은 메뉴입니다.\n");
        }
    }
}

// ──────────────────────── 메인 메뉴 ────────────────────────

int main() {
    char choice;
    while (1) {
        printf("\n[ 마그라테아 시스템 ]\n");
        printf("I. 오디션 관리\n");
        printf("II. 훈련\n");
        printf("III. 데뷔\n");
        printf("Q. 종료\n");
        printf("선택: ");
        scanf(" %c", &choice);

        if (choice == 'I' || choice == 'i') {
            printf("오디션 관리 기능은 아직 구현되지 않았습니다.\n");
        } else if (choice == 'II' || choice == 'i') {
            trainingMenu();
        } else if (choice == 'III' || choice == 'i') {
            printf("데뷔 기능은 아직 구현되지 않았습니다.\n");
        } else if (choice == 'Q' || choice == 'q' || choice == '0') {
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}
