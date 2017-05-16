#ifndef COMPARE__H__
#define COMPARE__H__

struct Compare
{
    bool operator() (const int& a, const int& b) const
    {
        return a > b;
    }
};

#endif  // COMPARE__H__

