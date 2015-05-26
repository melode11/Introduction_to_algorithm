#ifndef KMP
#define KMP
#include <string>
#include <vector>
namespace Algo
{
    template <typename CharT>
    int GetMaxMatch(CharT* substr,size_t len)
    {
        int max = 0;
        for(int i = 0;i<len-1;++i)
        {
            for(int j = 0; j<=i;++j)
            {
                if(substr[j] != substr[len - 1 - i + j])
                {
                    goto nextloop;
                }
            }
            max = i + 1;
nextloop:;
        }
        return max;
    }

    template <typename CharT>
    size_t kmp(std::basic_string<CharT> const& longstr, std::basic_string<CharT> const& shortstr)
    {
        std::vector<int> nexts(shortstr.length());
        nexts[0] = 0;
        for(size_t len =1;len<shortstr.length();++len)
        {
            nexts[len] = len - GetMaxMatch(shortstr.data(),len);
        }
        size_t j,i;
        for(j = 0,i = 0;i<longstr.length()&&j<shortstr.length();++j,++i)
        {
            if(longstr[i] != shortstr[j])
            {
                i+= nexts[j];
                j = 0;
            }
        }

        if(j == longstr.length())
        {
            return i - j;
        }
        else
        {
            return i;
        }
    }
}

#endif // KMP

