#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//컴파일 성공
//??

typedef struct diary{
    int year;
    int month;
    int date;
    int bookMark;
    char names[100];
    char title[15];
    char content[1000]; //공백포함
    int password [4];
    char weather[10]; //맑음, 바람, 비, 눈, 흐림 중에 설정
} Diary;

//파일 여는 함수
void openFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}


void saveDiary(const Diary *diaryList, int countDiaries, const char *fileName) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fwrite(&countDiaries, sizeof(int), 1, file);

    for (int i = 0; i < countDiaries; i++) {
        fwrite(&diaryList[i], sizeof(Diary), 1, file);
    }

    fclose(file);
    printf("Diaries saved successfully.\n");
}



#define MAX_DIARIES 100
//. 일기 구조체 배열(Diary 배열)에 저장할 수 있는 최대 일기 개수
// addSecretDiary(diaries, &numDiaries);

void addSecretDiary(Diary *diaryList, int *numDiaries) {
    if (*numDiaries >= MAX_DIARIES) {
        printf("Maximum number of diaries reached.\n"); // 정해진 일기 개수를 초과하였습니다.
        return;
    }

    Diary newDiary;
    printf("Enter the year: ");
    scanf("%d", &newDiary.year);
    printf("Enter the month: ");
    scanf("%d", &newDiary.month);
    printf("Enter the date: ");
    scanf("%d", &newDiary.date);

    printf("Set a password (4 digits): ");
    for (int i = 0; i < 4; i++) {
        scanf("%1d", &newDiary.password[i]);
    }

    printf("Enter the names: ");
    getchar(); // 버퍼 비우기
    fgets(newDiary.names, sizeof(newDiary.names), stdin);
    newDiary.names[strcspn(newDiary.names, "\n")] = '\0'; // 개행 문자 제거

    printf("Enter the title: ");
    fgets(newDiary.title, sizeof(newDiary.title), stdin);
    newDiary.title[strcspn(newDiary.title, "\n")] = '\0'; // 개행 문자 제거

    printf("Enter the content: ");
    fgets(newDiary.content, sizeof(newDiary.content), stdin);
    newDiary.content[strcspn(newDiary.content, "\n")] = '\0'; // 개행 문자 제거

    printf("Enter the weather: ");
    fgets(newDiary.weather, sizeof(newDiary.weather), stdin);
    newDiary.weather[strcspn(newDiary.weather, "\n")] = '\0'; // 개행 문자 제거

    diaryList[*numDiaries] = newDiary;
    (*numDiaries)++;

    printf("Secret diary added successfully.\n");
}

#include <time.h> // time 함수를 사용하기 위해 필요한 헤더 파일

// 주제로 사용할 수 있는 키워드 목록 배열
const char* keywords[] = {
    "Travel",
    "Food",
    "Nature",
    "Friendship",
    "Love",
    "Adventure",
    "Memories",
    "Reflection",
    // 추가적인 키워드를 필요에 따라 여기에 추가할 수 있습니다.
};

int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

const char* randomTopic() {
    srand(time(NULL)); // 시간을 기반으로 난수 생성기 초기화

    int randomIndex = rand() % numKeywords; // 0부터 numKeywords-1 사이의 난수 생성
    // printf("Random topic: %s\n", topic); 메인에 추가하거나 함수에서 바로 키워트 

    return keywords[randomIndex];
}

//날씨 선택 함수
//함수 호출하는 방법 
//const char* weather = selectWeather();
// printf("Selected weather: %s\n", weather);

// 오류나서
// const char* selectWeather() {
//     char weather[10];
//     printf("Select the weather (Sunny, Windy, Rainy, Snowy, Cloudy): ");
//     fgets(weather, sizeof(weather), stdin);
//     weather[strcspn(weather, "\n")] = '\0'; // 개행 문자 제거

//     return weather;
// }

void selectWeather(Diary* entry) {
    char weather[10];
    printf("Select the weather (Sunny, Windy, Rainy, Snowy, Cloudy): ");
    fgets(weather, sizeof(weather), stdin);
    weather[strcspn(weather, "\n")] = '\0'; // 개행 문자 제거

    strncpy(entry->weather, weather, sizeof(entry->weather));
}



void readDiary(Diary d){
    char isLocked = 'X';
    char isBookMark = 'X';
    if (d.password[0] != -1) isLocked = 'O';
    if (d.bookMark != 0) isBookMark = 'O';
    printf("| %c | %d-%d-%d | %s | %c |", isBookMark, d.year, d.month, d.date, d.title, isLocked);
}

void viewDiary(Diary *d){
    printf("��¥: %d�� %d�� %d��\n", d->year, d->month, d->date);
    printf("����: %s\n", d->weather);
    printf("����: %s\n", d->title);
    printf("\n%s\n\n", d->content);
    printf("�߾��� �Բ��� ���: %s\n", d->names);
}

int addDiary(Diary *d){
        printf("��¥�� �⵵, ��, �� ������ �������� �����Ͽ� �Է����ּ���. (ex. 2023 05 16): ");
        scanf("%d %d %d", &d->year, &d->month, &d->date);
        printf("�ϱ��� ������ �Է� ���ּ���. (ex. ����, �帲, �� ��): ");
        scanf("%s", d->weather);
        getchar();
        printf("�ϱ��� ������ �Է� ���ּ���. (���� �� ����: 15����): ");
        fgets(d->title, 15, stdin);
        printf("�ϱ��� ������ �Է� ���ּ���. (���� �� ����: 1000����): ");
        fgets(d->content, 1000, stdin);
        printf("�� �߾￡ �Բ��� �ι����� �����ּ���. (���� �� ����: 100����): ");
        fgets(d->names, 100, stdin);
        d->password[0] = -1;
        d->bookMark = 0;

        return 1;
}


int updateDiary(Diary *d){
        printf("��¥�� �⵵, ��, �� ������ �������� �����Ͽ� �Է����ּ���. (ex. 2023 05 16): ");
        scanf("%d %d %d", &d->year, &d->month, &d->date);
        printf("�ϱ��� ������ �Է� ���ּ���. (ex. ����, �帲, �� ��): ");
        scanf("%s", d->weather);
        getchar();
        printf("�ϱ��� ������ �Է� ���ּ���. (���� �� ����: 15����): ");
        fgets(d->title, 15, stdin);
        printf("�ϱ��� ������ �Է� ���ּ���. (���� �� ����: 1000����): ");
        fgets(d->content, 1000, stdin);
        printf("�� �߾￡ �Բ��� �ι����� �����ּ���. (���� �� ����: 100����): ");
        fgets(d->names, 100, stdin);
        d->password[0] = -1;
    d->password[0] = -1;

    printf("=> ��������!");
    return 1;
}

void deleteDiary(Diary *d){
    free(d);
    d->year = -1;
}

// #include "diaryCRUD.h"

int selectMenu(){
    int menu;
    printf("\n|------------ ���ϸ��� ���̾ ------------|\n");
    printf("| 1. 일기 조회 | 2. 일기 추가 | 3. 파일에 저장 | 4. 일기 수정 | 5. 일기 삭제 | 5. 즐겨찾기 목록 | 6. 즐겨찾기 추가/삭제 |\n| 7. 함께한 인물 이름별 검색 | 8. 제목으로 검색 |  8. 비밀일기 추가 | 9. 랜덤 키워드 선정 | 9. 날씨 선장 | 10. 일기 출력 | 11. 일기 목록 출력| | 0. 종료 |\n\n=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}

void listDiary(Diary *d, int count){
    printf("\n| NO | BookMark | YYYY-MM-DD | Title         Locked\n");
    printf("=====================================================\n");
    for(int i =0; i <count ; i++){
        if(d[i].year == -1) continue;
        printf("%2d ", i+1);
        readDiary(d[i]);
        printf("\n");
    }
   
}

// void listBookmark(Diary *d[], int count){
//     printf("\n| NO | BookMark | YYYY-MM-DD | Title         Locked\n");
//     printf("=====================================================\n");
    
//     for(int i =0; i <count ; i++){
//         if(d[i]->year == -1) continue;
//         if (d[i]->bookMark == 0) continue;
//         printf("%2d ", i+1);
//         readDiary(*d[i]);
//         }
//     printf("\n");
// }

//수정 시안
void listBookmark(const Diary *diaryList, int numDiaries) {
    printf("\n| NO | BookMark | YYYY-MM-DD | Title         Locked\n");
    printf("=====================================================\n");

    for (int i = 0; i < numDiaries; i++) {
        if (diaryList[i].bookMark == 0) continue;
        printf("%2d ", i + 1);
        readDiary(diaryList[i]);
        printf("\n");
    }
}

void setBookmark(Diary *d){
    if (d->bookMark == 1){
        d->bookMark = 0;
    }
    else d->bookMark = 1;
}

int selectNum(Diary *d[], int max){
    listDiary(*d,max);
    int no;
    printf("\n���ϴ� �ϱ� ��ȣ��(��� :0)? ");
    scanf("%d", &no);

    return no;
}


int searchName(Diary *d[], char *tname, int count){
    int index = -1;
    for (int i =0; i<count; i++){
        if (d[i]->year == -1) continue;
        if (strstr(d[i]->names,tname)== 0) {
            index = i;
            break;
        }
    }

    return index;
}

int searchTitle(Diary *d[], char *tname, int count){
    int index = -1;
    for (int i =0; i<count; i++){
        if (d[i]->year == -1) continue;
        if (strstr(d[i]->title,tname)== 0) {
            index = i;
            break;
        }
    }

    return index;

}

int main(){
    Diary *d[20];
    Diary *diaryList[100]; 
    int menu, count, index;
    count = 0;
    index = 0;


    while (1){
        printf("\n>>>>>>>index: %d | count: %d<<<<<<<<<<<<\n", index, count);
        menu = selectMenu();
        if (menu == 0) break;
        if (menu == 1) {
        listDiary(*d, index);
        }
        else if (menu == 2){
            d[index] = (Diary *)malloc(sizeof(Diary));
            addDiary(d[index]);
            index++;
            count++;
        }
            else if (menu == 3){ //파일에 저장 
             Diary diaryList[MAX_DIARIES];
            int numDiaries = 0;
            // 일기를 작성하고 diaryList에 추가하는 코드
            // 파일에 일기 저장
            saveDiary(diaryList, numDiaries, "diary.txt");
        }
        else if (menu == 4){
            int no = selectNum(d,index);
            if (no == 0) printf("��ҵ�!\n");
            else updateDiary(d[no-1]);
        }
        else if (menu == 5){
            int no = selectNum(d,index);
            if (no == 0) printf("��ҵ�!\n");
            else {
                int temp;
                printf("������ �����Ͻðڽ��ϱ�? (���� :1) ");
                scanf("%d", &temp);

                if (temp == 1) {
                    if (d[no-1]) {
                        deleteDiary(d[no-1]);
                    }
                    count--;
                }
            }
        }
        else if (menu == 6){
            printf("========���ã�� �� �ϱ� ���=======");
            listBookmark((const Diary*)d, count);
            int imenu;
            int itemp;
        }
        else if (menu == 7){
            int itemp;
            while(1){
                itemp = selectNum(d,index);
                if (itemp == 0) break;
                else setBookmark(d[itemp-1]);
            }
        }
        else if (menu == 8){
            char temp[20];
            int index;
            printf("�˻� �Ͻ� �̸��� �Է����ּ���. ");
            scanf("%s", temp);

            index = searchName(d,temp, count);
            if (index == -1) printf("�ش�Ǵ� �ϱⰡ �����ϴ�! \n");
            else{
                printf("\n| NO | BookMark | YYYY-MM-DD | Title         Locked\n");
                printf("=====================================================\n");
                readDiary(*d[index]);
            }

        }
        else if (menu==9){
            char temp[20];
            int index;
            printf("�˻� �Ͻ� �ϱ��� ������ �Է����ּ���. ");
            scanf("%s", temp);

            index = searchTitle(d,temp, count);
            if (index == -1) printf("�ش�Ǵ� �ϱⰡ �����ϴ�! \n");
            else{
                printf("\n| NO | BookMark | YYYY-MM-DD | Title         Locked\n");
                printf("=====================================================\n");
                readDiary(*d[index]);
            }
        }
            else if (menu==10){
            Diary diaryList[MAX_DIARIES];
            int numDiaries = 0;

            // 비밀 일기 추가
            addSecretDiary(diaryList, &numDiaries);
        }
            else if (menu==11){
            // 랜덤 키워드 선정
            const char* keyword = randomTopic();
            printf("Random topic: %s\n", keyword);

        }
            else if (menu==12){
            // 날씨 선정
            Diary myDiary;
            selectWeather(&myDiary);
            printf("Selected weather: %s\n", myDiary.weather);
        }
            else if (menu==13){


        }
            else if (menu==14){
            // 일기 구조체 배열과 일기 개수 변수
            Diary diaryList[MAX_DIARIES];
            int numDiaries = 0;

            // 일기 목록 출력
            listDiary(diaryList, numDiaries);

        }       

    }
        
    return 0;
}