#include <stdio.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define MAX_NAME_LEN 50
#define FIELD_LEN 20

typedef struct {
    char name[MAX_NAME_LEN];
    int id;
} Candidate;

typedef struct {
    int id;
    int music;
    int dance;
    int vocal;
    int visual;
    int delivery;
    int total;
} ScoringSheet;

void clear_input_buffer() {
    while (getchar() != '\n');
}

int get_valid_score(const char *field) {
    int score;
    while (1) {
        printf("%s: ", field);
        if (scanf("%d", &score) == 1 && score >= 10 && score <= 100) {
            break;
        } else {
            printf(">> 잘못된 값입니다. 10~100 사이의 숫자를 입력하세요.\n");
            clear_input_buffer();
        }
    }
    return score;
}

int main() {
    Candidate candidates[NUM_CANDIDATES] = {
        {"박지연", 100001},
        {"Ethan Smith", 100002},
        {"김서연", 100003},
        {"Liam Johnson", 100004},
        {"최민수", 100005},
        {"Emma Lee", 100006}
    };

    ScoringSheet sheets[NUM_CANDIDATES];

    char judge_name[MAX_NAME_LEN];
    char specialty[FIELD_LEN];
    char confirm;

    while (1) {
        printf("####################################\n");
        printf("#       오디션 심사 결과 입력       #\n");
        printf("####################################\n");

        printf("> 심사위원 이름: ");
        scanf("%s", judge_name);

        printf("> 전문 분야 (음악, 댄스, 보컬, 비주얼, 전달력): ");
        scanf("%s", specialty);

        printf("++++++++++++++++++++++++++++++++++++\n");

        // 점수 입력 초기화
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            sheets[i].id = candidates[i].id;
            sheets[i].music = sheets[i].dance = sheets[i].vocal = 0;
            sheets[i].visual = sheets[i].delivery = 0;
            sheets[i].total = 0;

            printf("후보자: %s\n", candidates[i].name);

            if (strcmp(specialty, "음악") == 0) {
                sheets[i].music = get_valid_score("음악 소양");
            } else if (strcmp(specialty, "댄스") == 0) {
                sheets[i].dance = get_valid_score("댄스");
            } else if (strcmp(specialty, "보컬") == 0) {
                sheets[i].vocal = get_valid_score("보컬");
            } else if (strcmp(specialty, "비주얼") == 0) {
                sheets[i].visual = get_valid_score("비주얼");
            } else if (strcmp(specialty, "전달력") == 0) {
                sheets[i].delivery = get_valid_score("전달력");
            } else {
                printf(">> 올바르지 않은 분야입니다. 프로그램을 다시 시작하세요.\n");
                return 1;
            }
            printf("------------------------------------\n");
        }

        // 결과 출력
        printf("++++++++++++++++++++++++++++++++++++\n");
        printf("입력을 모두 완료했습니다.\n");
        printf("입력하신 내용을 검토하세요!\n");
        printf("------------------------------------\n");

        for (int i = 0; i < NUM_CANDIDATES; i++) {
            int score = 0;
            if (strcmp(specialty, "음악") == 0) score = sheets[i].music;
            else if (strcmp(specialty, "댄스") == 0) score = sheets[i].dance;
            else if (strcmp(specialty, "보컬") == 0) score = sheets[i].vocal;
            else if (strcmp(specialty, "비주얼") == 0) score = sheets[i].visual;
            else if (strcmp(specialty, "전달력") == 0) score = sheets[i].delivery;

            printf("%s: %d\n", candidates[i].name, score);
        }

        printf("제출하시겠습니까? (Y/N): ");
        clear_input_buffer();
        scanf("%c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            printf("***최종 제출을 완료했습니다.***\n");
            break;
        } else {
            printf(">> 처음부터 다시 입력을 시작합니다.\n\n");
        }
    }

    return 0;
}
