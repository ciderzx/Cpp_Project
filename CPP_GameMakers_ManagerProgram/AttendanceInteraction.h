#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*�б�� ������ Ƚ��*/
#define MAX_ATTENDANCE_NUMBER 15

/*ä���� �ִ� ��*/
typedef int FilledPlace;

/*��¥ ����*/
typedef struct Dates {
	int year;
	int month;
	int day;
} Dates;

/*GM �⼮ ���� ����ü*/
typedef struct GMattendance {
	string PlaceName;
	string atten_Symbol[21]; // �⼮ ��ȣ��
}GMattendance;

/*��� �̸���*/
string PlaceName[MAX_ATTENDANCE_NUMBER];

/*�⼮ ������*/
GMattendance AttendanceInformation[MAX_ATTENDANCE_NUMBER];

/*���� ��¥*/
Dates GetPeopleDates[MAX_ATTENDANCE_NUMBER];

/*��Ұ� �󸶳� �ִ°�*/
FilledPlace currentFilled = 0;

