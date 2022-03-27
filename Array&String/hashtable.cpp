重要的模式识别:
1. 一旦需要统计一个元素集中元素出现的次数，我们应该想到 hash table///!!!!!重要！！！
2. 当处理当前结点需要依赖于之前的部分结果时，可以考虑使用hashtable记录之前的处理结果，

using namespace std;



1. Delermine if all characters of a string are unique
//bitset
bool isUnique(string input){
    bitset<256> hashMap;
    for(int i=0;i < input.length();i++){
        if(hashMap[(int)input[i]]){
            return false;
        }
        hashMap[(int)input[i]]=1;
    }
    return true;
}

2. grien two strings,determine if they are permutations of each other
解法1: 
hashtable
思路: 
bool isPermutation(string string1,string string2){
    if(string1.length()!=string2.length()){
        return false;
    }
    unordered_map<char,int> hashMapA;
    unordered_map<char,int> hashMapB;
    for(int i=0;i<string1.length();i++){
        hashMap1[string1[i]]++;
        hashMap2[string1[i]]++;
    }
    if(hashMap1.size()!=hashMap2.size()){
        return false;
    }

    for(auto it : hashMap1){
        if(it->second!=hashMap2[it->first]){
            return false;
        }
    }
    return true;
}

3. Given a newspaper and message as two strings,check if the message can be compoesd using letters in the nowspaper
bool canCompose(string newspaper,string message){
    unorders_map<char,int> hashMap;
    int i;
    if(newspaper.length()< message.length()){
        return false;
    }
    for(i =0;i<newspaper.length();i++){
        hashMap[newspaper[i]]++;
    }

    for( i=0; i<message.length();i++){
        if(hashMap.count(message[i])==0){
            return false;
        }
        if(--hashMap[message[i]]<0){
            return false;
        }
    }
    return ture;
}

4. 判断两个字符串是否是一样的，就是abcd和acbd是一样的

class Solution{
解法1:hashtable
bool anagram(string s,srting t){
    if(s.empty()|| t.empty()){
        return false;
    }
    if(s.size()!=t.size()){
        return false;
    }
    int letterCount[256]={0};
    for(int i=0;i!=s.size();++i){
        ++letterCount[s[i]];
        --letterCount[t[i]];//这里用了一个正负形抵消
    }
    for(int i=0;i!=t.size();++i){
        if(letterCount[t[i]]<0)return false;
    }
    return ture;
}

解法2: sort
bool anagram(string s,string t){
    if(s.empty()||t.empty()){
        return false;
    }
    if(s.size()!=t.size()){
        return false;
    }

    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    if(s==t){
        return true;
    }else{
        return false;
    }
}

};

当处理当前结点需要依赖于之前的部分结果时，可以考虑使用hashtable记录之前的处理结果，
