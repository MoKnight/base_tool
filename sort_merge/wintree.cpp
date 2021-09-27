/*
 * @Description: 
 * @version: 
 * @Author: MoonKnight
 * @Date: 2021-09-26 09:32:39
 * @LastEditors: MoonKnight
 * @LastEditTime: 2021-09-28 00:11:31
 */
#include "wintree.h"
#include "traits.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <cmath>
#include <iostream>

using namespace traits;
template <class T>
wintree<T>::wintree()
{   
    comp_data_vector.resize(LENGTH);
    min_value_vector.resize(1);
    min_value[0] = TypeTraits<T>::get_min();
    min_value_vector[0] = TypeTraits<T>::get_min();
    ori_data[LENGTH / 2] = min_value;
    ori_data_vector[LENGTH / 2] = &min_value_vector;   
    memset(flag, false, sizeof(flag)); 
    count = 0;
}

template <class T>
wintree<T>::~wintree(){};

template <class T>
bool wintree<T>::add_ori_data(T* data_pointer, int size)
{

    if (count > LENGTH / 2)
    {
        printf("there are already 64 groups of data in this wintree");
        return false;
    }
    ori_data[count] = data_pointer;
    left_length[count] = size - 1;
    if (size <= 0)
    {
        return true;
    }
    flag[count] = true;
    count++;
    set_count(count);
    return true;
}

template <class T>
bool wintree<T>::add_ori_data(vector<T>* data_pointer)
{
    if (count > LENGTH / 2)
    {
        printf("there are already 64 groups of data in this wintree");
        return false;
    }
    ori_data_vector[count] = data_pointer;
    iter_vector[count] = (*data_pointer).begin();
    if ((*data_pointer).empty())
    {
        return true;
    }
    flag[count] = true;
    count++;
    set_count(count);
    return true;
}

template <class T>
bool wintree<T>::print(FILE *fp)
{
    // todo
    return true;
}

template <class T>
bool wintree<T>::print(char *filename)
{
    // todo
    return true;
}

template <class T>
bool wintree<T>::compare_all()
{
    if (count == 0)
    {
        return false;
    }
    //first round
    int pos = 0;
    for (int i = 0; i < count; i += 2)
    {
        pos = i / 2 + (LENGTH / 2) / 2 - 1;
        if (flag[i] && flag[i + 1])
        {
            comp_data[pos] = *ori_data[i] > *ori_data[i + 1] ? i : i + 1;
        }
        else if (flag[i])
        {
            comp_data[pos] = i;
        }
        else if (flag[i + 1])
        {
            comp_data[pos] = i + 1;
        }
        else
        {
            comp_data[pos] = LENGTH / 2;
        }
    }

    for (int i = ((LENGTH / 2) / 2) - 2; i >= 0; i--)
    {
        comp_data[i] = *ori_data[comp_data[2 * i + 1]] > *ori_data[comp_data[2 * i + 2]] ? comp_data[2 * i + 1] : comp_data[2 * i + 2];
    }

    data.push_back(*ori_data[comp_data[0]]);

    //second round
    while (count != 0)
    {
        //update
        if (left_length[comp_data[0]] == 0)
        {
            flag[comp_data[0]] = false;
            count--;
            ori_data[comp_data[0]] = min_value;
            if (count == 0)
            {
                break;
            }
        }
        else
        {
            ori_data[comp_data[0]] += 1;
            left_length[comp_data[0]]--;
        }

        int curnum = comp_data[0] / 2 + (LENGTH / 2) / 2 - 1; //comp_data中的位置
        int midnum = (curnum - (LENGTH / 2) / 2 + 1) * 2;
        if (flag[midnum] && flag[midnum + 1])
        {
            comp_data[curnum] = *ori_data[midnum + 1] > *ori_data[midnum] ? midnum + 1 : midnum;
        }
        else if (flag[midnum])
        {
            comp_data[curnum] = midnum;
        }
        else if (flag[midnum + 1])
        {
            comp_data[curnum] = midnum + 1;
        }
        else
        {
            comp_data[curnum] = LENGTH / 2;
        }

        //quick round
        for (int i = 0; i < 5; i++)
        {
            curnum--;
            curnum /= 2;
            comp_data[curnum] = *ori_data[comp_data[curnum * 2 + 1]] > *ori_data[comp_data[curnum * 2 + 2]] ? comp_data[curnum * 2 + 1] : comp_data[curnum * 2 + 2];
        }
        data.push_back(*ori_data[comp_data[0]]);
    }

    for (const auto &c : data)
        cout << c << " ";
    return true;
}

template <class T>
bool wintree<T>::compare_all_vector()
{
    if (count == 0)
    {
        return false;
    }
    //first round
    int pos = 0;
    for (int i = 0; i < count; i += 2)
    {
        pos = i / 2 + (LENGTH / 2) / 2 - 1;
        if (flag[i] && flag[i + 1])
        {
            comp_data[pos] = *iter_vector[i]> *iter_vector[i+1] ? i : i + 1;
        }
        else if (flag[i])
        {
            comp_data[pos] = i;
        }
        else if (flag[i + 1])
        {
            comp_data[pos] = i + 1;
        }
        else
        {
            comp_data[pos] = LENGTH / 2;
        }
    }

    for (int i = ((LENGTH / 2) / 2) - 2; i >= 0; i--)
    {
        comp_data[i] = *iter_vector[comp_data[2 * i + 1]] > *iter_vector[comp_data[2 * i + 2]] ? comp_data[2 * i + 1] : comp_data[2 * i + 2];
    }

    data.push_back(*iter_vector[comp_data[0]]);

    //second round
    while (count != 0)
    {
        //update
        if (iter_vector[comp_data[0]] == (*ori_data_vector[comp_data[0]]).end()-1)
        {
            flag[comp_data[0]] = false;
            count--;
            ori_data[comp_data[0]] = min_value;
            if (count == 0)
            {
                break;
            }
        }
        else
        {
            iter_vector[comp_data[0]] += 1;
        }

        int curnum = comp_data[0] / 2 + (LENGTH / 2) / 2 - 1; //comp_data中的位置
        int midnum = (curnum - (LENGTH / 2) / 2 + 1) * 2;
        if (flag[midnum] && flag[midnum + 1])
        {
            comp_data[curnum] = *iter_vector[midnum + 1] > *iter_vector[midnum] ? midnum + 1 : midnum;
        }
        else if (flag[midnum])
        {
            comp_data[curnum] = midnum;
        }
        else if (flag[midnum + 1])
        {
            comp_data[curnum] = midnum + 1;
        }
        else
        {
            comp_data[curnum] = LENGTH / 2;
        }

        //quick round
        for (int i = 0; i < 5; i++)
        {
            curnum--;
            curnum /= 2;
            comp_data[curnum] = *(iter_vector[comp_data[curnum * 2 + 1]]) > *(iter_vector[comp_data[curnum * 2 + 2]]) ? comp_data[curnum * 2 + 1] : comp_data[curnum * 2 + 2];
        }
        data.push_back(*iter_vector[comp_data[0]]);
    }

    for (const auto &c : data)
        cout << c << " ";
    return true;
}
