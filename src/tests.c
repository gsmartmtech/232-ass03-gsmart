#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

void  swap(int *aPtr, int *bPtr);
char* find_last_char(char *sPtr);
void  link_three(Node *aPtr, Node *bPtr, Node *cPtr);
void  remove_middle(Node *aPtr, Node *bPtr, Node *cPtr);
void  remove_last(Node *bPtr);
void  remove_first(Node *aPtr);
void  swap_ptrs(int **aPtrPtr, int **bPtrPtr);
void  nullify(int **ppPtr);
void  assign_bytes(long long *nPtr);
int   sum_chain(Node *headPtr);


// ============================================================
//  UNIT TESTS
//
//  Rules:
//  - Set up all variables on the STACK — no malloc.
//  - Call the function under test.
//  - Use TEST_ASSERT_* to verify the result.
//  - Each function must be self-contained.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_swap_basic
//
// Call swap with two different integer values.
// Verify that both variables hold the exchanged values
// after the call.
// ============================================================

void test_swap_basic(void)
{
    int a = 5, b = 3;
    int aPtr = b, bPtr = a;
    swap(&a, &b);


    TEST_ASSERT_EQUAL(aPtr, a);
    TEST_ASSERT_EQUAL(bPtr, b);

}


// ============================================================
// test_swap_equal
//
// Call swap with two variables that hold the same value.
// Verify that both variables still hold that value after
// the call — nothing should change.
// ============================================================

void test_swap_equal(void)
{
    int a = 3, b = 3;
    int aPtr = b, bPtr = a;
    swap(&a, &b);


    TEST_ASSERT_EQUAL(aPtr, b);
    TEST_ASSERT_EQUAL(bPtr, a);
}


// ============================================================
// test_find_last_basic
//
// Call find_last_char on a string with multiple characters.
// Verify that the returned pointer points to the correct
// last character and has the correct address.
// ============================================================

void test_find_last_basic(void)
{
    char str[] = "hello";
    char *resultPtr = find_last_char(str);

    TEST_ASSERT_EQUAL(str[4],*resultPtr);
}


// ============================================================
// test_find_last_single
//
// Call find_last_char on a string with exactly one character.
// Verify that the returned pointer points to that character
// and equals the address of the first element.
// ============================================================

void test_find_last_single(void)
{
    char str[] = "e";
    char *resultPtr = find_last_char(str);

    TEST_ASSERT_EQUAL(str[0],*resultPtr);
}


// ============================================================
// test_find_last_empty
//
// Call find_last_char on an empty string.
// Verify that the function returns NULL.
// ============================================================

void test_find_last_empty(void)
{
    char str[] = "";
    char *resultPtr = find_last_char(str);

    TEST_ASSERT_EQUAL(0x0,resultPtr);
}


// ============================================================
// test_link_three_chain
//
// Declare three Node variables on the stack.
// Call link_three to connect them.
// Verify that:
//   - aPtr->nextPtr points to bPtr
//   - bPtr->nextPtr points to cPtr
//   - cPtr->nextPtr is NULL
// ============================================================

void test_link_three_chain(void)
{
    Node a;
    Node b;
    Node c;
    int aPtr = &a;
    int bPtr = &b;
    int cPtr = &c;

    link_three(aPtr, bPtr, cPtr);

    TEST_ASSERT_EQUAL(&b, a.nextPtr);
    TEST_ASSERT_EQUAL(&c, b.nextPtr);
    TEST_ASSERT_EQUAL(NULL, c.nextPtr);
}


// ============================================================
// test_remove_middle_reconnects
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_middle.
// Verify that:
//   - aPtr->nextPtr now points directly to cPtr
//   - bPtr->nextPtr is NULL (disconnected)
// ============================================================

void test_remove_middle_reconnects(void)
{
    Node a;
    Node b;
    Node c;
    int aPtr = &a;
    int bPtr = &b;
    int cPtr = &c;

    link_three(aPtr, bPtr, cPtr);

    remove_middle(aPtr, bPtr, cPtr);

    TEST_ASSERT_EQUAL(&c, a.nextPtr);
    TEST_ASSERT_EQUAL(NULL, c.nextPtr);
    TEST_ASSERT_EQUAL(NULL, b.nextPtr);
}


// ============================================================
// test_remove_last_truncates
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_last with bPtr.
// Verify that:
//   - bPtr->nextPtr is NULL
//   - aPtr->nextPtr still points to bPtr (unchanged)
// ============================================================

void test_remove_last_truncates(void)
{
    Node a;
    Node b;
    Node c;
    int aPtr = &a;
    int bPtr = &b;
    int cPtr = &c;

    link_three(aPtr, bPtr, cPtr);

    remove_last(bPtr);

    TEST_ASSERT_EQUAL(&b, a.nextPtr);
    TEST_ASSERT_EQUAL(NULL, b.nextPtr);
    TEST_ASSERT_EQUAL(NULL, c.nextPtr);
}


// ============================================================
// test_remove_first_isolates
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_first with aPtr.
// Verify that:
//   - aPtr->nextPtr is NULL (isolated)
//   - bPtr->nextPtr still points to cPtr (unchanged)
// ============================================================

void test_remove_first_isolates(void)
{
    Node a;
    Node b;
    Node c;
    int aPtr = &a;
    int bPtr = &b;
    int cPtr = &c;

    link_three(aPtr, bPtr, cPtr);

    remove_first(aPtr);

    TEST_ASSERT_EQUAL(NULL, a.nextPtr);
    TEST_ASSERT_EQUAL(&c, b.nextPtr);
    TEST_ASSERT_EQUAL(NULL, c.nextPtr);
}


// ============================================================
// test_swap_ptrs_redirects
//
// Declare two integer variables and two pointers to them.
// Call swap_ptrs.
// Verify that each pointer now points to the other variable.
// ============================================================

void test_swap_ptrs_redirects(void)
{
    int x = 10, y = 20;
    int *pPtr = &x, *qPtr = &y;

    swap_ptrs(&pPtr, &qPtr);

    TEST_ASSERT_EQUAL(&y, pPtr);
    TEST_ASSERT_EQUAL(&x, qPtr);
}


// ============================================================
// test_swap_ptrs_values_unchanged
//
// Declare two integer variables and two pointers to them.
// Call swap_ptrs.
// Verify that the INTEGER VALUES at the original addresses
// are completely unchanged after the call.
// ============================================================

void test_swap_ptrs_values_unchanged(void)
{
    int x = 10, y = 20;
    int *pPtr = &x, *qPtr = &y;

    swap_ptrs(&pPtr, &qPtr);

    TEST_ASSERT_EQUAL(y, *pPtr);
    TEST_ASSERT_EQUAL(x, *qPtr);
}


// ============================================================
// test_nullify_sets_null
//
// Declare an integer and a pointer to it.
// Verify the pointer is NOT NULL before the call.
// Call nullify.
// Verify the pointer IS NULL after the call.
// ============================================================

void test_nullify_sets_null(void)
{
    int x = 5;
    int *pPtr = &x;

    TEST_ASSERT_EQUAL(&x, pPtr);

    nullify(&pPtr);

    TEST_ASSERT_EQUAL(NULL, pPtr);
}


// ============================================================
// test_nullify_value_unchanged
//
// Declare an integer and a pointer to it.
// Call nullify.
// Verify that the INTEGER VALUE at the original address
// is unchanged after the call.
// ============================================================

void test_nullify_value_unchanged(void)
{
    int x = 5;
    int check = x;
    int *pPtr = &x;

    TEST_ASSERT_EQUAL(&x, pPtr);

    nullify(&pPtr);

    TEST_ASSERT_EQUAL(check, x);
}


// ============================================================
// test_assign_bytes_first_and_last
//
// Declare a long long variable initialized to zero.
// Call assign_bytes.
// Cast the address to unsigned char* and verify that
// byte 0 equals 1 and byte 7 equals 8.
// ============================================================

void test_assign_bytes_first_and_last(void)
{
    long long n = 0;
    
    assign_bytes(&n);

    unsigned char* bytesN = &n;

    TEST_ASSERT_EQUAL(1, *(bytesN + 0));
    TEST_ASSERT_EQUAL(8, *(bytesN + 7));
}


// ============================================================
// test_assign_bytes_all
//
// Declare a long long variable initialized to zero.
// Call assign_bytes.
// Cast the address to unsigned char* and verify that
// every byte i contains the value i + 1.
// ============================================================

void test_assign_bytes_all(void)
{
    long long n = 0;
    
    assign_bytes(&n);

    unsigned char* bytesN = &n;

    for (int i = 0; i < 8; i++)
    {
        TEST_ASSERT_EQUAL((i+1), *(bytesN + i));
    }
}


// ============================================================
// test_sum_chain_basic
//
// Declare three Node variables on the stack.
// Link them into a chain using link_three.
// Assign known values to each node.
// Call sum_chain and verify the returned sum is correct.
// ============================================================

void test_sum_chain_basic(void)
{
    Node a;
    Node b;
    Node c;
    int aPtr = &a;
    int bPtr = &b;
    int cPtr = &c;
    a.value = 1;
    b.value = 2;
    c.value = 3;

    link_three(aPtr, bPtr, cPtr);

    int result = sum_chain(aPtr);

    TEST_ASSERT_EQUAL((a.value + b.value + c.value), result);
}


// ============================================================
// test_sum_chain_single
//
// Declare a single Node with a known value.
// Set nextPtr to NULL.
// Call sum_chain and verify it returns that single value.
// ============================================================

void test_sum_chain_single(void)
{
    Node a;
    a.nextPtr = NULL;
    int aPtr = &a;
    a.value = 1;

    int result = sum_chain(aPtr);

    TEST_ASSERT_EQUAL((a.value), result);
}


// ============================================================
// test_sum_chain_null
//
// Call sum_chain with NULL.
// Verify the function returns 0 without crashing.
// ============================================================

void test_sum_chain_null(void)
{
    int result = sum_chain(NULL);

    TEST_ASSERT_EQUAL((0), result);
}