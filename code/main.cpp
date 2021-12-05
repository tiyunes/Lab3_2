#include <iostream>
#include <utility>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "dictionary.h"
#include "STUDENTS.H"
#include "histogram.h"
#include "benchmark.h"
#include "ArraySequence.h"
#include "SortedSequence.h"
#include "SFS.h"
#include "ISorter.h"
#include "sparse_matrix.h"
#include "sparse_vector.h"
#include "SparseVectorDict.h"
#include "SparseVectorSeq.h"
#include "BTree.h"
#include "BTree_node.h"
#include "tests.h"

using namespace std;


bool comp2(int a, int b)
{
    if(a < b)
    {
        return 1;
    }
    else return 0;
}

function<bool(int, int)>compInt2 = comp2;

int main()
{
    pair<int, int> p0;
    p0.first = 0;
    p0.second = 0;
    TPair<int, int> pair0(p0);
    TPair<int, int> l0(p0);

    pair<int, int> p1;
    p1.first = 11;
    p1.second = 12;
    TPair<int, int> pair1(p1);
    TPair<int, int> l1(p1);

    pair<int, int> p2;
    p2.first = 4;
    p2.second = 1;
    TPair<int, int> pair2(p2);
    TPair<int, int> l2(p2);

    pair<int, int> p3;
    p3.first = 1;
    p3.second = 10;
    TPair<int, int> pair3(p3);
    TPair<int, int> l3(p3);

    vector<int>* v = new vector<int>;
    v->push_back(4);
    v->push_back(0);
    v->push_back(3);
    SparseVector<int>* sparseVector = (SparseVector<int>*) new SparseVectorDict<int>(v, 0, cmpKey);
    cout << sparseVector->Get(1) << endl;

    vector<TPair<int, TPair<int, int>>>* vPair = new vector<TPair<int, TPair<int, int>>>;
    pair<int, TPair<int, int>> p4;
    p4.second = l1;
    p4.first = 2;
    TPair<int, TPair<int, int>> pair4(p4);

    pair<int, TPair<int, int>> p5;
    p5.second = l2;
    p5.first = 3;
    TPair<int, TPair<int, int>> pair5(p5);

    pair<int, TPair<int, int>> p6;
    p6.second = l3;
    p6.first = 7;
    TPair<int, TPair<int, int>> pair6(p6);

    vPair->push_back(pair4);
    vPair->push_back(pair5);
    vPair->push_back(pair6);

    int var = 0;
    while (var != 5)
    {
        cout << "Choose the option: " << endl;
        cout << "1. Histogram " << endl << "2. Sparse vector" << endl
        << "3. Sparse matrix" << endl << "4. Search frequent subsequences" << endl
        << "5. Exit" << endl;
        cin >> var;
        cout << endl;
        switch (var)
        {
        case 1:
            {
                int length = 0;
                cout << "Choose the number of students" << endl;
                cin >> length;
                cout << endl;
                Sequence<Student>* sStudent = new ArraySequence<Student>();
                for (int i = 0; i < length; i++)
                {
                    int number, series;
                    string s;
                    cout << "Enter the number and series of an ID of " << i + 1 << " student" << endl;
                    cin.ignore();
                    getline(cin >> ws, s);
                    istringstream iss(s);
                    iss >> number >> series;
                    StudentID* id = new StudentID(number, series);
                    cout << endl;

                    string s2;
                    cout << "Enter the first name and second name of " << i + 1 << " student" << endl;
                    cin.ignore();
                    getline(cin >> ws, s2);
                    istringstream iss2(s2);
                    string firstName, lastName;
                    iss2 >> firstName >> lastName;
                    string* firstName1 = new string(firstName);
                    string* lastName1 = new string(lastName);
                    cout << endl;

                    int age;
                    cout  << "Enter the age of " << i + 1 << " student" << endl;
                    cin >> age;
                    cout << endl;

                    int grade;
                    cout << "Enter the grade of " << i + 1 << " student" << endl;
                    cin >> grade;
                    cout << endl;

                    Student student(id, age, grade, firstName1, lastName1);
                    sStudent->Append(student);
                    cout << endl;
                }
                int N;
                cout << "Choose the amount of parts: " << endl;
                cin >> N;
                cout << endl;
                cout << "The parameter of partition: " << endl;
                int j = 0;
                cout << "Choose the parameter of partition: " << endl;
                cout << "1. Age " << endl << "2. Number of ID" << endl
                << "3. Grade" << endl;
                cin >> j;
                cout << endl;
                switch (j)
                {
                case 1:
                    {
                        int (Student::*GetP)() = Student::GetAge;
                        Histogram<int, int>* h = new Histogram<int, int>(sStudent, N, cmpKey, GetP);
                        ofstream file;
                        file.open("histogram_data.txt");
                        for (int i = 1; i <= h->GetSize(); i++)
                        {
//                            cout << i << " " << h->GetSubAmount(i) << endl;
                            file << (h->GetMin() + (i - 1)* h->GetRange()) << " " << h->GetSubAmount(i) << '\n';
                        }
                        cout << "Histogram by age" << endl;
                        file.close();
                        FILE *gnuplotPipe = popen("gnuplot -persist", "w");
                        if (gnuplotPipe)
                        {
                            fprintf(gnuplotPipe, "set encoding utf8\n");
                            fprintf(gnuplotPipe, "set terminal windows\n");
                            fprintf(gnuplotPipe, "set output \"plot3.pdf\" \n");
                            fprintf(gnuplotPipe, "min = %d\n", h->GetMin());
                            fprintf(gnuplotPipe, "max = %d\n", h->GetMax());
                            fprintf(gnuplotPipe, "set xlabel 'Values'\n");
                            fprintf(gnuplotPipe, "set ylabel 'Amount of subset'\n");
                            fprintf(gnuplotPipe, "set title 'Histogram'\n");
                            fprintf(gnuplotPipe, "set xrange [%d:%d]\n", h->GetMin(), h->GetMax());
                            fprintf(gnuplotPipe, "set yrange [0:%d]\n", sStudent->GetLength() + 1);
                            //fprintf(gnuplotPipe, "set yrange = %d\n, %d\n", h->GetMin(), h->GetMax());
                            fprintf(gnuplotPipe, "width = %lf\n", 1.0 * (h->GetMax() - h->GetMin()) / N);
                            fprintf(gnuplotPipe, "hist(x,width)=x+width/2.0\n");
                            fprintf(gnuplotPipe, "set boxwidth width*1.0\n");
                            fprintf(gnuplotPipe, "set style fill solid 0.5\n");
                            fprintf(gnuplotPipe, "set tics out nomirror\n");
                            fprintf(gnuplotPipe, "plot \"histogram_data.txt\" u (hist($1,width)):2 smooth freq w boxes lc rgb \"blue\" notitle\n");
                            fflush(gnuplotPipe);
                            fprintf(gnuplotPipe,"exit \n");
                            pclose(gnuplotPipe);
                        }
                        cout << endl;
                        break;
                    }
                case 2:
                    {
                        int (Student::*GetP)() = Student::GetNumber;
                        Histogram<int, int>* h = new Histogram<int, int>(sStudent, N, cmpKey, GetP);
                        ofstream file;
                        file.open("histogram_data.txt");
                        for (int i = 1; i <= h->GetSize(); i++)
                        {
//                            cout << i << " " << h->GetSubAmount(i) << endl;
                            file << (h->GetMin() + (i - 1)* h->GetRange()) << " " << h->GetSubAmount(i) << '\n';
                        }
                        cout << "Histogram by number of ID" << endl;
                        file.close();
                        FILE *gnuplotPipe = popen("gnuplot -persist", "w");
                        if (gnuplotPipe)
                        {
                            fprintf(gnuplotPipe, "set encoding utf8\n");
                            fprintf(gnuplotPipe, "set terminal windows\n");
                            fprintf(gnuplotPipe, "set output \"plot3.pdf\" \n");
                            fprintf(gnuplotPipe, "min = %d\n", h->GetMin());
                            fprintf(gnuplotPipe, "max = %d\n", h->GetMax());
                            fprintf(gnuplotPipe, "set xlabel 'Values'\n");
                            fprintf(gnuplotPipe, "set ylabel 'Amount of subset'\n");
                            fprintf(gnuplotPipe, "set title 'Histogram'\n");
                            fprintf(gnuplotPipe, "set xrange [%d:%d]\n", h->GetMin(), h->GetMax());
                            fprintf(gnuplotPipe, "set yrange [0:%d]\n", sStudent->GetLength() + 1);
                            //fprintf(gnuplotPipe, "set yrange = %d\n, %d\n", h->GetMin(), h->GetMax());
                            fprintf(gnuplotPipe, "width = %lf\n", 1.0 * (h->GetMax() - h->GetMin()) / N);
                            fprintf(gnuplotPipe, "hist(x,width)=x+width/2.0\n");
                            fprintf(gnuplotPipe, "set boxwidth width*1.0\n");
                            fprintf(gnuplotPipe, "set style fill solid 0.5\n");
                            fprintf(gnuplotPipe, "set tics out nomirror\n");
                            fprintf(gnuplotPipe, "plot \"histogram_data.txt\" u (hist($1,width)):2 smooth freq w boxes lc rgb \"blue\" notitle\n");
                            fflush(gnuplotPipe);
                            fprintf(gnuplotPipe,"exit \n");
                            pclose(gnuplotPipe);
                        }
                        cout << endl;
                        break;
                    }
                case 3:
                    {
                        int (Student::*GetP)() = Student::GetGrade;
                        Histogram<int, int>* h = new Histogram<int, int>(sStudent, N, cmpKey, GetP);
                        ofstream file;
                        file.open("histogram_data.txt");
                        for (int i = 1; i <= h->GetSize(); i++)
                        {
                            file << (h->GetMin() + (i - 1)* h->GetRange()) << " " << h->GetSubAmount(i) << '\n';
                        }
                        cout << "Histogram by grade" << endl;
                        file.close();
                        FILE *gnuplotPipe = popen("gnuplot -persist", "w");
                        if (gnuplotPipe)
                        {
                            fprintf(gnuplotPipe, "set encoding utf8\n");
                            fprintf(gnuplotPipe, "set terminal windows\n");
                            fprintf(gnuplotPipe, "set output \"plot3.pdf\" \n");
                            fprintf(gnuplotPipe, "min = %d\n", h->GetMin());
                            fprintf(gnuplotPipe, "max = %d\n", h->GetMax());
                            fprintf(gnuplotPipe, "set xlabel 'Values'\n");
                            fprintf(gnuplotPipe, "set ylabel 'Amount of subset'\n");
                            fprintf(gnuplotPipe, "set title 'Histogram'\n");
                            fprintf(gnuplotPipe, "set xrange [%d:%d]\n", h->GetMin(), h->GetMax());
                            fprintf(gnuplotPipe, "set yrange [0:%d]\n", sStudent->GetLength() + 1);
                            fprintf(gnuplotPipe, "width = %lf\n", 1.0 * (h->GetMax() - h->GetMin()) / N);
                            fprintf(gnuplotPipe, "hist(x,width)=x+width/2.0\n");
                            fprintf(gnuplotPipe, "set boxwidth width*1.0\n");
                            fprintf(gnuplotPipe, "set style fill solid 0.5\n");
                            fprintf(gnuplotPipe, "set tics out nomirror\n");
                            fprintf(gnuplotPipe, "plot \"histogram_data.txt\" u (hist($1,width)):2 smooth freq w boxes lc rgb \"blue\" notitle\n");
                            fflush(gnuplotPipe);
                            fprintf(gnuplotPipe,"exit \n");
                            pclose(gnuplotPipe);
                        }
                        cout << endl;
                        break;
                    }
                }
                break;
            }
                case 2:
                    {
                        vector<int>* v = new vector<int>;
                        int length;
                        cout << "Enter the number of elements in vector: " << endl;
                        cin >> length;
                        cout << endl;
                        int x;
                        string s;
                        cin.ignore();
                        cout << "Enter the elements of vector: " << endl;
                        getline(cin, s);
                        istringstream iss(s);
                        for (int  i = 0; i < length; i++)
                        {
                            iss >> x;
                            v->push_back(x);
                        }
                        cout << endl;
                        SparseVector<int>* sparseVector = (SparseVector<int>*) new SparseVectorDict<int>(v, 0, cmpKey);
                        cout << "Number of non null elements: " << sparseVector->GetSize() << endl;
                        cout << "Enter the index of element: " << endl;
                        int index;
                        cin >> index;
                        cout << endl;
                        if (index <= sparseVector->GetSize())
                        {
                            cout << "Corresponding element: " << sparseVector->Get(index - 1) << endl;
                        }
                        else
                        {
                            cout << "Invalid index" << endl;
                        }
                        cout << endl;
                        break;
                    }
                case 3:
                    {
                        vector<TPair<int, TPair<int, int>>>* vectPair = new vector<TPair<int, TPair<int, int>>>;
                        cout << "Enter the number of rows in matrix: " << endl;
                        int rows;
                        cin >> rows;
                        cout << endl;
                        cout << "Enter the number of columns in matrix: " << endl;
                        int columns;
                        cin >> columns;
                        cout << endl;
                        for (int i = 0; i < rows; i++)
                        {
                            cout << "Enter the elements of " << i + 1 << " row:" << endl;
                            string s;
                            s.clear();
                            getline(cin >> ws, s);
                            istringstream iss(s);
                            vector<int> v;
                            int x;
                            iss >> x;
                            for (int j = 0; j < columns; j++)
                            {
                                v.push_back(x);
                                iss >> x;
                            }
                            cout << endl;
                            for (int  j = 0; j < columns; j++)
                            {
                                pair<int, int> pp1;
                                pp1.first = i;
                                pp1.second = j;
                                TPair<int, int> ppair1(pp1);
                                pair<int, TPair<int, int>> pp2;
                                pp2.first = v[j];
                                pp2.second = ppair1;
                                TPair<int, TPair<int, int>> element(pp2);
                                vectPair->push_back(element);
                            }
                        }
                        SparseMatrix<int>* sparseMatrix3 = new SparseMatrix<int>(vectPair, rows, columns, 0, compMatrix);
                        vector<TPair<int, TPair<int, int>>>* vPair2 = new vector<TPair<int, TPair<int, int>>>;
                        sparseMatrix3->GetTree()->ToVector(vPair2);
                        cout << "Number of non null elements: " << vPair2->size() << endl;
                        cout << "Non null elements and their position: " << endl;
                        for (int  i = 0; i < vPair2->size(); i++)
                        {
                            cout << "(" << vPair2->at(i).GetElement().GetKey() + 1 << ", " <<
                             vPair2->at(i).GetElement().GetElement() + 1 << ")" << " " << vPair2->at(i).GetKey() << endl;
                        }
                        cout << endl;
                        break;
                    }
                case 4:
                    {
                        Sequence<char>* sChar = new ArraySequence<char>();
                        cout << "Enter the number of symbols in sequence: " << endl;
                        int length;
                        cin >> length;
                        string strChar;
                        cout << "Enter the symbols of sequence: " << endl;
                        cin.ignore();
                        getline(cin, strChar);
                        for (int i = 0; i < length; i++)
                        {
                            sChar->Append(strChar[i]);
                        }
                        string s;
                        int lmin, lmax;
                        cout << "Enter the min and max sizes of subsequences: " << endl;
                        getline(cin, s);
                        istringstream iss(s);
                        iss >> lmin >> lmax;
                        cout << endl;
                        ISortedSequence<TPair<string, int>>* ISeq = new ISortedSequence<TPair<string, int>>(11);
                        SFS* class1 = (SFS*) new SFS_Seq(sChar, lmin, lmax, compSFS, sorter1);
                        class1->print();
                        cout << endl;
                        break;
                    }

                case 5:
                    break;
                default:
                    {
                        cout << "Choose correct option" << endl;
                        break;
                    }
        }
    }

    TimeVector(cmpKey, sorter2);
//    TimeMatrix(vPair, 1, 3, 0, compMatrix);
    TestSFS();
    TestSparseVector();
    TestSparseMatrix();
    TestHistogram();
    return 0;
}
