//https://leetcode.cn/problems/sentence-similarity-iii/

#include <vector>
#include <string>

class Solution {
public:
    bool areSentencesSimilar(std::string sentence1, std::string sentence2) {
        int ptr1=0,ptr2=0;
        std::vector<int> sentence1_list{0},sentence2_list{0};
        while(ptr1<sentence1.length()) {
            ptr1++;
            if(sentence1[ptr1]==' ') {
                sentence1_list.push_back(ptr1+1);
            }
        }
        while (ptr2<sentence2.length()) {
            ptr2++;
            if(sentence2[ptr2]==' ') {
                sentence2_list.push_back(ptr2+1);
            }
        }
        int i=0;int j=1;
        int state1=0,state2=0;
        if(sentence1_list.size()>=sentence2_list.size()) {}
        else {
            std::swap(sentence1_list,sentence2_list);
            std::swap(sentence1,sentence2);

        }
            if(similarWord(sentence1_list[i],sentence2_list[i],sentence1,sentence2)==true) {
                state1=1;
                for(i=1;i<sentence1_list.size()&&i<sentence2_list.size();i++) {
                    if(similarWord(sentence1_list[i],sentence2_list[i],sentence1,sentence2)==false) {
                        break;
                    }
                }
                if(i==sentence2_list.size())
                    return true;
            }

            if(similarWord(sentence1_list[sentence1_list.size()-j],sentence2_list[sentence2_list.size()-j],sentence1,sentence2)==true) {
                state2=1;
                for(j=1;j<=sentence1_list.size()&&j<=sentence2_list.size();j++) {
                    if(similarWord(sentence1_list[sentence1_list.size()-j],sentence2_list[sentence2_list.size()-j],sentence1,sentence2)==false) {
                        j--;
                        break;
                    }
                }
                if(j>sentence2_list.size())
                    return true;
            }
            if(i+j>=sentence2_list.size() && state1==1 &&state2==1) {
                return true;
            }
            return false;

    }
    bool similarWord(int ptr1,int ptr2,const std::string& sentence1,const std::string& sentence2) {
        while(sentence1[ptr1]==sentence2[ptr2]) {
            ptr1++;
            ptr2++;
            if(ptr1>=sentence1.length() && ptr2<sentence2.length() && sentence2[ptr2]==' ')
                return true;
            if(ptr2>=sentence2.length() && ptr1<sentence1.length() && sentence1[ptr1]==' ')
                return true;
            if(ptr1>=sentence1.length() && ptr2>=sentence2.length())
                return true;
            if(sentence1[ptr1]==sentence2[ptr2] &&sentence1[ptr1]==' ')
                return true;
        }
        return false;
    }
};