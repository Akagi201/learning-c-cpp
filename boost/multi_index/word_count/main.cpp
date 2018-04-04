#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "boost/algorithm/string.hpp"
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/hashed_index.hpp"
#include "boost/multi_index/identity.hpp"
#include "boost/multi_index/member.hpp"

//WordCnt类，记录了单词及对应的出现个数
struct WordCnt {
    std::string word;
    int cnt;

    WordCnt(const std::string& word_, int cnt_) :
        word(word_),
        cnt(cnt_) {
        }

    //默认按照cnt排序
    bool operator<(const WordCnt& rhs) const {
        return cnt < rhs.cnt;
    }
};//WordCnt

typedef boost::multi_index::multi_index_container<
        //容器内元素类型
        WordCnt,
        boost::multi_index::indexed_by<
            //有序非唯一，顺序参考identtiy<WordCnt>，也就是WordCnt.operator<
            boost::multi_index::ordered_non_unique<
                boost::multi_index::identity<WordCnt> >,
            //无序，也就是hash表，hashkey使用 WorkdCnt::word
            boost::multi_index::hashed_unique<
                boost::multi_index::member<WordCnt, std::string, &WordCnt::word> >
        >
> WordCntContainer;

int main() {
    WordCntContainer word_cnt_container;

    std::vector<std::string> contents;
    //文本 -> 单词vec
    boost::split(contents,
            "hello hello hello hello hello cpp cpp cpp cpp go go go python python shell",
            boost::is_any_of(" "));

    //取第二个索引，也就是hash表
    auto& word_index = word_cnt_container.get<1>();
    for (size_t i = 0; i < contents.size(); ++i) {
        const std::string& word = contents[i];
        auto iter = word_index.find(word);
        //存在则cnt+1，否则插入1
        if (iter == word_index.end()) {
            word_index.insert({word, 1});
        } else {
            word_index.modify(iter, [](WordCnt& word_cnt){ word_cnt.cnt++; });
        }
    }

    //取word_cnt_container，即第一个索引，也就是按照cnt升序排列
    for (const auto word_cnt : word_cnt_container) {
        //shell   1
        //python  2
        //go      3
        //cpp     4
        //hello   5
        std::cout << word_cnt.word << "\t" << word_cnt.cnt << std::endl;
    }

    return 0;
}