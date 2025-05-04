#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <complex>

class SpinSystem
{
    protected:
        int site_number;
        int dimension;
        std::vector<std::vector<int>> basis;
    public:
        SpinSystem(int site_num):site_number(site_num),dimension(1<<site_num)
        {
            basis=generate_basis();
        }
        SpinSystem(int site_num,int dimension,const std::vector<std::vector<int>>& custom_basis)
            :site_number(site_num),dimension(dimension),basis(custom_basis){}

        int get_site_number(){return site_number;}
        int get_dimension(){return dimension;}
        std::vector<std::vector<int>> get_basis(){return basis;}

        std::vector<std::vector<int>> generate_basis()
        {
            std::vector<std::vector<int>> states(dimension, std::vector<int>(site_number,0));
            for(int i=0;i<dimension;i++)
            {
                int temp=i;
                for(int j=0;j<site_number;j++)
                {
                    states[i][j]=temp%2;
                    temp/=2;
                }
            }
            return states;
        }

        std::vector<int> index_to_binary(int index)
        {
            std::vector<int> state(site_number);
            for(int i=0;i<site_number;i++) state[i]=(index>>i)&1;
            return state;
        }
        int binary_to_index(const std::vector<int>& state)
        {
            int index=0;
            for(int i=0;i<site_number;i++) index|=state[i]<<i;
            return index;
        }
};

class SpinSystemU1 : public SpinSystem
{
    private:
        int up_num;

        std::vector<std::vector<int>> generate_U1_basis(int up_num) const
        {
            int new_dimension=1;
            for(int i=site_number;i>site_number-up_num;i--) new_dimension *= i;
            for(int i = 1; i <= up_num; i++) new_dimension /= i;

            std::vector<std::vector<int>> new_basis;
            for(int i = 0; i < (1 << site_number); i++)
            {
                std::vector<int> state(site_number);
                int count = 0;
                for(int j = 0; j < site_number; j++)
                {
                    state[j] = (i >> j) & 1;
                    if(state[j] == 0) count++;
                }
                if(count == up_num)
                    new_basis.push_back(state);
            }
            return new_basis;
        }

    public:
        SpinSystemU1(int site_num, int up_num)
            : SpinSystem(site_num), up_num(up_num)
        {
            basis = generate_U1_basis(up_num);
            dimension = basis.size();
        }

        int get_up_num() const { return up_num; }

        std::vector<int> index_to_binary_U1(int index) const
        {
            return basis[index];
        }
        int binary_to_index_U1(const std::vector<int>& state) const
        {
            for(int i = 0; i < dimension; i++)
                if(basis[i] == state) return i;
            return -1;
        }
};
