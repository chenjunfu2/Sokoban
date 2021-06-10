#pragma once

#ifndef _linked_list
#define _linked_list

#include <cstddef>
#include <new>

#include "error.h"


//数据结构体
typedef struct Queue {
	Queue* uQueue = NULL;//上一节点
	int list_x = 0;//移动数据x
	int list_y = 0;//移动数据y
	int list_n = 0;//移动数据n
	Queue* nQueue = NULL;//下一节点
}QUEUE;

//链表指针结构体
typedef struct Node {
	QUEUE* hpQueue = NULL;//头节点指针
	QUEUE* cpQueue = NULL;//尾节点指针
	//int numQueue;//链表个数
}NODE;


//从头部添加一项
extern inline ERR Add_HpQueue(NODE& node, int list_x, int list_y, int list_n);
//从尾部添加一项
extern inline ERR Add_CpQueue(NODE& node, int list_x, int list_y, int list_n);



//查看尾部一项
extern inline ERR See_CpQueue(const NODE& node, int& list_x, int& list_y, int& list_n);
//查看头部一项
extern inline ERR See_HpQueue(const NODE& node, int& list_x, int& list_y, int& list_n);



//移动尾部一项到另外一条链表尾部
extern inline ERR Move_CpQueue_To_CpQueue(NODE& nodeI, NODE& nodeO);
//移动头部一项到另外一条链表头部
extern inline ERR Move_HpQueue_To_HpQueue(NODE& nodeI, NODE& nodeO);



//批量读取（正向）
template <typename T>
extern inline ERR See_All_G(const NODE& node, T fSee_P);
//批量读取（反向）
template <typename T>
extern inline ERR See_All_B(const NODE& node, T fSee_P);
//批量添加（正向）
template <typename T>
extern inline ERR Add_All_G(NODE& node, T fAdd_P);
//批量添加（反向）
template <typename T>
extern inline ERR Add_All_B(NODE& node, T fAdd_P);



//从尾部删除一项
extern inline ERR Del_CpQueue(NODE& node, int& list_x, int& list_y, int& list_n);
//删除所有
extern inline ERR Del_AllQueue(NODE& node);

#endif