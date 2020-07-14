#include <iostream>
#include <vector>
using namespace std;

int bitOFFToON(int no, int k)
{
    int mask = (1 << k);
    return (no | mask);
}

int bitONToOFF(int no, int k)
{
    int mask = (~(1 << k));
    return (no & mask);
}

int noOfSetBits(int num)
{
    int bitCount = 0;
    int totalBits = 32;

    while (num != 0 && totalBits != 0)
    {
        if ((num & 1) != 0)
            bitCount++;
        num >>= 1;
        totalBits--;
    }
    return bitCount;
}

// Leetcode 191
int noOfSetBits(int num)
{
    int bitCount = 0;
    int totalBits = 32;

    while (num != 0 && totalBits != 0)
    {
        if ((num & 1) != 0)
            bitCount++;
        num >>= 1;
        totalBits--;
    }
    return bitCount;
}

//leetcode 338
int noOfSetBits_01(int num)
{
    int bitcount = 0;
    while (num != 0)
    {
        num &= (num - 1);
        bitcount++;
    }
    return bitcount;
}

// LeetCode Qno : 137 ===============================
int singleNumber(vector<int> &nums)
{
    int no = 0;
    for (int i = 0; i < 32; i++)
    {
        int count = 0;
        int mask = (1 << i);
        for (int ele : nums)
        {
            if ((mask & ele) != 0)
            {
                count++;
            }
        }

        if (count % 3 != 0)
            no |= mask;
    }
    return no;
}

// LeetCode Qno : 260 =============================

vector<int> singleNumberII(vector<int> &nums)
{
    int Xnornum = 0;
    for (int ele : nums)
        Xnornum ^= ele;
    int flsb = (Xnornum & (-Xnornum));
    int a = 0;
    int b = 0;
    for (int ele : nums)
    {
        if ((ele & flsb) == 0)
            a ^= ele;
        else
            b ^= ele;
    }
    return {a, b};
}

//Leetcode Qn0 :231 ===============================

bool isPowerOfTwo(int n)
{

    return n > 0 && !(n & (n - 1));
}

//leetcode 342=========================
bool isPowerOfFour(int n)
{
    if (n > 0 && !(n & (n - 1))) // is num power of 2
    {
        int count = 0; // count of all zeros after 1.
        while (n > 1)
        {
            count++;
            n >>= 1;
        }

        if ((count & 1) == 0)
            return true; // count of zeros after 1 should be a even number.
    }

    return false;
}
void solve()
{
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
