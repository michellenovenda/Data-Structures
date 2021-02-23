#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<math.h>

using namespace std;

void merge(int* A, int start, int mid, int end)
{
    int sizeL, sizeR;
    sizeL = mid - start + 1;
    sizeR = end - mid;

    int* L;
    int* R;
    L = new int[sizeL];
    R = new int[sizeR];

    for (int i = 0; i < sizeL; i++)
        L[i] = A[start + i];
    for (int j = 0; j < sizeR; j++)
        R[j] = A[mid + 1 + j];

    int m = 0, n = 0;
    for (int k = start; k <= end; k++)
    {
        if ((n >= sizeR) || ((m < sizeL) && (L[m] <= R[n])))
            A[k] = L[m++];
        else
            A[k] = R[n++];
    }
    delete[] L;
    delete[] R;
}

int mergecnt(int* A, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        int cnt = mergecnt(A, start, mid) + mergecnt(A, mid + 1, end);

        int j = mid + 1;
        for (int i = start; i <= mid; i++)
        {
            while ((j <= end) && (A[i] > A[j] * 2LL))
                j++;
            cnt += j - (mid + 1);
        }
        merge(A, start, mid, end);
        return cnt;
    }

    else
        return 0;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int divide(int* arr, int left, int right)
{
    int val = arr[right];
    int idx = left;

    for (int j = left; j <= right - 1; j++)
    {
        if (arr[j] <= val)
        {
            swap(&arr[idx], &arr[j]);
            idx++;
        }
    }
    swap(&arr[idx], &arr[right]);
    return idx;
}

int select(int* arr, int left, int right, int op)
{
    if (op > 0 && op <= (right - left + 1))
    {
        int position = divide(arr, left, right);

        if (position - left == op - 1)
            return arr[position];
        if (position - left > op - 1)
            return select(arr, left, position - 1, op);
        return select(arr, position + 1, right, op - position + left - 1);
    }
    return INT_MAX;
}

int main()
{
    int n, op;
    while (cin >> n >> op)
    {
        int* arr;
        arr = new int[n + 10];

        for (int i = 0; i < n; i++)
            cin >> arr[i];


        if (op == 0)
            cout << mergecnt(arr, 0, n - 1) << endl;
        else
            cout << select(arr, 0, n - 1, n + 1 - op) << endl;

        delete[] arr;
    }
}