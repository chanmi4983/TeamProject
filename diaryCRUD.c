#include "diaryCRUD.h"

void readDiary(Diary d){
    char isLocked = 'X';
    char isBookMark = 'X';
    if (d.password[0] != -1) isLocked = 'O';
    if (d.bookMark != 0) isBookMark = 'O';
    printf("| %c | %d-%d-%d | %s | %c |", isBookMark, d.year, d.month, d.date, d.title, isLocked);
}

void viewDiary(Diary *d){
    printf("날짜: %d년 %d월 %d일\n", d->year, d->month, d->date);
    printf("날씨: %s\n", d->weather);
    printf("제목: %s\n", d->title);
    printf("\n%s\n\n", d->content);
    printf("추억을 함께한 사람: %s\n", d->names);
}

int addDiary(Diary *d){
        printf("날짜를 년도, 월, 일 순서로 공백으로 구분하여 입력해주세요. (ex. 2023 05 16): ");
        scanf("%d %d %d", &d->year, &d->month, &d->date);
        printf("일기의 날씨를 입력 해주세요. (ex. 맑음, 흐림, 비 등): ");
        scanf("%s", d->weather);
        getchar();
        printf("일기의 제목을 입력 해주세요. (글자 수 제한: 15글자): ");
        fgets(d->title, 15, stdin);
        printf("일기의 내용을 입력 해주세요. (글자 수 제한: 1000글자): ");
        fgets(d->content, 1000, stdin);
        printf("이 추억에 함께한 인물들을 적어주세요. (글자 수 제한: 100글자): ");
        fgets(d->names, 100, stdin);
        d->password[0] = -1;
        d->bookMark = 0;

        return 1;
}


int updateDiary(Diary *d){
        printf("날짜를 년도, 월, 일 순서로 공백으로 구분하여 입력해주세요. (ex. 2023 05 16): ");
        scanf("%d %d %d", &d->year, &d->month, &d->date);
        printf("일기의 날씨를 입력 해주세요. (ex. 맑음, 흐림, 비 등): ");
        scanf("%s", d->weather);
        getchar();
        printf("일기의 제목을 입력 해주세요. (글자 수 제한: 15글자): ");
        fgets(d->title, 15, stdin);
        printf("일기의 내용을 입력 해주세요. (글자 수 제한: 1000글자): ");
        fgets(d->content, 1000, stdin);
        printf("이 추억에 함께한 인물들을 적어주세요. (글자 수 제한: 100글자): ");
        fgets(d->names, 100, stdin);
        d->password[0] = -1;
    d->password[0] = -1;

    printf("=> 수정성공!");
    return 1;
}

void deleteDiary(Diary *d){
    free(d);
    d->year = -1;
}
        