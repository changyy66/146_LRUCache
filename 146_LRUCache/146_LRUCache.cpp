// 146_LRUCache.cpp : 定义控制台应用程序的入口点。
//
/*
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

进阶:

你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:

LRUCache cache = new LRUCache( 2 /* 缓存容量 */ /*);*/
/*
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4

来源：力扣（LeetCode）
链接：https ://leetcode-cn.com/problems/lru-cache
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#include "stdafx.h"
#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;



class LRUCache {
private:
	typedef struct node {
		int k;
		int v;
		struct node *prv;
		struct node *next;
		node(int k, int v) {
			this->k = k;
			this->v = v;
			prv = this;
			next = this;
		};
	}Node;

	Node *head;
	unordered_map<int, Node *> _m;
 
	int maxCapacity;
	int size;
public:
	LRUCache(int capacity) {
		maxCapacity = capacity;
		size = 0;
		head = new Node(0, 0);
	}

	int get(int key) {
		auto value = _m.find(key);
		if (value != _m.end())
		{
			moveNode2Head(value->second);
			_m[key] = head->next;
			return value->second->v;
		}
		return -1;
	}

	void put(int key, int value) {
		auto it = _m.find(key);
		if (it != _m.end())
		{
			it->second->v = value;
			moveNode2Head(it->second);
			_m[key] = head->next;
			return;
		}
		addNode(key, value);
		_m[key] = head->next;
		size++;
		if (size>maxCapacity)
		{
			_m.erase(head->prv->k);
			delNode(head->prv);
		}
	}
private:
	void addNode(int k, int v)
	{
		Node *newnode = new Node(k, v);
		newnode->next = head->next;
		head->next->prv = newnode;
		head->next = newnode;
		newnode->prv = head;
	}

	void delNode(Node *tmp)
	{
		tmp->prv->next = tmp->next;
		tmp->next->prv = tmp->prv;
		delete tmp;
		tmp = NULL;	
	}

	void moveNode2Head(Node *tmp)
	{
		addNode(tmp->k, tmp->v);
		delNode(tmp);
	}
};

int main()
{
	LRUCache cache(2);
	cache.put(1, 2);
	cache.put(2, 3);
	cout << cache.get(1) << endl;
	cout << cache.get(3) << endl;
	cache.put(3, 6);
	cout << cache.get(2) << endl;
    return 0;
}

