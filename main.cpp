#include <iostream>
#include <vector>
#include <string>
#include <fstream>


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
void casting_rows_columns(vector <vector <int>>& applicant_matrix, int num_vacancies, int num_applicants)
{
    for (int i = 0; i < num_vacancies; i++)
    {
        int min_elem = 9999999;
        for (int j = 0;j < num_applicants; j++)
        {
            if (applicant_matrix[i][j] < min_elem)
            {
                min_elem = applicant_matrix[i][j];
            }
        }
        for (int j = 0;j < num_applicants; j++)
            applicant_matrix[i][j] = applicant_matrix[i][j] - min_elem;
    }
    for (int j = 0;j < num_applicants; j++)
    {
        int min_elem = 9999999;
        for (int i = 0; i < num_vacancies; i++)
        {
            if (applicant_matrix[i][j] < min_elem)
            {
                min_elem = applicant_matrix[i][j];
            }
        }
        for (int i = 0; i < num_vacancies; i++)
            applicant_matrix[i][j] = applicant_matrix[i][j] - min_elem;
    }
    print_matrix(applicant_matrix, num_vacancies, num_applicants);
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

void main()
{
    int num_vacancies = 8, num_applicants = 10;
    vector <vector <int>> applicant_matrix(num_vacancies, vector<int>(num_applicants,0) );
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
        switch (survey[0])
        {
        case '1':
            cout << "Enter the performance matrix of applicants for vacant positions:" << endl;
            cout << "The dimension is 8 by 10! " << endl;
            for (int i = 0; i < num_vacancies; i++)
                for (int j = 0; j < num_applicants; j++)
                    cin >> applicant_matrix[i][j];
            cout << endl << "Subtracting the maximum element from each row and column " << endl;
            maximum_element(applicant_matrix, num_vacancies, num_applicants);           
            cout << endl << "Casting row and column " << endl;
            casting_rows_columns(applicant_matrix, num_vacancies, num_applicants);
            cout << endl << "Most profitable candidates " << endl;
            most_profitable_candidates(applicant_matrix, num_vacancies, num_applicants);

            is_continue = false;
            break;
        case '2':
            fin.open("input");
           
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