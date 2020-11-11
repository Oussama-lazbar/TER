#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include "fonctions.h"
#include <string>
int main()
{
    // constantes et parametres
    double x0(0.), xn(1.), dx0(0.04);
    const int N(int(ceil(xn / dx0)));
    dx0 = xn / N;
    Eigen::VectorXd v1(N + 1), RHS(N + 1), X(N + 1);
    //premier maillage regulier
    for (int i(0); i < N + 1; ++i)
    {
        v1(i) = i * dx0;
        RHS(i) = 0.;
        X(i) = 0.;
    }
    RHS(N) = pow(10, 12);

    // adaptation
    Eigen::MatrixXd Me(N + 1, N + 1);
    Eigen::MatrixXd P(2, 2);
    double xi, xi_plus;
    int iteration(0);
    while (((v1 - X).array().abs()).sum() > 0.0001)
    {
        iteration++;
        std::cout<<"iteration : "<<iteration<<std::endl;
        //matrice d'adaptation Me
        for (int elem(0); elem < N; ++elem)
        {
            xi = v1(elem);
            xi_plus = v1(elem + 1);
            P = Melem(xi, xi_plus);
            Me(elem, elem) += P(0, 0);
            Me(elem, elem + 1) += P(0, 1);
            Me(elem + 1, elem) += P(1, 0);
            Me(elem + 1, elem + 1) += P(1, 1);
        }
        // conditions limites
        Me(0, 0) = pow(10, 12);
        Me(N, N) = pow(10, 12);
        //resolution systeme MeX = RHS
        X = v1;
        v1 = Me.colPivHouseholderQr().solve(RHS);
    }

    // sauvegarde des resultats
    std::ofstream file_out;
    std::string file_name("results.dat");
    file_out.open(file_name);
    for (int i(0);i < N+1; ++i)
    {
        file_out<< v1(i)<<"         "<<u(v1(i))<<"         "<<0<<std::endl;
    }
    file_out.close();
    return 0;
}