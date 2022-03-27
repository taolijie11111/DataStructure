5. find a pair of two elements in an array,whose sum is a given target number
vector<int> addsToTarget(vector<int> & numbers,int target){
    unordered_map<int,int> numToIndex;
    vector<int> vi(2);
    for(auto it : numbers){
        if(numToIndex.count(target - *it)){
            vi[0]=numToIndex[target - *it]+1; 
            vi[1]=(int)(it-numbers.begin())+1;
            return vi;
        }
       numToIndex[*it]=(int)(it-numbers.begin());
    }
}

6. 找到一个数组中最长的连续序列
struct  Bound
{
    int high;
    int low;

    Bound(int h=0,int l=0){
        high=h;
        low=l;
    }
};

int longestConsecutive(vector<int> &num){
    unorderd_map<int,Bond> table;
    int local;
    int maxLen =0;
    for(int i=0;i<num.size();i++){
        if(table.count(num[i])){//判断重复
            continue;
        }
        local = num[i];
        int low = local,high = local;
        if(table.count(local-1)){
            low=table[local-1].low;
        }
        if(table.count(local-1)){
            high=table[local-1].high;
        }
        table[low].high =table[local].high=high;
        table[high]].low =table[local].low = low;

        if(high - low +1 > maxlen){
            maxlen = high -low +1;
        }
    }
    return maxlen;
}

7. 查找两个字符串最长的长度


字符串会有edge case 需要注意
