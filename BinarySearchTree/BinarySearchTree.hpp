#pragma once
#include <iostream>

template <class T>
struct BSTNode{

	BSTNode(const T& data = T())
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _data(data)
	{}

	BSTNode<T>* _pLeft;
	BSTNode<T>* _pRight;
	T _data;
};

template <class T>
class BSTree{
	typedef BSTNode<T> Node;
	typedef Node* PNode;

public:
	BSTree()
		: _pRoot(nullptr)
	{}

	// 插入元素
	bool Insert(const T& data)
	{
		// 要插入的新节点
		Node* nNode = new Node(data);
		
		// 如果节点为空，新节点为根节点
		if (nullptr == _pRoot){
			_pRoot = nNode;
			return true;
		}

		PNode pParent = nullptr; // 记录插入位置的双亲节点
		PNode pCur = _pRoot;
		// 查找插入的位置
		while (pCur){
			pParent = pCur;
			if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
		}

		if (data < pParent->_data)
			pParent->_pLeft = nNode;
		else
			pParent->_pRight = nNode;

		return true;
	}

	// 查找
	PNode Find(const T& data)
	{
		PNode pCur = _pRoot;

		while (pCur){
			if (data == pCur->_data)
				return pCur;
			else if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}
		return nullptr;
	}

	/*
		删除：
			查找待删除节点位置
			1. 叶子节点 --- 直接删除(与只有一个孩子情况合并处理)
			2. 只有右孩子 --- 可以直接删除，双亲节点指向右孩子
			3. 只有左孩子 --- 可以直接删除，双亲节点指向左孩子
			4. 有左孩子和右孩子
			5. 每次也要考虑是否为根节点
	*/
	bool Erase(const T& data)
	{
		// 查找待删除节点位置，需要记录双亲节点位置
		PNode pCur = _pRoot;
		PNode pParent = nullptr;
		while (pCur){
			if (data == pCur->_data)
				break;
			else if (data < pCur->_data){
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}

		if (nullptr == pCur)
			return false;

		// 只有右孩子
		if (nullptr == pCur->_pLeft){
			if (pCur == _pRoot){
				_pRoot = pCur->_pRight;
			}
			else{
				if (pParent->_pLeft == pCur){
					pParent->_pLeft = pCur->_pRight;
				}
				else
					pParent->_pRight = pCur->_pRight;
			}
		}
		// 只有左孩子
		else if (nullptr == pCur->_pRight){
			if (pCur == _pRoot){
				_pRoot = pCur->_pLeft;
			}
			else{
				if (pParent->_pLeft == pCur){
					pParent->_pLeft = pCur->_pLeft;
				}
				else
					pParent->_pRight = pCur->_pLeft;
			}
		}
		// 有左右孩子，通过替代节点（左子树最大节点或右子树最小的）删除
		else{
			// 找右子树最小节点
			PNode pReplace = pCur->_pRight;
			pParent = pCur;
			while (pReplace->_pLeft){
				pParent = pReplace;
				pReplace = pReplace->_pLeft;
			}

			pCur->_data = pReplace->_data;

			// 删除替代节点
			if (pReplace == pParent->_pLeft)
				pParent->_pLeft = pReplace->_pRight;
			else
				pParent->_pRight = pReplace->_pRight;

			pCur = pReplace;
		}

		delete pCur;
		return true;
	}

	// 中序遍历
	void InOrder()
	{
		_InOrder(_pRoot);
	}

	~BSTree()
	{
		_Destory(_pRoot);
	}

private:
	void _InOrder(const PNode& pRoot)
	{
		if (pRoot){
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	void _Destory(PNode& pRoot)
	{
		if (pRoot){
			_Destory(pRoot->_pLeft);
			_Destory(pRoot->_pRight);
			pRoot = nullptr;
		}
	}

private:
	PNode _pRoot;

};
