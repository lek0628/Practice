#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MEMBER_COUNT 3
#define FIELD_COUNT 8  // 7개 체력 항목 + 닉네임

// 밀리웨이즈 멤버 이름과 닉네임
const char *milliways_members[MEMBER_COUNT][2] = {
    {"박지연", "jiyeon"},
    {"Ethan Smith", "ethan"},
    {"김하늘", "sky"}
};

// 체력 항목명
const char *fitness_fields[7] = {
    "1마일 러닝 (분)",
    "100m 스프린트 (초)",
    "푸시업 30회 (분)",
    "스쿼트 50회 (분)",
    "팔굽혀펴기 50회 (분)",
    "수영 400m (분)",
    "무게 들기 (배수)"
};

// 체력 데이터 배열: [멤버 수][항목 수 + 닉네임]
char health_scores[MEMBER_COUNT][FIELD_COUNT][30];

// === [A] 체력 상태 입력 함수 ===
void setHealth() {
    char input[256];
    printf("\n=== 체력 상태 입력 ===\n");

    for (int i = 0; i < MEMBER_COUNT; i++) {
        printf("\n[%s (%s)]의 7개 체력 항목 데이터를 입력하세요\n", 
                milliways_members[i][0], milliways_members[i][1]);
        printf("형식: 1마일,100m,푸시업,스쿼트,팔굽혀펴기,수영,무게 : ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // 개행 제거

        char *token = strtok(input, ",");
        int field_index = 0;

        while (token && field_index < 7) {
            strncpy(health_scores[i][field_index], token, 29);
            health_scores[i][field_index][29] = '\0';
            token = strtok(NULL, ",");
            field_index++;
        }

        if (field_index != 7) {
            printf("❌ 입력 항목이 부족합니다. 다시 시도하세요.\n");
            i--; // 현재 멤버 다시 입력
            continue;
        }

        // 닉네임 저장
        strncpy(health_scores[i][7], milliways_members[i][1], 29);
        health_scores[i][7][29] = '\0';
    }

    printf("\n✅ 모든 체력 데이터를 입력받았습니다.\n");
}

// === [B] 체력 상태 조회 함수 ===
void getHealth() {
    char input[50];
    printf("\n=== 체력 상태 조회 ===\n");
    printf("특정 멤버 닉네임 입력 (전체 조회는 ENTER): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        // 전체 출력
        for (int i = 0; i < MEMBER_COUNT; i++) {
            printf("\n[%s (%s)]\n", milliways_members[i][0], milliways_members[i][1]);
            for (int j = 0; j < 7; j++) {
                printf("%s: %s\n", fitness_fields[j], health_scores[i][j]);
            }
        }
    } else {
        // 특정 닉네임 출력
        int found = 0;
        for (int i = 0; i < MEMBER_COUNT; i++) {
            if (strcmp(health_scores[i][7], input) == 0) {
                found = 1;
                printf("\n[%s (%s)] 체력 상태\n", milliways_members[i][0], input);
                for (int j = 0; j < 7; j++) {
                    printf("%s: %s\n", fitness_fields[j], health_scores[i][j]);
                }
                break;
            }
        }

        if (!found) {
            printf("❌ 해당 닉네임의 데이터를 찾을 수 없습니다.\n");
        }
    }
}

// === [1-1] 체력과 지식 메뉴 ===
void fitnessMenu() {
    char choice[10];
    while (1) {
        printf("\n[훈련 > 1. 체력과 지식]\n");
        printf("A. 체력 상태 입력\n");
        printf("B. 체력 상태 조회\n");
        printf("0. 이전 메뉴로\n");
        printf("선택: ");
        fgets(choice, sizeof(choice), stdin);

        switch (toupper(choice[0])) {
            case 'A': setHealth(); break;
            case 'B': getHealth(); break;
            case '0': return;
            default: printf("❌ 올바른 메뉴를 선택하세요.\n");
        }
    }
}

// === [II] 훈련 메뉴 ===
void trainingMenu() {
    char choice[10];
    while (1) {
        printf("\n[II. 훈련 메뉴]\n");
        printf("1. 체력과 지식\n");
        printf("0. 이전 메뉴로\n");
        printf("선택: ");
        fgets(choice, sizeof(choice), stdin);

        switch (choice[0]) {
            case '1': fitnessMenu(); break;
            case '0': return;
            default: printf("❌ 유효한 메뉴 번호를 선택하세요.\n");
        }
    }
}

// === [I] 오디션 관리 메뉴 (임시) ===
void auditionMenu() {
    printf("\n[오디션 관리 기능은 아직 구현되지 않았습니다.]\n");
}

// === [III] 데뷔 메뉴 (임시) ===
void debutMenu() {
    printf("\n[데뷔 기능은 아직 구현되지 않았습니다.]\n");
}

// === [Main] 주 메뉴 ===
void mainMenu() {
    char choice[10];

    while (1) {
        printf("\n====== 마그라테아 ======\n");
        printf("I. 오디션 관리\n");
        printf("II. 훈련\n");
        printf("III. 데뷔\n");
        printf("Q. 종료\n");
        printf("========================\n");
        printf("메뉴를 선택하세요: ");

        fgets(choice, sizeof(choice), stdin);
        switch (toupper(choice[0])) {
            case 'I': auditionMenu(); break;
            case 'I' - 'A' + '1': auditionMenu(); break;
            case 'I' - 'A' + '2': trainingMenu(); break;
            case 'I' - 'A' + '3': debutMenu(); break;
            case '1': auditionMenu(); break;
            case '2': trainingMenu(); break;
            case '3': debutMenu(); break;
            case 'Q': case 'q': case '0':
                printf("👋 프로그램을 종료합니다.\n");
                return;
            default: printf("❌ 올바른 메뉴를 선택하세요.\n");
        }
    }
}

// === 진입점 ===
int main() {
    mainMenu();
    return 0;
}
