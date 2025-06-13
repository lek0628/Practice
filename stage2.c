#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TRAINEES 8
#define MAX_NAME_LEN 50
#define MAX_MENTORS 8

typedef struct {
    char name[MAX_NAME_LEN];
    int id;        // ASCII 합
    int ability;
} Trainee;

typedef struct {
    int id;              // 1 ~ 8
    char name[MAX_NAME_LEN];
    int mentee_id;       // 연습생 ID
} Mentor;

// 함수 선언
int parseIntMember(const char *name);
int getRandomAbility();
void initializeTrainees(Trainee trainees[], const char *names[], int count);
void registerMentors(Mentor mentors[]);
void matchMentoring(Trainee trainees[], Mentor mentors[], int count);
void printMentoringResults(Trainee trainees[], Mentor mentors[], int count);

// ASCII 합산
int parseIntMember(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum;
}

// 능력치 랜덤 부여
int getRandomAbility() {
    return rand() % 901 + 100;  // 100 ~ 1000
}

// 연습생 초기화
void initializeTrainees(Trainee trainees[], const char *names[], int count) {
    for (int i = 0; i < count; i++) {
        strncpy(trainees[i].name, names[i], MAX_NAME_LEN);
        trainees[i].id = parseIntMember(names[i]);
        trainees[i].ability = getRandomAbility();
    }
}

// 멘토 입력
void registerMentors(Mentor mentors[]) {
    printf(">> 멘토 정보를 입력하세요 (최대 8명):\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        printf("멘토 %d 이름: ", i + 1);
        scanf("%s", mentors[i].name);
        mentors[i].mentee_id = -1; // 초기값
    }
}

// 매칭 함수
void matchMentoring(Trainee trainees[], Mentor mentors[], int count) {
    for (int i = 0; i < count; i++) {
        int mentor_id = (trainees[i].id % 8) + 1; // 1~8
        for (int j = 0; j < MAX_MENTORS; j++) {
            if (mentors[j].id == mentor_id) {
                mentors[j].mentee_id = trainees[i].id;
                break;
            }
        }
    }
}

// 출력 함수
void printMentoringResults(Trainee trainees[], Mentor mentors[], int count) {
    printf("\n[멘토링 결과]\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        int trainee_idx = -1;
        for (int j = 0; j < count; j++) {
            if (trainees[j].id == mentors[i].mentee_id) {
                trainee_idx = j;
                break;
            }
        }

        if (trainee_idx != -1) {
            printf("연습생 %-12s(ID: %d) ➜ 멘토 %-12s(ID: %d)\n",
                   trainees[trainee_idx].name,
                   trainees[trainee_idx].id,
                   mentors[i].name,
                   mentors[i].id);
        }
    }
}

// 메뉴 시스템 (문제 1에서 확장)
void showMenu() {
    printf("\n=== [II. 훈련 > 2. 자기관리와 팀워크 > A. 멘토링] ===\n");
    printf("1. 멘토링 매칭 실행\n");
    printf("0. 종료\n");
}

int main() {
    srand((unsigned int)time(NULL));

    const char *trainee_names[NUM_TRAINEES] = {
        "Jisoo", "Mark", "Somi", "Lucas", "Yuna", "Kai", "Jennie", "Felix"
    };

    Trainee trainees[NUM_TRAINEES];
    Mentor mentors[MAX_MENTORS];

    int choice;

    while (1) {
        showMenu();
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initializeTrainees(trainees, trainee_names, NUM_TRAINEES);
                registerMentors(mentors);
                matchMentoring(trainees, mentors, NUM_TRAINEES);
                printMentoringResults(trainees, mentors, NUM_TRAINEES);
                break;
            case 0:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
