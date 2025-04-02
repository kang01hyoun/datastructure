#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int s_id;
    char name[20];
} student;

student enroll[MAX];
int length = 0;

int strcmp(const char *str1, const char *str2);
int same_Check(student s);
void save();
void load();
int apply(student s);
int drop(int id);
void print();
void doRequest(char ch);

int main() {
    char ch;
    load();
    do {
        printf("\n---------------------------------------\n");
        printf("자료구조 수강신청 및 수강철회\n");
        printf("-----------------------------------------\n");
        printf("1. 수강신청\n");
        printf("2. 수강철회\n");
        printf("3. 수강조회\n");
        printf("q. 프로그램 종료\n");
        printf("-----------------------------------------\n");
        printf("원하시는 서비스를 선택하세요: ");
        scanf(" %c", &ch);
        doRequest(ch);
    } while (ch != 'q');
    return 0;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int same_Check(student s) {
    for (int i = 0; i < length; i++) {
        if (enroll[i].s_id == s.s_id && strcmp(enroll[i].name, s.name) == 0) {
            return 1;
        }
    }
    return 0;
}

void save() {
    FILE *f1 = fopen("enroll.txt", "w");
    if (f1 == NULL) {
        printf("파일 저장 실패\n");
        return;
    }
    for (int i = 0; i < length; i++) {
        fprintf(f1, "%d %s\n", enroll[i].s_id, enroll[i].name);
    }
    fclose(f1);
}

void load() {
    FILE *f1 = fopen("enroll.txt", "r");
    int i = 0;
    while (fscanf(f1, "%d %s", &enroll[i].s_id, enroll[i].name) != EOF) {
        i++;
    }
    length = i;
    fclose(f1);
}

int apply(student s) {
    if (length >= MAX) {
        return 0;
    }
    if (same_Check(s)) {
        return -1;
    }
    int index = 0;
    while (index < length && s.s_id > enroll[index].s_id) {
        index++;
    }
    length++;
    for (int i = length-1; i > index; i--) {
        enroll[i] = enroll[i-1];
    }
    enroll[index] = s;
    return 1;
}

int drop(int id) {
    for (int i = 0; i < length; i++) {
        if (enroll[i].s_id == id) {
            for (int j = i; j < length - 1; j++) {
                enroll[j] = enroll[j + 1];
            }
            length--;
            return 1;
        }
    }
    return 0;
}

void print() {
    printf("\n<< 수강신청 명단 >>\n");
    for (int i = 0; i < length; i++) {
        printf("학번: %d, 이름: %s\n", enroll[i].s_id, enroll[i].name);
    }
}

void doRequest(char ch) {
    student s;
    int flag;
    switch (ch) {
        case '1':
            system("cls");
            printf("\n** 수강신청 처리중 **\n");
            printf("학번: ");
            scanf("%d", &s.s_id);
            printf("이름: ");
            scanf("%s", s.name);
            flag = apply(s);
            if (flag == 0) {
                printf("\n수강신청 마감됨.\n");
            }
            else if (flag == -1) {
                printf("\n이미 등록된 학생 정보입니다.\n");
            }
            else {
                printf("\n수강신청 승인됨.\n");
                save();
            }
            break;

        case '2':
            system("cls");
            printf("\n** 수강철회 처리중 **\n");
            printf("학번: ");
            scanf("%d", &s.s_id);
            printf("이름: ");
            scanf("%s", s.name);
            flag = drop(s.s_id);
            if (flag == 0) {
                printf("\n수강신청 정보 없음\n");
            }
            else {
                printf("\n신청철회 승인됨\n");
                save();
            }
            break;

        case '3':
            system("cls");
            print();
            break;

        case 'q':
            system("cls");
            save();
            printf("프로그램 종료\n");
            break;

        default:
            system("cls");
            printf("잘못된 입력입니다. 다시 선택해주세요.\n");
    }
}
