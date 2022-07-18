#ifndef ITERATORANGE_H
#define ITERATORANGE_H

#include<Qt>
template<typename Iterator>
class IteratorRange
{
public:
    template<typename Container>
    inline IteratorRange(const Container&container):b(container.begin()),e(container.end()){};
    template<typename Container>
    inline IteratorRange(Container&container):b(container.begin()),e(container.end()){};
    inline IteratorRange(const std::pair<Iterator,Iterator>&pair):b(pair.first),e(pair.second){};
    inline IteratorRange(const Iterator&begin,const Iterator& end):b(begin),e(end){};

    inline Iterator begin()const{return b;};
    inline Iterator end()const{return e;};
    inline void setBegin(const Iterator&begin){b=begin;};
    inline void setEnd(const Iterator&end){e=end;};
    inline Iterator&beginRef(){return b;};
    inline Iterator&endRef(){return e;};
    inline bool isEmpty(){return b==e;};
private:
    Iterator b,e;

};

template<typename Iterator>
IteratorRange<Iterator> makeIteratorRange(const Iterator&begin,const Iterator& end){return IteratorRange<Iterator>(begin,end);};
template<typename Container>
auto makeIteratorRange(const Container&container){return IteratorRange<decltype (container.begin())>(container);};
template<typename Container>
auto makeIteratorRange( Container&container){return IteratorRange<decltype (container.begin())>(container);};
template<typename Iterator>
IteratorRange<Iterator> makeIteratorRange(const std::pair<Iterator,Iterator>&pair){return IteratorRange<Iterator>(pair);};

#endif // ITERATORANGE_H
