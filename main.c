#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <string.h>


int getTestParams();

int getOptionsNumbers();

char *getFileName();

int getIterationsFromFile(char *filename);

int *generateIntNumbers(int iterations);

int *readIntFromFile(char *filename, int iterations);

float *generateFloatNumbers(int iterations);

float *readFloatFromFile(char *filename, int iterations);

double addTwoInt(int a, int b);

double addTwoFloat(float a, float b);

void testInt(int iterations, int *generatedIntNumbersA, int *generatedIntNumbersB);

void testFloat(int iterations, float *generatedFloatNumbers, float *generatedFloatNumbersB);

void saveIntArrayToFile(int *array, int size, char *filename);

void saveFloatArrayToFile(float *array, int size, char *filename);

void saveDoubleArrayToFile(double *array, int size, char *filename);

int main(void) {
    int choice;
    int iterations;
    int *generatedIntNumbersA = NULL;
    int *generatedIntNumbersB = NULL;
    float *generatedFloatNumbersA = NULL;
    float *generatedFloatNumbersB = NULL;

    do {
        printf("Menu:\n");
        printf("1. Generowanie liczb\n");
        printf("2. Testy int\n");
        printf("3. Testy float\n");
        printf("4. Wyjscie\n");
        printf("Wybierz opcje: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                iterations = getTestParams();
                int typ;
                printf("Jakiego typu liczby chcesz wygenerowac 1 - int 2 - float:\n");
                scanf("%d", &typ);
                if (typ == 1) {
                    generatedIntNumbersA = generateIntNumbers(iterations);
                    generatedIntNumbersB = generateIntNumbers(iterations);

                    saveIntArrayToFile(generatedIntNumbersA, iterations, "intA.txt");
                    saveIntArrayToFile(generatedIntNumbersB, iterations, "intB.txt");
                } else if (typ == 2) {
                    generatedFloatNumbersA = generateFloatNumbers(iterations);
                    generatedFloatNumbersB = generateFloatNumbers(iterations);

                    saveFloatArrayToFile(generatedFloatNumbersA, iterations, "floatA.txt");
                    saveFloatArrayToFile(generatedFloatNumbersB, iterations, "floatB.txt");
                }
                break;
            case 2: {
                int choice = getOptionsNumbers();
                if (choice == 1) {
                    testInt(iterations, generatedIntNumbersA, generatedIntNumbersB);
                } else if (choice == 2) {
                    iterations = getTestParams();
                    generatedIntNumbersA = generateIntNumbers(iterations);
                    generatedIntNumbersB = generateIntNumbers(iterations);

                    saveIntArrayToFile(generatedIntNumbersA, iterations, "intA.txt");
                    saveIntArrayToFile(generatedIntNumbersB, iterations, "intB.txt");

                    testInt(iterations, generatedIntNumbersA, generatedIntNumbersB);
                } else if (choice == 3) {
                    printf("Podaj nazwe pliku A do odczytu\n");
                    char *filename1 = getFileName();
                    printf("Podaj nazwe pliku B do odczytu\n");
                    char *filename2 = getFileName();
                    int iterations = getIterationsFromFile(filename1);
                    testInt(iterations, readIntFromFile(filename1, iterations),
                            readIntFromFile(filename2, iterations));
                }
            }
                break;
            case 3: {
                int choice = getOptionsNumbers();
                if (choice == 1) {
                    testFloat(iterations, generatedFloatNumbersA, generatedFloatNumbersB);
                } else if (choice == 2) {
                    iterations = getTestParams();
                    generatedFloatNumbersA = generateFloatNumbers(iterations);
                    generatedFloatNumbersB = generateFloatNumbers(iterations);

                    saveFloatArrayToFile(generatedFloatNumbersA, iterations, "floatA.txt");
                    saveFloatArrayToFile(generatedFloatNumbersB, iterations, "floatB.txt");

                    testFloat(iterations, generatedFloatNumbersA, generatedFloatNumbersB);
                } else if (choice == 3) {
                    printf("Podaj nazwe pliku A do odczytu\n");
                    char *filename1 = getFileName();
                    printf("Podaj nazwe pliku B do odczytu\n");
                    char *filename2 = getFileName();
                    int iterations = getIterationsFromFile(filename1);
                    testFloat(iterations, readFloatFromFile(filename1, iterations),
                              readFloatFromFile(filename2, iterations));
                }
            }
                break;
            case 4:
                printf("Wyjscie z programu.\n");
                break;
            default:
                printf("Niepoprawny choice. Wybierz ponownie.\n");
        }
    } while (choice != 4);

    // Zwolnienie pamięci dla tablic
    free(generatedIntNumbersA);
    free(generatedIntNumbersB);
    free(generatedFloatNumbersA);
    free(generatedFloatNumbersB);

    return 0;
}

int getTestParams() {
    int iterations;
    printf("Podaj liczbe dodawan ktore chcesz sprawdzic: \n");
    scanf("%d", &iterations);
    return iterations;
}


double addTwoInt(int a, int b) {
    struct timespec start, end;
    double time;

    clock_gettime(CLOCK_MONOTONIC, &start);

    int result = a + b;

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Oblicz różnicę czasów
    time = end.tv_nsec - start.tv_nsec;
    printf("%f\n",time);

    return time;
}

double addTwoFloat(float a, float b) {
    struct timespec start, end;
    double time;

    clock_gettime(CLOCK_MONOTONIC, &start);

    float result = a + b;

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Oblicz różnicę czasów
    time = end.tv_nsec - start.tv_nsec;
    printf("%f\n",time);
    return time;
}

int *generateIntNumbers(int iterations) {
    int *numbers = (int *) malloc(iterations * sizeof(int)); // Alokacja pamięci dla tablicy dynamicznej
    if (numbers == NULL) {
        printf("Blad alokacji pamieci.\n");
        exit(1);
    }

    // Generowanie liczb całkowitych
    for (int i = 0; i < iterations; i++) {
        numbers[i] = rand(); // Przykładowa generacja liczb całkowitych
    }

    return numbers; // Zwracanie wskaźnika do tablicy
}

float *generateFloatNumbers(int iterations) {
    float *numbers = (float *) malloc(iterations * sizeof(float)); // Alokacja pamięci dla tablicy dynamicznej
    if (numbers == NULL) {
        printf("Blad alokacji pamieci.\n");
        exit(1);
    }

    // Generowanie liczb zmiennoprzecinkowych
    for (int i = 0; i < iterations; i++) {
        numbers[i] = (float) rand() / RAND_MAX * 100.0;
    }

    return numbers; // Zwracanie wskaźnika do tablicy
}

void testInt(int iterations, int *generatedIntNumbersA, int *generatedIntNumbersB) {
    double *resultTime = (double *) malloc(iterations * sizeof(double));
    double time;
    for (int i = 0; i < iterations; ++i) {
        time = addTwoInt(generatedIntNumbersA[i], generatedIntNumbersB[i]);
        resultTime[i] = time;
    }
    saveDoubleArrayToFile(resultTime, iterations, "intTime.txt");
    printf("Testy zakończone pomyślnie\n");
}

void testFloat(int iterations, float *generatedFloatNumbersA, float *generatedFloatNumbersB) {
    double *resultTime = (double *) malloc(iterations * sizeof(double));
    double time;
    for (int i = 0; i < iterations; ++i) {
        time = addTwoFloat(generatedFloatNumbersA[i], generatedFloatNumbersB[i]);
        resultTime[i] = time;
    }
    saveDoubleArrayToFile(resultTime, iterations, "floatTime.txt");
    printf("Testy zakończone pomyślnie\n");
}


void saveIntArrayToFile(int *array, int size, char *filename) {
    FILE *file = fopen(filename, "w"); // Otwarcie pliku do zapisu
    if (file == NULL) {
        printf("Nie można otworzyć pliku %s\n", filename);
        return;
    }

    // Zapisanie każdej liczby całkowitej z tablicy do pliku
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", array[i]);
    }

    fclose(file); // Zamknięcie pliku
}

void saveFloatArrayToFile(float *array, int size, char *filename) {
    FILE *file = fopen(filename, "w"); // Otwarcie pliku do zapisu
    if (file == NULL) {
        printf("Nie można otworzyć pliku %s\n", filename);
        return;
    }

    // Zapisanie każdej liczby zmiennoprzecinkowej z tablicy do pliku
    for (int i = 0; i < size; i++) {
        fprintf(file, "%f\n", array[i]);
    }

    fclose(file); // Zamknięcie pliku

}

void saveDoubleArrayToFile(double *array, int size, char *filename) {
    FILE *file = fopen(filename, "w"); // Otwarcie pliku do zapisu
    if (file == NULL) {
        printf("Nie można otworzyć pliku %s\n", filename);
        return;
    }

    // Zapisanie każdej liczby całkowitej z tablicy do pliku
    for (int i = 0; i < size; i++) {
        fprintf(file, "%.0f\n", array[i]);
    }

    fclose(file); // Zamknięcie pliku
}

int getOptionsNumbers() {
    int choice;
    printf("Wybierz które liczby chcesz uzyc do obliczen\n");
    printf("1. Wygenerowane w programie\n");
    printf("2. Wygeneruj nowe\n");
    printf("3. Wczytaj z pliku\n");
    scanf("%d", &choice);
    return choice;
}

int getIterationsFromFile(char *filename) {
    FILE *file = fopen(filename, "r"); // Otwórz plik do odczytu
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return -1; // Zwróć -1 w przypadku błędu otwarcia pliku
    }

    int iterations = 0;
    char buffer[100]; // Bufor do przechowywania wczytywanych linii

    // Iteruj przez każdą linię w pliku i zwiększaj licznik iteracji
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        iterations++;
    }

    fclose(file); // Zamknij plik

    return iterations; // Zwróć liczbę iteracji
}


int *readIntFromFile(char *filename, int iterations) {
    FILE *file = fopen(filename, "r"); // Otwórz plik do odczytu
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return NULL; // Zwróć NULL w przypadku błędu otwarcia pliku
    }

    int *numbers = (int *) malloc(iterations * sizeof(int)); // Alokacja pamięci dla tablicy dynamicznej

    // Wczytaj liczby z pliku do tablicy
    for (int i = 0; i < iterations; i++) {
        if (fscanf(file, "%d", &numbers[i]) != 1) {
            printf("Błąd odczytu z pliku.\n");
            free(numbers); // Zwolnij pamięć, jeśli wystąpił błąd odczytu
            fclose(file); // Zamknij plik
            return NULL;
        }
    }

    fclose(file); // Zamknij plik

    return numbers; // Zwróć wskaźnik do tablicy z wczytanymi liczbami
}

float *readFloatFromFile(char *filename, int iterations) {
    FILE *file = fopen(filename, "r"); // Otwórz plik do odczytu
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return NULL; // Zwróć NULL w przypadku błędu otwarcia pliku
    }

    float *numbers = (float *) malloc(iterations * sizeof(float)); // Alokacja pamięci dla tablicy dynamicznej

    // Wczytaj liczby z pliku do tablicy
    for (int i = 0; i < iterations; i++) {
        if (fscanf(file, "%f", &numbers[i]) != 1) {
            printf("Błąd odczytu z pliku.\n");
            free(numbers); // Zwolnij pamięć, jeśli wystąpił błąd odczytu
            fclose(file); // Zamknij plik
            return NULL;
        }
    }

    fclose(file); // Zamknij plik

    return numbers; // Zwróć wskaźnik do tablicy z wczytanymi liczbami
}

char *getFileName() {
    char buffer[100]; // Bufor na wczytanie nazwy pliku
    scanf("%99s", buffer);

    // Oblicz długość wczytanej nazwy pliku (bez uwzględniania znaku nowej linii)
    size_t length = strlen(buffer);
    if (buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0'; // Usuń znak nowej linii
        length--; // Zmniejsz długość o 1
    }

    // Alokuj pamięć dla nazwy pliku i skopiuj do niej wczytaną nazwę
    char *filename = (char *) malloc((length + 1) * sizeof(char)); // +1 na znak końca ciągu
    if (filename == NULL) {
        printf("Błąd alokacji pamięci.\n");
        return NULL;
    }
    strcpy(filename, buffer);

    return filename; // Zwróć wskaźnik na nazwę pliku
}
