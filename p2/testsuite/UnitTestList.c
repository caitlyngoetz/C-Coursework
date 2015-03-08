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

int nullNodeTest()
{
	struct node *node = NULL;
	addAtFront(testlist, node);
	
	myassert(testlist->size == 0);
	myassert(testlist->head == NULL);
	myassert(testlist->tail == NULL);
	return 1;
}

int searchEmptyListTest()
{
	struct node *node = createTestNode(1);
	search(NULL, node);
	freeNode(node, testlist->freeObject);
	return 1;
}

int searchListNotFound()
{
	struct node *node = createTestNode(1);
	search(testlist, node);
	myassert(testlist->size == 0);
	freeNode(node, testlist->freeObject);
	return 1;
}

int searchListFound()
{
	struct node *node = createTestNode(1);
	struct node *node2 = createTestNode(2);
	addAtFront(testlist, node);
	addAtRear(testlist, node2);
	
	search(testlist, node2);
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

        testName = "addAtFrontToNullListTest";
        beforeTest(testName);
        result = addAtFrontToNullListTest();
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
