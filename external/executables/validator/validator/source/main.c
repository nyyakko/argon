#include <stdint.h>

#define TO_INT(x) ((x) - '0')
#define TO_CHR(x) ((x) + '0')
#define FROM_STR(x) x, sizeof(x)

char calculate_verifier(char const* begin, char const* end);
bool validate_cpf(char const* cpf);

int main(int argc, char const** argv)
{
    if (argc == 1)
    {
        return 69;
    }

    return validate_cpf(argv[1]);
}

bool validate_cpf(char const* cpf)
{
    return calculate_verifier(&cpf[0], &cpf[8]) && cpf[10] == calculate_verifier(&cpf[0], &cpf[9]);
}

char calculate_verifier(char const* begin, char const* end)
{
    int verifier = 0;
    int distance = (int)(2 + end - begin);

    for (char const* position = begin; position <= end; ++position)
    {
        if (!((*position) >= '0' && (*position) <= '9'))
        {
            continue;
        }

        verifier += (distance * TO_INT(*position));
        distance -= 1;
    }

    if (verifier % 11 < 2)
    {
        return TO_CHR(0);
    }

    return (char)TO_CHR(11 - verifier % 11);
}

