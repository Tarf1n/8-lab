#include <iostream>
#include <fstream>
#include <clocale>
using namespace std;

struct Team {
    char name[50];
    char city[50];
    int players;
    int points;
};

int main() {
    setlocale(LC_ALL, "Ru");
    system("chcp 1251");
    system("cls");
    int count;
    const char* filename = "teams.dat";
    Team team;
    int minPoints;

    cout << "�������� �����..." << endl;
    ofstream fout(filename, ios::binary);

    cout << "������� ���������� ������:" << endl;
    cin >> count;
    cin.ignore();
    for (int i = 0; i < count; i++) {
        cout << "\n������� #" << i + 1 << endl;
        cout << "��������: "; cin.getline(team.name, 50);
        cout << "�����: "; cin.getline(team.city, 50);
        cout << "�������: "; cin >> team.players;
        cout << "�����: "; cin >> team.points;
        cin.ignore();
        fout.write(reinterpret_cast<char*>(&team), sizeof(Team));
    }
    fout.close();

    cout << "\n\n���������� ����� ����� ��������:" << endl;
    ifstream fin(filename, ios::binary);
    while (fin.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
        cout << "\n��������: " << team.name;
        cout << "\n�����: " << team.city;
        cout << "\n�������: " << team.players;
        cout << "\n�����: " << team.points << endl;
    }
    fin.close();

    cout << "\n\n������� ����������� ���������� �����: ";
    cin >> minPoints;
    cin.ignore();
    
    {
        ifstream inFile(filename, ios::binary);
        ofstream outFile("temp.dat", ios::binary);

        while (inFile.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
            if (team.points >= minPoints) {
                outFile.write(reinterpret_cast<char*>(&team), sizeof(Team));
            }
        }
        inFile.close();
        outFile.close();
    }
    remove(filename);
    rename("temp.dat", filename);

    cout << "\n\n���������� ����� ����� ��������:" << endl;
    fin.open(filename, ios::binary);
    while (fin.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
        cout << "\n��������: " << team.name;
        cout << "\n�����: " << team.city;
        cout << "\n�������: " << team.players;
        cout << "\n�����: " << team.points << endl;
    }
    fin.close();

    cout << "\n\n���������� 2 ������ � ������..." << endl;
    {
        Team newTeams[2];
        ofstream tempFile("temp.dat", ios::binary);

        for (int i = 0; i < 2; i++) {
            cout << "\n������� #" << i + 1 << endl;
            cout << "��������: "; cin.getline(newTeams[i].name, 50);
            cout << "�����: "; cin.getline(newTeams[i].city, 50);
            cout << "�������: "; cin >> newTeams[i].players;
            cout << "�����: "; cin >> newTeams[i].points;
            cin.ignore();
            tempFile.write(reinterpret_cast<char*>(&newTeams[i]), sizeof(Team));
        }

        ifstream inFile(filename, ios::binary);
        while (inFile.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
            tempFile.write(reinterpret_cast<char*>(&team), sizeof(Team));
        }
        inFile.close();
        tempFile.close();

        remove(filename);
        rename("temp.dat", filename);
    }

    cout << "\n\n�������� ���������� �����:" << endl;
    fin.open(filename, ios::binary);
    while (fin.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
        cout << "\n��������: " << team.name;
        cout << "\n�����: " << team.city;
        cout << "\n�������: " << team.players;
        cout << "\n�����: " << team.points << endl;
    }
    fin.close();

    return 0;
}