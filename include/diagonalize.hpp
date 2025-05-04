#include <vector>
#include <iostream>
#include <complex>
extern "C" {
    void dsyev_(const char* jobz, const char* uplo, const int* n, double* a, const int* lda, double* w, double* work, const int* lwork, int* info);
}
void diagonalize(int dimension,std::vector<double>& hamiltonian,std::vector<double>& eigenvals)
{
    int index=0;
    int lwork=-1;
    std::vector<double> work(1);
    int lda=dimension;
    int info;

    std::cerr<<"Now diagonalizing..."<<std::endl;

    dsyev_("V","U",&dimension,hamiltonian.data(),&lda,eigenvals.data(),work.data(),&lwork,&info);
    lwork = static_cast<int>(work[0]);
    work.resize(lwork);
    dsyev_("V","U",&dimension,hamiltonian.data(),&lda,eigenvals.data(),work.data(),&lwork,&info);

    if(info==0) std::cerr<<"Successfully diagonalized."<<std::endl;
    else std::cerr<<"Diagonalization failed."<<std::endl;
}

