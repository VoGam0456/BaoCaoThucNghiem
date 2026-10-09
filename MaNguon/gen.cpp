#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
using namespace std;

int main() {
    const int SO_PHAN_TU = 1000000;
    mt19937_64 bo_sinh_ngau_nhien(12345);
    uniform_real_distribution<double> khoang_gia_tri(-1e6, 1e6);

    for (int stt = 1; stt <= 10; stt++) {
        vector<double> day_so(SO_PHAN_TU);
        for (auto &so : day_so) so = khoang_gia_tri(bo_sinh_ngau_nhien);

        if (stt == 1) sort(day_so.begin(), day_so.end());
        if (stt == 2) sort(day_so.begin(), day_so.end(), greater<double>());

        ofstream tep_ghi("data" + to_string(stt) + ".txt");
        tep_ghi << SO_PHAN_TU << "\n";
        for (double so : day_so) tep_ghi << so << " ";
    }
    return 0;
}
