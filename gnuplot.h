#ifndef GNUPLOT_H_INCLUDED
#define GNUPLOT_H_INCLUDED
#include <string>
using namespace std;

class gnuplot
{
protected:
    FILE* gnuplotpipe;
public:
    gnuplot()
    {
        gnuplotpipe = popen("gnuplot -persist", "w");
        if (!gnuplotpipe)
        {
            cerr<<("Gnuplot not found");
        }
    }
//    gnuplot~()
//    {
//        fprintf(gnuplotpipe, "exit\n");
//        pclose(gnuplotpipe);
//    }
    void operator() (const string & command)
    {
        fprintf(gnuplotpipe, "%s\n", command.c_str());
        fflush(gnuplotpipe);
    }
};


#endif // GNUPLOT_H_INCLUDED
