#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 10
#define BUFFER_SIZE 512

char *judges_array[MAX_JUDGES];

void parse_and_print_judge(int index, const char *json) {
    char buffer[BUFFER_SIZE];
    strcpy(buffer, json);

    char *token = strtok(buffer, ",");
    printf("[심사위원 %d]\n", index + 1);
    while (token != NULL) {
        char *key = strtok(token, ":");
        char *value = strtok(NULL, ":");

        if (key && value) {
            printf("%s:%s\n", key, value);
        }
        token = strtok(NULL, ",");
    }
    printf("-----------------------------------\n");
}

int main() {
    char project[100];
    int total_judges, selected_members;

    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");

    printf("> 참여 프로젝트: ");
    fgets(project, sizeof(project), stdin);
    project[strcspn(project, "\n")] = 0;

    printf("> 심사 총 인원: ");
    scanf("%d", &total_judges);
    printf("> 선발 멤버 수: ");
    scanf("%d", &selected_members);
    getchar(); // 개행 문자 제거

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    for (int i = 0; i < total_judges; i++) {
        char input[BUFFER_SIZE];
        while (1) {
            printf("*심사위원 %d: ", i + 1);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            if (strlen(input) == 0) {
                printf("입력이 누락되었습니다. 다시 입력해주세요.\n");
                continue;
            }

            judges_array[i] = malloc(strlen(input) + 1);
            strcpy(judges_array[i], input);
            break;
        }
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사위원 정보 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char confirm;
    printf("\"%s 심사위원 정보를 확인할까요?\" (Y/N): ", project);
    scanf(" %c", &confirm);

    if (confirm == 'Y') {
        printf("####################################\n");
        printf("#        심사위원 데이터 출력        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            parse_and_print_judge(i, judges_array[i]);
        }
    } else {
        printf("프로그램을 종료합니다.\n");
    }

    for (int i = 0; i < total_judges; i++) {
        free(judges_array[i]);
    }

    return 0;
}
