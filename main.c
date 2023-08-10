#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_WORDS 1500   // リストに格納できる最大単語数
#define MAX_WORD_LEN 50  // 単語の最大長さ

void readWordsFromFile(const char *filename, char words[][MAX_WORD_LEN], int *wordCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ファイルを開けませんでした。\n");
        exit(1);
    }

    char buffer[MAX_WORD_LEN];
    while ((*wordCount < MAX_WORDS) && fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        strcpy(words[*wordCount], buffer);
        (*wordCount)++;
    }

    fclose(file);
}

bool isValidWord(const char *word, const char lastChar) {
    return (word[0] == lastChar) && (word[strlen(word) - 1] != ' ');
}

void removeWord(char words[][MAX_WORD_LEN], int *wordCount, int index) {
    if (index < 0 || index >= *wordCount) {
        return;
    }

    for (int i = index; i < *wordCount - 1; i++) {
        strcpy(words[i], words[i + 1]);
    }
    (*wordCount)--;
}

int main() {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int wordCount = 0;

    readWordsFromFile("あいえんか.txt", words, &wordCount);

    char lastChar = 'r'; // 一文字としてしりとりを始める
    char input[MAX_WORD_LEN];

    printf("しりとりを始めます！\n");

    while (1) {
        printf("前の単語: %c\n", lastChar);
        printf("あなたの英単語を入力してください: ");
        scanf("%s", input);

        if (!isValidWord(input, lastChar)) {
            printf("無効な単語です。正しい単語を入力してください。\n");
            continue;
        }

        bool found = false;
        int usedIndex = -1;

        for (int i = 0; i < wordCount; i++) {
            if (words[i][0] == input[strlen(input) - 1]) {
                printf("次の単語: %s\n", words[i]);
                usedIndex = i;
                found = true;
                break;
            }
        }

        if (!found) {
            printf("適切な単語が見つかりませんでした。あなたの勝ちです！\n");
            break;
        }

        lastChar = words[usedIndex][strlen(words[usedIndex]) - 1];

        if (usedIndex >= 0) {
            removeWord(words, &wordCount, usedIndex);
        }
    }

    return 0;
}
