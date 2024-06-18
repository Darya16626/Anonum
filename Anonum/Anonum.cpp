#include <iostream>
#include <vector>
#include <thread>
#include <functional>

class MergeSort {
public:
    void Sort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            Sort(arr, left, mid);
            Sort(arr, mid + 1, right);
            Merge(arr, left, mid, right);
        }
    }

    void Merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<int> arr(10);
    std::cout << "Введите 10 целых чисел для сортировки: ";
    for (int i = 0; i < 10; i++) {
        std::cin >> arr[i];
    }

    MergeSort mergeSort;
    auto sortFunc = [&](std::vector<int>& arr) {
        mergeSort.Sort(arr, 0, arr.size() - 1);
        };

    std::thread mergeSortThread(sortFunc, std::ref(arr));
    mergeSortThread.join();

    std::cout << "Сортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
