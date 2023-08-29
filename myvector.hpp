//
// Created by Administrator on 2023/7/18.
//

#ifndef CLION_C___MYVECTOR_HPP
#define CLION_C___MYVECTOR_HPP
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<ctime>
template<typename T>
class Vector
{
private:
    T* Data;
    int Len,Size;
public:
    inline Vector()
    {
        Data=NULL;
        Len=Size=0;
    }
    inline Vector(const Vector& other)
    {
        if(this==&other||!Len)return;
        Data=(T*)malloc(sizeof(T)*other.Len);
        for(int i=0;i<other.Size;i++)Data[i]=other.Data[i];
        Len=other.Len,Size=other.Size;
    }
    inline T &operator[](const int x)
    {
        return Data[x];
    }
    const Vector&push_back(const T x)
    {
        if(Size==Len)
        {
            Len=Len==0?1:Len<<1;
            T* newData=(T*)malloc(sizeof(T)*Len);
            memcpy(newData,Data,Size*sizeof(T));
            free(Data);
            Data=newData;
        }
        Data[Size++]=x;
        return *this;
    }
    const Vector&pop_back()
    {
        Size--;
        if(Size==(Len>>2))
        {
            Len=Len>>1;
            T* newData=(T*)malloc(sizeof(T)*Len);
            memcpy(newData,Data,Size*sizeof(T));
            free(Data);
            Data=newData;
        }
        return *this;
    }
    inline unsigned int size()
    {
        return Size;
    }
    inline unsigned int len()
    {
        return Len;
    }
};

#endif //CLION_C___MYVECTOR_HPP
