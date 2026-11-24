#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void sortByExchange(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[i]) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

template <typename T>
class SquareTransformer {
public:
    void transformToSquares(T arr[], int size) const {
        for (int i = 0; i < size; ++i) {
            arr[i] = arr[i] * arr[i];
        }
    }
};

template <typename T>
void printArray(const T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main() {
    int intSortArr[] = {25, -4, 12, 0, -19, 8};
    int intSortSize = sizeof(intSortArr) / sizeof(intSortArr[0]);

    cout << "Original integer array for exchange sort:\n";
    printArray(intSortArr, intSortSize);

    sortByExchange(intSortArr, intSortSize);

    cout << "Sorted integer array (exchange sort):\n";
    printArray(intSortArr, intSortSize);

    double doubleSortArr[] = {3.5, -1.2, 4.8, 0.0, -7.1};
    int doubleSortSize = sizeof(doubleSortArr) / sizeof(doubleSortArr[0]);

    cout << "Original double array for exchange sort:\n";
    printArray(doubleSortArr, doubleSortSize);

    sortByExchange(doubleSortArr, doubleSortSize);

    cout << "Sorted double array (exchange sort):\n";
    printArray(doubleSortArr, doubleSortSize);

    SquareTransformer<int> intSq;
    SquareTransformer<float> floatSq;
    SquareTransformer<long> longSq;

    int sqIntArr[] = {2, -3, 5, 10};
    int sqIntSize = sizeof(sqIntArr) / sizeof(sqIntArr[0]);

    float sqFloatArr[] = {1.5f, -2.5f, 0.5f, 4.0f};
    int sqFloatSize = sizeof(sqFloatArr) / sizeof(sqFloatArr[0]);

    long sqLongArr[] = {1000L, -2000L, 3000L};
    int sqLongSize = sizeof(sqLongArr) / sizeof(sqLongArr[0]);

    intSq.transformToSquares(sqIntArr, sqIntSize);
    cout << "Squared int array:\n";
    printArray(sqIntArr, sqIntSize);

    floatSq.transformToSquares(sqFloatArr, sqFloatSize);
    cout << "Squared float array:\n";
    printArray(sqFloatArr, sqFloatSize);

    longSq.transformToSquares(sqLongArr, sqLongSize);
    cout << "Squared long array:\n";
    printArray(sqLongArr, sqLongSize);

    return 0;
}