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
    void GetNextSet(std::basic_string<CharT> const& str,std::vector<int>& nexts)
    {
        nexts.resize(str.length());
        for(size_t len =1;len<=str.length();++len)
        {
            nexts[len-1] = len - GetMaxMatch(str.data(),len);
        }
    }

    template <typename CharT>
    size_t kmp(std::basic_string<CharT> const& longstr, std::basic_string<CharT> const& shortstr)
    {
        if(shortstr.length()>longstr.length())
        {
            return longstr.length();
        }
        std::vector<int> nexts;
        GetNextSet(shortstr,nexts);
        size_t j,i;
        for(j = 0,i = 0;i<longstr.length()&&j<shortstr.length();)
        {
            if(longstr[i] != shortstr[j])
            {
                i+= nexts[j];
                j = 0;
            }
            else
            {
                ++j;
                ++i;
            }
        }

        if(j == shortstr.length())
        {
            return i - j;
        }
        else
        {
            return longstr.length();
        }
    }
}

#endif // KMP

