#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*분기당 나오는 횟수*/
#define MAX_ATTENDANCE_NUMBER 15

/*채워져 있는 수*/
typedef int FilledPlace;

/*날짜 정보*/
typedef struct Dates {
	int year;
	int month;
	int day;
} Dates;

/*GM 출석 정보 구조체*/
typedef struct GMattendance {
	string PlaceName;
	string atten_Symbol[21]; // 출석 기호들
}GMattendance;

/*장소 이름들*/
string PlaceName[MAX_ATTENDANCE_NUMBER];

/*출석 정보들*/
GMattendance AttendanceInformation[MAX_ATTENDANCE_NUMBER];

/*모인 날짜*/
Dates GetPeopleDates[MAX_ATTENDANCE_NUMBER];

/*장소가 얼마나 있는가*/
FilledPlace currentFilled = 0;

