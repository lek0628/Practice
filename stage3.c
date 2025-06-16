#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_QUESTIONS 10
#define QUIZ_COUNT 5
#define MAX_MEMBERS 4
#define MAX_NAME_LEN 30
#define MAX_NICK_LEN 20
#define MAX_ANSWER_LEN 100

typedef struct
{
  int id;
  char question[MAX_ANSWER_LEN];
  char answer[MAX_ANSWER_LEN];
} KoreanQuiz;

typedef struct
{
  char name[MAX_NAME_LEN];
  char nickname[MAX_NICK_LEN];
  char nationality[20];
  int score;
  char passed;
} Trainee;

typedef struct
{
  int question_id;
  char correct; /* 'O' or 'X' */
} QuizResult;

KoreanQuiz questionBank[MAX_QUESTIONS] = {
    {1, "What is the Korean word for 'Love'?", "사랑"},
    {2, "Translate to Korean: 'Thank you'", "감사합니다"},
    {3, "Translate to Korean: 'Hello'", "안녕하세요"},
    {4, "Translate to Korean: 'Delicious'", "맛있어요"},
    {5, "Translate to Korean: 'I am happy'", "행복해요"},
    {6, "Translate to Korean: 'Good night'", "안녕히 주무세요"},
    {7, "Translate to Korean: 'Friend'", "친구"},
    {8, "Translate to Korean: 'Family'", "가족"},
    {9, "Translate to Korean: 'School'", "학교"},
    {10, "Translate to Korean: 'Dream'", "꿈"}};

Trainee members[MAX_MEMBERS] = {
    {"박지연", "Nova", "Korea", 0, 'X'},
    {"John Smith", "Echo", "USA", 0, 'X'},
    {"Sakura Tanaka", "Vega", "Japan", 0, 'X'},
    {"Liam Wang", "Lumen", "China", 0, 'X'}};

QuizResult result[QUIZ_COUNT];
int servedQuestions[QUIZ_COUNT];

/* 정답 여부 확인 */
int
isAnswer(int id, const char *userAnswer, KoreanQuiz *questionBank)
{
  for (int i = 0; i < MAX_QUESTIONS; i++)
    {
      if (questionBank[i].id == id)
        {
          return strcmp(userAnswer, questionBank[i].answer) == 0;
        }
    }
  return 0;
}

/* 중복 없는 랜덤 인덱스 생성 */
int *
generateRandomIndices(int size, int count)
{
  static int indices[QUIZ_COUNT];
  int used[MAX_QUESTIONS] = {0};
  int i = 0;

  while (i < count)
    {
      int r = rand() % size;
      if (!used[r])
        {
          indices[i++] = r;
          used[r] = 1;
        }
    }

  return indices;
}

/* 응시자 무작위 선택 (비한국인) */
Trainee *
selectRandomTakers()
{
  time_t now = time(NULL);
  struct tm *lt = localtime(&now);
  srand(lt->tm_hour);

  while (1)
    {
      int r = rand() % MAX_MEMBERS;
      if (strcmp(members[r].nationality, "Korea") != 0)
        {
          printf("\n[%s]님, 한국어 퀴즈 세션에 오신 걸 환영합니다!\n\n", members[r].name);
          return &members[r];
        }
    }
}

/* 퀴즈 출제 및 채점 */
void
serveRandomQuiz(Trainee *taker, KoreanQuiz *questionBank)
{
  printf("30초 뒤에 퀴즈가 시작됩니다. 준비하세요...\n");
  sleep(30);

  int *indices = generateRandomIndices(MAX_QUESTIONS, QUIZ_COUNT);
  int score = 0;

  for (int i = 0; i < QUIZ_COUNT; i++)
    {
      int qid = indices[i];
      servedQuestions[i] = questionBank[qid].id;

      printf("\nQ%d. %s\n", questionBank[qid].id, questionBank[qid].question);
      printf("답변 입력: ");

      char answer[MAX_ANSWER_LEN];
      fgets(answer, MAX_ANSWER_LEN, stdin);
      strtok(answer, "\n");

      int correct = (strlen(answer) > 0
                     && isAnswer(questionBank[qid].id, answer, questionBank))
                        ? 1
                        : 0;

      result[i].question_id = questionBank[qid].id;
      result[i].correct = correct ? 'O' : 'X';
      score += correct ? 20 : 0;
    }

  taker->score = score;
  taker->passed = (score >= 80) ? 'O' : 'X';

  printf("\n===== 퀴즈 결과 =====\n");
  for (int i = 0; i < QUIZ_COUNT; i++)
    {
      printf("문제 %d: %c\n", result[i].question_id, result[i].correct);
    }
  printf("총점: %d점\n", taker->score);
  printf("합격 여부: %c\n", taker->passed);
}

/* 메인 퀴즈 진입 함수 */
void
testKoreanLang()
{
  Trainee *taker = selectRandomTakers();
  getchar(); /* flush stdin */
  serveRandomQuiz(taker, questionBank);
}

/* 예시 메인 메뉴 */
int
main()
{
  int choice;
  while (1)
    {
      printf("\n=== 밀리웨이즈 훈련 시스템 ===\n");
      printf("1. 한국어 퀴즈 실행\n");
      printf("0. 종료\n");
      printf("선택: ");
      scanf("%d", &choice);
      getchar(); /* flush newline */

      switch (choice)
        {
        case 1:
          testKoreanLang();
          break;
        case 0:
          printf("종료합니다.\n");
          return 0;
        default:
          printf("잘못된 입력입니다.\n");
        }
    }

  return 0;
}
