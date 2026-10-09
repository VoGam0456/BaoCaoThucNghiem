#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
using namespace std;

void QuickSort(vector<double>& day_so, int trai, int phai) {
    int i = trai;
    int j = phai;
    double chot = day_so[(trai + phai) / 2];

    while (i <= j) {
        while (day_so[i] < chot) i++;
        while (day_so[j] > chot) j--;
        if (i <= j) {
            swap(day_so[i], day_so[j]);
            i++;
            j--;
        }
    }
    if (trai < j) QuickSort(day_so, trai, j);
    if (i < phai) QuickSort(day_so, i, phai);
}

void Heapify(vector<double>& day_so, int n, int i) {
    int lon_nhat = i;
    int con_trai = 2 * i + 1;
    int con_phai = 2 * i + 2;

    if (con_trai < n && day_so[con_trai] > day_so[lon_nhat])
        lon_nhat = con_trai;
    if (con_phai < n && day_so[con_phai] > day_so[lon_nhat])
        lon_nhat = con_phai;

    if (lon_nhat != i) {
        swap(day_so[i], day_so[lon_nhat]);
        Heapify(day_so, n, lon_nhat);
    }
}

void HeapSort(vector<double>& day_so, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(day_so, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(day_so[0], day_so[i]);
        Heapify(day_so, i, 0);
    }
}

void Merge(vector<double>& day_so, vector<double>& mang_tam, int trai, int giua, int phai) {
    int i = trai;
    int j = giua + 1;
    int k = trai;

    while (i <= giua && j <= phai) {
        if (day_so[i] <= day_so[j]) {
            mang_tam[k] = day_so[i];
            i++;
        } else {
            mang_tam[k] = day_so[j];
            j++;
        }
        k++;
    }
    while (i <= giua) {
        mang_tam[k] = day_so[i];
        i++;
        k++;
    }
    while (j <= phai) {
        mang_tam[k] = day_so[j];
        j++;
        k++;
    }
    for (k = trai; k <= phai; k++)
        day_so[k] = mang_tam[k];
}

void MergeSort(vector<double>& day_so, vector<double>& mang_tam, int trai, int phai) {
    if (trai >= phai) return;
    int giua = (trai + phai) / 2;
    MergeSort(day_so, mang_tam, trai, giua);
    MergeSort(day_so, mang_tam, giua + 1, phai);
    Merge(day_so, mang_tam, trai, giua, phai);
}

bool daSapXep(vector<double>& day_so, int n) {
    for (int i = 0; i < n - 1; i++)
        if (day_so[i] > day_so[i + 1]) return false;
    return true;
}

double tinhMs(clock_t bat_dau, clock_t ket_thuc) {
    return (double)(ket_thuc - bat_dau) * 1000.0 / CLOCKS_PER_SEC;
}

int main() {
    ofstream tep_ket_qua("result.csv");
    tep_ket_qua << "Data,Quicksort,Heapsort,Mergesort,sort\n";

    double tong[4] = {0, 0, 0, 0};

    for (int stt = 1; stt <= 10; stt++) {
        cout << "Dang chay file data" << stt << ".txt ..." << endl;
        ifstream tep_doc("data" + to_string(stt) + ".txt");
        int n;
        tep_doc >> n;
        vector<double> day_goc(n);
        for (int i = 0; i < n; i++)
            tep_doc >> day_goc[i];
        double thoi_gian[4];
        clock_t bat_dau, ket_thuc;
        vector<double> a = day_goc;
        bat_dau = clock();
        QuickSort(a, 0, n - 1);
        ket_thuc = clock();
        thoi_gian[0] = tinhMs(bat_dau, ket_thuc);
        if (!daSapXep(a, n)) cout << "QuickSort sai!" << endl;
        a = day_goc;
        bat_dau = clock();
        HeapSort(a, n);
        ket_thuc = clock();
        thoi_gian[1] = tinhMs(bat_dau, ket_thuc);
        if (!daSapXep(a, n)) cout << "HeapSort sai!" << endl;
        a = day_goc;
        vector<double> mang_tam(n);
        bat_dau = clock();
        MergeSort(a, mang_tam, 0, n - 1);
        ket_thuc = clock();
        thoi_gian[2] = tinhMs(bat_dau, ket_thuc);
        if (!daSapXep(a, n)) cout << "MergeSort sai!" << endl;
        a = day_goc;
        bat_dau = clock();
        sort(a.begin(), a.end());
        ket_thuc = clock();
        thoi_gian[3] = tinhMs(bat_dau, ket_thuc);
        if (!daSapXep(a, n)) cout << "sort sai!" << endl;
        tep_ket_qua << stt;
        for (int i = 0; i < 4; i++) {
            tep_ket_qua << "," << thoi_gian[i];
            tong[i] += thoi_gian[i];
        }
        tep_ket_qua << "\n";
    }
    tep_ket_qua << "TB";
    for (int i = 0; i < 4; i++)
        tep_ket_qua << "," << tong[i] / 10;
    tep_ket_qua << "\n";

    tep_ket_qua.close();
    cout << "Ket thuc. Mo file result.csv de xem ket qua." << endl;
    return 0;
}
