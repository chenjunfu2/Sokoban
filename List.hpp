#pragma once

#include "Error.hpp"
#include <new>
#include <initializer_list>

template<typename DataType>
class List
{
private:
	//节点声明
	struct Node
	{
		Node *pPrev;//上一个节点
		Node *pNext;//下一个节点
		DataType tData;//数据
	};

	Node *pHead;//头部
	Node *pTail;//尾部
	size_t szNodeNum;//元素个数计数
public:
	//迭代器
	class Iterator//迭代器
	{
	private:
		friend class List;//设置主类为友元类
		Node *pCurrent;
	protected:
		//构造(只允许主类和继承类使用Node构造)
		Iterator(Node *_pcurrent = nullptr) : pCurrent(_pcurrent)
		{}
	public:
		//拷贝构造
		Iterator(const Iterator &_Iterator) :pCurrent(_Iterator.pCurrent)
		{}

		//移动构造
		Iterator(Iterator &&_Iterator) :pCurrent(_Iterator.pCurrent)
		{
			_Iterator.pCurrent = nullptr;
		}

		//默认析构（平凡析构类）
		~Iterator(void) = default;

		//前缀递增
		Iterator &operator++(void)//无int是前缀递增
		{
			if (pCurrent != nullptr)
			{
				pCurrent = pCurrent->pNext;
			}
			return *this;
		}

		//前缀递减
		Iterator &operator--(void)//无int是前缀递减
		{
			if (pCurrent != nullptr)
			{
				pCurrent = pCurrent->pPrev;
			}
			return *this;
		}

		//后缀递增
		Iterator operator++(int)//有int是后缀递增
		{
			Node *pLast = pCurrent;//保存原来的
			if (pCurrent != nullptr)
			{
				pCurrent = pCurrent->pNext;//前进到下一个
			}
			return pLast;//返回原来的
		}

		//后缀递减
		Iterator operator--(int)//有int是后缀递减
		{
			Node *pLast = pCurrent;//保存原来的
			if (pCurrent != nullptr)
			{
				pCurrent = pCurrent->pPrev;//后退到上一个
			}
			return pLast;//返回原来的
		}

		//从当前点往后_szAdd个点
		Iterator operator+(size_t _szAdd) const
		{
			Node *pAddNode = pCurrent;//保持原来的不变
			while (pAddNode != nullptr)//依次迭代
			{
				if (_szAdd == 0)
				{
					break;//找到要的了
				}
				//递减然后访问下一个元素
				--_szAdd;
				pAddNode = pAddNode->pNext;
			}
			return pAddNode;//返回最新的
		}

		//从当前点往前_szDel个点
		Iterator operator-(size_t _szDel) const
		{
			Node *pRemove = pCurrent;//保持原来的不变
			while (pRemove != nullptr)//依次迭代
			{
				if (_szDel == 0)
				{
					break;//找到要的了
				}
				//递减然后访问上一个元素
				--_szDel;
				pRemove = pRemove->pPrev;
			}
			return pRemove;//返回最新的
		}

		//解引用获取Data
		DataType &operator*(void) const
		{
			return pCurrent->tData;//不判断了，如果用户解引用nullptr直接让程序炸
		}
		
		//不等判断
		bool operator!=(Iterator &_rRight) const
		{
			return pCurrent != _rRight.pCurrent;
		}
		
		//相等判断
		bool operator==(Iterator &_rRight) const
		{
			return pCurrent == _rRight.pCurrent;
		}

		//迭代器有效性检测（检测pCurrent是不是nullptr）
		operator bool(void) const
		{
			return pCurrent != nullptr;
		}

		//迭代器有效性检测（检测pCurrent是不是nullptr）
		bool operator!(void) const
		{
			return pCurrent == nullptr;
		}
	};

	//默认无参构造
	List(void) :pHead(nullptr), pTail(nullptr), szNodeNum(0)
	{}

	//从一个data元素构造
	List(const DataType &_tData) :pHead(nullptr), pTail(nullptr), szNodeNum(0)
	{
		InsertTail(_tData);//插入
	}

	//从一个初始化列表构造
	List(const std::initializer_list<DataType> &_tInitDataList) :pHead(nullptr), pTail(nullptr), szNodeNum(0)
	{
		for (auto &it : _tInitDataList)//遍历整个列表
		{
			if (!InsertTail(it))//依次插入
			{
				return;//失败提前返回
			}
		}
	}

	//拷贝构造
	List(const List &_List) :pHead(nullptr), pTail(nullptr), szNodeNum(0)
	{
		Node *pAdd = _List.pHead;
		while (pAdd != nullptr)//遍历整个结构
		{
			if (!InsertTail(pAdd->tData))//插入到自身
			{
				break;//失败返回
			}
			pAdd = pAdd->pNext;//访问下一个
		}
	}

	//移动构造
	List(List &&_List) :pHead(_List.pHead), pTail(_List.pTail), szNodeNum(_List.szNodeNum)
	{
		_List.pHead = nullptr;
		_List.pTail = nullptr;
		_List.szNodeNum = 0;
	}

	//析构
	~List(void)
	{
		RemoveAll();
	}

	//赋值
	List &operator=(const List &_List)
	{
		RemoveAll();
		Node *pAdd = _List.pHead;
		while (pAdd != nullptr)//遍历整个结构
		{
			if (!InsertTail(pAdd->tData))//插入到自身
			{
				break;//失败返回
			}
			pAdd = pAdd->pNext;//访问下一个
		}
		return *this;
	}

	//删除所有元素，清空链表
	Error RemoveAll(void)
	{
		if (pHead == nullptr && pTail == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "链表已经为空");
		}
		else if (pHead != nullptr && pTail == nullptr)//不同步
		{
			return Error(true, 0, __FUNCTION__, "链表数据不同步");
		}
		else if (pHead == nullptr && pTail != nullptr)//不同步
		{
			return Error(true, 0, __FUNCTION__, "链表数据不同步");
		}

		Node *pDel = pHead;
		while (pDel != nullptr)//遍历删除所有元素
		{
			pHead = pHead->pNext;
			delete pDel;
			pDel = pHead;
		}
		
		//置空链表
		pHead = nullptr;
		pTail = nullptr;
		szNodeNum = 0;

		return Error(false);
	}

	//是否为空
	bool IsEmpty(void)
	{
		return pHead == pTail == nullptr;
	}

	//获取Node个数
	size_t GetNodeNum(void) const
	{
		return szNodeNum;
	}

	//头插
	Error InsertHead(const DataType &tData)
	{
		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{nullptr,pHead,tData};
		if (pInsert == nullptr)
		{
			return Error(true, 0, __FUNCTION__, "内存不足");
		}

		//设置头节点指向前一个节点的指针为当前分配的节点
		if (pHead != nullptr)
		{
			pHead->pPrev = pInsert;
		}

		//设置头节点为新节点
		pHead = pInsert;

		//设置尾节点
		if (pTail == nullptr)
		{
			pTail = pInsert;
		}

		//递增元素计数
		++szNodeNum;

		return Error(false);
	}

	//尾插
	Error InsertTail(const DataType &tData)
	{
		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{pTail,nullptr,tData};
		if (pInsert == nullptr)
		{
			return Error(true, 0, __FUNCTION__, "内存不足");
		}

		//设置尾节点的后一个节点指针为当前分配的节点
		if (pTail != nullptr)
		{
			pTail->pNext = pInsert;
		}

		//设置尾节点为新节点
		pTail = pInsert;

		//设置头节点
		if (pHead == nullptr)
		{
			pHead = pInsert;
		}

		//递增元素计数
		++szNodeNum;

		return Error(false);
	}

	//中间插入(在itpos指向的元素后插入)
	Error InsertMid(const DataType &tData, Iterator &itPos)
	{
		Node *pInsertPrev = itPos.pCurrent;//在这个位置后插入
		if (pInsert == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "迭代器为空");
		}

		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{pInsertPrev,pInsertPrev->pNext,tData};
		if (pInsert == nullptr)
		{
			return Error(true, 0, __FUNCTION__, "内存不足");
		}

		//设置插入点的下一个节点为新节点
		pInsertPrev->pNext = pInsert;

		//如果存在下一个节点，那么下一个节点的上一个节点为新节点
		if (pInsert->pNext != nullptr)
		{
			pInsert->pNext->pPrev = pInsert;
		}
		else//如果不存在下一个节点，即当前节点是尾节点
		{
			pTail = pInsert;//设置尾节点为新插入的节点
		}

		//递增元素计数
		++szNodeNum;

		//递增itPos使其指向新插入的节点
		++itPos;

		return Error(false);
	}

	//头删
	Error RemoveHead(void)
	{
		if (pHead == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "链表头为空");
		}

		//保存头部指针
		Node *pRemove = pHead;

		//设置指针
		pHead = pHead->pNext;
		if (pHead != nullptr)//还有元素
		{
			pHead->pPrev = nullptr;//取消对前一个元素指针的引用
		}
		else//删完了
		{
			pTail = nullptr;//尾部指针也要取消对最后一个元素的引用
		}

		//删除
		delete pRemove;
		pRemove = nullptr;

		//递减元素计数
		--szNodeNum;

		return Error(false);
	}

	//尾删
	Error RemoveTail(void)
	{
		if (pHead == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "链表尾为空");
		}

		//保存尾部指针
		Node *pRemove = pTail;

		//设置指针
		pTail = pTail->pPrev;
		if (pTail != nullptr)//还有元素
		{
			pTail->pNext = nullptr;//取消对后一个元素指针的引用
		}
		else//删完了
		{
			pHead = nullptr;//头部指针也要取消对最后一个元素的引用
		}

		//删除
		delete pRemove;
		pRemove = nullptr;

		//递减元素计数
		--szNodeNum;

		return Error(false);
	}

	//中间删除
	Error RemoveMid(Iterator &itPos)
	{
		Node *pRemove = itPos.pCurrent;
		if (pRemove == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "迭代器为空");
		}

		//让它引用下一个元素
		++itPos;

		//设置前节点指向后一个节点指针为要删除节点后一个节点的指针
		if (pRemove->pPrev != nullptr)
		{
			pRemove->pPrev->pNext = pRemove->pNext;
		}
		else//要删除节点是头节点
		{
			pHead = pRemove->pNext;//设置头节点指向要删除节点的下一个节点
		}

		//设置后节点指向前一个节点的指针为要删除节点前一个节点的指针
		if (pRemove->pNext != nullptr)
		{
			pRemove->pNext->pPrev = pRemove->pPrev;
		}
		else//要删除节点是尾节点
		{
			pTail = pRemove->pPrev;//设置尾节点指向要删除节点的上一个节点
		}
		
		//删除
		delete pRemove;
		pRemove = nullptr;

		//递减元素计数
		--szNodeNum;

		return Error(false);
	}

	//移动头部到目标结构
	Error MoveHeadToHead(List &rTargetList)
	{
		if (pHead == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "源链表头为空");
		}

		//保存头部指针
		Node *pRemove = pHead;

		//从源链表中删除目标元素但不释放
		pHead = pHead->pNext;
		if (pHead != nullptr)//还有元素
		{
			pHead->pPrev = nullptr;//取消对前一个元素指针的引用
		}
		else//删完了
		{
			pTail = nullptr;//尾部指针也要取消对最后一个元素的引用
		}

		//设置指针
		Node *&pInsert = pRemove;

		pInsert->pPrev = nullptr;
		pInsert->pNext = rTargetList.pHead;

		//添加到目标链表
		//设置头节点指向前一个节点的指针为当前的节点
		if (rTargetList.pHead != nullptr)
		{
			rTargetList.pHead->pPrev = pInsert;
		}

		//设置头节点为新节点
		rTargetList.pHead = pInsert;

		//设置尾节点
		if (rTargetList.pTail == nullptr)
		{
			rTargetList.pTail = pInsert;
		}

		//递减元素计数
		--szNodeNum;

		return Error(false);
	}

	//移动尾部到目标结构
	Error MoveTailToTail(List &rTargetList)
	{
		if (pTail == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "源链表尾为空");
		}

		//保存尾部指针
		Node *pRemove = pTail;

		//从源链表中删除目标元素但不释放
		pTail = pTail->pPrev;
		if (pTail != nullptr)//还有元素
		{
			pTail->pNext = nullptr;//取消对后一个元素指针的引用
		}
		else//删完了
		{
			pHead = nullptr;//头部指针也要取消对最后一个元素的引用
		}

		//设置指针
		Node *&pInsert = pRemove;

		pInsert->pPrev = rTargetList.pTail;
		pInsert->pNext = nullptr;

		//添加到目标链表
		//设置尾节点指向后一个节点的指针为当前的节点
		if (rTargetList.pTail != nullptr)
		{
			rTargetList.pTail->pNext = pInsert;
		}

		//设置尾节点为新节点
		rTargetList.pTail = pInsert;

		//设置头节点
		if (rTargetList.pHead == nullptr)
		{
			rTargetList.pHead = pInsert;
		}

		//递减元素计数
		--szNodeNum;

		return Error(false);
	}

	//获取头部一项
	Error GetHead(DataType &tDataGet)
	{
		if (pHead == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "源链表头为空");
		}

		//拷贝到目标
		tDataGet = pHead->tData;

		return Error(false);
	}

	//获取尾部一项
	Error GetTail(DataType &tDataGet)
	{
		if (pTail == nullptr)
		{
			return Error(true, 1, __FUNCTION__, "源链表尾为空");
		}

		//拷贝到目标
		tDataGet = pTail->tData;

		return Error(false);
	}

	//迭代器开始
	Iterator begin(void) const
	{
		return Iterator(pHead);
	}

	//迭代器结束
	Iterator end(void) const
	{
		return Iterator(nullptr);
	}

	//反向迭代器开始
	Iterator rbegin(void) const
	{
		return Iterator(pTail);
	}

	//反向迭代器结束
	Iterator rend(void) const
	{
		return Iterator(nullptr);
	}
};