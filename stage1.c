#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TRAINING 8

// 훈련 상태 저장: 'N' = 미실시, 'P' = 통과, 'F' = 실패
char trainingStatus[MAX_TRAINING] = { 'N','N','N','N','N','N','N','N' };

// 메뉴 문자열 배열 (보너스 조건: 2차원 배열)
const char *mainMenu[] = {
    "I. 오디션 관리",
    "II. 훈련",
    "III. 데뷔"
};

const char *trainingMenu[] = {
    "1. 체력과 지식",
    "2. 자기관리 및 팀워크",
    "3. 언어 및 발음",
    "4. 보컬",
    "5. 댄스",
    "6. 비주얼 및 이미지",
    "7. 연기 및 무대 퍼포먼스",
    "8. 팬 소통"
};

// ===== 함수 선언 =====
void showMainMenu();
void showTrainingMenu();
void handleTraining(int index);
int isAllowedTraining(int index);
int isAllPassedBefore(int index);
void clearInputBuffer();

// ===== 메인 함수 =====
int main() {
    char input[10];

    while (1) {
        showMainMenu();
        printf("메뉴 선택 (0/Q/q/Enter = 종료): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || input[0] == '0' ||
            tolower(input[0]) == 'q') {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        switch (input[0]) {
            case '1':
                printf(">> 오디션 관리 기능 (미구현)\n");
                break;
            case '2':
                showTrainingMenu();
                break;
            case '3':
                printf(">> 데뷔 기능 (미구현)\n");
                break;
            default:
                printf("잘못된 입력입니다.\n");
        }
    }

    return 0;
}

// ===== 메인 메뉴 출력 =====
void showMainMenu() {
    printf("\n========= 프로그램 마그라테아 =========\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, mainMenu[i]);
    }
    printf("=====================================\n");
}

// ===== 훈련 메뉴 출력 및 선택 =====
void showTrainingMenu() {
    char input[10];

    while (1) {
        printf("\n======= 훈련 메뉴 =======\n");
        for (int i = 0; i < MAX_TRAINING; i++) {
            printf("%d. %s [%c]\n", i + 1, trainingMenu[i], trainingStatus[i]);
        }
        printf("0. 상위 메뉴로\n");
        printf("=========================\n");
        printf("훈련을 선택하세요: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0') return;

        int choice = input[0] - '0';
        if (choice < 1 || choice > MAX_TRAINING) {
            printf("잘못된 선택입니다.\n");
            continue;
        }

        if (!isAllowedTraining(choice - 1)) {
            printf("해당 훈련은 아직 선택할 수 없습니다.\n");
            continue;
        }

        if (trainingStatus[choice - 1] == 'P') {
            printf("이미 통과한 훈련입니다.\n");
            continue;
        }

        handleTraining(choice - 1);  // 인덱스 전달
    }
}

// ===== 훈련 선택 가능 여부 확인 =====
int isAllowedTraining(int index) {
    if (index == 0) return 1; // 첫 번째는 언제나 허용
    return (trainingStatus[index - 1] == 'P');
}

// ===== 훈련 진행 처리 =====
void handleTraining(int index) {
    char answer[10];

    printf(">> [%s] 평가 결과를 입력하시겠습니까? (Y/N): ", trainingMenu[index]);
    fgets(answer, sizeof(answer), stdin);

    if (tolower(answer[0]) == 'y') {
        printf("훈련을 마치고 인증에 통과했나요? (P/F): ");
        fgets(answer, sizeof(answer), stdin);

        if (toupper(answer[0]) == 'P' || toupper(answer[0]) == 'F') {
            trainingStatus[index] = toupper(answer[0]);
            printf("결과가 저장되었습니다.\n");
        } else {
            printf("잘못된 입력입니다. 훈련 메뉴로 돌아갑니다.\n");
        }
    } else {
        printf("훈련 메뉴로 돌아갑니다.\n");
    }
}
