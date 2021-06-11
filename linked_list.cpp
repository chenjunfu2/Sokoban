#include "linked_list.h"

using namespace std;

//从头部添加一项
extern inline ERR Add_HpQueue(NODE& node, int list_x, int list_y, int list_n)
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

	//保存数据
	npQueue->list_x = list_x;
	npQueue->list_y = list_y;
	npQueue->list_n = list_n;

	//设置新节点的前后节点指针
	npQueue->uQueue = NULL;
	npQueue->nQueue = node.hpQueue;

	//设置头节点的前节点指针
	if (node.hpQueue != NULL)
		node.hpQueue->uQueue = npQueue;
	//设置头节点为新节点
	node.hpQueue = npQueue;

	//设置尾节点
	if (node.cpQueue == NULL)
		node.cpQueue = npQueue;

	return error;
}

//从尾部添加一项
extern inline ERR Add_CpQueue(NODE& node, int list_x, int list_y, int list_n)
{
	ERR error;

	QUEUE* npQueue = NULL;
	try {
		npQueue = new (QUEUE);
	}
	catch (bad_alloc&) {
		no_good(error, new_failed, Add_HpQueue_F);
		return error;
	}

	//保存数据
	npQueue->list_x = list_x;
	npQueue->list_y = list_y;
	npQueue->list_n = list_n;

	//设置新节点的前后节点指针
	npQueue->uQueue = node.cpQueue;
	npQueue->nQueue = NULL;

	//设置尾节点的后节点指针
	if (node.cpQueue != NULL)
		node.cpQueue->nQueue = npQueue;
	//设置尾节点为新节点
	node.cpQueue = npQueue;

	//设置头节点
	if (node.hpQueue == NULL)
		node.hpQueue = npQueue;

	return error;
}



//查看尾部一项
extern inline ERR See_CpQueue(const NODE& node, int& list_x, int& list_y, int& list_n)
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

//查看头部一项
extern inline ERR See_HpQueue(const NODE& node, int& list_x, int& list_y, int& list_n)
{
	ERR error;

	if (node.hpQueue == NULL)
	{
		no_good(error, hpQueue_Null, Find_HpQueue_F);
		return error;
	}

	list_x = node.hpQueue->list_x;
	list_y = node.hpQueue->list_y;
	list_n = node.hpQueue->list_n;

	return error;
}


//移动尾部一项到另外一条链表尾部
extern inline ERR Move_CpQueue_To_CpQueue(NODE& nodeI, NODE& nodeO)
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
	//if(nodeO.cpQueue!=NULL)
		//nodeO.cpQueue->nQueue = NULL;
	if (nodeO.cpQueue == NULL)
		nodeO.hpQueue = NULL;
	else
		nodeO.cpQueue->nQueue = NULL;


	//添加
	MovQueue->uQueue = nodeI.cpQueue;
	MovQueue->nQueue = NULL;

	if (nodeI.cpQueue != NULL)
		nodeI.cpQueue->nQueue = MovQueue;
	nodeI.cpQueue = MovQueue;

	if (nodeI.hpQueue == NULL)
		nodeI.hpQueue = MovQueue;

	return error;
}

//移动头部一项到另外一条链表头部
extern inline ERR Move_HpQueue_To_HpQueue(NODE& nodeI, NODE& nodeO)
{
	ERR error;

	if (nodeO.hpQueue == NULL)
	{
		no_good(error, cpQueue_Null, Move_HpQ_To_HpQ_F);
		return error;
	}

	//删除
	QUEUE* MovQueue = nodeO.hpQueue;
	nodeO.hpQueue = nodeO.hpQueue->nQueue;
	//if(nodeO.cpQueue!=NULL)
		//nodeO.cpQueue->nQueue = NULL;
	if (nodeO.hpQueue == NULL)
		nodeO.cpQueue = NULL;
	else
		nodeO.hpQueue->uQueue = NULL;


	//添加
	MovQueue->uQueue = NULL;
	MovQueue->nQueue = nodeI.hpQueue;

	if (nodeI.hpQueue != NULL)
		nodeI.hpQueue->uQueue = MovQueue;
	nodeI.hpQueue = MovQueue;

	if (nodeI.cpQueue == NULL)
		nodeI.cpQueue = MovQueue;

	return error;
}


//批量读取（正向）
template <typename T>
extern inline ERR See_All_G(const NODE& node, T fSee_P)//bool(*const fSee_P)(const int&, const int&, const int&)
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

//批量读取（反向）
template <typename T>
extern inline ERR See_All_B(const NODE& node, T fSee_P)//bool(*const fSee_P)(const int&, const int&, const int&)
{
	ERR error;
	if (node.cpQueue == NULL)
	{
		no_good(error, hpQueue_Null, See_All_F);
		return error;
	}

	QUEUE* seeQueue = node.cpQueue;

	while (seeQueue != NULL)
	{
		if (fSee_P(seeQueue->list_x, seeQueue->list_y, seeQueue->list_n))
			seeQueue = seeQueue->uQueue;
		else
			break;
	}

	return error;
}

//批量添加（正向）
template <typename T>
extern inline ERR Add_All_G(NODE& node, T fAdd_P)//bool(*fAdd_P)(int&, int&, int&)
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
		if ((error = Add_HpQueue(node, list_x, list_y, list_n)).no_good)
			break;
	}

	return error;
}

//批量添加（反向）
template <typename T>
extern inline ERR Add_All_B(NODE& node, T fAdd_P)//bool(*fAdd_P)(int&, int&, int&)
{
	ERR error;
	if (node.cpQueue != NULL)
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



//从尾部删除一项
extern inline ERR Del_CpQueue(NODE& node, int& list_x, int& list_y, int& list_n)
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
	if (node.cpQueue == NULL)
		node.hpQueue = NULL;
	else
		node.cpQueue->nQueue = NULL;

	try {
		delete delQueue;
		delQueue = NULL;
	}
	catch (...) {
		no_good(error, delete_failed, Del_CpQueue_F);
		return error;
	}

	
	//if (node.cpQueue != NULL)
		//node.cpQueue->nQueue = NULL;
	//if (node.cpQueue == NULL)
		//node.hpQueue = NULL;

	return error;
}

//删除所有
extern inline ERR Del_AllQueue(NODE& node)
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