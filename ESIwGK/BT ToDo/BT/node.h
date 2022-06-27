#ifndef NODE_H
#define NODE_H

/*#include "behaviortree.h"*/
#include "returncode.h"
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

//class BehaviorTree; // at this point we have an incomplete def. of 'BehaviorTree'
// https://stackoverflow.com/questions/2133250/does-not-name-a-type-error

class Node
{


public:
	Node(){};
	~Node(){};

	virtual ReturnCode tick(){ //cout << "node" << endl; 
		return ReturnCode::FAILURE;
		};
	
};


class Leaf : public Node
{

};

class Action : public Leaf
{
private:
	// http://www.learncpp.com/cpp-tutorial/78-function-pointers/
	function<ReturnCode()> action;

public:
	Action(function<ReturnCode()> act){ action = act; };
	~Action(){};
	
	ReturnCode tick();

};


class Conditional : public Leaf
{
private:
	//http://www.learncpp.com/cpp-tutorial/78-function-pointers/
	function<ReturnCode()> predicate;

public:
	Conditional(function<ReturnCode()> pred){ predicate = pred; };
	~Conditional(){};
	ReturnCode tick();

};




class Composite : public Node
{
protected:
	//bool resumable;
	int currentChild; //aktualne dziecko
	vector<Node*> children;

public:
	Composite(){ currentChild = 0; };
	~Composite(){};
	
	void addChild(Node *n) { children.push_back(n); }
	virtual ReturnCode tick() { return ReturnCode::FAILURE; };
};

class Sequence : public Composite
{
public:
	Sequence(){};
	~Sequence(){};
	ReturnCode tick();
};

class Selector : public Composite
{
public:
	Selector(){};
	~Selector(){};
	ReturnCode tick();
};


#endif // NODE_H
