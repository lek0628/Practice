#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_MEMBERS 10
#define MAX_QUESTIONS 5
#define MAX_ANSWERS 3
#define MAX_NICKNAME 20
#define MAX_TRAUMA 100
#define MAX_RESPONSE 101

// 트라우마 구조체
typedef struct {
    char nickname[MAX_NICKNAME];
    int age;
    char trauma[MAX_TRAUMA];
} TraumaInfo;

// 질문 구조체
typedef struct {
    int id;
    char question[200];
} Question;

// 상담 구조체
typedef struct {
    char nickname[MAX_NICKNAME];
    char question[200];
    char answer[MAX_RESPONSE];
} Counseling;

TraumaInfo traumaMembers[MAX_MEMBERS];
Question questions[MAX_QUESTIONS] = {
    {1, "어떤 상황에서 그 트라우마를 경험하셨나요?"},
    {2, "해당 상황이 당신의 일상생활과 감정에 어떤 영향을 미치고 있나요?"},
    {3, "이 트라우마를 어떻게 극복하려고 노력하셨나요?"},
    {4, "트라우마와 관련하여 어떤 감정을 느끼고 계신가요?"},
    {5, "트라우마를 극복하기 위해 어떤 지원이 필요한 것으로 생각하시나요?"}
};
Counseling counselingSessions[MAX_MEMBERS * MAX_ANSWERS];
int counselingCount = 0;
int traumaCount = 0;

void inputTrauma() {
    char nickname[MAX_NICKNAME];
    while (1) {
        printf("\n닉네임 입력 (종료하려면 Q 입력): ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = '\0';
        if (strcasecmp(nickname, "Q") == 0) break;

        int found = -1;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(traumaMembers[i].nickname, nickname) == 0) {
                found = i;
                break;
            }
        }

        found = (found == -1) ? -1 : found;

        (found == -1) ? printf("닉네임을 찾을 수 없습니다. 다시 시도하세요.\n") : ({
            printf("트라우마 내용 입력: ");
            fgets(traumaMembers[found].trauma, MAX_TRAUMA, stdin);
            traumaMembers[found].trauma[strcspn(traumaMembers[found].trauma, "\n")] = '\0';
            printf("입력 완료\n");
        });
    }
}

void startCounseling() {
    printf("\n[상담 가능한 멤버 목록]\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strlen(traumaMembers[i].trauma) > 0) {
            printf("- %s\n", traumaMembers[i].nickname);
        }
    }
    char nickname[MAX_NICKNAME];
    printf("\n상담할 닉네임 입력: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = '\0';

    int memberIndex = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(traumaMembers[i].nickname, nickname) == 0 && strlen(traumaMembers[i].trauma) > 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("해당 멤버를 찾을 수 없습니다.\n");
        return;
    }

    srand((unsigned int)time(NULL));
    int used[MAX_QUESTIONS] = {0};
    int questionIndices[MAX_ANSWERS];
    int qCount = 0;
    while (qCount < MAX_ANSWERS) {
        int r = rand() % MAX_QUESTIONS;
        if (!used[r]) {
            used[r] = 1;
            questionIndices[qCount++] = r;
        }
    }

    for (int i = 0; i < MAX_ANSWERS; i++) {
        char answer[MAX_RESPONSE];
        while (1) {
            printf("Q%d: %s\n> ", questions[questionIndices[i]].id, questions[questionIndices[i]].question);
            fgets(answer, sizeof(answer), stdin);
            answer[strcspn(answer, "\n")] = '\0';
            if (strlen(answer) == 0 || strlen(answer) > 100) {
                printf("답변은 1자 이상 100자 이하로 입력하세요.\n");
            } else break;
        }
        strcpy(counselingSessions[counselingCount].nickname, traumaMembers[memberIndex].nickname);
        strcpy(counselingSessions[counselingCount].question, questions[questionIndices[i]].question);
        strcpy(counselingSessions[counselingCount].answer, answer);
        counselingCount++;
    }
    printf("상담 세션이 완료되었습니다.\n");
}

void viewCounselingResult() {
    char nickname[MAX_NICKNAME];
    printf("\n상담 결과를 조회할 닉네임 입력: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = '\0';

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(traumaMembers[i].nickname, nickname) == 0) {
            printf("\n[%s님의 상담 정보]\n트라우마: %s\n", nickname, traumaMembers[i].trauma);
            for (int j = 0; j < counselingCount; j++) {
                if (strcmp(counselingSessions[j].nickname, nickname) == 0) {
                    printf("Q: %s\nA: %s\n", counselingSessions[j].question, counselingSessions[j].answer);
                }
            }
            return;
        }
    }
    printf("해당 닉네임의 상담 정보를 찾을 수 없습니다.\n");
}

void traumaMenu() {
    int choice;
    while (1) {
        printf("\n===== 트라우마 관리 메뉴 =====\n");
        printf("1. 트라우마 입력\n");
        printf("2. 상담 세션 시작\n");
        printf("3. 상담 결과 조회\n");
        printf("0. 뒤로 가기\n");
        printf("선택: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: inputTrauma(); break;
            case 2: startCounseling(); break;
            case 3: viewCounselingResult(); break;
            case 0: return;
            default: printf("잘못된 선택입니다.\n");
        }
    }
}

void initializeMembers() {
    strcpy(traumaMembers[0].nickname, "Neo"); traumaMembers[0].age = 23;
    strcpy(traumaMembers[1].nickname, "Trin"); traumaMembers[1].age = 22;
    strcpy(traumaMembers[2].nickname, "Morpheus"); traumaMembers[2].age = 30;
    strcpy(traumaMembers[3].nickname, "Zion"); traumaMembers[3].age = 21;
    strcpy(traumaMembers[4].nickname, "Oracle"); traumaMembers[4].age = 40;
    strcpy(traumaMembers[5].nickname, "Tank"); traumaMembers[5].age = 28;
    strcpy(traumaMembers[6].nickname, "Dozer"); traumaMembers[6].age = 27;
    strcpy(traumaMembers[7].nickname, "Switch"); traumaMembers[7].age = 25;
    strcpy(traumaMembers[8].nickname, "Apoc"); traumaMembers[8].age = 24;
    strcpy(traumaMembers[9].nickname, "Mouse"); traumaMembers[9].age = 20;
}

int main() {
    initializeMembers();
    traumaMenu();
    return 0;
}
