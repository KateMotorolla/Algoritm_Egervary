#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

void print_matrix(vector<vector<int>> &applicant_matrix, int num_vacancies, int num_applicants)
{
    for (int i = 0; i < num_vacancies; i++)
    {
        for (int j = 0; j < num_applicants; j++)
            cout << applicant_matrix[i][j] << "  ";
        cout << endl;
    }
}
void maximum_element(vector <vector <int>> &applicant_matrix, int num_vacancies ,int num_applicants)
{
    int max_elem = 0;
    for (int i = 0; i < num_vacancies; i++)
    {
        for (int j = 0;j < num_applicants; j++)
        {
            if (applicant_matrix[i][j] > max_elem)
            {
                max_elem = applicant_matrix[i][j];
            }   
        }
    } 
    for (int i = 0; i < num_vacancies; i++)
    {
        for (int j = 0;j < num_applicants; j++)
            applicant_matrix[i][j] = max_elem - applicant_matrix[i][j];
    }
    print_matrix(applicant_matrix, num_vacancies, num_applicants);
}
void casting_rows_columns(vector <vector <int>>& applicant_matrix, vector<vector<int>>& intermediate_matrix, int num_vacancies, int num_applicants)
{
    intermediate_matrix = applicant_matrix;
    for (int i = 0; i < num_vacancies; i++)
    {
        int min_elem = 9999999;
        for (int j = 0;j < num_applicants; j++)
        {
            if (intermediate_matrix[i][j] < min_elem)
            {
                min_elem = intermediate_matrix[i][j];
            }
        }
        for (int j = 0;j < num_applicants; j++)
            intermediate_matrix[i][j] = intermediate_matrix[i][j] - min_elem;
    }
    for (int j = 0;j < num_applicants; j++)
    {
        int min_elem = 9999999;
        for (int i = 0; i < num_vacancies; i++)
        {
            if (intermediate_matrix[i][j] < min_elem)
            {
                min_elem = intermediate_matrix[i][j];
            }
        }
        for (int i = 0; i < num_vacancies; i++)
            intermediate_matrix[i][j] = intermediate_matrix[i][j] - min_elem;
    }
    print_matrix(intermediate_matrix, num_vacancies, num_applicants);
    applicant_matrix = intermediate_matrix;
}
void most_profitable_candidates(vector <vector <int>>& applicant_matrix, int num_vacancies, int num_applicants)
{
    for (int i = 0; i < num_vacancies; i++)
    {
        for (int j = 0;j < num_applicants; j++)
        {
            if (applicant_matrix[i][j] == 0)
                applicant_matrix[i][j] = 1;
            else
                applicant_matrix[i][j] = 0;
        }
    }
    print_matrix(applicant_matrix, num_vacancies, num_applicants);
}
void greedy_algoritm(vector<vector<int>>& applicant_matrix, vector<vector<int>>& result_matrix, int num_vacancies, int num_applicants)
{
    result_matrix = vector<vector<int>>(num_vacancies, vector<int>(num_applicants, 0));
    for (int i = 0; i < num_vacancies; ++i)
    {
        for (int j = 0; j < num_applicants; ++j)
        {
            if (applicant_matrix[i][j] > 0)
            {
                for (int k = 0; k < num_vacancies; ++k)
                {
                    if (k != i)
                        applicant_matrix[k][j] = applicant_matrix[k][j] > 0 ? -1 : applicant_matrix[k][j];
                }
                for (int k = 0; k < num_applicants; ++k)
                {
                    if (k != j)
                        applicant_matrix[i][k] = applicant_matrix[i][k] > 0 ? -1 : applicant_matrix[i][k];
                }
                result_matrix[i][j] = 1;
                break;
            }
        }
    }
    print_matrix(applicant_matrix, num_vacancies, num_applicants);
    cout << endl;
    print_matrix(result_matrix, num_vacancies, num_applicants);
}
bool check_result(const vector<vector<int>>& result_matrix, int num_vacancies, int num_applicants)
{
    for (int i = 0; i < num_vacancies; ++i)
    {
        int counter = 0;
        for (int j = 0; j < num_applicants; ++j)
        {
            if (result_matrix[i][j] == 1)
                ++counter;
        }
        if (counter != 1)
            return false;
    }
    for (int j = 0; j < num_applicants; ++j)
    {
        int counter = 0;
        for (int i = 0; i < num_vacancies; ++i)
        {
            if (result_matrix[i][j] == 1)
                ++counter;
        }
        if (counter > 1)
            return false;
    }
    return true;
}
void chain_dfs(const vector<vector<int>>& applicant_matrix, int num_vacancies, int num_applicants, stack<int, vector<int>>& chain, int val, int index)
{
    if (val > 0)
    {
        for (int i = 0; i < num_applicants; ++i)
        {
            if (applicant_matrix[index][i] == -1)
            {
                chain.push(i);
                chain_dfs(applicant_matrix, num_vacancies, num_applicants, chain, -1, i);
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < num_vacancies; ++i)
        {
            if (applicant_matrix[i][index] == 1)
            {
                chain.push(i);
                chain_dfs(applicant_matrix, num_vacancies, num_applicants, chain, 1, i);
                break;
            }
        }
    }
}
void egervary_algoritm(vector<vector<int>>& applicant_matrix, vector<vector<int>>& intermediate_matrix, vector<vector<int>>& result_matrix, int num_vacancies, int num_applicants)
{
    int index = 0;
    for (int i = 0; i < num_vacancies; ++i)
    {
        bool is_null_row = true;
        for (int j = 0; j < num_applicants; ++j)
        {
            if (result_matrix[i][j] != 0)
                is_null_row = false;
        }
        if (is_null_row)
        {
            index = i;
            break;
        }
    }
    stack<int, vector<int>> chain;
    chain.push(index);
    chain_dfs(applicant_matrix, num_vacancies, num_applicants, chain, 1, index);
    vector<int> chain_arr = chain._Get_container();
    cout << "Chain: ";
    for (int i = 0; i < chain_arr.size(); ++i)
        cout << chain_arr[i] << "  ";
    cout << endl;
    if (chain.size() % 2 == 0)
    {
        cout << "Chain is unsaturated" << endl;
        for (int i = 0; i < chain_arr.size() - 1; ++i)
        {
            if (i % 2 == 0)
                result_matrix[chain_arr[i]][chain_arr[i + 1]] = 1;
            else
                result_matrix[chain_arr[i + 1]][chain_arr[i]] = 0;
        }
        cout << "Egervary iteration result: " << endl;
        print_matrix(result_matrix, num_vacancies, num_applicants);
    }
    else
    {
        cout << "Chain is saturated" << endl;
        int vacansia = chain.top();
        chain.pop();
        int applicant = chain.top();
        int row_min = intermediate_matrix[vacansia][0];
        for (int j = 0; j < num_applicants; ++j)
        {
            if (intermediate_matrix[vacansia][j] < row_min && j != applicant)
                row_min = intermediate_matrix[vacansia][j];
        }
        for (int j = 0; j < num_applicants; ++j)
        {
            if (j != applicant)
                intermediate_matrix[vacansia][j] -= row_min;
        }
        for (int i = 0; i < num_vacancies; ++i)
        {
            if (i != applicant)
                intermediate_matrix[i][applicant] += row_min;
        }
        cout << "Intermediate matrix: " << endl;
        print_matrix(intermediate_matrix, num_vacancies, num_applicants);
        cout << endl;
        for (int j = 0; j < num_applicants; ++j)
            applicant_matrix[vacansia][j] = intermediate_matrix[vacansia][j] == 0 ? 1 : 0;
        if (chain_arr.size() > 1)
            applicant_matrix[chain_arr[0]][chain_arr[1]] = 1;
        greedy_algoritm(applicant_matrix, result_matrix, num_vacancies, num_applicants);
        cout << "Egervary iteration result: " << endl;
        print_matrix(result_matrix, num_vacancies, num_applicants);
    }
}

void main()
{
    int num_vacancies = 0, num_applicants = 0;
    vector <vector <int>> applicant_matrix, intermediate_matrix, result_matrix;
    int max_elem = 0;
    string survey;
    bool is_continue = true;
    ifstream fin;
    while (is_continue)
    {
        cout << "Choose a solution option:" << endl;
        cout << "1 - Enter the matrix yourself " << endl;
        cout << "2 - Read the matrix from the file " << endl;
        cout << "1/2:  ";
        cin >> survey;
        if (survey.length() > 1)
        {
            cout << "Error" << endl;
            continue;
        }

#define EGERVARY_ALGORITM_CALL                                                                                  \
cout << endl << "Subtracting the maximum element from each row and column " << endl;                            \
maximum_element(applicant_matrix, num_vacancies, num_applicants);                                               \
cout << endl << "Casting row and column " << endl;                                                              \
casting_rows_columns(applicant_matrix, intermediate_matrix, num_vacancies, num_applicants);                     \
cout << endl << "Most profitable candidates " << endl;                                                          \
most_profitable_candidates(applicant_matrix, num_vacancies, num_applicants);                                    \
cout << endl << "Greedy algoritm " << endl;                                                                     \
greedy_algoritm(applicant_matrix, result_matrix, num_vacancies, num_applicants);                                \
while (!check_result(result_matrix, num_vacancies, num_applicants))                                             \
    egervary_algoritm(applicant_matrix, intermediate_matrix, result_matrix, num_vacancies, num_applicants);     \
cout << endl << "This is solution" << endl;                                                                     \

        switch (survey[0])
        {
        case '1':
            cout << "Enter the matrix dimension with condition by num vacancies <= num applicants (for example: 8 10 ): ";
            cin >> num_vacancies >> num_applicants;
            if (num_vacancies > num_applicants)
            {
                cout << "Error" << endl;
                break;
            }
            applicant_matrix = vector<vector<int>>(num_vacancies, vector<int>(num_applicants, 0));
            cout << "Enter the performance matrix of applicants for vacant positions:" << endl;
            for (int i = 0; i < num_vacancies; i++)
                for (int j = 0; j < num_applicants; j++)
                    cin >> applicant_matrix[i][j];
            EGERVARY_ALGORITM_CALL
            is_continue = false;
            break;
        case '2':
            fin.open("input.txt");
            fin >> num_vacancies >> num_applicants;
            applicant_matrix = vector<vector<int>>(num_vacancies, vector<int>(num_applicants, 0));
            for (int i = 0; i < num_vacancies; i++)
                for (int j = 0; j < num_applicants; j++)
                    fin >> applicant_matrix[i][j];
            EGERVARY_ALGORITM_CALL
            fin.close();
            is_continue = false;
            break;
        default:
            cout << "Error" << endl;
            break;
        }
    }
    system("pause");
}