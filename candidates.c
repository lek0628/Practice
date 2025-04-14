// candidates.c
#include <stdio.h>
#include <stdlib.h>

#define MAX 6

// 후보자 정보 구조체 정의
struct member_info {
    char name[50];
    char birth[9];         // YYYYMMDD
    char gender;           // 'F' or 'M'
    char email[100];
    char nationality[30];
    float bmi;
    char main_skill[50];
    char sub_skill[50];
    int topik;             // 0~6
    char mbti[10];
    char intro[300];
};

// 후보자 배열 정의
struct member_info candidate01, candidate02, candidate03,
                   candidate04, candidate05, candidate06;

int main() {
    struct member_info *candidates[MAX] = {
        &candidate01, &candidate02, &candidate03,
        &candidate04, &candidate05, &candidate06
    };

    int i = 0;
    while (i < MAX) {
        printf("####################################\n");
        printf("     오디션 후보자 데이터 입력     \n");
        printf("####################################\n");
        printf("%d번째 후보자의 정보를 입력합니다.\n", i + 1);
        printf("---------------------------------\n");

        printf("1. 성명: ");
        fgets(candidates[i]->name, sizeof(candidates[i]->name), stdin);
        candidates[i]->name[strcspn(candidates[i]->name, "\n")] = '\0';

        printf("2. 생일(YYYY/MM/DD 형식): ");
        char birth_temp[11];
        fgets(birth_temp, sizeof(birth_temp), stdin);
        birth_temp[strcspn(birth_temp, "\n")] = '\0';
        sscanf(birth_temp, "%4c/%2c/%2c", 
               &candidates[i]->birth[0], &candidates[i]->birth[4], &candidates[i]->birth[6]);
        candidates[i]->birth[8] = '\0';  // NULL 종료

        printf("3. 성별(여성이면 F 또는 남성이면 M): ");
        scanf(" %c", &candidates[i]->gender); getchar();

        printf("4. 메일 주소: ");
        fgets(candidates[i]->email, sizeof(candidates[i]->email), stdin);
        candidates[i]->email[strcspn(candidates[i]->email, "\n")] = '\0';

        printf("5. 국적: ");
        fgets(candidates[i]->nationality, sizeof(candidates[i]->nationality), stdin);
        candidates[i]->nationality[strcspn(candidates[i]->nationality, "\n")] = '\0';

        printf("6. BMI: ");
        scanf("%f", &candidates[i]->bmi); getchar();

        printf("7. 주 스킬: ");
        fgets(candidates[i]->main_skill, sizeof(candidates[i]->main_skill), stdin);
        candidates[i]->main_skill[strcspn(candidates[i]->main_skill, "\n")] = '\0';

        printf("8. 보조 스킬: ");
        fgets(candidates[i]->sub_skill, sizeof(candidates[i]->sub_skill), stdin);
        candidates[i]->sub_skill[strcspn(candidates[i]->sub_skill, "\n")] = '\0';

        printf("9. 한국어 등급(TOPIK): ");
        scanf("%d", &candidates[i]->topik); getchar();

        printf("10. MBTI: ");
        fgets(candidates[i]->mbti, sizeof(candidates[i]->mbti), stdin);
        candidates[i]->mbti[strcspn(candidates[i]->mbti, "\n")] = '\0';

        printf("11. 소개: ");
        fgets(candidates[i]->intro, sizeof(candidates[i]->intro), stdin);
        candidates[i]->intro[strcspn(candidates[i]->intro, "\n")] = '\0';

        printf("=================================\n");

        i++;
    }

    // 출력
    printf("####################################\n");
    printf("     오디션 후보자 데이터 조회     \n");
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("성   명 | 생   일 | 성별 | 메   일            | 국적 | BMI  | 주스킬 | 보조스킬 | TOPIK  | MBTI |\n");
    printf("=============================================================================================\n");

    for (i = 0; i < MAX; i++) {
        const char* topik_str;
        if (candidates[i]->topik == 0)
            topik_str = "원어민";
        else {
            static char level[3];
            sprintf(level, "%d", candidates[i]->topik);
            topik_str = level;
        }

        printf("%-6s |%-8s | %-3c | %-18s |%-5s | %-4.1f | %-6s | %-8s | %-6s | %-4s |\n",
               candidates[i]->name, candidates[i]->birth,
               candidates[i]->gender == 'F' ? '여' : '남',
               candidates[i]->email, candidates[i]->nationality,
               candidates[i]->bmi,
               candidates[i]->main_skill, candidates[i]->sub_skill,
               topik_str, candidates[i]->mbti);

        printf("-------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i]->intro);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
