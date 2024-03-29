/*
 * UnitTestList.c
 *
 *      Author: marissa
 */

#include <stdio.h>
#include <stdlib.h>

#include "Object.h"
#include "Node.h"
#include "List.h"

/*
 * macro to mimic the functionality of assert() from <assert.h>. The difference is that this version doesn't exit the program entirely.
 * It will just break out of the current function (or test case in this context).
 */
#define myassert(expr) if(!(expr)){ fprintf(stderr, "\t[assertion failed] %s: %s\n", __PRETTY_FUNCTION__, __STRING(expr)); return 0; }

struct list *testlist;

int testCount = 0;
int passCount = 0;

void printTestInfo(char* testName, char *info)
{
	fprintf(stdout, "%s - %s\n", testName, info);
}

void printTestResult(char* testName, int passed)
{
	if(passed){
		fprintf(stdout, "%s - %s\n\n", "[PASSED]", testName);
	}else{
		fprintf(stdout, "%s - %s\n\n", "[FAILED]", testName);
	}
}

struct node *createTestNode(int jobid)
{
	struct object * job = createObject(jobid, "cmd args");
	struct node *node = createNode(job);
	return node;
}

int addAtFrontToNullListTest()
{
        struct node *node = createTestNode(1);
        addAtFront(NULL, node);
        freeNode(node, testlist->freeObject);
        return 1;
}

int addAtRearToNullListTest()
{
	struct node *node = createTestNode(1);
	addAtRear(NULL, node);
	freeNode(node, testlist->freeObject);
	return 1;
}

int addAtFrontWithNoNodes()
{
	struct node *node = createTestNode(1);
	addAtFront(testlist, node);
	myassert(testlist->size == 1)
	myassert(testlist->head == node)
	myassert(testlist->tail == node)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == NULL)
	return 1;
}

int addAtFrontWithOneNode()
{
	struct node *node = createTestNode(1);
        addAtFront(testlist, node);
        myassert(testlist->size == 1);

        struct node *node2 = createTestNode(2);
        addAtFront(testlist, node2);

        myassert(testlist->size == 2);
        myassert(testlist->head == node2)
	myassert(testlist->tail == node)
        myassert(node2->next == node)
	myassert(node->prev == node2)
        myassert(testlist->head->next->next == NULL)
	myassert(testlist->tail->prev->prev == NULL)
        return 1;
}

int addAtRearWithNoNodes()
{
	struct node *node = createTestNode(1);
	addAtRear(testlist, node);
	myassert(testlist->size == 1);
	myassert(testlist->head == node);
	myassert(testlist->tail == node);
	myassert(testlist->head->next == NULL);
	myassert(testlist->head->prev == NULL);
	myassert(testlist->tail->next == NULL);
	myassert(testlist->tail->prev == NULL);
	return 1;
}

int addAtRearWithOneNode()
{
	struct node *node = createTestNode(1);
	addAtRear(testlist, node);
	myassert(testlist->size == 1);

	struct node *node2 = createTestNode(2);
	addAtRear(testlist, node2);
	myassert(testlist->size == 2);

	myassert(testlist->head == node);
	myassert(testlist->tail == node2);
	myassert(node->next == node2);
	myassert(node2->prev == node);
	myassert(testlist->head->next->next == NULL);
	myassert(testlist->tail->prev->prev == NULL);
	return 1;
}

int removeFromListWithOneNode()
{
	struct node *node = createTestNode(1);
	addAtFront(testlist, node);
	myassert(testlist->size == 1);

	removeNode(testlist, node);
	myassert(testlist->size == 0);
	myassert(testlist->head == NULL);
	myassert(testlist->tail == NULL);
	freeNode(node, testlist->freeObject);
	return 1;
}

int removeNullList()
{
	struct node *node = createTestNode(1);
	struct node *removed = removeNode(NULL, node);
	myassert(removed == NULL);
	freeNode(node, testlist->freeObject);
	return 1;
}

int removeNullNode()
{
	struct node *removed = removeNode(testlist, NULL);
	myassert(removed == NULL);
	return 1;
}

int nullNodeTest()
{
	struct node *node = NULL;
	addAtFront(testlist, node);
	
	myassert(testlist->size == 0);
	myassert(testlist->head == NULL);
	myassert(testlist->tail == NULL);
	return 1;
}

int searchNullListTest()
{
	struct node *node = createTestNode(1);
	struct node *found = search(NULL, node->obj);
	myassert(found == NULL);
	freeNode(node, testlist->freeObject);
	return 1;
}

int searchEmptyListTest()
{
	struct node *node = createTestNode(1);
	struct node *found = search(testlist, node->obj);
	myassert(found == NULL);
	freeNode(node, testlist->freeObject);
	return 1;
}

int searchListNotFound()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	addAtFront(testlist, node2);

	struct node *found = search(testlist, node->obj);
	myassert(testlist->size == 1);
	myassert(found == NULL);

	freeNode(node, testlist->freeObject);
	return 1;
}

int searchListFound()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	addAtFront(testlist, node);
	addAtRear(testlist, node2);
	myassert(testlist->size == 2);	
	struct node *found = search(testlist, node->obj);
	myassert(found == node);
	return 1;
	
}

int reverseListTwoNodes()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	addAtFront(testlist, node);
	addAtRear(testlist, node2);

	myassert(testlist->size == 2);
	myassert(testlist->head == node);
	myassert(testlist->tail == node2);

	reverseList(testlist);
	myassert(testlist->size == 2);
	myassert(testlist->head == node2);
	myassert(testlist->tail == node);
	return 1;
}

int reverseListThreeNodes()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	struct node *node3 = createTestNode(3);
	addAtFront(testlist, node3);
	addAtFront(testlist, node2);
	addAtFront(testlist, node);

	myassert(testlist->size == 3);
	myassert(testlist->head == node);
	myassert(testlist->head->next == node2);
	myassert(testlist->head->next->next == node3);
	myassert(testlist->tail == node3);
	myassert(testlist->tail->prev == node2);
	myassert(testlist->tail->prev->prev == node);
	myassert(testlist->head->prev == NULL);
	myassert(testlist->tail->next == NULL);

	reverseList(testlist);
	
	myassert(testlist->size == 3);
	myassert(testlist->head == node3);
	myassert(testlist->head->next == node2);
	myassert(testlist->head->next->next == node);
	myassert(testlist->tail == node);
	myassert(testlist->tail->prev == node2);
	myassert(testlist->tail->prev->prev == node3);
	myassert(testlist->head->prev == NULL);
	myassert(testlist->tail->next == NULL);
	return 1;
}

int reverseListFourNodes()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	struct node *node3 = createTestNode(3);
	struct node *node4 = createTestNode(4);

	addAtFront(testlist, node4);
	addAtFront(testlist, node3);
	addAtFront(testlist, node2);
	addAtFront(testlist, node);
	
	myassert(testlist->size == 4);
	myassert(testlist->head == node);
	myassert(testlist->head->next == node2);
	myassert(testlist->head->next->next == node3);
	myassert(testlist->head->next->next->next == node4);
	myassert(testlist->tail == node4);
	myassert(testlist->tail->prev == node3);
	myassert(testlist->tail->prev->prev == node2);
	myassert(testlist->tail->prev->prev->prev == node);
	myassert(testlist->tail->next == NULL);
	myassert(testlist->head->prev == NULL);

	reverseList(testlist);

	myassert(testlist->size == 4);
	myassert(testlist->head == node4);
	myassert(testlist->head->next == node3);
	myassert(testlist->head->next->next == node2);
	myassert(testlist->head->next->next->next == node);
	myassert(testlist->tail == node);
	myassert(testlist->tail->prev == node2);
	myassert(testlist->tail->prev->prev == node3);
	myassert(testlist->tail->prev->prev->prev == node4);
	myassert(testlist->tail->next == NULL);
	myassert(testlist->head->prev == NULL);
	return 1; 
}

int reverseListNullList()
{
	reverseList(NULL);
	return 1;
}

int removeFrontTest()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	struct node *node3 = createTestNode(3);

	addAtFront(testlist, node3);
	addAtFront(testlist, node2);
	addAtFront(testlist, node);

	myassert(testlist->size == 3);
	
	struct node *removed = removeFront(testlist);

	myassert(testlist->size == 2);
	myassert(testlist->head == node2);
	myassert(testlist->tail == node3);
	myassert(testlist->head->prev == NULL);
	myassert(testlist->tail->next == NULL);
	myassert(removed == node);
	freeNode(node, testlist->freeObject);
	return 1;
}

int removeFrontNullList()
{
	struct node *node = removeFront(NULL);
	myassert(node == NULL);
	return 1;
}

int removeRearTest()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	struct node *node3 = createTestNode(3);

	addAtFront(testlist, node3);
	addAtFront(testlist, node2);
	addAtFront(testlist, node);

	myassert(testlist->size == 3);
	
	struct node *removed = removeRear(testlist);

	myassert(testlist->size == 2);
	myassert(testlist->head == node);
	myassert(testlist->tail == node2);
	myassert(testlist->head->prev == NULL);
	myassert(testlist->tail->next == NULL);
	myassert(removed == node3);
	freeNode(node3, testlist->freeObject);
	return 1;
}

int removeRearNullList()
{
	struct node *node = removeRear(NULL);
	myassert(node == NULL);
	return 1;
}

int getSizeTest()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	struct node *node3 = createTestNode(3);

	addAtFront(testlist, node3);
	addAtFront(testlist, node2);
	addAtFront(testlist, node);
	
	myassert(testlist->size == 3);
	int size = getSize(testlist);

	myassert(size == 3);
	return 1;
}

int getSizeTest2()
{
	int size = getSize(testlist);
	myassert(size == 0);
	return 1;
}

int isEmptyTest()
{
	struct node *node = createTestNode(1);
	addAtFront(testlist, node);
		
	int empty = isEmpty(testlist);
		
	myassert(empty == 0);
	return 1;
}

int isEmptyTest2()
{
	int empty = isEmpty(testlist);
	myassert(empty != 0);
	return 1;
}

int isEmptyNullList()
{
	int empty = isEmpty(NULL);
	myassert(empty == 1);
	return 1;
}

int getSizeNullList()
{
	int size = getSize(NULL);
	myassert(size == 0);
	return 1;
}

int addToFrontNullNodeToOneElement()
{
	struct node *node = createTestNode(1);
	addAtRear(testlist, node);

	addAtFront(testlist, NULL);
	
	myassert(testlist->size == 1);
	myassert(testlist->head->next == NULL);
	myassert(testlist->head->prev == NULL);
	return 1;
}

int removeNullNodeToOneElement()
{
	struct node *node = createTestNode(1);
	addAtFront(testlist, node);
	
	remove(NULL);

	myassert(testlist->size == 1);
	myassert(testlist->head == node);
	return 1;
}

int addToRearNullNodeToOneElement()
{
	struct node *node = createTestNode(1);
	addAtFront(testlist, node);
	
	addAtRear(testlist, NULL);

	myassert(testlist->size == 1);
	myassert(testlist->head == node);
	return 1;
}

int addAtFrontNodeContainingNull()
{
	struct node *node = NULL;

	addAtFront(testlist, node);

	myassert(testlist->size == 0);
	myassert(testlist->head == NULL);
	myassert(testlist->tail == NULL);
	return 1;
}

int addNullNodesAndStuff()
{
	struct node *node = createTestNode(1);
	addAtFront(testlist, NULL);
	addAtFront(testlist, NULL);
	addAtFront(testlist, NULL);
	addAtFront(NULL, NULL);
	addAtFront(testlist, NULL);
	addAtFront(testlist, NULL);
	addAtFront(NULL, node);
	
	addAtRear(testlist, NULL);
	addAtRear(NULL, NULL);
	addAtRear(NULL, node);
	

	myassert(testlist->size == 0);
	freeNode(node, testlist->freeObject);
	return 1;
}

int removeNullNodesAndStuff()
{
	removeFront(testlist);
	removeFront(NULL);
	
	removeRear(testlist);
	removeRear(NULL);
	
	remove(NULL);

	myassert(testlist->size == 0);
	return 1;
}

void beforeTest(char* testName)
{
	printTestInfo(testName, "Running...");
	testlist = createList(equals, toString, freeObject);
	testCount++;
}
void afterTest(char* testName, int result)
{
	printTestResult(testName, result);
	freeList(testlist);
	passCount += result;
}
/*
 * TODO: Write your test functions here
 */

void runUnitTests()
{
	int result;
	char *testName;

	testName = "removeNullNodesAndStuff";
	beforeTest(testName);
	result = removeNullNodesAndStuff();
	afterTest(testName, result);

	testName = "addNullNodesAndStuff";
	beforeTest(testName);
	result = addNullNodesAndStuff();
	afterTest(testName, result);

	testName = "addAtFrontNodeContainingNull";
	beforeTest(testName);
	result = addAtFrontNodeContainingNull();
	afterTest(testName, result);

	testName = "addToRearNullNodetoOneElement";
	beforeTest(testName);
	result = addToRearNullNodeToOneElement();
	afterTest(testName, result);
	
	testName = "removeNullNodeToOneElement";
	beforeTest(testName);
	result = removeNullNodeToOneElement();
	afterTest(testName, result);

	testName = "addToFrontNullNodeToOneElement";
	beforeTest(testName);
	result = addToFrontNullNodeToOneElement();
	afterTest(testName, result);

        testName = "addAtFrontToNullListTest";
        beforeTest(testName);
        result = addAtFrontToNullListTest();
        afterTest(testName, result);

	testName = "addAtRearToNullListTest";
	beforeTest(testName);
	result = addAtRearToNullListTest();
	afterTest(testName, result);

	testName = "addAtFrontWithNoNodes";
	beforeTest(testName);
	result = addAtFrontWithNoNodes();
	afterTest(testName, result);

	testName = "addAtFrontWithOneNode";
	beforeTest(testName);
	result = addAtFrontWithOneNode();
	afterTest(testName, result);

	testName = "addAtRearWithNoNodes";
	beforeTest(testName);
	result = addAtRearWithNoNodes();
	afterTest(testName, result);

	testName = "addAtRearWithOneNode";
	beforeTest(testName);
	result = addAtRearWithOneNode();
	afterTest(testName, result);

	testName = "removeFromListWithOneNode";
	beforeTest(testName);
	result = removeFromListWithOneNode();
	afterTest(testName, result);

	testName = "nullNodeTest";
	beforeTest(testName);
	result = nullNodeTest();
	afterTest(testName, result);

	testName = "searchNullListTest";
	beforeTest(testName);
	result = searchNullListTest();
	afterTest(testName, result);

	testName = "searchEmptyListTest";
        beforeTest(testName);
        result = searchEmptyListTest();
        afterTest(testName, result);

	testName = "searchListNotFound";
        beforeTest(testName);
        result = searchListNotFound();
        afterTest(testName, result);

	testName = "searchListFound";
        beforeTest(testName);
        result = searchListFound();
        afterTest(testName, result);

	testName = "reverseListTwoNodes";
	beforeTest(testName);
	result = reverseListTwoNodes();
	afterTest(testName, result);
	
	testName = "reverseListThreeNodes";
	beforeTest(testName);
	result = reverseListThreeNodes();
	afterTest(testName, result);

	testName = "reverseListFourNodes";
	beforeTest(testName);
	result = reverseListFourNodes();
	afterTest(testName, result);

	testName = "removeFrontTest";
	beforeTest(testName);
	result = removeFrontTest();
	afterTest(testName, result);

	testName = "removeRearTest";
	beforeTest(testName);
	result = removeRearTest();
	afterTest(testName, result);

	testName = "getSizeTest";
	beforeTest(testName);
	result = getSizeTest();
	afterTest(testName, result);

	testName = "getSizeTest2";
	beforeTest(testName);
	result = getSizeTest2();
	afterTest(testName, result);

	testName = "isEmptyTest";
	beforeTest(testName);
	result = isEmptyTest();
	afterTest(testName, result);
	
	testName = "isEmptyTest2";
	beforeTest(testName);
	result = isEmptyTest2();
	afterTest(testName, result);

	testName = "getSizeNullList";
	beforeTest(testName);
	result = getSizeNullList();
	afterTest(testName, result);

	testName = "isEmptyNullList";
	beforeTest(testName);
	result = isEmptyNullList();
	afterTest(testName, result);

	testName = "reverseListNullList";
	beforeTest(testName);
	result = reverseListNullList();
	afterTest(testName, result);

	testName = "removeFrontNullList";
	beforeTest(testName);
	result = removeFrontNullList();
	afterTest(testName, result);

	testName = "removeRearNullList";
	beforeTest(testName);
	result = removeRearNullList();
	afterTest(testName, result);

	testName = "removeNullList";
	beforeTest(testName);
	result = removeNullList();
	afterTest(testName, result);

	testName = "removeNullNode";
	beforeTest(testName);
	result = removeNullNode();
	afterTest(testName, result);

	//TODO: Add in your tests here

	fprintf(stdout, "Test Cases: %d\n",  testCount);
	fprintf(stdout, "Passed: %d\n", passCount);
	fprintf(stdout, "Failed: %d\n", testCount - passCount);
}

int main(int argc, char *argv[])
{
	runUnitTests();
	exit(0);
}
