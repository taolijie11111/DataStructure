/**
 * @file 排列问题模板.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//无重复的全排列
void Permutation(char* pStr, char*)
{
    assert(pStr && pBegin);

    if(*pBegin == '\0')
        printf("%s\n",pStr);
    else
    {
        for(char* pCh=pBegin; *pCh != '\0';pCh++){
            swap(*pBegin,*pCh);
            Permutation(pStr,pBegin+1);
            swap(*pBegin,*pCh);
        }
    }
}