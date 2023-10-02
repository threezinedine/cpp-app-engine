#include "EngineCores/StringUtils.hpp"


namespace ntt
{
    std::vector<std::string> SplitString(const std::string& word, char separateChar)
    {
        int index = 0;
        std::vector<std::string> splittedWords;
        std::string currentWord = "";

        while (index < word.length())
        {
            auto currentCharacter = word[index]; 

            if (currentCharacter == separateChar)
            {
                splittedWords.push_back(currentWord);
                currentWord = "";
            }
            else 
            {
                currentWord += currentCharacter;
            }

            index ++;
        }

        splittedWords.push_back(currentWord);

        return splittedWords;
    }

    std::string ConcatString(const std::vector<std::string>& vector, char linkChar)
    {
        std::string result;

        for (int i=0; i<vector.size(); i++)
        {
            result += vector[i];
            if (i < vector.size() - 1)
            {
                result += linkChar;
            }
        }

        return result;
    }

    std::string ConcatString(const std::vector<std::string>& vector)
    {
        std::string result;

        for (int i=0; i<vector.size(); i++)
        {
            result += vector[i];
        }

        return result;
    }
} // namespace ntt
