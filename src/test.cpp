#include <bits/stdc++.h>
#include <all>
using namespace std;
void IsingHam(SpinSystem S, vector<vector<double>>& hamiltonian)
{
    int site_number=S.get_site_number();
    int dimension=S.get_dimension();
    vector<vector<int>> basis=S.get_basis();
    for(int i=0;i<dimension;i++)
    {
        double first=0.0;
        for(int j=0;j<site_number-1;j++)
        {
            double temp=1.0;
            if(basis[i][j]==basis[i][j+1]) temp=-0.25;
            else temp=0.25;
            first+=temp;
        }
        hamiltonian[i][i]=first;
        for(int j=0;j<site_number;j++)
        {
            vector<int> copy_of_state=basis[i];
            if(basis[i][j]==1)
            {
                copy_of_state[j]=0;
                int  temp=S.binary_to_index(copy_of_state);
                hamiltonian[i][temp]+=-0.5;
            }
            else
            {
                copy_of_state[j]=1;
                int  temp=S.binary_to_index(copy_of_state);
                hamiltonian[i][temp]+=-0.5;
            }
        }
    }
}
int main()
{
    cout<<fixed<<setprecision(15);

    cerr<<"preparing hamiltonian..."<<endl;
    int site_number=10;
    SpinSystem system(site_number);
    int dimension=system.get_dimension();
    vector<vector<double>> hamiltonian(dimension,vector<double>(dimension,0.0));

    IsingHam(system,hamiltonian);

    vector<double> eigenvals(dimension);
    vector<double> temp_ham(dimension*dimension);
    int index=0;
    for(int i=0;i<dimension;i++)for(int j=0;j<dimension;j++) temp_ham[index]=hamiltonian[j][i],index++;

    diagonalize(dimension,temp_ham,eigenvals);
    vector<vector<double>> eigenstates(dimension,vector<double>(dimension,0.0));
    index=0;
    for(int i=0;i<dimension;i++)for(int j=0;j<dimension;j++) eigenstates[i][j]=temp_ham[index],index++;

}
