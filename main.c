#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>


int getTestParams();

int *generateIntNumbers(int iterations);

float *generateFloatNumbers(int iterations);

unsigned long long int addTwoInt(int a, int b);

unsigned long long int addTwoFloat(float a, float b);

void testInt(int iterations, int *generatedIntNumbersa, int *generatedIntNumbersB);

void testFloat(int iterations, float *generatedFloatNumbers, float *generatedFloatNumbersB);

void saveIntArrayToFile(int *array, int size, char *filename);

void saveFloatArrayToFile(float *array, int size, char *filename);
void saveLongLongArrayToFile(unsigned long long int *array, int size, char *filename) ;

int main(void) {
    int wybor;
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
        scanf("%d", &wybor);

        switch (wybor) {
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
            case 2:
                testInt(iterations, generatedIntNumbersA, generatedIntNumbersB);
                break;
            case 3:
                testFloat(iterations, generatedFloatNumbersA, generatedFloatNumbersB);
                break;
            case 4:
                printf("Wyjscie z programu.\n");
                break;
            default:
                printf("Niepoprawny wybor. Wybierz ponownie.\n");
        }
    } while (wybor != 4);

    // Zwolnienie pamięci dla tablic
    free(generatedIntNumbersA);
    free(generatedIntNumbersB);
    free(generatedFloatNumbersA);
    free(generatedFloatNumbersB);

    return 0;
}

int getTestParams() {
    int iterations;
    printf("Podaj liczbe dodawan ktore chcesz sprawdzic: ");
    scanf("%d", &iterations); // Poprawka: dodano & przed iterations
    return iterations;
}


unsigned long long int addTwoInt(int a, int b) {
    clock_t start, end;
    unsigned long long int cykle_procesora;

    start = clock(); // Zapisanie czasu startu
    // Wywołanie funkcji dodawania
    int wynik = a + b;
    end = clock(); // Zapisanie czasu zakończenia

    // Obliczenie liczby cykli procesora
    cykle_procesora = (unsigned long long int) (end - start);

    return cykle_procesora;
}

unsigned long long int addTwoFloat(float a, float b) {
    clock_t start, end;
    unsigned long long int cykle_procesora;

    start = clock(); // Zapisanie czasu startu
    // Wywołanie funkcji dodawania
    float wynik = a + b;
    end = clock(); // Zapisanie czasu zakończenia

    // Obliczenie liczby cykli procesora
    cykle_procesora = (unsigned long long int) (end - start);

    return cykle_procesora;
}

int *generateIntNumbers(int iterations) {
    int *numbers = (int *) malloc(iterations * sizeof(int)); // Alokacja pamięci dla tablicy dynamicznej
    if (numbers == NULL) {
        printf("Blad alokacji pamieci.\n");
        exit(1);
    }
    srand(time(NULL));
    // Generowanie liczb całkowitych
    for (int i = 0; i < iterations; i++) {
        numbers[i] = rand(); // Przykładowa generacja liczb całkowitych
    }
    for (int i = 0; i < iterations; i++) {
        printf("%d\n", numbers[i]);
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
        numbers[i] = (float) rand() / RAND_MAX; // Przykładowa generacja liczb zmiennoprzecinkowych z zakresu [0,1]
    }

    for (int i = 0; i < iterations; i++) {
        printf("%.100f\n", numbers[i]);
    }

    return numbers; // Zwracanie wskaźnika do tablicy
}

void testInt(int iterations, int *generatedIntNumbersA, int *generatedIntNumbersB) {
    unsigned long long int  *resultTime = (unsigned long long int *) malloc(iterations * sizeof(unsigned long long int));

    for (int i = 0; i < iterations; ++i) {
        resultTime[i] = addTwoInt(generatedIntNumbersA[i], generatedIntNumbersB[i]);
        printf("%.8f\n", resultTime[i]);
    }
    saveLongLongArrayToFile(resultTime, iterations, "intTime.txt");
}

void testFloat(int iterations, float *generatedFloatNumbersA, float *generatedFloatNumbersB) {
    unsigned long long int  *resultTime = (unsigned long long int *) malloc(iterations * sizeof(unsigned long long int));
    for (int i = 0; i < iterations; ++i) {
        addTwoFloat(generatedFloatNumbersA[i], generatedFloatNumbersB[i]);
    }
    saveLongLongArrayToFile(resultTime, iterations, "floatTime.txt");
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

void saveLongLongArrayToFile(unsigned long long int *array, int size, char *filename) {
    FILE *file = fopen(filename, "w"); // Otwarcie pliku do zapisu
    if (file == NULL) {
        printf("Nie można otworzyć pliku %s\n", filename);
        return;
    }

    // Zapisanie każdej liczby zmiennoprzecinkowej z tablicy do pliku
    for (int i = 0; i < size; i++) {
        fprintf(file, "%llu\n", array[i]);
    }

    fclose(file); // Zamknięcie pliku

}
