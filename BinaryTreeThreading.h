#pragma once

enum PointerTag {THREAD, LINK};

template <class T>
struct BinaryTreeNodeThd
{
	T _data ;							// 数据
	BinaryTreeNodeThd<T >* _left;		// 左孩子
	BinaryTreeNodeThd<T >* _right;		// 右孩子
	PointerTag   _leftTag ;				// 左孩子线索标志
	PointerTag   _rightTag ;			// 右孩子线索标志

	BinaryTreeNodeThd(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};

template <class T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;
public:
	BinaryTreeThd()
		:_root(NULL)
	{}
	
	BinaryTreeThd(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index, invalid);
	}

	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root, prev);
	}

	void PostOrderThreading()
	{
		Node* prev = NULL;
		//_PostOrderThreading(_root, prev);
	}

	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}

	void InOrderThd()
	{
		Node* cur = _root;

		while (cur)
		{
			// 找最左节点
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			cout<<cur->_data<<" ";

			// 访问连续后继
			while(cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}

			cur = cur->_right;
		}

		cout<<endl;
	}

	void PrevOrderThd()
	{
		Node* cur = _root;

		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout<<cur->_data<<" ";
				cur = cur->_left;
			}

			cout<<cur->_data<<" ";

			cur = cur->_right;

		/*	while(cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}

			if (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}*/
		}

		cout<<endl;
	}

protected:
	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		_InOrderThreading(cur->_left, prev);

		// 线索化
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		_InOrderThreading(cur->_right, prev);
	}

	void _PrevOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		if (cur->_leftTag == LINK)
			_PrevOrderThreading(cur->_left, prev);

		if (cur->_rightTag == LINK)
			_PrevOrderThreading(cur->_right, prev);
	}

	Node* _CreateTree(const T* a, size_t size,
		size_t& index, const T& invalid)
	{
		Node* root = NULL;
		if (index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a, size, ++index, invalid);
			root->_right = _CreateTree(a, size, ++index, invalid);
		}

		return  root;
	}
	
protected:
	Node* _root;
};

void TestThd()
{
	int array1[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int array2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};

	BinaryTreeThd<int> t1(array1, 10, '#');
	t1.InOrderThreading();
	t1.InOrderThd();

	BinaryTreeThd<int> t2(array1, 10, '#');
	t2.PrevOrderThreading();
	t2.PrevOrderThd();

	BinaryTreeThd<int> t3(array2, 15, '#');
	t3.PrevOrderThreading();
	t3.PrevOrderThd();

	BinaryTreeThd<int> t4(array2, 15, '#');
	t4.InOrderThreading();
	t4.InOrderThd();
}
