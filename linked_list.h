#pragma once

#ifndef LINKED_LIST
#define LINKED_LIST
#include "error.h"

//数据结构体
typedef struct Queue {
	Queue* uQueue;//上一节点
	int list_x;//移动数据x
	int list_y;//移动数据y
	int list_n;//移动数据n
	Queue* nQueue;//下一节点
}QUEUE;

//链表指针结构体
typedef struct Node {
	QUEUE* hpQueue = NULL;//头节点指针
	QUEUE* cpQueue = NULL;//尾节点指针
	//int numQueue;//链表个数
}NODE;


//从尾部添加一项
inline ERR Add_CpQueue(NODE& node, int list_x, int list_y, int list_n)
{
	ERR error;

	QUEUE* npQueue = NULL;
	try {
		npQueue = new (QUEUE);
	}
	catch (bad_alloc&) {
		no_good(error, new_failed, Add_CpQueue_F);
		return error;
	}

	npQueue->uQueue = node.cpQueue;
	npQueue->nQueue = NULL;

	npQueue->list_x = list_x;
	npQueue->list_y = list_y;
	npQueue->list_n = list_n;

	if (node.hpQueue == NULL)
		node.hpQueue = npQueue;

	node.cpQueue = npQueue;

	return error;
}

//从尾部删除一项
inline ERR Del_CpQueue(NODE& node, int& list_x, int& list_y, int& list_n)
{
	ERR error;

	if (node.cpQueue == NULL)
	{
		no_good(error, cpQueue_Null, Del_CpQueue_F);
		return error;
	}
		
	list_x = node.cpQueue->list_x;
	list_y = node.cpQueue->list_y;
	list_n = node.cpQueue->list_n;

	QUEUE* delQueue = node.cpQueue;
	node.cpQueue = node.cpQueue->uQueue;
	try {
		delete delQueue;
	}
	catch (...) {
		no_good(error, delete_failed, Del_CpQueue_F);
		return error;
	}

	delQueue = NULL;
	if (node.cpQueue == NULL)
		node.hpQueue = NULL;

	return error;
}

//查看尾部一项
inline ERR See_CpQueue(const NODE& node, int& list_x, int& list_y, int& list_n)
{
	ERR error;

	if (node.cpQueue == NULL)
	{
		no_good(error, cpQueue_Null, Find_CpQueue_F);
		return error;
	}

	list_x = node.cpQueue->list_x;
	list_y = node.cpQueue->list_y;
	list_n = node.cpQueue->list_n;

	return error;
}

//删除所有
inline ERR Del_AllQueue(NODE& node)
{
	ERR error;
	if (node.hpQueue == NULL)
		return error;

	QUEUE* delQueue = node.hpQueue;

	while (delQueue != NULL)
	{
		node.hpQueue = node.hpQueue->nQueue;
		try {
			delete delQueue;
		}
		catch (...) {
			no_good(error, delete_failed, Del_AllQueue_F);
			return error;
		}
		delQueue = node.hpQueue;
	}

	node.cpQueue = node.hpQueue = NULL;

	return error;
}


//批量读取（正向）
inline ERR See_All(NODE& node, bool(&fSee_P)(int&, int&, int&))
{
	ERR error;
	if (node.hpQueue == NULL)
	{
		no_good(error, hpQueue_Null, See_All_F);
		return error;
	}

	QUEUE* seeQueue = node.hpQueue;

	while (seeQueue != NULL)
	{
		if (fSee_P(seeQueue->list_x, seeQueue->list_y, seeQueue->list_n))
			seeQueue = seeQueue->nQueue;
		else
			break;
	}

	return error;
}

//批量添加（正向）
inline ERR Add_All(NODE& node, bool(&fAdd_P)(int&, int&, int&))
{
	ERR error;
	if (node.hpQueue != NULL)
	{
		no_good(error, hpQueue_Have, Add_All_F);
		return error;
	}

	int list_x(0), list_y(0), list_n(0);

	while (fAdd_P(list_x, list_y, list_n))
	{
		if ((error = Add_CpQueue(node, list_x, list_y, list_n)).no_good)
			break;
	}

	return error;
}

//将nodeO尾部节点移动到nodeI尾部节点
inline ERR Move_CpQueue_To_CpQueue(NODE& nodeI, NODE& nodeO)
{
	ERR error;
	
	if (nodeO.cpQueue == NULL)
	{
		no_good(error, cpQueue_Null, Move_CpQ_To_CpQ_F);
		return error;
	}

	//删除
	QUEUE* MovQueue = nodeO.cpQueue;
	nodeO.cpQueue = nodeO.cpQueue->uQueue;
	if (nodeO.cpQueue == NULL)
		nodeO.hpQueue = NULL;


	//添加
	MovQueue->uQueue = nodeI.cpQueue;
	MovQueue->nQueue = NULL;

	if (nodeI.hpQueue == NULL)
		nodeI.hpQueue = MovQueue;

	nodeI.cpQueue = MovQueue;

	return error;


	/*
	if (nodeO.cpQueue == NULL)
		return error;

	QUEUE* QueSave = nodeO.cpQueue;

	nodeO.cpQueue->nQueue = NULL;
	nodeO.cpQueue = nodeO.cpQueue->uQueue;
	if (nodeO.cpQueue == NULL)
		nodeO.hpQueue = NULL;

	QueSave->uQueue = nodeI.cpQueue;
	nodeI.cpQueue = QueSave;
	if (nodeI.cpQueue != NULL)
		nodeI.cpQueue->nQueue = QueSave;
	if (nodeI.hpQueue == NULL)
		nodeI.hpQueue = QueSave;*/
	//nodeI.cpQueue = QueSave;
}

#endif