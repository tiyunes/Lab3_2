#ifndef BENCHMARK_H_INCLUDED
#define BENCHMARK_H_INCLUDED
#include <chrono>
#include <fstream>
#include "sparse_matrix.h"
#include "sparse_vector.h"
#include "SparseVectorDict.h"
#include "SparseVectorSeq.h"
#include "dictionary.h"

void TimeVector(function<bool(TPair<int, int>, TPair<int, int>)> cmp,
                 function<Sequence<TPair<int, int>>*(Sequence<TPair<int, int>>*, function<bool(TPair<int, int>, TPair<int, int>)>)> sorter)
{
    int N = 11;
    int a[N] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000};

    srand(time(NULL));
    int r;
    ofstream file("vector.txt");
    ofstream fout("time_vector.txt");
    ofstream graphD1("graphD1.txt");
    ofstream graphD2("graphD2.txt");
    ofstream graphS1("graphS1.txt");
    ofstream graphS2("graphS2.txt");

    for (int i = 0; i < N; i++)
    {
        vector<int>* v = new vector<int>;
        fout << "Size of vector = " << a[i] << endl;
        file << "Size of vector = " << a[i] << endl;
        for (int j = 0; j < a[i]; j++)
        {
            r = (rand() % 2) * rand();
            v->push_back(r);
            file << r << " ";
        }

        auto start1 = chrono::steady_clock::now();
        SparseVector<int>* sparseVector = (SparseVector<int>*) new SparseVectorDict<int>(v, 0, cmp);
        auto end1 = chrono::steady_clock::now();
        chrono::duration<double, milli> duration1 = end1 - start1;
        double time1 = duration1.count();
        fout << "Time of creation the sparse vector with size: " << v->size() << " based on dictionary = " << time1 << " ms" << endl;
        graphD1 << v->size() << " " << time1 << endl;

        auto start2 = chrono::steady_clock::now();
        int x = sparseVector->Get(r % (v->size() / 2));
        auto end2 = chrono::steady_clock::now();
        chrono::duration<double, milli> duration2 = end2 - start2;
        double time2 = duration2.count();
        fout << "Time of getting the random element in the sparse vector with size: " <<
        v->size() << " based on dictionary = " << time2 << " ms" << endl;
        graphD2 << v->size() << " " << time2 << endl;

        auto start3 = chrono::steady_clock::now();
        SparseVector<int>* sparseVector3 = (SparseVector<int>*) new SparseVectorSeq<int>(v, 0, cmp, sorter);
        auto end3 = chrono::steady_clock::now();
        chrono::duration<double, milli> duration3 = end3 - start3;
        double time3 = duration3.count();
        fout << "Time of creation the sparse vector with size: " << v->size() <<
        " based on sorted sequence = " << time3 << " ms" << endl;
        graphS1 << v->size() << " " << time3 << endl;

        auto start4 = chrono::steady_clock::now();
        int y = sparseVector3->Get(r % (v->size() / 2));
        auto end4 = chrono::steady_clock::now();
        chrono::duration<double, milli> duration4 = end4 - start4;
        double time4 = duration4.count();
        fout << "Time of getting the random element in the sparse vector with size: " <<
        v->size() << " based on sorted sequence = " << time4 << " ms" << endl;
        graphS2 << v->size() << " " << time4 << endl;
    }

    FILE *gnuplotP = popen("gnuplot -persist", "w");
    if (gnuplotP)
    {
        fprintf(gnuplotP, "set encoding utf8\n");
        fprintf(gnuplotP, "set terminal windows\n");
        fprintf(gnuplotP, "set output \"plotGraph.pdf\" \n");
        fprintf(gnuplotP, "set multiplot layout 2,1 \n");
        fprintf(gnuplotP, "set xlabel 'Size of vector'\n");
        fprintf(gnuplotP, "set ylabel 'Time (in ms)'\n");
        fprintf(gnuplotP, "set title 'Time of creating'\n");
        fprintf(gnuplotP, "set xrange [*:*]\n");
        fprintf(gnuplotP, "set yrange [*:*]\n");
        fprintf(gnuplotP, "plot \"graphD1.txt\"  using 1:2 w lines title \"Vector based on dictionary\"\n");
        fprintf(gnuplotP, "plot \"graphS1.txt\"  using 1:2 w lines lc rgb \"blue\" title \"Vector based on sorted sequence\"\n");
        fprintf(gnuplotP, "unset multiplot\n");
        fflush(gnuplotP);
        fprintf(gnuplotP,"exit \n");
        pclose(gnuplotP);
    }

    FILE *gnuP = popen("gnuplot -persist", "w");
    if (gnuP)
    {
        fprintf(gnuP, "set encoding utf8\n");
        fprintf(gnuP, "set terminal windows\n");
        fprintf(gnuP, "set output \"plotGraph2.pdf\" \n");
        fprintf(gnuP, "set multiplot layout 2,1 \n");
        fprintf(gnuP, "set xlabel 'Size of vector'\n");
        fprintf(gnuP, "set ylabel 'Time (in ms)'\n");
        fprintf(gnuP, "set title 'Time of getting the random element'\n");
        fprintf(gnuP, "set xrange [*:*]\n");
        fprintf(gnuP, "set yrange [*:*]\n");
        fprintf(gnuP, "plot \"graphD2.txt\"  using 1:2 w lines title \"Vector based on dictionary\"\n");
        fprintf(gnuP, "plot \"graphS2.txt\"  using 1:2 w lines lc rgb \"blue\" title \"Vector based on sorted sequence\"\n");
        fprintf(gnuP, "unset multiplot\n");
        fflush(gnuP);
        fprintf(gnuP,"exit \n");
        pclose(gnuP);
    }

}

void TimeMatrix(vector<TPair<int, TPair<int, int>>>* v, int rows, int columns, int null,
                 function<bool(TPair<int, TPair<int, int>>, TPair<int, TPair<int, int>>)> cmp)
{
    ofstream fout("time_matrix.txt");
    auto start1 = chrono::steady_clock::now();
    SparseMatrix<int>* sparseMatrix = new SparseMatrix<int>(v, rows, columns, null, cmp);
    auto end1 = chrono::steady_clock::now();
    chrono::duration<double, milli> duration1 = end1 - start1;
    double time1 = duration1.count();
    fout << "Time of creation the sparse matrix based on B tree = " << time1 << " ms" << endl;

    srand(time(NULL));
    int r;
    r = rand() % (v->size() / 2);
    auto start2 = chrono::steady_clock::now();
    BTreeNode<TPair<int, TPair<int, int>>>* y = sparseMatrix->FindKey(v->at(0).GetKey());
    auto end2 = chrono::steady_clock::now();
    chrono::duration<double, milli> duration2 = end2 - start2;
    double time2 = duration2.count();
    fout << "Time of finding the random element in the sparse matrix based on B Tree = " << time2 << " ms" << endl;
}


#endif // BENCHMARK_H_INCLUDED
