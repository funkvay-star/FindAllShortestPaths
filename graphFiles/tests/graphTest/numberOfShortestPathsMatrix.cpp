#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <list>

typedef std::vector<std::list<std::pair<int, int>>> adjacency_list;

struct Coordinate
{
    int x;
    int y;

    Coordinate()
        :
        x(0),
        y(0)
    {
    }

    Coordinate(int x, int y)
        : 
        x(x),
        y(y)
    {
            
    }
};

class BigInt 
{
private:
    std::string number;

    void Normalize()
    {
        std::reverse(number.begin(), number.end());
        while (this->number[number.size() - 1] == '0')
        {
            number.pop_back();
        }
        std::reverse(number.begin(), number.end());

        if (number.size() == 0)
        {
            number = "0";
        }
    }

public:
    BigInt()
        : BigInt("0")
    {
    }

    BigInt(std::string number)
    {
        this->number = number;
    }

    int numDigits()
    {
        return this->number.length();
    }

    bool operator==(BigInt other)
    {
        if (this->number.length() != other.number.length())
            return false;
        for (int i = 0; i < this->number.length(); ++i) 
        {
            if (this->number[i] != other.number[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator==(const BigInt other) const
    {
        if (this->number.length() != other.number.length())
            return false;
        for (int i = 0; i < this->number.length(); ++i)
        {
            if (this->number[i] != other.number[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const BigInt other)
    {
        return !(*this == other);
    }

    bool operator!=(const BigInt other) const
    {
        return !(*this == other);
    }

    bool operator<=(BigInt other)
    {
        if (this->number.length() < other.number.length())
        {
            return true;
        }
        if (this->number.length() > other.number.length())
        {
            return false;
        }
        for (int i = 0; i < this->number.length(); ++i) 
        {
            if (this->number[i] > other.number[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const BigInt other) const 
    {
        if (this->number.length() < other.number.length())
        {
            return true;
        }
        if (this->number.length() > other.number.length())
        {
            return false;
        }
        for (int i = 0; i < this->number.length(); ++i)
        {
            if (this->number[i] > other.number[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator<(BigInt other)
    {
        if (!(*this <= other))
        {
            return false;
        }
        if (*this == other)
        {
            return false;
        }
        return true;
    }

    bool operator<(const BigInt other) const
    {
        if (!(*this <= other))
        {
            return false;
        }
        if (*this == other)
        {
            return false;
        }
        return true;
    }

    bool operator>=(BigInt other)
    {
        if (this->number.length() > other.number.length())
        {
            return true;
        }
        if (this->number.length() < other.number.length())
        {
            return false;
        }

        for (int i = 0; i < this->number.length(); ++i) 
        {
            if (this->number[i] < other.number[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator>(BigInt other)
    {
        if (!(*this >= other)) return false;
        if (*this == other) return false;
        return true;
    }

    BigInt operator+(BigInt other)
    {
        if (this->number.length() <= other.number.length()) 
        {
            std::reverse(this->number.begin(),
                this->number.end());
            std::reverse(other.number.begin(),
                other.number.end());
            int extraZeroes
                = other.number.length()
                - this->number.length();
            for (int i = 0; i < extraZeroes; ++i) 
            {
                this->number.push_back('0');
            }
        }
        if (this->number.length() > other.number.length()) 
        {
            std::reverse(this->number.begin(),
                this->number.end());
            std::reverse(other.number.begin(),
                other.number.end());
            int extraZeroes
                = this->number.length()
                - other.number.length();
            for (int i = 0; i < extraZeroes; ++i)
            {
                other.number.push_back('0');
            }
        }
        std::string answer = "";
        int carry = 0;
        int ansDigit = 0;
        for (int i = 0; i < this->number.length(); ++i)
        {
            int firstDigit = this->number[i] - '0';
            int secondDigit = other.number[i] - '0';
            int sum = firstDigit + secondDigit + carry;
            ansDigit = sum % 10;
            carry = sum / 10;
            char toPush = ansDigit + '0';
            answer += toPush;
            if (i == this->number.length() - 1 && carry != 0) 
            {
                char extraPush = carry + '0';
                answer += extraPush;
            }
        }
        std::reverse(answer.begin(), answer.end());
        return answer;
    }

    BigInt operator-(BigInt other)
    {
        if (*this == other)
        {
            return BigInt("0");
        }

        std::string str1 = this->number;
        std::string str2 = other.number;

        std::string str = "";

        int n1 = str1.length(), n2 = str2.length();

        reverse(str1.begin(), str1.end());
        reverse(str2.begin(), str2.end());

        int carry = 0;

        for (int i = 0; i < n2; ++i) 
        {
            int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);

            if (sub < 0) 
            {
                sub = sub + 10;
                carry = 1;
            }
            else
                carry = 0;

            str.push_back(sub + '0');
        }

        for (int i = n2; i < n1; ++i) 
        {
            int sub = ((str1[i] - '0') - carry);

            if (sub < 0) 
            {
                sub = sub + 10;
                carry = 1;
            }
            else
                carry = 0;

            str.push_back(sub + '0');
        }

        reverse(str.begin(), str.end());


        BigInt answer(str);
        answer.Normalize();

        return answer;
    }

    BigInt operator*(BigInt other)
    {
        std::vector<BigInt> result;
        std::reverse(other.number.begin(),
            other.number.end());
        for (int i = 0; i < this->number.length(); ++i) 
        {
            int carry = 0;
            int product = 0;
            std::string ans = "";
            int digit = this->number[i] - '0';
            for (int j = 0; j < other.number.length(); ++j) 
            {
                int otherDigit = other.number[j] - '0';
                product = digit * otherDigit + carry;
                carry = product / 10;
                int remainderNumber = carry * 10;
                int number;
                if (remainderNumber != 0)
                    number = product % remainderNumber;
                else
                    number = product % 10;
                char toPush = number + '0';
                ans += toPush;
                if (j == other.number.length() - 1 && carry != 0) 
                {
                    char extraPush = carry + '0';
                    ans += extraPush;
                }
            }
            for (int k = 0; k < this->number.length() - i - 1; ++k) 
            {
                ans = '0' + ans;
            }
            std::reverse(ans.begin(), ans.end());
            BigInt add(ans);
            result.push_back(add);
        }
        BigInt sum("0");
        for (int i = 0; i < result.size(); ++i) 
        {
            sum = sum + result[i];
        }
        return sum;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& bin)
    {
        out << bin.number;
        out << std::endl;
        return out;
    }

    void operator++(int)
    {
        BigInt newNumber(this->number);
        newNumber = newNumber + BigInt("1");
        this->number = newNumber.number;
    }

    void operator++()
    {
        BigInt newNumber(this->number);
        newNumber = newNumber + BigInt("1");
        this->number = newNumber.number;
    }
};

int min(int a, int b)
{
    return (a < b) ? a : b;
}

BigInt BinomialCoeff(int setPower, int subsetPower)
{
    std::vector<std::vector<BigInt>> Combination(setPower + 1, std::vector<BigInt>(subsetPower + 1));
    int i, j;

    for (i = 0; i <= setPower; ++i)
    {
        for (j = 0; j <= min(i, subsetPower); ++j)
        {
            if (j == 0 || j == i)
            {
                Combination[i][j] = BigInt("1");
            }
            else
            {
                Combination[i][j] = Combination[i - 1][j - 1] + Combination[i - 1][j];
            }
        }
    }
    return Combination[setPower][subsetPower];
}

bool VertexInRnge(int vertex, int verticesCount)
{
    return vertex >= 0 && vertex < verticesCount;
}

Coordinate FindCoordinates(int vertex)
{
    int y = vertex % 100;
    int x = vertex / 100;

    return Coordinate(x, y);
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::ifstream in;

    std::string pathToFile = argv[1];

    in.open(pathToFile);

    if (!in.is_open())
    {
        std::cout << "Coudn't open the file to read the Source and Destination vertices" << std::endl;
        return 1;
    }
    else
    {
        int fromVertex, toVertex;

        in >> fromVertex >> toVertex;

        if (!VertexInRnge(fromVertex, 10000) || !VertexInRnge(toVertex, 10000))
        {
            std::cout << "Invalid values for fromVertex or toVertex " << fromVertex << " " << toVertex << std::endl;
            return 1;
        }

        in.close();

        Coordinate fromVertexCoord = FindCoordinates(fromVertex);
        Coordinate toVertexCoord = FindCoordinates(toVertex);

        std::ofstream out;

        //out.open("../AnswerFiles/AnswerNOSPM.txt");

        pathToFile = argv[2];

        out.open(pathToFile);

        if (!out.is_open())
        {
            std::cout << "Coudn't open the file to write the answer" << std::endl;
            return 1;
        }
        else
        {
            int setPower = std::abs(toVertexCoord.y - fromVertexCoord.y) + std::abs(toVertexCoord.x - fromVertexCoord.x);
            int subsetPower = std::abs(toVertexCoord.x - fromVertexCoord.x);
            out << BinomialCoeff(setPower, subsetPower);
        }
        out.close();
    }
}