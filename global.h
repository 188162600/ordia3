#ifndef GLOBAL_H
#define GLOBAL_H
#include<Qt>
enum Eyelid{UpperEyelid=0x01,LowerEyelid=0x02};
template<typename Interger,typename std::enable_if<std::is_integral<Interger>::value>::type*Test=nullptr>
inline bool isOdd(Interger value){return value%2==1;};
template<typename Interger,typename std::enable_if<std::is_integral<Interger>::value>::type*Test=nullptr>
inline bool isEven(Interger value){return value%2==0;};

inline int randInt(int max){return rand()%(max+1);}
inline int randInt(int min,int max){return randInt(max-min)+min;};

#endif // GLOBAL_H
