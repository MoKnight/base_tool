/*
 * @Description: 
 * @version: 
 * @Author: MoonKnight
 * @Date: 2021-09-26 09:32:33
 * @LastEditors: MoonKnight
 * @LastEditTime: 2021-09-28 00:08:32
 */
#ifndef __WINTREE_H__
#define __WINTREE_H__

#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <vector>
#define LENGTH 128

using namespace std;

template <class T>
class wintree
{

public:
  wintree();
  ~wintree();

  /**
   * @name: 
   * @test: test font
   * @msg: load array中的数据
   * @param {int} size
   * @return {*}
   */
  bool add_ori_data(T *data_pointer, int size);

  /**
   * @name: 
   * @test: test font
   * @msg: load vector 的数据
   * @param {vector<T>} data_pointer
   * @return {*}
   */
  bool add_ori_data(vector<T> *data_pointer);

  /**
   * @name: 
   * @test: test font
   * @msg: 排序
   * @param {*}
   * @return {*}
   */
  bool compare_all();

  /**
   * @name: 
   * @test: test font
   * @msg: 
   * @param {*}
   * @return {*}
   */
  bool compare_all_vector();

  /**
   * @name: 
   * @test: test font
   * @msg: 打印结果至fp指向的文件
   * @param {FILE} *fp
   * @return {*}
   */
  bool print(FILE *fp);

  /**
   * @name: 
   * @test: test font
   * @msg: 打印结果至filename指向的文件
   * @param {char} *filename
   * @return {*}
   */
  bool print(char *filename);

  int get_count() { return count; }
  void set_count(int new_count) { count = new_count; }

private:
  vector<T> min_value_vector; //当前数据类型的最小值
  T min_value[1];             //当前数据类型的最小值

  T *ori_data[LENGTH / 2 + 1];   //以array做底层
  int comp_data[LENGTH / 2 - 1]; //做比较array空间
  vector<T> data;                //结果缓存
  int left_length[LENGTH / 2];   //以array为底层时，需要记录剩余的array数据个数
  bool flag[LENGTH / 2];         //判断该数组是否存在的标志位

  vector<T> *ori_data_vector[LENGTH / 2 + 1];           //以vector做底层，适配各种容器的转换函数
  typename vector<T>::iterator iter_vector[LENGTH / 2]; //以array为底层时，需要记录当前迭代器的位置
  vector<T> comp_data_vector;                           //做比较array空间
  int count;                                            //当前剩余需要排序的数组
};
#endif