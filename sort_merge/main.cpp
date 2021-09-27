/*
 * @Description: 
 * @version: 
 * @Author: MoonKnight
 * @Date: 2021-09-27 11:11:59
 * @LastEditors: MoonKnight
 * @LastEditTime: 2021-09-28 00:19:11
 */
#include "wintree.h"
#include "wintree.cpp"
#include<algorithm>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iostream>
using namespace std;

int compare( const void *arg1, const void *arg2 )
{
    return *(int*)arg2-*(int*)arg1;
}

// int main()
// {

//     srand((unsigned)time(NULL));
//     int rangeR = 1000;
//     int result = 0;

//     int new_data[64][5];
//     int control_num[2] = {4,5};
//     wintree<int> test_wintree;

//     for(int i = 0;i<64;i++)
//     {
//         int k = control_num[i%2];
//         for(int j = 0;j<k;j++)
//         {
//             result = static_cast<int>(rand()/static_cast<int>((RAND_MAX/(rangeR))));
//             new_data[i][j] = result;
//         }
//         qsort(new_data[i],k,sizeof(int),compare);
//         if(test_wintree.add_ori_data(new_data[i],k)){}

//     }
//     for(int i = 0;i<64;i++)
//     {
//         int k = control_num[i%2];
//         for(int j = 0;j<k;j++)
//         {
//             cout<<new_data[i][j]<<' ';
//         }
//     }
//     cout<<endl;
//     cout<<endl;
//     test_wintree.compare_all();
// }

int main()
{
    srand((unsigned)time(NULL));
    int rangeR = 1000;
    int result = 0;

    vector<int>* new_data[64];
    int control_num[2] = {4,5};
    wintree<int> test_wintree;

    for(int i = 0;i<64;i++)
    {
        int k = control_num[i%2];
        new_data[i] = new vector<int>();
        for(int j = 0;j<k;j++)
        {
            result = static_cast<int>(rand()/static_cast<int>((RAND_MAX/(rangeR))));
            (*new_data[i]).push_back(result);
        }
        sort((*new_data[i]).rbegin(), (*new_data[i]).rend());
        // qsort(new_data[i],k,sizeof(int),compare);
        if(test_wintree.add_ori_data(new_data[i])){}

    }
    for(int i = 0;i<64;i++)
    {
        for (const auto &c : *new_data[i])
        cout << c << " ";
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    test_wintree.compare_all_vector();
}
